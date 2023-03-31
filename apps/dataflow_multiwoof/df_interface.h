#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include "df.h"
#include "woofc.h"

#include <map>
#include <set>
#include <string>

#define OUTPUT_HANDLER "output_handler"
#define SUBSCRIPTION_EVENT_HANDLER "subscription_event_handler"

void woof_create(const std::string &name, unsigned long element_size, unsigned long history_size);

unsigned long woof_put(const std::string &name, const std::string &handler, const void *element);

int woof_get(const std::string &name, void *element, unsigned long seq_no);

unsigned long woof_last_seq(const std::string &name);

void set_host(int host_id);

void add_host(int host_id, const std::string &host_ip, const std::string &woof_path);

void add_node(int ns, int host_id, int id, DF_OPERATION operation);

void add_operand(int ns, int host_id, int id);

void subscribe(int dst_ns, int dst_id, int dst_port, int src_ns, int src_id);

void subscribe(const std::string &dst_addr, const std::string &src_addr);

void setup();

void reset();

std::string graphviz_representation();

std::string generate_woof_path(DFWoofType woof_type, int ns = -1, int node_id = -1, int host_id = -1, int port_id = -1);

unsigned long get_node_id_from_woof_path(const std::string &woof_path);

int get_ns_from_woof_path(const std::string &woof_path);

#endif // DFINTERFACE_H