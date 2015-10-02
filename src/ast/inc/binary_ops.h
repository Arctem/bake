
#ifndef __BINARY_OPS__
#define __BINARY_OPS__

#include "node.h"

namespace bake_ast {
  class BinaryOp : public Node {
  public:
    BinaryOp(NodeType type) : Node(type) {};

    void setLhs(Node* n) { this->lhs = n; }
    Node* getLhs() { return this->lhs; }
    void setRhs(Node* n) { this->rhs = n; }
    Node* getRhs() { return this->rhs; }
    virtual void accept(bake_ast::Visitor* v) { v->visit(this); }

  protected:
    Node* lhs;
    Node* rhs;
  };
  
  class Plus : public BinaryOp {
  public:
    Plus() : BinaryOp(PLUS) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Minus : public BinaryOp {
  public:
    Minus() : BinaryOp(MINUS) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Multiply : public BinaryOp {
  public:
    Multiply() : BinaryOp(MULTIPLY) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Divide : public BinaryOp {
  public:
    Divide() : BinaryOp(DIVIDE) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class LessThan : public BinaryOp {
  public:
    LessThan() : BinaryOp(LESSTHAN) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class LessThanEqual : public BinaryOp {
  public:
    LessThanEqual() : BinaryOp(LESSTHANEQUAL) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Equal : public BinaryOp {
  public:
    Equal() : BinaryOp(EQUAL) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Assign : public BinaryOp {
  public:
    Assign() : BinaryOp(ASSIGN) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
}

#endif