#include "df.h"
#include "df_interface.h"
#include "operation_system/df_operation.h"

#include <iostream>
#include <string>
#include <vector>


operand perform_operation(const std::vector<operand>& operands, int ns, node& node, unsigned long consumer_seq) {
    const DF_OPERATION operation = node.operation;
    DF_VALUE operands_array[operands.size()];
    for (size_t i = 0; i < operands.size(); ++i) {
        operands_array[i] = operands[i].value;
    }
    DF_OPERATION_METADATA metadata = {
        .host_id = node.host_id, .laminar_namespace = ns, .node_id = node.id, .consumer_sequence = consumer_seq};
    DF_VALUE result_value;
    int operation_result = df_operation_with_type(
        operation, operands_array, operands.size(), &metadata, operands[0].value.type, &result_value);
    if (!operation_result) {
        printf("UNKNOWN OPERATION ERROR OCCURRED!\n");
    }
    operand result(result_value, metadata.consumer_sequence);
    return result;
}

extern "C" int subscription_event_handler(WOOF* wf, unsigned long seqno, void* ptr) {
    // auto start = std::chrono::high_resolution_clock::now();
    // std::cout << "SUBSCRIPTION EVENT HANDLER STARTED" << std::endl;

    int err;

    // Get name of this woof
    std::string woof_name(WoofGetFileName(wf));
    // Extract id
    const unsigned long node_id = get_node_id_from_woof_path(woof_name);
    // Extract namespace
    const int ns = get_ns_from_woof_path(woof_name);
    // Get subscription_event
    auto* subevent = static_cast<subscription_event*>(ptr);

    // Get current execution iteration
    execution_iteration_lock exec_iter_lk;
    std::string consumer_ptr_woof = generate_woof_path(SUBSCRIPTION_POINTER_WOOF_TYPE, ns, node_id);
    err = woof_get(consumer_ptr_woof, &exec_iter_lk, 0);
    if (err < 0) {
        std::cout << "Error reading woof (s1): " << consumer_ptr_woof << std::endl;
        return err;
    }

    const unsigned long consumer_seq = exec_iter_lk.iter;

    // Only proceed if this event is relevant to the current execution iteration
    if (subevent->seq > consumer_seq) {
        DEBUG_PRINT("event seq: " << subevent->seq << ", consumer seq: " << consumer_seq)
        DEBUG_PRINT("Event is not for current seq, exiting")
        return 0;
    }
    // Only proceed if this event is not already being handled
    if (exec_iter_lk.lock) {
        DEBUG_PRINT("Another handler already locked, exiting")
        // return 0;
    }

    // Look up subscriptions to determine required number of operands
    std::string submap = generate_woof_path(SUBSCRIPTION_MAP_WOOF_TYPE, ns);
    std::string subdata = generate_woof_path(SUBSCRIPTION_DATA_WOOF_TYPE, ns);
    unsigned long start_idx, end_idx;
    unsigned long last_seq = woof_last_seq(submap);

    err = woof_get(submap, &start_idx, node_id);
    if (err < 0) {
        std::cout << "Error reading submap woof (s1): " << submap << std::endl;
        return err;
    }

    if (node_id == last_seq) {
        end_idx = woof_last_seq(subdata) + 1;
    } else {
        err = woof_get(submap, &end_idx, node_id + 1);
        if (err < 0) {
            std::cout << "Error reading submap woof (s2): " << submap << std::endl;
            return err;
        }
    }

    int num_ops = static_cast<int>(end_idx - start_idx);

    // Scan through subscription outputs and collect operands
    std::vector<operand> op_values(num_ops);
    std::string output_woof;
    for (unsigned long i = start_idx; i < end_idx; i++) {
        // Get last used output and seqno for this port
        cached_output last_output;
        std::string last_used_sub_pos_woof =
            generate_woof_path(SUBSCRIPTION_POS_WOOF_TYPE, ns, node_id, -1, i - start_idx);
        if (woof_last_seq(last_used_sub_pos_woof) == 0) {
            // On first read, check if output woof is empty
            if (woof_last_seq(output_woof) == 0) {
                DEBUG_PRINT("No outputs yet, exiting")
                return 0;
            }
        } else {
            // std::cout << "Loading last_used_subscription_positions" << std::endl;
            woof_get(last_used_sub_pos_woof, &last_output, 0);
        }

        // std::cout << "[" << woof_name << "] " << "[" << consumer_seq << "] last_output_seq: " << last_output.op.seq
        // << ", consumer_seq: " << consumer_seq << std::endl;
        if (last_output.op.seq == consumer_seq) {
            // Operand for this seq has already been found and cached
            // Retrieve from cache and proceed
            // std::cout << "already retrieved input #" << i - start_idx << ", proceeding" << std::endl;
            op_values[i - start_idx] = last_output.op;
            continue;
        } else if (last_output.op.seq > consumer_seq) {
            // Another handler has already cached an operand from a later
            // execution iteration, thus this execution iteration has already
            // been completed, exit
            DEBUG_PRINT("Cached operand exceeds current excecution iteration, exiting")
            return 0;
        }

        // std::cout << "subscription port: " << i - start_idx << std::endl;
        // Get subscription id
        subscription sub;
        err = woof_get(subdata, &sub, i);
        if (err < 0) {
            std::cout << "Error reading subdata woof: " << subdata << std::endl;
            return err;
        }

        // Get relevant operand from subscription output (if it exists)
        output_woof = generate_woof_path(OUTPUT_WOOF_TYPE, sub.ns, sub.id);

        // Scan from last used output until finding current seq
        unsigned long idx = last_output.seq;
        unsigned long last_idx = woof_last_seq(output_woof);

        if (idx >= last_idx) {
            DEBUG_PRINT("No new outputs to check")
            return 0;
        }

        operand op;
        // Increment sequence number (idx) until finding current execution iteration
        do {
            idx++;
            err = woof_get(output_woof, &op, idx);
            if (err < 0) {
                std::cout << "Error reading output woof: " << output_woof << std::endl;
                return err;
            }
        } while (op.seq < consumer_seq && idx < last_idx);

#ifdef DEBUG
        if (op.seq != consumer_seq) {
            DEBUG_PRINT("ERROR: UNEXPECTED BEHAVIOR (SKIPPED EXECUTION ITER)")
            std::vector<operand> v;
            for (int j = 1; j <= idx; j++) {
                operand tmp;
                woof_get(output_woof, &tmp, j);
                v.push_back(tmp);
            }

            std::cout << "op.seq: " << op.seq << ", consumer_seq: " << consumer_seq << std::endl;

            for (auto& o : v) {
                char* value_string = value_to_string(&o.value);
                std::cout << output_woof << " @ " << o.seq << ": " << value_string << std::endl;
                free(value_string);
            }
        }
#endif

        // Write latest idx back to `last used subscription position` woof
        // std::cout << "Writing back: " << "op = " << op.value << ", seq=" << idx << std::endl;
        last_output = cached_output(op, idx);
        woof_put(last_used_sub_pos_woof, "", &last_output);

        if (op.seq == consumer_seq) {
            // Relevant operand found, save and continue
            // std::cout << "[" << woof_name<< "] getting op" << std::endl;
            // std::cout << "[" << woof_name<< "] consumer_seq: "
            // << consumer_seq << ", woof: " << output_woof << ", op: "
            // << op.value << std::endl;
            op_values[i - start_idx] = op;
        } else {
            // At least one input is not ready --> exit handler
            // std::cout << "idx: " << idx << ", consumer_seq: " << consumer_seq
            // << ", op.seq: " << op.seq << std::endl;
            DEBUG_PRINT("Not all operands are present, exiting")
            return 0;
        }
    }

    /* Fire node */

    DEBUG_PRINT("Firing node")

    // TODO: Factor out into function [
    // Get current execution iteration
    err = woof_get(consumer_ptr_woof, &exec_iter_lk, 0);
    if (err < 0) {
        std::cout << "Error reading woof (s2): " << consumer_ptr_woof << std::endl;
        return err;
    }

    // Only proceed if this event is relevant to the current execution iteration
    if (subevent->seq > exec_iter_lk.iter) {
        DEBUG_PRINT("event seq: " << subevent->seq << ", consumer seq: " << exec_iter_lk.iter)
        DEBUG_PRINT("Event is not for current seq, exiting")
        return 0;
    }

    // Only proceed if this event is not already being handled
    if (exec_iter_lk.lock) {
        DEBUG_PRINT("Another handler already locked, exiting")
    }
    // TODO: Factor out into function ]

    // TODO: Factor out into function [
    // Test-and-set to take lock for this execution iteration
    exec_iter_lk.lock = true;
    unsigned long lk_seq = woof_put(consumer_ptr_woof, "", &exec_iter_lk);
    execution_iteration_lock prev_exec_iter_lk;
    woof_get(consumer_ptr_woof, &prev_exec_iter_lk, lk_seq - 1);
    if (prev_exec_iter_lk.iter > exec_iter_lk.iter) {
        DEBUG_PRINT("ERROR: UNEXPECTED BEHAVIOR (LOCKS OUT OF ORDER)")
        DEBUG_PRINT("\tprev: " << prev_exec_iter_lk.iter << ", " << prev_exec_iter_lk.lock)
        DEBUG_PRINT("\tthis: " << exec_iter_lk.iter << ", " << exec_iter_lk.lock)

        // Put previous entry back and trigger subscription handler manually (if not locked)
        woof_put(consumer_ptr_woof, "", &prev_exec_iter_lk);
        if (!prev_exec_iter_lk.lock) {
            subevent->seq++;
            subscription_event_handler(wf, seqno + 1, subevent);
        }

        return 0;
    }
    if (prev_exec_iter_lk.lock) {
        DEBUG_PRINT("Failed to acquire lock, exiting");
    } else {
        DEBUG_PRINT("Lock acquired");
    }
    // TODO: Factor out into function ]

    // Get opcode
    node n;
    std::string nodes_woof = generate_woof_path(NODES_WOOF_TYPE, ns);
    err = woof_get(nodes_woof, &n, node_id);
    if (err < 0) {
        std::cout << "Error reading nodes woof: " << nodes_woof << std::endl;
        return err;
    }
    // std::cout << "[" << woof_name<< "] get node" << std::endl;

    operand result = perform_operation(op_values, ns, n, consumer_seq);
    // std::cout << "[" << woof_name<< "] result = " << result.value << std::endl;

    // Do not write result if it already exists
    output_woof = generate_woof_path(OUTPUT_WOOF_TYPE, ns, node_id);

    operand last_result;
    woof_get(output_woof, &last_result, 0);
    // TODO handler is dependent on operation
    if (!(n.operation.category == DF_INTERNAL && n.operation.operation == DF_INTERNAL_OFFSET)) {
        // Fix for offset: the following code prevents duplicates with most
        // nodes, but renders the offset node useless. For now, this feature
        // will be disabled for offset nodes. TODO: account for offset node's
        // `offset` to check for duplicates.
        if (last_result.seq >= consumer_seq) {
            DEBUG_PRINT("Operation already performed, exiting")
            // // Relinquish lock and increment execution iteration
            // exec_iter_lk.lock = false;
            // exec_iter_lk.iter++;
            // woof_put(consumer_ptr_woof, "", &exec_iter_lk);

            // // Call handler for next iter in case all operands were received before this function finished
            // if (woof_last_seq(woof_name) > seqno) {
            //     subevent->seq++;
            //     subscription_event_handler(wf, seqno + 1, subevent);
            // }

            return 0;
        }
    }

    // Write result (unless FILTER should omit result)
    // TODO! only works for doubles
    if (!(n.operation.category == DF_INTERNAL && n.operation.operation == DF_INTERNAL_FILTER) ||
        op_values[0].value.value.df_double) {
        woof_put(output_woof, OUTPUT_HANDLER, &result);
        DEBUG_PRINT("Wrote result #" << consumer_seq)
    }

    // // linreg_multinode
    // if (id == 8 && woof_name == "laminar-1.subscription_events.8") {

    // // linreg_uninode
    // if (id == 1 && woof_name == "laminar-1.subscription_events.1") {

    //     std::cout << "start: "
    //             << std::chrono::duration_cast<std::chrono::nanoseconds>(
    //                     start.time_since_epoch())
    //                     .count()
    //             << "ns" << std::endl;
    // }

    // std::cout << "SUBSCRIPTION EVENT HANDLER DONE" << std::endl;

    // Relinquish lock and increment execution iteration
    exec_iter_lk.lock = false;
    exec_iter_lk.iter++;
    woof_put(consumer_ptr_woof, "", &exec_iter_lk);

    // Call handler for next iter in case all operands were received before this function finished
    // if (woof_last_seq(woof_name) > seqno) {
    //     subevent->seq++;
    //     subscription_event_handler(wf, seqno + 1, subevent);
    // }
    subevent->seq++;
    subscription_event_handler(wf, seqno + 1, subevent);

    return 0;
}
