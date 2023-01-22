#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

int main() {
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
    int idx;
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
    woof_put(p + ".output.1", "output_handler", &op);
    sleep(2);

    subscription_event se;
    woof_get(p + ".subscription_events.2", &se, 1);

    std::cout << "{id=" << se.id << ", port=" << se.port << "}" << std::endl;

    std::cout << "DONE" << std::endl;

}