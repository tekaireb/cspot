#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>


void simple_test() {
    std::ofstream out("test.txt");
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);


    add_node(ns, 1, ADD);
    add_node(ns, 2, MUL);

    add_operand(ns, 3);
    add_operand(ns, 4);
    add_operand(ns, 5);

    subscribe(ns, 1, 0, ns, 3);
    subscribe(ns, 1, 1, ns, 4);
    subscribe(ns, 2, 0, ns, 1);
    subscribe(ns, 2, 1, ns, 5);

    setup(ns);

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


void simple_test_2() {
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, ADD);

    add_operand(ns, 2);
    add_operand(ns, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup(ns);
    sleep(1);

    operand op1(1.0, 1);
    woof_put(p + ".output.2", "output_handler", &op1);
    woof_put(p + ".output.3", "output_handler", &op1);

    operand op2(2.0, 2);
    woof_put(p + ".output.2", "output_handler", &op2);
    woof_put(p + ".output.3", "output_handler", &op2);

    operand op3(3.0, 3);
    operand op4(3.0, 4);
    woof_put(p + ".output.2", "output_handler", &op3);
    woof_put(p + ".output.2", "output_handler", &op4);

    woof_put(p + ".output.3", "output_handler", &op3);
    woof_put(p + ".output.3", "output_handler", &op4);

    sleep(3);


    std::vector<operand> v;
    unsigned long last = woof_last_seq(p + ".output.1");
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(p + ".output.1", &op1, i);
        v.push_back(op1);
    }

    // Expected: 2 4 6 6
    std::cout << "OUTPUTS: ";
    for (auto& i : v) {
        std::cout << i.seq << ": " << i.value << " | ";
    }
    std::cout << std::endl;
}


void quadratic_test(double a, double b, double c) {
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, DIV);
    add_node(ns, 2, MUL);
    add_node(ns, 3, MUL);
    add_node(ns, 4, ADD);
    add_node(ns, 5, SQR);
    add_node(ns, 6, SUB);
    add_node(ns, 7, MUL);
    add_node(ns, 8, MUL);

    add_operand(ns, 9); // a
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
    int ns = 1;

    add_node(ns, 1, DIV);
    add_node(ns, 2, MUL);
    add_node(ns, 3, MUL);
    add_node(ns, 4, ADD);
    add_node(ns, 5, SQR);
    add_node(ns, 6, SUB);
    add_node(ns, 7, MUL);
    add_node(ns, 8, MUL);

    add_operand(ns, 9); // a
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

    std::cout << graphviz_representation() << std::endl;
}

void namespace_graphviz_test() {

    add_operand(1, 1); // a
    add_operand(1, 2); // b

    add_node(2, 1, ADD);
    add_node(2, 2, MUL);
    add_node(2, 3, MUL);

    add_node(3, 1, ADD);
    add_node(3, 2, MUL);
    add_node(3, 3, MUL);

    add_node(4, 1, ADD);
    add_node(4, 2, MUL);
    add_node(4, 3, MUL);

    // subscribe(1, 1, 0, 4, 1);
    // subscribe(1, 1, 1, 4, 2);
    // subscribe(1, 2, 0, 1, 1);
    // subscribe(1, 2, 1, 1, 1);
    // subscribe(1, 3, 0, 1, 1);
    // subscribe(1, 3, 1, 1, 1);

    subscribe("2:1:0", "1:1");
    subscribe("2:1:1", "1:2");
    subscribe("2:2:0", "2:1");
    subscribe("2:2:1", "2:1");
    subscribe("2:3:0", "2:1");
    subscribe("2:3:1", "2:1");

    // subscribe(2, 1, 0, 1, 2);
    // subscribe(2, 1, 1, 1, 3);
    // subscribe(2, 2, 0, 2, 1);
    // subscribe(2, 2, 1, 2, 1);
    // subscribe(2, 3, 0, 2, 1);
    // subscribe(2, 3, 1, 2, 1);

    subscribe("3:1:0", "2:2");
    subscribe("3:1:1", "2:3");
    subscribe("3:2:0", "3:1");
    subscribe("3:2:1", "3:1");
    subscribe("3:3:0", "3:1");
    subscribe("3:3:1", "3:1");

    // subscribe(3, 1, 0, 2, 2);
    // subscribe(3, 1, 1, 2, 3);
    // subscribe(3, 2, 0, 3, 1);
    // subscribe(3, 2, 1, 3, 1);
    // subscribe(3, 3, 0, 3, 1);
    // subscribe(3, 3, 1, 3, 1);

    subscribe("4:1:0", "3:2");
    subscribe("4:1:1", "3:3");
    subscribe("4:2:0", "4:1");
    subscribe("4:2:1", "4:1");
    subscribe("4:3:0", "4:1");
    subscribe("4:3:1", "4:1");

    std::cout << graphviz_representation() << std::endl;
}

void selector_test() {
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, ADD); // (a or b) + 1
    add_node(ns, 2, SEL); // a or b

    add_operand(ns, 3); // a
    add_operand(ns, 4); // b
    add_operand(ns, 5); // 1
    add_operand(ns, 6); // Selector (0 or 1)

    subscribe(ns, 1, 0, ns, 2); // SEL --> ADD:0
    subscribe(ns, 1, 1, ns, 5); // 1 --> ADD:1
    subscribe(ns, 2, 0, ns, 6); // Selector --> SEL:0
    subscribe(ns, 2, 1, ns, 3); // a --> SEL:1
    subscribe(ns, 2, 2, ns, 4); // b --> SEL:2

    setup(ns); sleep(2);
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

void filter_test() {
    int ns = 1;
    std::string p = "laminar-" + std::to_string(ns);

    add_node(ns, 1, FILTER);

    add_operand(ns, 2); // Filter condition
    add_operand(ns, 3); // Value

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup(ns);
    sleep(1);

    operand filter(0.0);
    operand data(1.0);
    woof_put(p + ".output.2", "output_handler", &filter);
    woof_put(p + ".output.3", "output_handler", &data);

    filter.value = 1.0;
    data.value = 2.0;
    woof_put(p + ".output.2", "output_handler", &filter);
    woof_put(p + ".output.3", "output_handler", &data);

    filter.value = 1.0;
    data.value = 3.0;
    woof_put(p + ".output.2", "output_handler", &filter);
    woof_put(p + ".output.3", "output_handler", &data);

    filter.value = 0.0;
    data.value = 4.0;
    woof_put(p + ".output.2", "output_handler", &filter);
    woof_put(p + ".output.3", "output_handler", &data);

    filter.value = 1.0;
    data.value = 5.0;
    woof_put(p + ".output.2", "output_handler", &filter);
    woof_put(p + ".output.3", "output_handler", &data);

    sleep(2);


    std::vector<double> v;
    unsigned long last = woof_last_seq(p + ".output.1");
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(p + ".output.1", &data, i);
        v.push_back(data.value);
    }

    // Expected: 2 3 5
    std::cout << "OUTPUTS: ";
    for (auto& i : v) {
        std::cout << i << " ";
    }
}

void namespace_test() {
    add_operand(1, 1); // a
    add_operand(1, 2); // b

    add_node(2, 1, ADD);
    add_node(2, 2, MUL);
    add_node(2, 3, MUL);

    add_node(3, 1, ADD);
    add_node(3, 2, MUL);
    add_node(3, 3, MUL);

    add_node(4, 1, ADD);
    add_node(4, 2, MUL);
    add_node(4, 3, MUL);

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

    setup(1);
    setup(2);
    setup(3);
    setup(4);

    sleep(1);

    operand op(1.0);
    woof_put("laminar-1.output.1", "output_handler", &op);
    woof_put("laminar-1.output.2", "output_handler", &op);

    sleep(2);

    std::vector<double> v;
    unsigned long last = woof_last_seq("laminar-4.output.1");
    for (unsigned long i = 1; i <= last; i++) {
        woof_get("laminar-4.output.1", &op, i);
        v.push_back(op.value);
    }

    // Expected: 128
    std::cout << "OUTPUTS: ";
    for (auto& i : v) {
        std::cout << i << " ";
    }


}

void sqrt_loop_test() {
    /* Nodes */
    
    // Inputs
    add_operand(1, 1);      // X
    add_operand(1, 2);      // Epsilon

    // // Initialization
    add_node(2, 1, DIV);    // Root = X / 2.0
    add_node(2, 2, SEL);    // Initial root or body output?
    add_node(2, 3, OFFSET); // Account for no body output before first iter
    add_operand(2, 4);      // 2.0
    add_operand(2, 5);      // SEL: root, body, body, ...
    add_operand(2, 6);      // Offset = 1
    
    // Test
    add_node(3, 1, MUL);    
    add_node(3, 2, SUB);
    add_node(3, 3, ABS);
    add_node(3, 4, LT);
    add_node(3, 5, NOT);
    add_node(3, 6, FILTER); // Repeat body
    add_node(3, 7, FILTER); // Produce result
    
    // Body
    add_node(4, 1, DIV);
    add_node(4, 2, ADD);
    add_node(4, 3, DIV);    // Root
    add_operand(4, 4);      // 2.0

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

    setup(1);
    setup(2);
    setup(3);
    setup(4);

    sleep(1);

    double x = 144.0;
    double epsilon = 10;

    

    operand op(2.0, 1);
    woof_put("laminar-4.output.4", "output_handler", &op);
    operand op2(2.0, 2);
    woof_put("laminar-4.output.4", "output_handler", &op2);
    operand op3(2.0, 3);
    woof_put("laminar-4.output.4", "output_handler", &op3);
    operand op4(2.0, 4);
    woof_put("laminar-4.output.4", "output_handler", &op4);

    op.value = op2.value = op3.value = op4.value = x;
    woof_put("laminar-1.output.1", "output_handler", &op);
    woof_put("laminar-1.output.1", "output_handler", &op2);
    woof_put("laminar-1.output.1", "output_handler", &op3);
    woof_put("laminar-1.output.1", "output_handler", &op4);
    op.value = op2.value = op3.value = op4.value = epsilon;
    woof_put("laminar-1.output.2", "output_handler", &op);
    woof_put("laminar-1.output.2", "output_handler", &op2);
    woof_put("laminar-1.output.2", "output_handler", &op3);
    woof_put("laminar-1.output.2", "output_handler", &op4);

    // Initialization

    // Seed initialization feedback with junk (not used in first iter)
    op.value = 0;
    woof_put("laminar-2.output.3", "output_handler", &op);
    // unsigned long consumer_ptr = 2;
    // woof_put("laminar-2.subscription_pointer.3", "", &consumer_ptr);

    op.value = op2.value = op3.value = op4.value = 2.0;
    woof_put("laminar-2.output.4", "output_handler", &op);
    woof_put("laminar-2.output.4", "output_handler", &op2);
    woof_put("laminar-2.output.4", "output_handler", &op3);
    woof_put("laminar-2.output.4", "output_handler", &op4);
    op.value = 0;
    op2.value = op3.value = op4.value = 1;
    woof_put("laminar-2.output.5", "output_handler", &op);
    woof_put("laminar-2.output.5", "output_handler", &op2);
    woof_put("laminar-2.output.5", "output_handler", &op3);
    woof_put("laminar-2.output.5", "output_handler", &op4);
    op.value = op2.value = op3.value = op4.value = 1;
    woof_put("laminar-2.output.6", "output_handler", &op);
    woof_put("laminar-2.output.6", "output_handler", &op2);
    woof_put("laminar-2.output.6", "output_handler", &op3);
    woof_put("laminar-2.output.6", "output_handler", &op4);

    sleep(4);

    std::vector<double> v;
    unsigned long last = woof_last_seq("laminar-3.output.6");
    for (unsigned long i = 1; i <= last; i++) {
        woof_get("laminar-3.output.6", &op, i);
        v.push_back(op.value);
    }

    double result;
    woof_get("laminar-3.output.7", &op, 0);
    result = op.value;

    // Expected: 37, 20.4459, ...
    std::cout << "Intermediate values: ";
    for (auto& i : v) {
        std::cout << i << " | ";
    }
    std::cout << std::endl;

    std::cout << "Result: " << result << std::endl;
    
}

void mat_test(const std::vector<std::vector<double>>& a,
              const std::vector<std::vector<double>>& b) {
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
            add_operand(1, i * cols_a + j + 1);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            add_operand(2, i * cols_b + j + 1);
        }
    }

    int id;
    std::string id_str;
    for (int r = 0; r < rows_r; r++) {
        for (int c = 0; c < cols_r; c++) {
            // Create addition node for intermediate products
            add_node(4, r * cols_r + c + 1, ADD);

            // Create all multiplication nodes for one output cell
            for (int i = 0; i < cols_a; i++) {
                id = r * (cols_r * cols_a) + c * cols_a + i + 1;
                add_node(3, id, MUL);
                subscribe(3, id, 0, 1, r * cols_a + i + 1);
                subscribe(3, id, 1, 2, i * cols_b + c + 1);

                // Connect product to be summed
                subscribe(4, r * cols_r + c + 1, i, 3, id);
            }
        }
    }
    
    /* Run program */

    setup(1);
    setup(2);
    setup(3);
    setup(4);
    sleep(1);

    // Write matrices to operands
    for (int i = 0; i < rows_a; i++) {
        for (int j = 0; j < cols_a; j++) {
            operand op(a[i][j], 1);
            id = i * cols_a + j + 1;
            id_str = std::to_string(id);
            woof_put("laminar-1.output." + id_str, "output_handler", &op);
        }
    }

    for (int i = 0; i < rows_b; i++) {
        for (int j = 0; j < cols_b; j++) {
            operand op(b[i][j], 1);
            id = i * cols_b + j + 1;
            id_str = std::to_string(id);
            woof_put("laminar-2.output." + id_str, "output_handler", &op);
        }
    }    

    sleep(3);

    operand op;
    std::vector<std::vector<double>> v;
    for (int r = 0; r < rows_r; r++) {
        v.push_back({});
        for (int c = 0; c < cols_r; c++) {
            id = r * cols_r + c + 1;
            id_str = std::to_string(id);
            woof_get("laminar-4.output." + id_str, &op, 1);
            v[r].push_back(op.value);
        }
    }

    std::cout << "OUTPUTS:" << std::endl;
    for (auto& row : v) {
        for (auto& i : row) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // simple_test();
    // simple_test_2();
    // quadratic_test(2, 5, 2);
    // quadratic_graphviz_test();
    // namespace_graphviz_test();
    // selector_test();
    // filter_test();
    // namespace_test();
    // sqrt_loop_test();

    // std::vector<std::vector<double>> a = {
    //     {1, 2},
    //     {3, 4}
    // };

    // std::vector<std::vector<double>> b = {
    //     {5, 6},
    //     {7, 8}
    // };

    std::vector<std::vector<double>> a = {
        {1, 2, 3},
        {4, 5, 6}
    };

    std::vector<std::vector<double>> b = {
        {10, 11},
        {20, 21},
        {30, 31}
    };
    mat_test(a, b);
}