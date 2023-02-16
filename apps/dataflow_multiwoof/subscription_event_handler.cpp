#include "df.h"
#include "dfinterface.h"
#include "woofc.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

operand perform_operation(const std::vector<operand>& ops, int opcode, unsigned long consumer_seq) {
    std::cout << "Perform operation: ops = ";
    for (auto& op : ops) std::cout << op.value << " ";
    std::cout << "\nopcode: " << OPCODE_STR[opcode] << std::endl;

    operand result(0, consumer_seq);
    switch (opcode) {
    case ADD:
        result.value = 0;
        for (auto& op : ops) {
            result.value += op.value;
        }
        break;
    case SUB:
        result.value = ops[0].value;
        for (size_t i = 1; i < ops.size(); i++) {
            result.value -= ops[i].value;
        }
        break;
    case MUL:
        result.value = 1;
        for (auto& op : ops) {
            result.value *= op.value;
        }
        break;
    case DIV:
        result.value = ops[0].value;
        for (size_t i = 1; i < ops.size(); i++) {
            result.value /= ops[i].value;
        }
        break;
    case SQR:
        result.value = sqrt(ops[0].value);
        break;

    case LT:
        result.value = (double)(ops[0].value < ops[1].value);
        break;

    case GT:
        result.value = (double)(ops[0].value > ops[1].value);
        break;

    case EQ:
        result.value = (double)(ops[0].value == ops[1].value);
        break;

    case ABS:
        result.value = (ops[0].value < 0 ? -ops[0].value : ops[0].value);
        break;

    case NOT:
        result.value = (ops[0].value ? 0 : 1);
        break;
    
    case SEL:
        // Use selector value to index alternatives
        result.value = ops[(int)ops[0].value + 1].value;
        break;

    case FILTER:
        result.value = ops[1].value;
        // if (!static_cast<bool>(ops[0].value)) {
        //     exit(0);
        // }
        break;

    case OFFSET:
        result.value = ops[1].value;
        result.seq = consumer_seq + static_cast<unsigned long>(ops[0].value);
        break;
    
    default:
        result.value = 0;
        break;
    }
    return result;
}

extern "C" int subscription_event_handler(WOOF* wf, unsigned long seqno, void* ptr) {
    std::cout << "SUBSCRIPTION EVENT HANDLER STARTED" << std::endl;

    std::cout << "wf: " << WoofGetFileName(wf) << std::endl;
    std::cout << "seqno: " << seqno << std::endl;

    // Get name of this woof
    std::string woof_name(WoofGetFileName(wf));

    // Extract id
    unsigned long id = get_id_from_woof_path(woof_name);

    //Extract namespace
    int ns = get_ns_from_woof_path(woof_name);

    // Get subscription_event
    subscription_event* subevent = static_cast<subscription_event*>(ptr);

    // Get current execution iteration
    unsigned long consumer_seq;
    std::string consumer_ptr_woof = generate_woof_path(SUBSCRIPTION_POINTER_WOOF_TYPE, ns, id);
    woof_get(consumer_ptr_woof, &consumer_seq, 0);

    // Only proceed if this event is relevant to the current execution iteration
    if (subevent->seq > consumer_seq) {
        std::cout << "event seq: " << subevent->seq << ", consumer seq: " << consumer_seq << std::endl;
        std::cout << "[" << woof_name<< "] event is not for current seq, exiting" << std::endl;
        exit(0);
    }

    // Look up subscriptions to determine required number of operands
    // TODO: Cache this value
    std::string submap = generate_woof_path(SUBSCRIPTION_MAP_WOOF_TYPE, ns);
    std::string subdata = generate_woof_path(SUBSCRIPTION_DATA_WOOF_TYPE, ns);
    unsigned long start_idx, end_idx;
    unsigned long last_seq = woof_last_seq(submap);
    
    woof_get(submap, &start_idx, id);
    if (id == last_seq) {
        end_idx = woof_last_seq(subdata) + 1;
    } else {
        woof_get(submap, &end_idx, id + 1);
    }

    std::cout << "[" << woof_name<< "] start_idx: " << start_idx \
    << ", end_idx: " << end_idx << std::endl;

    int num_ops = static_cast<int>(end_idx - start_idx);

    // Scan through subscription outputs and collect operands
    // TODO: Cache last scanned seq and array of found operands
    std::cout << "[" << woof_name<< "] searching for operands..." << std::endl;
    std::vector<operand> op_values(num_ops);
    subscription sub;
    operand op(0);
    std::string output_woof;
    for (unsigned long i = start_idx; i < end_idx; i++) {
        std::cout << "subscription port: " << i - start_idx << std::endl;
        // Get subscription id
        woof_get(subdata, &sub, i);

        // Get relevant operand from subscription output (if it exists)
        output_woof = generate_woof_path(OUTPUT_WOOF_TYPE, sub.ns, sub.id);
        std::cout << "[" << woof_name<< "] consumer_seq: "
                  << consumer_seq
                  << ", woof_last_seq: " << woof_last_seq(output_woof)
                  << std::endl;

        // Scan backwards from most recent output until finding current seq
        unsigned long idx = woof_last_seq(output_woof) + 1;
        std::cout << "idx initial: " << idx << std::endl;
        do {
            idx--;
            woof_get(output_woof, &op, idx);
            std::cout << "idx, seq, val: " << idx << ", " << op.seq << ", " \
            << op.value << std::endl;
        } while (op.seq > consumer_seq && idx > 1);

        if (op.seq == consumer_seq) {
            std::cout << "[" << woof_name<< "] getting op" << std::endl;
            std::cout << "[" << woof_name<< "] consumer_seq: " \
            << consumer_seq << ", woof: " << output_woof << ", op: " \
            << op.value << std::endl;
            op_values[i - start_idx] = op;
        } else {
            // At least one input is not ready --> exit handler
            std::cout << "idx: " << idx << ", consumer_seq: " << consumer_seq \
            << ", op.seq: " << op.seq << std::endl;
            std::cout << "[" << woof_name<< "] not all operands are present, exiting" << std::endl;
            exit(0);
        }
    }

    /* Fire node */

    std::cout << "[" << woof_name<< "] firing node" << std::endl;

    // Increment consumer pointer

    unsigned long current_seq;
    woof_get(consumer_ptr_woof, &current_seq, 0);
    if (current_seq > consumer_seq) {
        // Exit if this iteration has already been completed
        return 0;
    }

    consumer_seq++; // TODO: May cause race conditions. Lock-free compare and set?
    std::cout << "[" << woof_name<< "] incr" << std::endl;
    woof_put(consumer_ptr_woof, "", &consumer_seq);
    std::cout << "[" << woof_name<< "] put" << std::endl;
    consumer_seq--;
    std::cout << "[" << woof_name<< "] decr" << std::endl;

    // Get opcode
    node n;
    std::string nodes_woof = generate_woof_path(NODES_WOOF_TYPE, ns); 
    woof_get(nodes_woof, &n, id);
    std::cout << "[" << woof_name<< "] get node" << std::endl;

    operand result = perform_operation(op_values, n.opcode, consumer_seq);
    std::cout << "[" << woof_name<< "] result = " << result.value << std::endl;
    // Do not write result if it already exists
    output_woof = generate_woof_path(OUTPUT_WOOF_TYPE, ns, id); 
    if (woof_last_seq(output_woof) > consumer_seq) {
        std::cout << "[" << woof_name<< "] Operation already performed, exiting" << std::endl;

        // Call handler for next iter in case all operands were received before this function finished
        subscription_event_handler(wf, seqno + 1, static_cast<void*>(subevent));
        return 0;
    }
    // Write result (unless FILTER should omit result)
    if (n.opcode != FILTER || op_values[0].value) {
        woof_put(output_woof, "output_handler", &result);
    }
    
    std::cout << "SUBSCRIPTION EVENT HANDLER DONE" << std::endl;

    // Call handler for next iter in case all operands were received before this function finished
    subscription_event_handler(wf, seqno + 1, static_cast<void*>(subevent));

    return 0;
}