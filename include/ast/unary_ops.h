
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
    UnaryOp(NodeType type, Node* c) : Node(type) {
      child = c;
    }
    virtual ~UnaryOp() { delete child; };

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
    LogicalNot(Node* c) : UnaryOp(LOGICALNOT, c) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class BitNot : public UnaryOp {
  public:
    BitNot() : UnaryOp(BITNOT) {};
    BitNot(Node* c) : UnaryOp(BITNOT, c) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class Isvoid : public UnaryOp {
  public:
    Isvoid() : UnaryOp(ISVOID) {};
    Isvoid(Node* c) : UnaryOp(ISVOID, c) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };

  /**
   * Represents the bitwise not
   */
  class New : public UnaryOp {
  public:
    New() : UnaryOp(NEW) {};
    New(Node* c) : UnaryOp(NEW, c) {};

    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }
  };
}

#endif