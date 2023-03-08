#include "../dfinterface.h"
#include "test_utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <unistd.h>

void sqrt_loop_test() {
    TEST("Square root loop test");

    /* Nodes */
    
    // Inputs
    add_operand(1, 1, 1);      // X
    add_operand(1, 1, 2);      // Epsilon

    // // Initialization
    add_node(2, 1, 1, DIV);    // Root = X / 2.0
    add_node(2, 1, 2, SEL);    // Initial root or body output?
    add_node(2, 1, 3, OFFSET); // Account for no body output before first iter
    add_operand(2, 1, 4);      // 2.0
    add_operand(2, 1, 5);      // SEL: root, body, body, ...
    add_operand(2, 1, 6);      // Offset = 1
    
    // Test
    add_node(3, 1, 1, MUL);    
    add_node(3, 1, 2, SUB);
    add_node(3, 1, 3, ABS);
    add_node(3, 1, 4, LT);
    add_node(3, 1, 5, NOT);
    add_node(3, 1, 6, FILTER); // Repeat body
    add_node(3, 1, 7, FILTER); // Produce result
    
    // Body
    add_node(4, 1, 1, DIV);
    add_node(4, 1, 2, ADD);
    add_node(4, 1, 3, DIV);    // Root
    add_operand(4, 1, 4);      // 2.0

    /* Edges */

    // Initialization
    subscribe("2:1:0", "1:1");  // Root = X / _
    subscribe("2:1:1", "2:4");  // Root = X / 2.0
    subscribe("2:2:0", "2:5");  // Selector
    subscribe("2:2:1", "2:1");  // SEL=0: Root = X / 2.0
    subscribe("2:2:2", "2:3");  // SEL=1: Root = result of body
    subscribe("2:3:0", "2:6");  // Offset = 1
    subscribe("2:3:1", "3:6");  // Result of body with offset

    // Test
    subscribe("3:1:0", "4:3");  // 3N1 = Root * _
    subscribe("3:1:1", "4:3");  // 3N1 = Root * Root
    subscribe("3:2:0", "1:1");  // 3N2 = X - _
    subscribe("3:2:1", "3:1");  // 3N2 = X - 3N1
    subscribe("3:3:0", "3:2");  // 3N3 = ABS(3N2)
    subscribe("3:4:0", "3:3");  // 3N4 = 3N3 < _
    subscribe("3:4:1", "1:2");  // 3N4 = 3N3 < Epsilon
    subscribe("3:5:0", "3:4");  // 3N5 = NOT(3N4)
    subscribe("3:6:0", "3:5");  // Repeat if !(delta < epsilon)
    subscribe("3:6:1", "4:3");  // Pass root back to body
    subscribe("3:7:0", "3:4");  // Result if (delta < epsilon)
    subscribe("3:7:1", "4:3");  // Pass root to result
    
    // Body
    subscribe("4:1:0", "1:1");  // 4N1 = X / _
    subscribe("4:1:1", "2:2");  // 4N1 = X / Root
    subscribe("4:2:0", "4:1");  // 4N2 = 4N1 + _
    subscribe("4:2:1", "2:2");  // 4N2 = 4N1 + Root
    subscribe("4:3:0", "4:2");  // 4N3 = 4N2 / _
    subscribe("4:3:1", "4:4");  // 4N3 = 4N2 / 2.0

    /* Run program */

    setup();

    double x = 144.0;
    double epsilon = 10;

    operand op(2.0, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 4), OUTPUT_HANDLER, &op);
    operand op2(2.0, 2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 4), OUTPUT_HANDLER, &op2);
    operand op3(2.0, 3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 4), OUTPUT_HANDLER, &op3);
    operand op4(2.0, 4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 4), OUTPUT_HANDLER, &op4);

    op.value = op2.value = op3.value = op4.value = x;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 1), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 1), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 1), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 1), OUTPUT_HANDLER, &op4);
    op.value = op2.value = op3.value = op4.value = epsilon;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 2), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 2), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 2), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 2), OUTPUT_HANDLER, &op4);

    // Initialization

    // Seed initialization feedback with junk (not used in first iter)
    op.value = 0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 3), OUTPUT_HANDLER, &op);
    // unsigned long consumer_ptr = 2;
    // woof_put("laminar-2.subscription_pointer.3", "", &consumer_ptr);

    op.value = op2.value = op3.value = op4.value = 2.0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 4), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 4), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 4), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 4), OUTPUT_HANDLER, &op4);
    op.value = 0;
    op2.value = op3.value = op4.value = 1;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 5), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 5), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 5), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 5), OUTPUT_HANDLER, &op4);
    op.value = op2.value = op3.value = op4.value = 1;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 6), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 6), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 6), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, 6), OUTPUT_HANDLER, &op4);

    do {
        usleep(5e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, 3, 7)) == 0);

    std::vector<double> v;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, 3, 6));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, 3, 6), &op, i);
        v.push_back(op.value);
    }

    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, 3, 7), &op, 0);
    double result = op.value;

    // // Expected: 37, 20.4459, ...
    // std::cout << "Intermediate values: ";
    // for (auto& i : v) {
    //     std::cout << i << " | ";
    // }
    // std::cout << std::endl;
    // std::cout << "Result: " << result << std::endl;

    ASSERT_EQ(v[0], 37, "First iteration");
    ASSERT_EQ(round(v[1] * 1e4) / 1e4, 20.4459, "Second iteration");
    ASSERT_EQ(round(v[2] * 1e4) / 1e4, 13.7445, "Third iteration");
    ASSERT_EQ(round(result * 1e4) / 1e4, 12.1107, "Final result");

    END_TEST();
}

void loop_tests() {

    set_host(1);
    add_host(1, "localhost", "/home/centos/cspot/build/bin/");

    sqrt_loop_test();
}