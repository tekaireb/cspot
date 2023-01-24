#include "df.h"
#include "dfinterface.h"
#include "woofc.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

operand perform_operation(const std::vector<operand>& ops, int opcode) {
    std::cout << "Perform operation: ops = ";
    for (auto& op : ops) std::cout << op.value << " ";
    std::cout << "\nopcode: " << opcode << std::endl;

    operand result(0);
    switch (opcode) {
    case ADD:
        result.value = 0;
        for (auto& op : ops) {
            result.value += op.value;
        }
        break;
    case SUB:
        result.value = 0;
        for (auto& op : ops) {
            result.value -= op.value;
        }
        break;
    case MUL:
        result.value = 1;
        for (auto& op : ops) {
            result.value *= op.value;
        }
        break;
    case DIV:
        result = ops[0].value;
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
    // Name format: [program_name].subscription_events.[id]
    size_t last_dot = woof_name.find_last_of('.');
    std::string id_str = woof_name.substr(last_dot + 1);
    std::cout << "woof_name: " << woof_name << std::endl;
    std::cout << "id_str: " << id_str << std::endl;
    unsigned long id = std::stoul(id_str);

    // Extract program name
    size_t first_dot = woof_name.find('.');
    std::string program = woof_name.substr(0, first_dot);

    // Get subscription_event
    subscription_event* subevent = static_cast<subscription_event*>(ptr);

    // Get current execution iteration
    unsigned long consumer_seq;
    std::string consumer_ptr_woof = program + ".subscription_pointer." + id_str;
    woof_get(consumer_ptr_woof, &consumer_seq, 0);

    // Only proceed if this event is relevant to the current execution iteration
    if (subevent->seq > consumer_seq) {
        std::cout << "Subscription event handler: event is not for current seq, exiting" << std::endl;
        exit(0);
    }

    // Look up subscriptions to determine required number of operands
    // TODO: Cache this value

    std::string submap = program + ".subscription_map";
    std::string subdata = program + ".subscription_data";
    unsigned long start_idx, end_idx;
    unsigned long last_seq = woof_last_seq(submap);

    woof_get(submap, &start_idx, id);
    if (id == last_seq) {
        end_idx = woof_last_seq(subdata) + 1;
    } else {
        woof_get(submap, &end_idx, id + 1);
    }

    std::cout << "Subscription event handler: start_idx: " << start_idx \
    << ", end_idx: " << end_idx << std::endl;

    int num_ops = static_cast<int>(end_idx - start_idx);

    // Scan through subscription outputs and collect operands
    // TODO: Cache last scanned seq and array of found operands
    std::cout << "Subscription event handler: searching for operands..." << std::endl;
    std::vector<operand> op_values(num_ops);
    subscription sub;
    operand op(0);
    std::string output_base = program + ".output.";
    std::string output_woof;
    for (unsigned long i = start_idx; i < end_idx; i++) {
        // Get subscription id
        woof_get(subdata, &sub, i);

        // Get relevant operand from subscription output (if it exists)
        output_woof = output_base + std::to_string(sub.id);
        std::cout << "Subscription event handler: consumer_seq: " \
            << consumer_seq << ", woof_last_seq: " << woof_last_seq(output_woof) << std::endl;
        if (woof_last_seq(output_woof) >= consumer_seq) {
            std::cout << "Subscription event handler: getting op" << std::endl;
            woof_get(output_woof, &op, consumer_seq);
            std::cout << "Subscription event handler: consumer_seq: " \
            << consumer_seq << ", woof: " << output_woof << ", op: " \
            << op.value << std::endl;
            op_values[i - start_idx] = op;
        } else {
            // At least one input is not ready --> exit handler
            std::cout << "Subscription event handler: not all operands are present, exiting" << std::endl;
            exit(0);
        }
    }

    /* Fire node */

    std::cout << "Subscription event handler: firing node" << std::endl;

    // Increment consumer pointer
    consumer_seq++; // TODO: May cause race conditions. Lock-free compare and set?
    std::cout << "Subscription event handler: incr" << std::endl;
    woof_put(consumer_ptr_woof, "", &consumer_seq);
    std::cout << "Subscription event handler: put" << std::endl;
    consumer_seq--;
    std::cout << "Subscription event handler: decr" << std::endl;

    // Get opcode
    node n;
    woof_get(program + ".nodes", &n, id);
    std::cout << "Subscription event handler: get node" << std::endl;

    operand result = perform_operation(op_values, n.opcode);
    std::cout << "Subscription event handler: result = " << result.value << std::endl;
    woof_put(program + ".output." + id_str, "output_handler", &result);

    std::cout << "SUBSCRIPTION EVENT HANDLER DONE" << std::endl;

    return 0;
}