#include "df.h"

#include <math.h>

double DFOperation(int opcode, double* op_values, int size) {
    double result;
    int i;
    switch (opcode) {
    case ADD:
        result = 0;
        for (i = 0; i < size; i++) {
            result += op_values[i];
        }
        break;
    case SUB:
        result = 0;
        for (i = 0; i < size; i++) {
            result -= op_values[i];
        }
        break;
    case MUL:
        result = 1;
        for (i = 0; i < size; i++) {
            result *= op_values[i];
        }
        break;
    case DIV:
        result = op_values[0];
        for (i = 1; i < size; i++) {
            result /= op_values[i];
        }
        break;
    case SQR:
        result = sqrt(op_values[0]);
        break;

    case LT:
        result = (double)(op_values[0] < op_values[1]);
        break;

    case GT:
        result = (double)(op_values[0] > op_values[1]);
        break;

    case EQ:
        result = (double)(op_values[0] == op_values[1]);
        break;
    
    case MUX:
        result = op_values[(int)(op_values[0]) + 1];
        break;

    default:
        result = NAN;
        break;
    }
    return (result);
}
