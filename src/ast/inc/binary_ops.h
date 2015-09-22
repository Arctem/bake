
#ifndef __BINARY_OPS__
#define __BINARY_OPS__

#include "node.h"

namespace bake_ast {
  class BinaryOp : public Node {
  public:
    NodeType type;

    BinaryOp() : type(BINARYOP) {};

    void setLhs(Node* n) { this->lhs = n; }
    Node* getLhs() { return this->lhs; }
    void setRhs(Node* n) { this->rhs = n; }
    Node* getRhs() { return this->rhs; }
    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }

  protected:
    Node* lhs;
    Node* rhs;
  };
}

#endif