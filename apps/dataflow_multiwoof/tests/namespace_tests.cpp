#include "../df_interface.h"
#include "test_utils.h"
#include "tests.h"

#include <iostream>
#include <vector>
#include <unistd.h>

void simple_namespace_test() {
    TEST("Simple namespace test")

    add_operand(1, 1, 1); // a
    add_operand(1, 1, 2); // b

    const DF_OPERATION addition = {DF_ARITHMETIC, DF_ARITH_ADDITION};
    const DF_OPERATION multiplication = {DF_ARITHMETIC, DF_ARITH_MULTIPLICATION};
    add_node(2, 1, 1, addition);
    add_node(2, 1, 2, multiplication);
    add_node(2, 1, 3, multiplication);

    add_node(3, 1, 1, addition);
    add_node(3, 1, 2, multiplication);
    add_node(3, 1, 3, multiplication);

    add_node(4, 1, 1, addition);
    add_node(4, 1, 2, multiplication);
    add_node(4, 1, 3, multiplication);

    subscribe("2:1:0", "1:1");
    subscribe("2:1:1", "1:2");
    subscribe("2:2:0", "2:1");
    subscribe("2:2:1", "2:1");
    subscribe("2:3:0", "2:1");
    subscribe("2:3:1", "2:1");

    subscribe("3:1:0", "2:2");
    subscribe("3:1:1", "2:3");
    subscribe("3:2:0", "3:1");
    subscribe("3:2:1", "3:1");
    subscribe("3:3:0", "3:1");
    subscribe("3:3:1", "3:1");

    subscribe("4:1:0", "3:2");
    subscribe("4:1:1", "3:3");

    setup();

    DF_VALUE *op_value = build_double(1);
    operand op(*op_value);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 1), OUTPUT_HANDLER, &op);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, 1, 2), OUTPUT_HANDLER, &op);
    deep_delete(op_value);

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 1)) == 0);

    std::vector<double> v;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, 4, 1), &op, i);
        v.push_back(op.value.value.df_double);
    }

    // // Expected: 128
    // std::cout << "OUTPUTS: ";
    // for (auto& i : v) {
    //     std::cout << i << " ";
    // }

    ASSERT_EQ(v[0], 128, "2(2(1+1)^2)^2 = 128")

    END_TEST()
}

void namespace_tests() {
    set_host(1);
    add_host(1, "127.0.0.1", "/home/centos/cspot/build/bin/");

    simple_namespace_test();
}