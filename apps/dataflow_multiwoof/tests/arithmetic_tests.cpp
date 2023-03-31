#include "../df_interface.h"
#include "test_utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>

void simple_arithmetic() {
    TEST("Simple arithmetic");

    int ns = 1;

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    add_node(ns, 1, 1, addition);

    add_operand(ns, 1, 2);
    add_operand(ns, 1, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup();
    sleep(1);

    // 1 + 1 == 2
    DF_VALUE *op1_value = build_double(1);
    operand op1(*op1_value, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op1);
    sleep(2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op1);
    deep_delete(op1_value);

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) == 0);

    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &op1, 1);

    ASSERT_EQ(op1.value.value.df_double, 2, "1 + 1 == 2")

    END_TEST()
}

void complex_arithmetic() {
    TEST("Complex arithmetic")

    int ns = 1;

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    add_node(ns, 1, 1, addition);

    add_operand(ns, 1, 2);
    add_operand(ns, 1, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup();

    // 1 + 1 == 2
    DF_VALUE *op1_value = build_double(1);
    operand op1(*op1_value, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op1);
    deep_delete(op1_value);

    // 2 + 2 == 4
    DF_VALUE *op2_value = build_double(2);
    operand op2(*op2_value, 2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op2);
    deep_delete(op2_value);

    // 3 + 3 == 6
    // Receive two inputs on a before receiving inputs on b
    DF_VALUE *op3_value = build_double(3);
    operand op3(*op3_value, 3);
    DF_VALUE *op4_value = build_double(3);
    operand op4(*op4_value, 4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op4);
    deep_delete(op3_value);
    deep_delete(op4_value);

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) < 4);

    std::vector<operand> v;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &op1, i);
        v.push_back(op1);
    }

    // // Expected: 2 4 6 6
    // std::cout << "OUTPUTS: ";
    // for (auto& i : v) {
    //     std::cout << i.seq << ": " << i.value << " | ";
    // }
    // std::cout << std::endl;

    // Note: duplicates are allowed (e.g., [2, 2, 4, 6, 6] is valid as long as internal sequence numbers are correct)
    std::vector<unsigned long> expected = {0, 2, 4, 6, 6};
    unsigned long prev_seq = 1;
    for (auto &op: v) {
        ASSERT(op.seq == prev_seq || op.seq == prev_seq + 1, "Sequence increases monotonically")
        ASSERT_EQ(op.value.value.df_double, expected[op.seq], "Ensure value is correct for each sequence number")
        prev_seq = op.seq;
    }

    END_TEST()
}

void stream_arithmetic() {
    TEST("Stream arithmetic")

    int ns = 1;

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    add_node(ns, 1, 1, addition);

    add_operand(ns, 1, 2);
    add_operand(ns, 1, 3);
    add_operand(ns, 1, 4);
    add_operand(ns, 1, 5);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);
    subscribe(ns, 1, 2, ns, 4);
    subscribe(ns, 1, 3, ns, 5);

    setup();

    unsigned long iters = 20;
    double a = 1.0;
    double b = 2.0;
    double c = 3.0;
    double d = 4.0;

    for (unsigned long i = 1; i <= iters; i++) {
        DF_VALUE *op_value = build_double(a);
        operand op(*op_value, i);
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op);
        op_value->value.df_double = b;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op);
        op_value->value.df_double = c;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 4), OUTPUT_HANDLER, &op);
        op_value->value.df_double = d;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 5), OUTPUT_HANDLER, &op);
        deep_delete(op_value);
    }

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) < iters);

    operand result;
    std::string woof = generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1);
    woof_get(woof, &result, woof_last_seq(woof));
    ASSERT_EQ(result.value.value.df_double, a + b + c + d, "Final result should be a + b + c + d")
    ASSERT_EQ(result.seq, iters, "Final seq should be last iteration")

    std::vector<operand> v;
    operand op;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &op, i);
        v.push_back(op);
    }

    // TODO: Additional checks for correctness (monotonicity, etc.)

    // std::cout << "OUTPUTS: ";
    // for (auto& i : v) {
    //     std::cout << i.seq << ": " << i.value << " | ";
    // }
    // std::cout << std::endl;

    END_TEST()
}

void quadratic_test() {
    TEST("Quadratic test")
    double a = 2, b = 5, c = 2;

    int ns = 1;

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    const DF_OPERATION subtraction = {DF_ARITHMETIC, DF_ARITH_SUBTRACTION};
    const DF_OPERATION multiplication = {DF_ARITHMETIC, DF_ARITH_MULTIPLICATION};
    const DF_OPERATION division = {DF_ARITHMETIC, DF_ARITH_DIVISION};
    const DF_OPERATION sqrt = {DF_ARITHMETIC, DF_ARITH_SQRT};
    add_node(ns, 1, 1, division);
    add_node(ns, 1, 2, multiplication); // 2 * a
    add_node(ns, 1, 3, multiplication); // -1 * b
    add_node(ns, 1, 4, addition); // -b + sqrt(b^2 - 4ac)
    add_node(ns, 1, 5, sqrt); // sqrt(b^2 - 4ac)
    add_node(ns, 1, 6, subtraction); // b^2 - 4ac
    add_node(ns, 1, 7, multiplication); // b ^ 2
    add_node(ns, 1, 8, multiplication); // 4 * a * c

    add_operand(ns, 1, 9);  // a
    add_operand(ns, 1, 10); // b
    add_operand(ns, 1, 11); // c
    add_operand(ns, 1, 12); // 2 for 2 * a
    add_operand(ns, 1, 13); // -1 for -1 * b
    add_operand(ns, 1, 14); // 4 for 4 * a * c

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

    setup();

    DF_VALUE *op_value = build_double(a);
    operand op(*op_value);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 9), OUTPUT_HANDLER, &op);
    op_value->value.df_double = b;
    op.value = *op_value;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 10), OUTPUT_HANDLER, &op);
    op_value->value.df_double = c;
    op.value = *op_value;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 11), OUTPUT_HANDLER, &op);
    op_value->value.df_double = 2;
    op.value = *op_value;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 12), OUTPUT_HANDLER, &op);
    op_value->value.df_double = -1;
    op.value = *op_value;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 13), OUTPUT_HANDLER, &op);
    op_value->value.df_double = 4;
    op.value = *op_value;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 14), OUTPUT_HANDLER, &op);
    deep_delete(op_value);

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) == 0);

    // operand result;
    // woof_get(p + ".output.4", &result, 1);
    // std::cout << "node #4" << " result = " << result.value << std::endl;
    // for (int i = 14; i > 0; i--) {
    //     woof_get(p + ".output." + std::to_string(i), &result, 1);
    //     std::cout << "node #" << i << " result = " << result.value << std::endl;
    // }

    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &op, 1);
    ASSERT_EQ(op.value.value.df_double, -0.5, "Final result should be -0.5")

    END_TEST();
}

void stream_quadratic_test() {
    TEST("Stream quadratic test");
    double a = 2, b = 5, c = 2;

    int ns = 1;

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    const DF_OPERATION subtraction = {DF_ARITHMETIC, DF_ARITH_SUBTRACTION};
    const DF_OPERATION multiplication = {DF_ARITHMETIC, DF_ARITH_MULTIPLICATION};
    const DF_OPERATION division = {DF_ARITHMETIC, DF_ARITH_DIVISION};
    const DF_OPERATION sqrt = {DF_ARITHMETIC, DF_ARITH_SQRT};
    add_node(ns, 1, 1, division);
    add_node(ns, 1, 2, multiplication); // 2 * a
    add_node(ns, 1, 3, multiplication); // -1 * b
    add_node(ns, 1, 4, addition); // -b + sqrt(b^2 - 4ac)
    add_node(ns, 1, 5, sqrt); // sqrt(b^2 - 4ac)
    add_node(ns, 1, 6, subtraction); // b^2 - 4ac
    add_node(ns, 1, 7, multiplication); // b ^ 2
    add_node(ns, 1, 8, multiplication); // 4 * a * c

    add_operand(ns, 1, 9);  // a
    add_operand(ns, 1, 10); // b
    add_operand(ns, 1, 11); // c
    add_operand(ns, 1, 12); // 2 for 2 * a
    add_operand(ns, 1, 13); // -1 for -1 * b
    add_operand(ns, 1, 14); // 4 for 4 * a * c

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

    setup();

    unsigned long iters = 15;

    for (unsigned long i = 1; i <= iters; i++) {
        DF_VALUE *op_value = build_double(a);
        operand op(*op_value, i);
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 9), OUTPUT_HANDLER, &op);
        op_value->value.df_double = b;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 10), OUTPUT_HANDLER, &op);
        op_value->value.df_double = c;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 11), OUTPUT_HANDLER, &op);
        op_value->value.df_double = 2;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 12), OUTPUT_HANDLER, &op);
        op_value->value.df_double = -1;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 13), OUTPUT_HANDLER, &op);
        op_value->value.df_double = 4;
        op.value = *op_value;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 14), OUTPUT_HANDLER, &op);
        deep_delete(op_value);
    }

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) < iters);

    operand result;
    // woof_get(p + ".output.4", &result, 1);
    // std::cout << "node #4" << " result = " << result.value << std::endl;
    // for (int i = 14; i > 0; i--) {
    //     woof_get(p + ".output." + std::to_string(i), &result, 1);
    //     std::cout << "node #" << i << " result = " << result.value << std::endl;
    // }

    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &result, iters);
    ASSERT_EQ(result.value.value.df_double, -0.5, "Final result should be -0.5")

    END_TEST();
}

std::vector<std::vector<double>> mat_test(
        const std::vector<std::vector<double>> &a,
        const std::vector<std::vector<double>> &b) {
    int rows_a = a.size();
    int cols_a = a[0].size();
    int rows_b = b.size();
    int cols_b = b[0].size();

    // Result matrix dimensions    
    int rows_r = a.size();
    int cols_r = b[0].size();

    // Create operands
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            add_operand(1, 1, i * cols_a + j + 1);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            add_operand(2, 1, i * cols_b + j + 1);
        }
    }

    int id;
    std::string id_str;
    for (int r = 0; r < rows_r; r++) {
        for (int c = 0; c < cols_r; c++) {
            // Create addition node for intermediate products
            const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
            add_node(4, 1, r * cols_r + c + 1, addition);

            // Create all multiplication nodes for one output cell
            for (int i = 0; i < cols_a; i++) {
                id = r * (cols_r * cols_a) + c * cols_a + i + 1;
                const DF_OPERATION multiplication = {DF_ARITHMETIC, DF_ARITH_MULTIPLICATION};
                add_node(3, 1, id, multiplication);
                subscribe(3, id, 0, 1, r * cols_a + i + 1);
                subscribe(3, id, 1, 2, i * cols_b + c + 1);

                // Connect product to be summed
                subscribe(4, r * cols_r + c + 1, i, 3, id);
            }
        }
    }

    /* Run program */
    setup();

    // Write matrices to operands
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            DF_VALUE *op_value = build_double(a[i][j]);
            operand op(*op_value, 1);
            id = i * cols_a + j + 1;
            woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, id), OUTPUT_HANDLER, &op);
            deep_delete(op_value);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            DF_VALUE *op_value = build_double(b[i][j]);
            operand op(*op_value, 1);
            id = i * cols_b + j + 1;
            woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 2, id), OUTPUT_HANDLER, &op);
            deep_delete(op_value);
        }
    }

    operand op;
    std::vector<std::vector<double>> v;
    for (int r = 0; r < rows_r; r++) {
        v.push_back({});
        for (int c = 0; c < cols_r; c++) {
            id = r * cols_r + c + 1;

            do {
                usleep(2e5);
            } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, 4, id)) == 0);

            woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, 4, id), &op, 1);
            v[r].push_back(op.value.value.df_double);
        }
    }

    // std::cout << "OUTPUTS:" << std::endl;
    // for (auto& row : v) {
    //     for (auto& i : row) {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return v;
}

void mat_test_1() {
    TEST("Matrix test 1")

    std::vector<std::vector<double>> a = {
            {1, 2},
            {3, 4}
    };

    std::vector<std::vector<double>> b = {
            {5, 6},
            {7, 8}
    };

    std::vector<std::vector<double>> expected = {
            {19, 22},
            {43, 50}
    };

    std::vector<std::vector<double>> result = mat_test(a, b);

    ASSERT((result == expected), "Incorrect matrix multiplication result")

    END_TEST()
}

void mat_test_2() {
    TEST("Matrix test 2")

    std::vector<std::vector<double>> a = {
            {1, 2, 3},
            {4, 5, 6}
    };

    std::vector<std::vector<double>> b = {
            {10, 11},
            {20, 21},
            {30, 31}
    };

    std::vector<std::vector<double>> expected = {
            {140, 146},
            {320, 335}
    };

    std::vector<std::vector<double>> result = mat_test(a, b);

    ASSERT((result == expected), "Incorrect matrix multiplication result")

    END_TEST()
}

void arithmetic_tests() {

    set_host(1);
    add_host(1, "127.0.0.1", "/home/centos/cspot/build/bin/");

    simple_arithmetic();
    complex_arithmetic();
    stream_arithmetic();
    quadratic_test();
    stream_quadratic_test();
    mat_test_1();
    mat_test_2();
}
