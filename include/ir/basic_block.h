
#pragma once

#include <vector>
#include "ir/op.h"
#include "ir/ir_visitor.h"

namespace ir {
  class BasicBlock {
  public:
    BasicBlock* getBrOnTrue() { return brOnTrue; }
    BasicBlock* getBrOnFalse() { return brOnFalse; }
    std::vector<Op*> getOps() { return ops; }

    void setBrOnTrue(BasicBlock* block) { brOnTrue = block; }
    void setBrOnFalse(BasicBlock* block) { brOnFalse = block; }
    void addOp(Op* op);

    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    BasicBlock* brOnTrue = nullptr;
    BasicBlock* brOnFalse = nullptr;
    std::vector<Op*> ops;
  };
}