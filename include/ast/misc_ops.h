
#ifndef __THE_AWSOME__
#define __THE_AWSOME__

#include "node.h"
using namespace bake_ast;

namespace bake_ast {
  class WhileLoop : public Node {
  public:
    WhileLoop() : Node(WHILELOOP) {};
    WhileLoop(Node* c, Node* b) : Node(WHILELOOP) {
      cond = c;
      body = b;
    }
    virtual ~WhileLoop() {
      delete cond;
      delete body;
    }

    void setCond(Node* n) { this->cond = n; }
    Node* getCond() { return this->cond; }

    void setBody(Node* n) { this->body = n; }
    Node* getBody() { return this->body; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* cond;
    Node* body;
  };
  
  // this class also supports the optional expression assignment.
  class FormalDeclare : public Node {
  public:
    FormalDeclare() : Node(FORMALDECLARE) {};
    FormalDeclare(Node* i, Node* t, Node* e = nullptr) : Node(FORMALDECLARE) {
      id = i;
      type = t;
      expr = e;
    }
    virtual ~FormalDeclare() {
      delete id;
      delete type;
      delete expr;
    }

    Node* getID() { return this->id; }
    Node* getType() { return this->type; }
    Node* getExpr() { return this->expr; }

    void setID(Node* n) { id = n; }
    void setType(Node* n) { type = n; }
    void setExpr(Node* n) { expr = n; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* id;
    Node* type;
    Node* expr = nullptr;

  };

  class IfStatement : public Node {
  public:
    IfStatement() : Node(IFSTATEMENT) {};
    IfStatement(Node* c, Node* b, Node* e) : Node (IFSTATEMENT) {
      cond = c;
      body = b;
      elseBody = e;
    }
    virtual ~IfStatement() {
      delete cond;
      delete body;
      delete elseBody;
    }

    void setCond(Node* n) { this->cond = n; }
    Node* getCond() { return this->cond; }

    void setBody(Node* n) { this->body = n; }
    Node* getBody() { return this->body; }

    void setElseBody(Node* n) { this->elseBody = n; }
    Node* getElseBody() { return this->elseBody; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* cond;
    Node* body;
    Node* elseBody;
  };

  // this class also supports the optional expression assignment.
  class Case : public Node {
  public:
    Case() : Node(CASE) {};
    Case(Node* i, Node* t, Node* e = nullptr) : Node(CASE) {
      id = i;
      type = t;
      expr = e;
    }
    virtual ~Case() {
      delete id;
      delete type;
      delete expr;
    }

    Node* getID() { return this->id; }
    Node* getType() { return this->type; }
    Node* getExpr() { return this->expr; }

    void setID(Node* n) { id = n; }
    void setType(Node* n) { type = n; }
    void setExpr(Node* n) { expr = n; }

    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* id;
    Node* type;
    Node* expr = nullptr;

  };
}

#endif
