
#include "ir/basic_block.h"

void ir::BasicBlock::addOp(Op* op, int pos) {
  // -1 is the default value.
  if(pos == -1) {
    ops.push_back(op);
  } else {
    ops.insert(ops.begin() + pos, op);
  }
}

void ir::Method::addStackVar(int size) {
  stack_vars.push_back(size);
}
