#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unistd.h>

void namespace_graphviz_test() {

    std::ofstream out("test.txt");
    int ns = 1;
    add_operand(1, 1, 1); // a
    add_operand(1, 1, 2); // b

    add_node(2, 1, 1, ADD);
    add_node(2, 1, 2, MUL);
    add_node(2, 1, 3, MUL);

    add_node(3, 1, 1, ADD);
    add_node(3, 1, 2, MUL);
    add_node(3, 1, 3, MUL);

    add_node(4, 1, 1, ADD);
    add_node(4, 1, 2, MUL);
    add_node(4, 1, 3, MUL);


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
    subscribe("4:2:0", "4:1");
    subscribe("4:2:1", "4:1");
    subscribe("4:3:0", "4:1");
    subscribe("4:3:1", "4:1");

    std::cout << graphviz_representation() << std::endl;
}


int main() {

    set_host(1);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    namespace_graphviz_test();
}
