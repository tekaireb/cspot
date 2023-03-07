#include "../dfinterface.h"
#include "test_utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

void simple_arithmetic() {
    TEST("Simple arithmetic");

    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, ADD);

    add_operand(ns, 2);
    add_operand(ns, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup(ns);
    sleep(1);

    // 1 + 1 == 2
    operand op1(1.0, 1);
    woof_put(p + ".output.2", "output_handler", &op1);
    woof_put(p + ".output.3", "output_handler", &op1);

    do {
        usleep(1e5);
    } while (woof_last_seq(p + ".output.1") == 0);

    woof_get(p + ".output.1", &op1, 1);
    
    ASSERT_EQ(op1.value, 2, "1 + 1 == 2");

    END_TEST();
}

void stream_arithmetic() {
    TEST("Stream arithmetic");

    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, ADD);

    add_operand(ns, 2);
    add_operand(ns, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup(ns);

    // 1 + 1 == 2
    operand op1(1.0, 1);
    woof_put(p + ".output.2", "output_handler", &op1);
    woof_put(p + ".output.3", "output_handler", &op1);

    // 2 + 2 == 4
    operand op2(2.0, 2);
    woof_put(p + ".output.2", "output_handler", &op2);
    woof_put(p + ".output.3", "output_handler", &op2);

    // 3 + 3 == 6
    // Receive two inputs on a before receiving inputs on b
    operand op3(3.0, 3);
    operand op4(3.0, 4);
    woof_put(p + ".output.2", "output_handler", &op3);
    woof_put(p + ".output.2", "output_handler", &op4);

    woof_put(p + ".output.3", "output_handler", &op3);
    woof_put(p + ".output.3", "output_handler", &op4);

    do {
        usleep(1e5);
    } while (woof_last_seq(p + ".output.1") < 4);

    std::vector<operand> v;
    unsigned long last = woof_last_seq(p + ".output.1");
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(p + ".output.1", &op1, i);
        v.push_back(op1);
    }

    // // Expected: 2 4 6 6
    // std::cout << "OUTPUTS: ";
    // for (auto& i : v) {
    //     std::cout << i.seq << ": " << i.value << " | ";
    // }
    // std::cout << std::endl;

    // Note: duplicates are allowed (e.g., [2, 2, 4, 6, 6] is valid as long as internal sequence numbers are correct)
    std::vector<unsigned long> expected = {NULL, 2, 4, 6, 6};
    unsigned long prev_seq = 1;
    for (auto& op : v) {
        ASSERT(op.seq == prev_seq || op.seq == prev_seq + 1, "Sequence increases monotonically");
        ASSERT_EQ(op.value, expected[op.seq], "Ensure value is correct for each sequence number");
        prev_seq = op.seq;
    }

    END_TEST();
}

void quadratic_test() {
    TEST("Quadratic test");
    double a = 2, b = 5, c = 2;
    
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, DIV);
    add_node(ns, 2, MUL); // 2 * a
    add_node(ns, 3, MUL); // -1 * b
    add_node(ns, 4, ADD); // -b + sqrt(b^2 - 4ac)
    add_node(ns, 5, SQR); // sqrt(b^2 - 4ac)
    add_node(ns, 6, SUB); // b^2 - 4ac
    add_node(ns, 7, MUL); // b ^ 2
    add_node(ns, 8, MUL); // 4 * a * c

    add_operand(ns, 9);  // a
    add_operand(ns, 10); // b
    add_operand(ns, 11); // c
    add_operand(ns, 12); // 2 for 2 * a
    add_operand(ns, 13); // -1 for -1 * b
    add_operand(ns, 14); // 4 for 4 * a * c

    subscribe(ns, 1, 0, ns, 4);
    subscribe(ns, 1, 1, ns, 2);
    subscribe(ns, 2, 0, ns, 9);
    subscribe(ns, 2, 1, ns, 12);
    subscribe(ns, 3, 0, ns, 13);
    subscribe(ns, 3, 1, ns, 10);
    subscribe(ns, 4, 0, ns, 5);
    subscribe(ns, 4, 1, ns, 3);
    subscribe(ns, 5, 0, ns, 6);
    subscribe(ns, 6, 0, ns, 7);
    subscribe(ns, 6, 1, ns, 8);
    subscribe(ns, 7, 0, ns, 10);
    subscribe(ns, 7, 1, ns, 10);
    subscribe(ns, 8, 0, ns, 9);
    subscribe(ns, 8, 1, ns, 11);
    subscribe(ns, 8, 2, ns, 14);

    setup(ns);

    operand op(a);
    woof_put(p + ".output.9", "output_handler", &op);
    op.value = b;
    woof_put(p + ".output.10", "output_handler", &op);
    op.value = c;
    woof_put(p + ".output.11", "output_handler", &op);
    op.value = 2;
    woof_put(p + ".output.12", "output_handler", &op);
    op.value = -1;
    woof_put(p + ".output.13", "output_handler", &op);
    op.value = 4;
    woof_put(p + ".output.14", "output_handler", &op);
    
    do {
        usleep(1e5);
    } while (woof_last_seq(p + ".output.1") == 0);

    // operand result;
    // woof_get(p + ".output.4", &result, 1);
    // std::cout << "node #4" << " result = " << result.value << std::endl;
    // for (int i = 14; i > 0; i--) {
    //     woof_get(p + ".output." + std::to_string(i), &result, 1);
    //     std::cout << "node #" << i << " result = " << result.value << std::endl;
    // }

    woof_get(p + ".output.1", &op, 1);
    ASSERT_EQ(op.value, -0.5, "Final result should be -0.5");

    END_TEST();
}

void stream_quadratic_test() {
    TEST("Stream quadratic test");
    double a = 2, b = 5, c = 2;
    
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, DIV);
    add_node(ns, 2, MUL); // 2 * a
    add_node(ns, 3, MUL); // -1 * b
    add_node(ns, 4, ADD); // -b + sqrt(b^2 - 4ac)
    add_node(ns, 5, SQR); // sqrt(b^2 - 4ac)
    add_node(ns, 6, SUB); // b^2 - 4ac
    add_node(ns, 7, MUL); // b ^ 2
    add_node(ns, 8, MUL); // 4 * a * c

    add_operand(ns, 9);  // a
    add_operand(ns, 10); // b
    add_operand(ns, 11); // c
    add_operand(ns, 12); // 2 for 2 * a
    add_operand(ns, 13); // -1 for -1 * b
    add_operand(ns, 14); // 4 for 4 * a * c

    subscribe(ns, 1, 0, ns, 4);
    subscribe(ns, 1, 1, ns, 2);
    subscribe(ns, 2, 0, ns, 9);
    subscribe(ns, 2, 1, ns, 12);
    subscribe(ns, 3, 0, ns, 13);
    subscribe(ns, 3, 1, ns, 10);
    subscribe(ns, 4, 0, ns, 5);
    subscribe(ns, 4, 1, ns, 3);
    subscribe(ns, 5, 0, ns, 6);
    subscribe(ns, 6, 0, ns, 7);
    subscribe(ns, 6, 1, ns, 8);
    subscribe(ns, 7, 0, ns, 10);
    subscribe(ns, 7, 1, ns, 10);
    subscribe(ns, 8, 0, ns, 9);
    subscribe(ns, 8, 1, ns, 11);
    subscribe(ns, 8, 2, ns, 14);

    setup(ns);

    unsigned long iters = 5;

    for (unsigned long i = 1; i <= iters; i++) {
        operand op(a, i);
        woof_put(p + ".output.9", "output_handler", &op);
        op.value = b;
        woof_put(p + ".output.10", "output_handler", &op);
        op.value = c;
        woof_put(p + ".output.11", "output_handler", &op);
        op.value = 2;
        woof_put(p + ".output.12", "output_handler", &op);
        op.value = -1;
        woof_put(p + ".output.13", "output_handler", &op);
        op.value = 4;
        woof_put(p + ".output.14", "output_handler", &op);
    }
    
    do {
        usleep(1e5);
    } while (woof_last_seq(p + ".output.1") < iters);

    operand result;
    // woof_get(p + ".output.4", &result, 1);
    // std::cout << "node #4" << " result = " << result.value << std::endl;
    // for (int i = 14; i > 0; i--) {
    //     woof_get(p + ".output." + std::to_string(i), &result, 1);
    //     std::cout << "node #" << i << " result = " << result.value << std::endl;
    // }

    woof_get(p + ".output.1", &result, iters);
    ASSERT_EQ(result.value, -0.5, "Final result should be -0.5");

    END_TEST();
}

void arithmetic_tests() {
    simple_arithmetic();
    stream_arithmetic();
    quadratic_test();
    // stream_quadratic_test();
}