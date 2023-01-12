#include "../dfinterface.h"

#include <unistd.h>


int main() {
    char* wf = "test";
    init(wf, 10000);

    ////////////////////////////////////
    // Basic test: mux (sel + 2 options)

    // add_node(wf, 1, 3, MUX, 0, 0);

    // sleep(2);

    // add_operand(wf, 1, 0, 1.0); // SEL = 1
    // sleep(2);
    // add_operand(wf, 1, 1, 0.0); // a = 0
    // sleep(2);
    // add_operand(wf, 1, 2, 10.0); // b = 10

    ////////////////////////////////////
    // Basic test: mux (sel + 5 options)

    // add_node(wf, 1, 6, MUX, 0, 0);

    // sleep(2);

    // add_operand(wf, 1, 0, 3.0); // SEL = 3
    // sleep(2);
    // add_operand(wf, 1, 1, 0.0); // a = 0
    // sleep(2);
    // add_operand(wf, 1, 2, 10.0); // b = 10
    // sleep(2);
    // add_operand(wf, 1, 3, 20.0); // b = 20
    // sleep(2);
    // add_operand(wf, 1, 4, 30.0); // b = 30
    // sleep(2);
    // add_operand(wf, 1, 5, 40.0); // b = 40

    ///////////////////////////////
    // Operation: |a - b| + |c - d|

    /*
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
    // add_node(wf, 4, 2, ADD, 2, 2);
    // add_node(wf, 5, 1, SUB, 4, 0);
    // // x = b - a
    // add_node(wf, 6, 2, ADD, 2, 1);
    // add_node(wf, 7, 1, SUB, 6, 0);


    // // ? c > d
    // add_node(wf, 8, 3, MUX, 1, 1);
    // add_node(wf, 9, 2, GT, 8, 0);

    // // y = c - d
    // add_node(wf, 10, 2, ADD, 8, 2);
    // add_node(wf, 11, 1, SUB, 10, 0);
    // // y = d - c
    // add_node(wf, 12, 2, ADD, 8, 1);
    // add_node(wf, 13, 1, SUB, 12, 0);
    
    // sleep(2);

    // // a = 1
    // add_operand(wf, 3, 0, 1.0);sleep(2);
    // add_operand(wf, 4, 1, 1.0);sleep(2);
    // add_operand(wf, 7, 0, 1.0);sleep(2);

    // // b = 2
    // add_operand(wf, 3, 1, 2.0);sleep(2);
    // add_operand(wf, 5, 0, 2.0);sleep(2);
    // add_operand(wf, 6, 1, 2.0);sleep(2);

    // // c = 3
    // add_operand(wf, 9, 0, 3.0);sleep(2);
    // add_operand(wf, 10, 1, 3.0);sleep(2);
    // add_operand(wf, 13, 0, 3.0);sleep(2);

    // // d = 4
    // add_operand(wf, 9, 1, 4.0);sleep(2);
    // add_operand(wf, 11, 0, 4.0);sleep(2);
    // add_operand(wf, 12, 1, 4.0);

    // Expected result: 2

    ////////////////////////////////////
    // Basic test: demux (sel + 2 options)

    // add_node(wf, 1, 2 + 2 * 2, DEMUX, 0, 0);

    // sleep(2);

    // // SEL = 1
    // add_operand(wf, 1, 0, 1.0); sleep(2);

    // // VAL = 10
    // add_operand(wf, 1, 1, 10.0); sleep(2);

    // // OPT #0 = 2:1
    // add_operand(wf, 1, 2, 2.0); sleep(2);
    // add_operand(wf, 1, 3, 1.0); sleep(2);

    // // OPT #1 = 0:0
    // add_operand(wf, 1, 4, 0.0); sleep(2);
    // add_operand(wf, 1, 5, 0.0); sleep(2);

    ////////////////////////////////////
    // Basic test: mux (sel + 5 options)

    add_node(wf, 1, 2 + 5 * 2, MUX, 0, 0);

    sleep(2);

    // SEL = 1
    add_operand(wf, 1, 0, 3.0); sleep(2);

    // VAL = 100
    add_operand(wf, 1, 1, 100.0); sleep(2);

    // OPT #0 = 2:1
    add_operand(wf, 1, 2, 2.0); sleep(2);
    add_operand(wf, 1, 3, 1.0); sleep(2);

    // OPT #1 = 3:1
    add_operand(wf, 1, 4, 3.0); sleep(2);
    add_operand(wf, 1, 5, 1.0); sleep(2);

    // OPT #2 = 4:1
    add_operand(wf, 1, 6, 4.0); sleep(2);
    add_operand(wf, 1, 7, 1.0); sleep(2);

    // OPT #3 = 0:0
    add_operand(wf, 1, 8, 0.0); sleep(2);
    add_operand(wf, 1, 9, 0.0); sleep(2);

    // OPT #4 = 5:1
    add_operand(wf, 1, 10, 5.0); sleep(2);
    add_operand(wf, 1, 11, 1.0); sleep(2);


    /////////////////////////////////////////////////
    // Perform op, classify as -, +, 0 to select dest
    
    /*
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