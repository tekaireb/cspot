#include "df.h"
#include "woofc.h"
#include "dfinterface.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

double perform_operation(const std::vector<double>& ops, int opcode) {
    double result;
    switch (opcode) {
        case ADD:
            result = 0;
            for (auto& op : ops) {
                result += op;
            }
            break;
        case SUB:
            result = 0;
            for (auto& op : ops) {
                result -= op;
            }
            break;
        case MUL:
            result = 1;
            for (auto& op : ops) {
                result *= op;
            }
            break;
        case DIV:
            result = ops[0];
            for (size_t i = 1; i < ops.size(); i++) {
                result /= ops[i];
            }
            break;
        case SQR:
            result = sqrt(ops[0]);
            break;

        case LT:
            result = (double)(ops[0] < ops[1]);
            break;

        case GT:
            result = (double)(ops[0] > ops[1]);
            break;

        case EQ:
            result = (double)(ops[0] == ops[1]);
            break;
        default:
            result = 0;
            break;
    }
    return (result);
}

extern "C" int operation_handler(WOOF* wf, unsigned long seqno, void* ptr) {
    std::string woof_name(WoofGetFileName(wf));
    
    // Extract id
    // Name format: [program_name].[woof_type].[id]
    size_t last_dot = woof_name.find_last_of('.');
    std::string id_str = woof_name.substr(last_dot + 1);
    unsigned long id = std::stoul(id_str);

    // Extract program name
    size_t first_dot = woof_name.find('.');
    std::string program = woof_name.substr(0, first_dot);

    // Get opcode
    node n;
    woof_get(program + ".nodes", &n, id);

    // Get subscription pointer and increment value in woof
    unsigned long sub_ptr;
    std::string sub_ptr_woof = program + ".subscription_pointer." + id_str;
    woof_get(sub_ptr_woof, &sub_ptr, 1);
    sub_ptr++; // May cause race conditions. Lock-free compare and set?
    woof_put(sub_ptr_woof, "", &sub_ptr);
    sub_ptr--;

    /* Gather operands */

    std::vector<double> op_values;

    std::string submap = program + ".subscription_map";
    std::string subdata = program + ".subscription_data";
    unsigned long start_idx, end_idx;
    unsigned long last_seq = woof_last_seq(submap);

    // Get data range (TODO: factor out into function for woofmap)
    woof_get(submap, &start_idx, id);
    if (start_idx == last_seq) {
        end_idx = woof_last_seq(subdata);
    } else {
        woof_get(submap, &end_idx, id + 1);
        end_idx--;
    }
    
    // Iterate over subscriptions and get operand values
    std::string output_woof_base = program + ".output.";
    double op;
    for (unsigned long i = start_idx; i <= end_idx; i++) {
        // Get subscription id
        subscription sub;
        woof_get(subdata, &sub, i);
        
        // Get relevant operand from subscription
        woof_get(output_woof_base + std::to_string(sub.id), &op, sub_ptr);
        op_values.push_back(op);
    }

    // Perform operation and write result to output woof
    double result = perform_operation(op_values, n.opcode);
    operand result_op(result);
    woof_put(program + ".output." + id_str, "output_handler", &result_op);
}