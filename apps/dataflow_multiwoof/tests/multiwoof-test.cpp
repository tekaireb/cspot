#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

void simple_test() {
    std::ofstream out("test.txt");
    std::string p = "test_program";

    add_node(p, 1, ADD);
    add_node(p, 2, MUL);

    add_operand(p, 3);
    add_operand(p, 4);
    add_operand(p, 5);

    subscribe(1, 0, 3);
    subscribe(1, 1, 4);
    subscribe(2, 0, 1);
    subscribe(2, 1, 5);

    setup(p);

    sleep(1);

    out << "subscriber_map size: " << woof_last_seq(p + ".subscriber_map") << std::endl;

    unsigned long last_seq;
    unsigned long idx;
    subscriber sub;

    last_seq = woof_last_seq(p + ".subscriber_map");
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(p + ".subscriber_map", &idx, seq);
        out << seq << ": " << idx << std::endl;
    }

    out << std::endl;
    out << "subscriber_data size: " << woof_last_seq(p + ".subscriber_data") << std::endl;

    last_seq = woof_last_seq(p + ".subscriber_data");
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(p + ".subscriber_data", &sub, seq);
        out << seq << ": {id=" << sub.id << ", port=" << sub.port << "}" << std::endl;
    }

    out << std::endl;
    out << "subscription_map size: " << woof_last_seq(p + ".subscription_map") << std::endl;

    last_seq = woof_last_seq(p + ".subscription_map");
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(p + ".subscription_map", &idx, seq);
        out << seq << ": " << idx << std::endl;
    }

    out << std::endl;
    out << "subscription_data size: " << woof_last_seq(p + ".subscription_data") << std::endl;

    last_seq = woof_last_seq(p + ".subscription_data");
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(p + ".subscription_data", &sub, seq);
        out << seq << ": {id=" << sub.id << ", port=" << sub.port << "}" << std::endl;
    }

    operand op(100.0);
    woof_put(p + ".output.3", "output_handler", &op);// sleep(2);
    woof_put(p + ".output.4", "output_handler", &op);// sleep(2);
    woof_put(p + ".output.5", "output_handler", &op);// sleep(2);

    sleep(2);
    subscription_event se;
    woof_get(p + ".subscription_events.1", &se, 1);
    std::cout << "{id=" << se.id << ", port=" << se.port << "}" << std::endl;

    operand result_node1, result_node2;
    woof_get(p + ".output.1", &result_node1, 1);
    woof_get(p + ".output.2", &result_node2, 1);
    std::cout << "node #1 result = " << result_node1.value << std::endl;
    std::cout << "node #2 result = " << result_node2.value << std::endl;

    std::cout << "DONE" << std::endl;
}

void quadratic_test(double a, double b, double c) {
    std::string p = "test_program";

    add_node(p, 1, DIV);
    add_node(p, 2, MUL);
    add_node(p, 3, MUL);
    add_node(p, 4, ADD);
    add_node(p, 5, SQR);
    add_node(p, 6, SUB);
    add_node(p, 7, MUL);
    add_node(p, 8, MUL);

    add_operand(p, 9); // a
    add_operand(p, 10); // b
    add_operand(p, 11); // c
    add_operand(p, 12); // 2 for 2 * a
    add_operand(p, 13); // -1 for -1 * b
    add_operand(p, 14); // 4 for 4 * a * c

    subscribe(1, 0, 4);
    subscribe(1, 1, 2);
    subscribe(2, 0, 9);
    subscribe(2, 1, 12);
    subscribe(3, 0, 13);
    subscribe(3, 1, 10);
    subscribe(4, 0, 5);
    subscribe(4, 1, 3);
    subscribe(5, 0, 6);
    subscribe(6, 0, 7);
    subscribe(6, 1, 8);
    subscribe(7, 0, 10);
    subscribe(7, 1, 10);
    subscribe(8, 0, 9);
    subscribe(8, 1, 11);
    subscribe(8, 2, 14);

    setup(p);

    sleep(2);

    std::cout << "Finished setup" << std::endl;

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
        sleep(1);
    } while (woof_last_seq(p + ".output.1") == 0);

    operand result;
    for (int i = 14; i > 0; i--) {
        woof_get(p + ".output." + std::to_string(i), &result, 1);
        std::cout << "node #" << i << " result = " << result.value << std::endl;
    }

    std::cout << "DONE" << std::endl;
}

void quadratic_graphviz_test() {
    std::string p = "test_program";

    add_node(p, 1, DIV);
    add_node(p, 2, MUL);
    add_node(p, 3, MUL);
    add_node(p, 4, ADD);
    add_node(p, 5, SQR);
    add_node(p, 6, SUB);
    add_node(p, 7, MUL);
    add_node(p, 8, MUL);

    add_operand(p, 9); // a
    add_operand(p, 10); // b
    add_operand(p, 11); // c
    add_operand(p, 12); // 2 for 2 * a
    add_operand(p, 13); // -1 for -1 * b
    add_operand(p, 14); // 4 for 4 * a * c

    subscribe(1, 0, 4);
    subscribe(1, 1, 2);
    subscribe(2, 0, 9);
    subscribe(2, 1, 12);
    subscribe(3, 0, 13);
    subscribe(3, 1, 10);
    subscribe(4, 0, 5);
    subscribe(4, 1, 3);
    subscribe(5, 0, 6);
    subscribe(6, 0, 7);
    subscribe(6, 1, 8);
    subscribe(7, 0, 10);
    subscribe(7, 1, 10);
    subscribe(8, 0, 9);
    subscribe(8, 1, 11);
    subscribe(8, 2, 14);

    std::cout << graphviz_representation() << std::endl;
}

void selector_test() {
    std::string p = "test_program";

    add_node(p, 1, ADD); // (a or b) + 1
    add_node(p, 2, SEL); // a or b

    add_operand(p, 3); // a
    add_operand(p, 4); // b
    add_operand(p, 5); // 1
    add_operand(p, 6); // Selector (0 or 1)

    subscribe(1, 0, 2); // SEL --> ADD:0
    subscribe(1, 1, 5); // 1 --> ADD:1
    subscribe(2, 0, 6); // Selector --> SEL:0
    subscribe(2, 1, 3); // a --> SEL:1
    subscribe(2, 2, 4); // b --> SEL:2

    setup(p); sleep(2);
    std::cout << "Finished setup" << std::endl;

    operand op(10); // a
    woof_put(p + ".output.3", "output_handler", &op);
    op.value = 20;  // b
    woof_put(p + ".output.4", "output_handler", &op);
    op.value = 1;   // 1
    woof_put(p + ".output.5", "output_handler", &op);
    op.value = 1;   // Selector
    woof_put(p + ".output.6", "output_handler", &op);
    
    do {
        sleep(1);
    } while (woof_last_seq(p + ".output.1") == 0);

    operand result;
    // woof_get(p + ".output.1", &result, 1);
    // std::cout << "result = " << result.value << std::endl;
    for (int i = 6; i > 0; i--) {
        woof_get(p + ".output." + std::to_string(i), &result, 1);
        std::cout << "node #" << i << " result = " << result.value << std::endl;
    }
    // Selector = 0 --> a --> result = a + 1 = 11
    // Selector = 1 --> b --> result = b + 1 = 21

    std::cout << "DONE" << std::endl;
}

int main() {
    // simple_test();
    // quadratic_test(2, 5, 2);
    // quadratic_graphviz_test();
    selector_test();
}