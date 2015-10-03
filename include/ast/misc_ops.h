
#ifndef __THE_AWSOME__
#define __THE_AWSOME__

#include <vector>
using namespace std;
#include "node.h"
#include "nary.h"
using namespace bake_ast;

namespace bake_ast {
  class WhileLoop : public Node {
  public:
    WhileLoop() : Node(WHILELOOP) {};
    
    
    void setCond(Node* n) { this->cond = n; }
    Node* getCond() { return this->cond; }
    
    void setBody(Node* n) { this->body = n; }
    Node* getBody() { return this->body; }
    
    void accept(Visitor* v) { v->visit(this); }  
    
  private:
    Node* cond;
    Node* body;
  };
  
  class IfStatement : public Node {
  public:
    IfStatement() : Node(IFSTATEMENT) {};
    
    
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
  class FormalDeclare : public Node {
  public:
    FormalDeclare() : Node(FORMALDECLARE) {};
    
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
  
    
  class ClassStatement : public Node {
  public:
    ClassStatement() : Node(CLASSSTATEMENT) {};
    
    Node* getType() { return this->type; }
    Node* getInheritType() { return this->inheritType; }
    Node* getFeature() { return this->feature; }
    
    void getType(Node* n) { this->type = n; }
    void getInheritType(Node* n) { this->inheritType = n; }
    void getFeature(Node* n) { this->feature = n; }
    
    void accept(Visitor* v) { v->visit(this); }
    
  private:
    Node* type;
    Node* inheritType = nullptr;
    Node* feature;
    
  
  };
}

#endif