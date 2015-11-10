
#include "ir/basic_block.h"

void ir::BasicBlock::addOp(Op* op) {
  ops.push_back(op);
}