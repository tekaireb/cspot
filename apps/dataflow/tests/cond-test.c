#include "../dfinterface.h"

#include <unistd.h>

/*
 *   0, 1, 2           0, 1, 2, 3
 *   node 2 (ADD)     node 3  (ADD)
 *       |        |
 *         0, 1
 *      node 1 (MUL)
 */
int main() {
    char* wf = "test";
    init(wf, 10000);

    // Basic test: Select

    add_node(wf, 1, 3, MUX, 0, 0);

    sleep(2);

    add_operand(wf, 1, 0, 1.0); // SEL = 1
    sleep(2);
    add_operand(wf, 1, 1, 1.0); // a = 1
    sleep(2);
    add_operand(wf, 1, 2, 2.0); // b = 2


    /*
    Operation: |a - b| + |c - d|

    a = 1
    b = 2
    c = 3
    d = 4

    if a > b:
        x = a - b
    else:
        x = b - a
        
    if c > d:
        y = c - d
    else:
        y = d - c
        
    result = x + y
    */

    // // result = x + y
    // add_node(wf, 1, 2, ADD, 0, 0);


    // // ? a > b
    // add_node(wf, 2, 3, MUX, 1, 0);
    // add_node(wf, 3, 2, GT, 2, 0);

    // // x = a - b
    // add_node(wf, 4, 2, ADD, 2, 1);
    // add_node(wf, 5, 1, SUB, 4, 0);
    // // x = b - a
    // add_node(wf, 6, 2, ADD, 2, 2);
    // add_node(wf, 7, 1, SUB, 6, 0);


    // // ? c > d
    // add_node(wf, 8, 3, MUX, 1, 0);
    // add_node(wf, 9, 2, GT, 6, 0);

    // // y = c - d
    // add_node(wf, 10, 2, ADD, 8, 1);
    // add_node(wf, 11, 1, SUB, 10, 0);
    // // y = d - c
    // add_node(wf, 12, 2, ADD, 8, 2);
    // add_node(wf, 13, 1, SUB, 12, 0);
    
    // sleep(2);

    // // a = 1
    // add_operand(wf, 3, 0, 1.0);
    // add_operand(wf, 4, 1, 1.0);
    // add_operand(wf, 6, 0, 1.0);

    // // b = 2
    // add_operand(wf, 3, 1, 2.0);
    // add_operand(wf, 5, 0, 2.0);
    // add_operand(wf, 6, 1, 2.0);

    // // c = 3
    // add_operand(wf, 9, 0, 3.0);
    // add_operand(wf, 10, 1, 3.0);
    // add_operand(wf, 13, 0, 3.0);

    // // d = 4
    // add_operand(wf, 9, 1, 4.0);
    // add_operand(wf, 11, 0, 4.0);
    // add_operand(wf, 12, 1, 4.0);

    // Expected result: 2

    /*
    Perform some operation and send result to one of three nodes based on condition

    a = 0
    b = 1

    res = a + b

    if res < 0:
        sel = 0
    elif res == 0:
        sel = 1
    else:
        sel = 2
        
    if sel == 0:
        neg = res
    elif sel == 1:
        zero = res
    else:
        pos = res
        
    */

    // TODO
}