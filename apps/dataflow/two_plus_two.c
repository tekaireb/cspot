#include <stdio.h>

#include "dfinterface.h"

int main() {
  init("test", 10000);

  add_node("test", 1, ADD, 0);

  add_operand("test", 2.0, 1, -1);
  add_operand("test", 2.0, 1, -1);
}