
#ifndef __BINARY_OPS__
#define __BINARY_OPS__

#include "node.h"

namespace bake_ast {
  class BinaryOp : public Node {
  public:
    NodeType type;

    BinaryOp() {};

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
    Plus() : type(PLUS) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Minus : public BinaryOp {
  public:
    Minus() : type(MINUS) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Multiply : public BinaryOp {
  public:
    Multiply() : type(MULTIPLY) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Divide : public BinaryOp {
  public:
    Divide() : type(DIVIDE) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class LessThan : public BinaryOp {
  public:
    LessThan() : type(LESSTHAN) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class LessThanEqual : public BinaryOp {
  public:
    LessThanEqual() : type(LESSTHANEQUAL) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Equal : public BinaryOp {
  public:
    Equal() : type(EQUAL) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  class Assign : public BinaryOp {
  public:
    Assign() : type(ASSIGN) {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
}

#endif