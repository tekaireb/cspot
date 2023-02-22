#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <vector>

#include <unistd.h>

void filter_test() {

    std::ofstream out("test.txt");
    int ns = 1;

    add_node(ns, 0, 1, FILTER);

    add_operand(ns, 0, 2); // Filter condition
    add_operand(ns, 0, 3); // Value

    subscribe(ns, 1, 0, ns, 2);
    subscribe(ns, 1, 1, ns, 3);

    setup();
    sleep(1);

    operand filter(0.0);
    operand data(1.0);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data);

    filter.value = 1.0;
    data.value = 2.0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data);

    filter.value = 1.0;
    data.value = 3.0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data);

    filter.value = 0.0;
    data.value = 4.0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data);

    filter.value = 1.0;
    data.value = 5.0;
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), OUTPUT_HANDLER, &filter);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &data);

    sleep(2);


    std::vector<double> v;
    unsigned long last = woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1));
    for (unsigned long i = 1; i <= last; i++) {
        woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &data, i);
        v.push_back(data.value);
    }

    // Expected: 2 3 5
    std::cout << "OUTPUTS: ";
    for (auto& i : v) {
        std::cout << i << " ";
    }
}

int main() {

    set_host(0);
    add_host(0, "169.231.235.168", "/home/centos/cspot/build/bin/");

    filter_test();

    return 0;
}

