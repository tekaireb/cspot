#include <stdio.h>

#include "dfinterface.h"

/*
*   0, 1, 2           0, 1, 2, 3
*   node 2 (ADD)     node 3  (ADD)
*       |        |
*         0, 1
*      node 1 (MUL)
*/
int main() {

    char *wf = "test";
    init(wf, 10000);

    add_node(wf, 1, MUL, 0, 0, 2);
    add_node(wf, 2, ADD, 1, 0, 3);
    add_node(wf, 3, ADD, 1, 1, 4);

    add_operand(wf, 1.0, 2, 0);
    add_operand(wf, 2.0, 2, 1);
    add_operand(wf, 3.0, 2, 2);
    // 6.0


    add_operand(wf, 4.0, 3, 0);
    add_operand(wf, 5.0, 3, 1);
    add_operand(wf, 6.0, 3, 2);
    add_operand(wf, 0.0, 3, 3);
    // 15.0

    //result : 90.0

}