#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

void quadratic_test(int curr_host_id) {
    
    std::ofstream out("test.txt");
    int ns = 1;

    double a = 2;
    double b = 5;
    double c = 2;

    add_node(ns, 1, 1, DIV);
    add_node(ns, 1, 2, MUL);
    add_node(ns, 1, 3, MUL);
    add_node(ns, 1, 4, ADD);
    add_node(ns, 1, 5, SQR);
    add_node(ns, 1, 6, SUB);
    add_node(ns, 2, 7, MUL);
    add_node(ns, 2, 8, MUL);

    add_operand(ns, 1, 9); // a
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

    sleep(6);

    std::cout << "Finished setup" << std::endl;

    if(curr_host_id == 1) {
        operand op(a);
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 9), OUTPUT_HANDLER, &op);
        op.value = b;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 10), OUTPUT_HANDLER, &op);
        op.value = c;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 11), OUTPUT_HANDLER, &op);
        op.value = 2;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 12), OUTPUT_HANDLER, &op);
        op.value = -1;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 13), OUTPUT_HANDLER, &op);
        op.value = 4;
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 14), OUTPUT_HANDLER, &op);
    }

    do {
        sleep(1);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) == 0);

    operand result;
    for (int i = 14; i > 0; i--) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, i), &result, 1);
        std::cout << "node #" << i << " result = " << result.value << std::endl;
    }

    std::cout << "DONE" << std::endl;
}

int main() {

    int CURR_HOST_ID = 1;
    set_host(CURR_HOST_ID);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");
    add_host(2, "169.231.234.248", "/home/centos/cspot/build/bin/");

    quadratic_test(CURR_HOST_ID);

    return 0;
}