
#pragma once

#include <string>
#include <unordered_map>
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

  class Method {
  public:
    std::vector<int> getStackVars() { return stack_vars; }

    void addStackVar(int);

  private:
    std::vector<int> stack_vars; // Vector containing the size of each variable that needs to be included in stack frames for this method
  };
}