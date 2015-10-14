
#ifndef __BINARY_OPS__
#define __BINARY_OPS__

#include "node.h"

namespace bake_ast {

  /*** Binary Ops Parent Class ***/
  class BinaryOp : public Node {
  public:
    BinaryOp(NodeType type) : Node(type) {};
    virtual ~BinaryOp() {
      delete lhs;
      delete rhs;
    }

    void setLhs(Node* n) { this->lhs = n; }
    Node* getLhs() { return this->lhs; }
    void setRhs(Node* n) { this->rhs = n; }
    Node* getRhs() { return this->rhs; }
    virtual void accept(bake_ast::Visitor* v) = 0;

  protected:
    Node* lhs;
    Node* rhs;
  };
  
  /*** Plus ***/
  class Plus : public BinaryOp {
  public:
    Plus() : BinaryOp(PLUS) {};
    Plus(Node* l, Node* r) : BinaryOp(PLUS) { lhs = l; rhs = r; }
    virtual ~Plus() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** Minus ***/
  class Minus : public BinaryOp {
  public:
    Minus() : BinaryOp(MINUS) {};
    Minus(Node* l, Node* r) : BinaryOp(MINUS) { lhs = l; rhs = r; }
    virtual ~Minus() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** Multiply ***/
  class Multiply : public BinaryOp {
  public:
    Multiply() : BinaryOp(MULTIPLY) {};
    Multiply(Node* l, Node* r) : BinaryOp(MULTIPLY) { lhs = l; rhs = r; }
    virtual ~Multiply() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** Divide ***/
  class Divide : public BinaryOp {
  public:
    Divide() : BinaryOp(DIVIDE) {};
    Divide(Node* l, Node* r) : BinaryOp(DIVIDE) { lhs = l; rhs = r; }
    virtual ~Divide() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** LessThan ***/
  class LessThan : public BinaryOp {
  public:
    LessThan() : BinaryOp(LESSTHAN) {};
    LessThan(Node* l, Node* r) : BinaryOp(LESSTHAN) { lhs = l; rhs = r; }
    virtual ~LessThan() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** LessThanEqual ***/
  class LessThanEqual : public BinaryOp {
  public:
    LessThanEqual() : BinaryOp(LESSTHANEQUAL) {};
    LessThanEqual(Node* l, Node* r) : BinaryOp(LESSTHANEQUAL) { lhs = l; rhs = r; }
    virtual ~LessThanEqual() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** Equality ***/
  class Equal : public BinaryOp {
  public:
    Equal() : BinaryOp(EQUAL) {};
    Equal(Node* l, Node* r) : BinaryOp(EQUAL) { lhs = l; rhs = r; }
    virtual ~Equal() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
  
  /*** Assignment ***/
  class Assign : public BinaryOp {
  public:
    Assign() : BinaryOp(ASSIGN) {};
    Assign(Node* l, Node* r) : BinaryOp(ASSIGN) { lhs = l; rhs = r; }
    virtual ~Assign() {};
    
    virtual void accept(bake_ast::Visitor* v) {v->visit(this); }
  };
}

#endif