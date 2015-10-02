
#ifndef __UNARY_OPS__
#define __UNARY_OPS__

#include "node.h"

namespace bake_ast {
  /**
   * Parent class for operations that only take one argument (e.g., logical not)
   */
  class UnaryOp : public Node {
  public:
    UnaryOp(NodeType type) : Node(type) { };
    virtual ~UnaryOp() { };

    void set(Node* n) { child = n; }
    Node* get() { return child; }
    virtual void accept(bake_ast::Visitor* v) = 0;

  protected:
    Node* child;
  };

  /**
   * Represents the "not" keyword
   */
  class LogicalNot : public UnaryOp {
  public:
    LogicalNot() : UnaryOp(LOGICALNOT) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class BitNot : public UnaryOp {
  public:
    BitNot() : UnaryOp(BITNOT) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class Isvoid : public UnaryOp {
  public:
    Isvoid() : UnaryOp(ISVOID) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class New : public UnaryOp {
  public:
    New() : UnaryOp(NEW) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };
}

#endif