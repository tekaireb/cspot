#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

void selector_test() {

    std::ofstream out("test.txt");
    int ns = 1;

    add_node(ns, 1, 1, ADD); // (a or b) + 1
    add_node(ns, 1, 2, SEL); // a or b

    add_operand(ns, 1, 3); // a
    add_operand(ns, 1, 4); // b
    add_operand(ns, 1, 5); // 1
    add_operand(ns, 1, 6); // Selector (0 or 1)

    subscribe(ns, 1, 0, ns, 2); // SEL --> ADD:0
    subscribe(ns, 1, 1, ns, 5); // 1 --> ADD:1
    subscribe(ns, 2, 0, ns, 6); // Selector --> SEL:0
    subscribe(ns, 2, 1, ns, 3); // a --> SEL:1
    subscribe(ns, 2, 2, ns, 4); // b --> SEL:2

    setup(); sleep(2);
    std::cout << "Finished setup" << std::endl;

    operand op(10); // a
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op);
    op.value = 20;  // b
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 4), OUTPUT_HANDLER, &op);
    op.value = 1;   // 1
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 5), OUTPUT_HANDLER, &op);
    op.value = 1;   // Selector
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 6), OUTPUT_HANDLER, &op);
    
    do {
        sleep(1);
    } while (woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1)) == 0);

    operand result;
    // woof_get(p + ".output.1", &result, 1);
    // std::cout << "result = " << result.value << std::endl;
    for (int i = 6; i > 0; i--) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, i), &result, 1);
        std::cout << "node #" << i << " result = " << result.value << std::endl;
    }
    // Selector = 0 --> a --> result = a + 1 = 11
    // Selector = 1 --> b --> result = b + 1 = 21

    std::cout << "DONE" << std::endl;
}

int main() {

    set_host(1);
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    selector_test();

    return 0;
}


