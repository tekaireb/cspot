#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

void multi_machine_test(int curr_host_id) {
    std::ofstream out("test.txt");
    int ns = 1;

    add_node(ns, 1, 1, ADD);
    add_node(ns, 2, 2, MUL); // second machine

    add_operand(ns, 1, 3);
    add_operand(ns, 1, 4);
    add_operand(ns, 2, 5); // second machine

    subscribe(ns, 1, 0, ns, 3);
    subscribe(ns, 1, 1, ns, 4);
    subscribe(ns, 2, 0, ns, 5);
    subscribe(ns, 2, 1, ns, 1);

    setup(); 

    sleep(6);

    operand op1(10.0);
    operand op2(2.0);
    
    //trigger the operands in the machine they exist logically.
    if(curr_host_id == 1) {
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), OUTPUT_HANDLER, &op1);
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 4), OUTPUT_HANDLER, &op1);
    }

    if (curr_host_id == 2) {
        woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 5), OUTPUT_HANDLER, &op2);
    }

    sleep(2);

    operand result_node1, result_node2, result_node3;
    while(!woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1))){
        sleep(1);
    }
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &result_node1, 1);

    out << "node #1 result = " << result_node1.value << std::endl;


    while(!woof_last_seq(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2))){
        sleep(1);
    }
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), &result_node2, 1);

    out << "node #2 result = " << result_node2.value << std::endl;
    out << "DONE" << std::endl;
    
}

int main() {

    int CURR_HOST_ID = 1;
    set_host(CURR_HOST_ID);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");
    add_host(2, "169.231.234.248", "/home/centos/cspot/build/bin/");

    multi_machine_test(CURR_HOST_ID);

    return 0;
}
