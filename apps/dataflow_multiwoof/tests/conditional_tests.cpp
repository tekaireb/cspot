#include "../df_interface.h"
#include "test_utils.h"
#include "tests.h"

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

void selector_test() {
    TEST("Selector test")

    int ns = 1;

    const DF_OPERATION select = {DF_INTERNAL, DF_INTERNAL_SELECT};
    add_node(ns, 1, 1, select); // a or b

    add_operand(ns, 1, 2); // Selector (0 or 1)
    add_operand(ns, 1, 3); // a
    add_operand(ns, 1, 4); // b

    subscribe(ns, 1, 0, ns, 2); // Selector --> SEL:0
    subscribe(ns, 1, 1, ns, 3); // a --> SEL:1
    subscribe(ns, 1, 2, ns, 4); // b --> SEL:2

    setup();

    for (int i = 1; i <= 2; i++) {
        DF_VALUE* selector = build_double(i - 1);
        operand op(*selector, i); // Selector
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op);
        deep_delete(selector);
        DF_VALUE* a_value = build_double(10);
        operand a(*a_value, i); // a
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &a);
        deep_delete(a_value);
        DF_VALUE* b_value = build_double(20);
        operand b(*b_value, i); // b
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 4), OUTPUT_HANDLER, &b);
        deep_delete(b_value);
    }

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) < 2);

    operand r1;
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &r1, 1);
    ASSERT_EQ(r1.value.value.df_double, 10, "SEL = 0 -> result = a = 10")

    operand r2;
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &r2, 2);
    ASSERT_EQ(r2.value.value.df_double, 20, "SEL = 1 -> result = b = 20")

    END_TEST()
}

void filter_test() {
    TEST("Filter test")

    int ns = 1;

    DF_OPERATION filter = {.category = DF_INTERNAL, .operation = DF_INTERNAL_FILTER};
    add_node(ns, 1, 1, filter);

    add_operand(ns, 1, 2); // Filter condition
    add_operand(ns, 1, 3); // Value

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup();

    DF_VALUE* filter1_value = build_double(0);
    operand filter1(*filter1_value, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter1);
    deep_delete(filter1_value);
    DF_VALUE* data1_value = build_double(1);
    operand data1(*data1_value, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data1);
    deep_delete(filter1_value);

    DF_VALUE* filter2_value = build_double(1);
    operand filter2(*filter2_value, 2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter2);
    deep_delete(filter2_value);
    DF_VALUE* data2_value = build_double(2);
    operand data2(*data2_value, 2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data2);
    deep_delete(data2_value);

    DF_VALUE* filter3_value = build_double(1);
    operand filter3(*filter3_value, 3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter3);
    deep_delete(filter3_value);
    DF_VALUE* data3_value = build_double(3);
    operand data3(*data3_value, 3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data3);
    deep_delete(data3_value);

    DF_VALUE* filter4_value = build_double(0);
    operand filter4(*filter4_value, 4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter4);
    deep_delete(filter4_value);
    DF_VALUE* data4_value = build_double(4);
    operand data4(*data4_value, 4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data4);
    deep_delete(data4_value);

    DF_VALUE* filter5_value = build_double(1);
    operand filter5(*filter5_value, 5);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter5);
    deep_delete(filter5_value);
    DF_VALUE* data5_value = build_double(5);
    operand data5(*data5_value, 5);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data5);
    deep_delete(data5_value);

    printf("TEST");

    do {
        usleep(1e5);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) < 3);

    std::vector<operand> v;
    operand data;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &data, i);
        v.push_back(data);
    }

    // // Expected: 2 3 5
    // std::cout << "OUTPUTS: ";
    // for (auto& i : v) {
    //     std::cout << i.value << " ";
    // }

    // Note: duplicates are allowed
    std::vector<unsigned long> expected = {NULL, NULL, 2, 3, NULL, 5};
    unsigned long prev_seq = 1;
    for (auto& op : v) {
        ASSERT(op.seq >= prev_seq, "Sequence increases monotonically")
        ASSERT_EQ(op.value.value.df_double, expected[op.seq], "Ensure value is correct for each sequence number")
        prev_seq = op.seq;
    }

    END_TEST()
}

void conditional_tests() {
    set_host(1);
    add_host(1, "127.0.0.1", "/home/centos/cspot/build/bin/");

    selector_test();
    filter_test();
}