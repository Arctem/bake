
#include "ir/basic_block.h"

void ir::BasicBlock::addOp(Op* op) {
  ops.push_back(op);
}

void ir::Method::addStackVar(int size) {
  stack_vars.push_back(size);
}