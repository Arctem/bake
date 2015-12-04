#pragma once

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "ir/op.h"
#include "ir/ir_visitor.h"
#include "ast/ast.h"

namespace ir {
  class BasicBlock {
  public:
    BasicBlock* getBrOnTrue() { return brOnTrue; }
    BasicBlock* getBrOnFalse() { return brOnFalse; }
    std::vector<Op*> getOps() { return ops; }
    string* getLabel();

    void setBrOnTrue(BasicBlock* block) { brOnTrue = block; }
    void setBrOnFalse(BasicBlock* block) { brOnFalse = block; }
    void addOp(Op* op, int pos = -1);

    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    BasicBlock* brOnTrue = nullptr;
    BasicBlock* brOnFalse = nullptr;
    std::vector<Op*> ops;
    string* label;
  };

  class Method : public BasicBlock {
  public:
    Method(std::string name) : name(name) {  }

    void setAst(bake_ast::Feature* n) { ast = n; } // Set the AST node corresponding to this class
    void addStackVar(int);

    std::vector<int> getStackVars() { return stack_vars; }
    bake_ast::Feature* getAst() { return ast; } // Return the AST node corresponding to this class
    std::string getName() { return name; }

    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    std::string name;
    std::vector<int> stack_vars; // Vector containing the size of each parameter that this method takes
    bake_ast::Feature* ast; // Reference to the AST node defining this class

  };
}
