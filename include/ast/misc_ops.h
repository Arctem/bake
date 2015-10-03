
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
    WhileLoop(Node* c, Node* b) : Node(WHILELOOP) {
      cond = c;
      body = b;
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

  class IfStatement : public Node {
  public:
    IfStatement() : Node(IFSTATEMENT) {};
    IfStatement(Node* c, Node* b, Node* e) : Node (IFSTATEMENT) {
      cond = c;
      body = b;
      elseBody = e;
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
  class FormalDeclare : public Node {
  public:
    FormalDeclare() : Node(FORMALDECLARE) {};
    FormalDeclare(Node* i, Node* t, Node* e = nullptr) : Node(FORMALDECLARE) {
      id = i;
      type = t;
      expr = e;
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

  // this class also supports the optional expression assignment.
  class Case : public Node {
  public:
    Case() : Node(CASE) {};
    Case(Node* i, Node* t, Node* e = nullptr) : Node(CASE) {
      id = i;
      type = t;
      expr = e;
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


  class ClassStatement : public Node {
  public:
    ClassStatement() : Node(CLASSSTATEMENT) {};
    ClassStatement(Node* t, Node* i = nullptr, FeatureList* f = nullptr) : Node(CLASSSTATEMENT) {
      type = t;
      inheritType = i;
      list = f;
    }

    Node* getType() { return this->type; }
    Node* getInheritType() { return this->inheritType; }
<<<<<<< Updated upstream
    Node* getFeature() { return this->feature; }

    void getType(Node* n) { this->type = n; }
    void getInheritType(Node* n) { this->inheritType = n; }
    void getFeature(Node* n) { this->feature = n; }

=======
    FeatureList* getList() { return this->list; }
    
    void setType(Node* n) { this->type = n; }
    void setInheritType(Node* n) { this->inheritType = n; }
    void setList(FeatureList* n) { this->list = n; }
    void add(FeatureOption* n) { list->add(n); }
    
>>>>>>> Stashed changes
    void accept(Visitor* v) { v->visit(this); }

  private:
    Node* type;
    Node* inheritType = nullptr;
<<<<<<< Updated upstream
    Node* feature = nullptr;


=======
    FeatureList* list;
    
  
>>>>>>> Stashed changes
  };
}

#endif
