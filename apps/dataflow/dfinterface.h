#ifndef DFINTERFACE_H
#define DFINTERFACE_H

#include "df.h"
#include "woofc.h"

/**
 * Initializes a woof.
 *
 * Must be called before invoking other functions.
 *
 * @param woof Name of woof to be created.
 * @param size Number of entries in woof.
 */
void init(char *woof, int size);

/**
 * Add an operand.
 *
 * An operand holds a constant value that is passed to a node.
 *
 * @param woof Name of woof in wich the operand will exist.
 * @param val Value of the operand.
 * @param dst ID of destination node.
 * @param order Should be -1 for now
 */
void add_operand(char *woof, double val, int dst, int order);

/**
 * Add a node.
 *
 * A node consumes values, performs some computation (determined by opcode), and
 * then passes the result to another node.
 *
 * @param woof Name of woof in wich the node will exist.
 * @param id ID of the node (must be unique).
 * @param op Opcode, which specifies computation to be performed.
 * @param dst ID of destination node.
 */
void add_node(char *woof, int id, int op, int dst);

#endif // DFINTERFACE_H