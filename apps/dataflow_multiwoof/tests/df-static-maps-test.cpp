#include "../dfinterface.h"

#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

void static_maps_test() {
    std::ofstream out("test.txt");
    int ns = 1;

    out << "Adding Nodes " << std::endl;
    add_node(ns, 1, 1, ADD);
    add_node(ns, 1, 2, ADD);
    add_node(ns, 1, 3, MUL);

    out << "Adding Operands " << std::endl;
    add_operand(ns, 1, 4);
    add_operand(ns, 1, 5);
    add_operand(ns, 1, 6);
    add_operand(ns, 1, 7);

    out << "Adding subscriptions " << std::endl;
    subscribe(ns, 1, 0, ns, 4);
    subscribe(ns, 1, 1, ns, 5);
    subscribe(ns, 2, 0, ns, 6);
    subscribe(ns, 2, 1, ns, 7);
    subscribe(ns, 3, 0, ns, 1);
    subscribe(ns, 3, 1, ns, 2);

    out << "Setup Started " << std::endl;
    setup(); 

    out << "Setup Ended " << std::endl;
    sleep(4);

    std::string subscriber_map_woof_path = generate_woof_path(SUBSCRIBER_MAP_WOOF_TYPE, ns);
    out << "subscriber_map size: " << woof_last_seq(subscriber_map_woof_path) << std::endl;

    unsigned long last_seq;
    unsigned long idx;
    subscriber sub;

    last_seq = woof_last_seq(subscriber_map_woof_path);
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(subscriber_map_woof_path, &idx, seq);
        out << seq << ": " << idx << std::endl;
    }

    out << std::endl;
    std::string subscriber_data_woof_path = generate_woof_path(SUBSCRIBER_DATA_WOOF_TYPE, ns);
    out << "subscriber_data size: " << woof_last_seq(subscriber_data_woof_path) << std::endl;

    last_seq = woof_last_seq(subscriber_data_woof_path);
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(subscriber_data_woof_path, &sub, seq);
        out << seq << ": {id=" << sub.id << ", port=" << sub.port << "}" << std::endl;
    }

    out << std::endl;
    std::string subscription_map_woof_path = generate_woof_path(SUBSCRIPTION_MAP_WOOF_TYPE, ns);
    out << "subscription_map size: " << woof_last_seq(subscription_map_woof_path) << std::endl;

    last_seq = woof_last_seq(subscription_map_woof_path);
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(subscription_map_woof_path, &idx, seq);
        out << seq << ": " << idx << std::endl;
    }

    out << std::endl;
    std::string subscription_data_woof_path = generate_woof_path(SUBSCRIPTION_DATA_WOOF_TYPE, ns);
    out << "subscription_data size: " << woof_last_seq(subscription_data_woof_path) << std::endl;

    last_seq = woof_last_seq(subscription_data_woof_path);
    for (unsigned long seq = 1; seq <= last_seq; seq++) {
        woof_get(subscription_data_woof_path, &sub, seq);
        out << seq << ": {id=" << sub.id << ", port=" << sub.port << "}" << std::endl;
    }

    std::string host_id_woof_path = generate_woof_path(HOST_ID_WOOF_TYPE);
    int host_id;
    woof_get(host_id_woof_path, &host_id, 0);
    out << "host id : " << host_id << std::endl;

    std::string host_url_woof_path = generate_woof_path(HOSTS_WOOF_TYPE);
    host h;
    woof_get(host_url_woof_path, &h, host_id);
    std::string host_url(h.host_url);
    out << "host url : " << host_url << std::endl;
    
    operand op(100.0);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 4), OUTPUT_HANDLER, &op);// sleep(2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 5), OUTPUT_HANDLER, &op);// sleep(2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 6), OUTPUT_HANDLER, &op);// sleep(2);
    woof_put(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 7), OUTPUT_HANDLER, &op);// sleep(2);

    sleep(2);
    subscription_event se;
    woof_get(generate_woof_path(SUBSCRIPTION_EVENTS_WOOF_TYPE, ns, 1), &se, 1);
    out << "{id=" << se.id << ", port=" << se.port << "}" << std::endl;
    woof_get(generate_woof_path(SUBSCRIPTION_EVENTS_WOOF_TYPE, ns, 2), &se, 1);
    out << "{id=" << se.id << ", port=" << se.port << "}" << std::endl;
    woof_get(generate_woof_path(SUBSCRIPTION_EVENTS_WOOF_TYPE, ns, 3), &se, 1);
    out << "{id=" << se.id << ", port=" << se.port << "}" << std::endl;

    operand result_node1, result_node2, result_node3;
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 1), &result_node1, 1);
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 2), &result_node2, 1);
    woof_get(generate_woof_path(OUTPUT_WOOF_TYPE, ns, 3), &result_node3, 1);
    out << "node #1 result = " << result_node1.value << std::endl;
    out << "node #2 result = " << result_node2.value << std::endl;
    out << "node #3 result = " << result_node3.value << std::endl;

    std::cout << "DONE" << std::endl;
}

int main() {

    set_host(1);
    
    add_host(1, "169.231.235.168", "/home/centos/cspot/build/bin/");

    static_maps_test();

    return 0;
}
