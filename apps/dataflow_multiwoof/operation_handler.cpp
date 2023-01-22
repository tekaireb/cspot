#include "df.h"
#include "woofc.h"

#include <math.h>

int operation_handler(WOOF* wf, unsigned long seqno, void* ptr) {
    return 0;
}

// double operation_handler(node *n, int opcode) {
//     double result;
//     int i;
//     switch (opcode) {
//     case ADD:
//         result = 0;
//         for (i = 0; i < size; i++) {
//             result += op_values[i];
//         }
//         break;
//     case SUB:
//         result = 0;
//         for (i = 0; i < size; i++) {
//             result -= op_values[i];
//         }
//         break;
//     case MUL:
//         result = 1;
//         for (i = 0; i < size; i++) {
//             result *= op_values[i];
//         }
//         break;
//     case DIV:
//         result = op_values[0];
//         for (i = 1; i < size; i++) {
//             result /= op_values[i];
//         }
//         break;
//     case SQR:
//         result = sqrt(op_values[0]);
//         break;

//     case LT:
//         result = (double)(op_values[0] < op_values[1]);
//         break;

//     case GT:
//         result = (double)(op_values[0] > op_values[1]);
//         break;

//     case EQ:
//         result = (double)(op_values[0] == op_values[1]);
//         break;
//     default:
//         result = NAN;
//         break;
//     }
//     return (result);
// }
