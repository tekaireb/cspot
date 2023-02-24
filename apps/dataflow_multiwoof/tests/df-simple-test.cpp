#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

void simple_test() {
    std::ofstream out("test.txt");
    int ns = 1;

    add_node(ns, 1, 1, ADD);

    add_operand(ns, 1, 2);
    add_operand(ns, 1, 3);

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup();
    sleep(1);

    operand op1(1.0, 1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op1);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op1);

    operand op2(2.0, 2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op2);

    operand op3(3.0, 3);
    operand op4(3.0, 4);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &op4);

    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op3);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op4);

    sleep(3);


    std::vector<operand> v;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &op1, i);
        v.push_back(op1);
    }

    // Expected: 2 4 6 6
    std::cout << "OUTPUTS: ";
    for (auto& i : v) {
        std::cout << i.seq << ": " << i.value << " | ";
    }
    std::cout << std::endl;
}

int main() {

    set_host(1);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    simple_test();

    return 0;
}

