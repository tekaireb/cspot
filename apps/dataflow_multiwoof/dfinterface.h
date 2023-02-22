#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include "df.h"
#include "woofc.h"

#include <string>
#include <map>
#include <set>

#define OUTPUT_HANDLER "output_handler"
#define SUBSCRIPTION_EVENT_HANDLER "subscription_event_handler"

void woof_create(std::string name, unsigned long element_size, unsigned long history_size);
unsigned long woof_put(std::string name, std::string handler, const void* element);
void woof_get(std::string name, void* element, unsigned long seq_no);
unsigned long woof_last_seq(std::string name);

void set_host(int host_id);
void add_host(int host_id, std::string host_ip, std::string woof_path);
void add_node(int ns, int host_id, int id, int opcode);
void add_operand(int ns, int host_id, int id);

void subscribe(int dst_ns, int dst_id, int dst_port, int src_ns, int src_id);
void subscribe(std::string dst_addr, std::string src_addr);

void setup();

std::string graphviz_representation();

std::string generate_woof_path(DFWoofType woof_type, int ns = -1, int id = -1, int host_id = -1);

unsigned long get_id_from_woof_path(std::string woof_path);

int get_ns_from_woof_path(std::string woof_path);

// /**
//  * Create a new woof.
//  * 
//  * @param element_size size of each element in the woof (e.g., sizeof(int))
//  * @param history_size maximum number of elements in woof
//  */

// void create_woof(const char* name, unsigned long element_size, unsigned long history_size);

// /**
//  * Initializes a woof.
//  *
//  * Must be called before invoking other functions.
//  *
//  * @param woof Name of woof to be created.
//  * @param size Number of entries in woof.
//  */
// void init(char* woof, int size);

// /**
//  * Add an operand.
//  *
//  * An operand holds a constant value that is passed to a node.
//  *
//  * @param woof Name of woof in which the operand will exist.
//  * @param destination_node_id ID of destination node.
//  * @param destination_node_port ID of destination port.
//  * @param value Value of the operand.
//  */
// void add_operand(char* woof, int destination_node_id, int destination_node_port, double value);

// /**
//  * Add a node.
//  *
//  * A node consumes values, performs some computation (determined by opcode), and
//  * then passes the result to another node.
//  *
//  * @param woof Name of woof in which the node will exist.
//  * @param node_id ID of the node (must be unique).
//  * @param input_count arity of the node.
//  * @param opcode Opcode, which specifies computation to be performed.
//  * @param destination_node_id ID of destination node.
//  * @param destination_node_port ID of destination port.
//  */
// void add_node(char* woof, int node_id, int input_count, int opcode, int destination_node_id, int destination_node_port);

#endif // DFINTERFACE_H