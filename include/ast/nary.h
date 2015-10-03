
#ifndef __NARY__
#define __NARY__

#include <vector>
using namespace std;
#include "node.h"

namespace bake_ast {
  class ExprList : public Node {
  public:
    ExprList() : Node(EXPRLIST) { };
    void add(Node* n) { children.push_back(n); }
    vector<Node*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<Node*> children;
  };
  
  class ClassList : public Node {
  public:
    ClassList() : Node(CLASSLIST) { };
    ClassList(vector<Node*> c) : Node(CLASSLIST){
      children = c;
    }
    
    void add(Node* n) { children.push_back(n); }
    vector<Node*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<Node*> children;
  };
  
  
  // TODO: optional expr, so change it around.
  class LetStatement : public Node {
  public:
    LetStatement() : Node(LETSTATEMENT) {};
    
    Node* getID() { return this->id; }
    Node* getType() { return this->type; }
    Node* getExpr() { return this->expr; }
    vector<Node*> getIdList() { return this->idList->getChildren();}
    vector<Node*> getTypeList() { return this->typeList->getChildren(); }
    vector<Node*> getExprList() { return this->exprList->getChildren(); }
    
    void setID(Node* n) { id = n; }
    void setType(Node* n) { type = n; }
    void setExpr(Node* n) { expr = n; }
    void addToIdList(Node* n) { idList->add(n); }
    void addToTypeList(Node* n) { typeList->add(n); }
    void addToExprList(Node* n) { exprList->add(n); }
    
    void accept(Visitor* v) { v->visit(this); }
  
  private:
    // required first arguments
    Node* id;
    Node* type;
    Node* expr;
    
    // other required arguments
    ExprList* idList;
    ExprList* typeList;
    ExprList* exprList;
  
  };
  
  class CaseStatement : public Node {
  public:
    CaseStatement() : Node(CASESTATEMENT) {};
    CaseStatement(Node* c, ExprList* i, ExprList* t, ExprList* e) ; Node(CASESTATEMENT) {
      caseExpr = c;
      idList = i;
      typeList = t;
      exprList = e;
    }
    
    Node* getCaseExpr() { return this->caseExpr; }
    vector<Node*> getIdList() { return this->idList->getChildren();}
    vector<Node*> getTypeList() { return this->typeList->getChildren(); }
    vector<Node*> getExprList() { return this->exprList->getChildren(); }
    
    void setCaseExpr(Node* n) { this->caseExpr = n; } 
    void addToIdList(Node* n) { idList->add(n); }
    void addToTypeList(Node* n) { typeList->add(n); }
    void addToExprList(Node* n) { exprList->add(n); }
    
    void accept(Visitor* v) { v->visit(this); }
  
  private:
    Node* caseExpr;
    
    // there will be at least one in each of these lists.
    ExprList* idList;
    ExprList* typeList;
    ExprList* exprList;
  
  };
  
  class Dispatch : public Node {
  public:
    Dispatch() : Node(DISPATCH) {};
    Dispatch(Node* e, Node* t, Node* id, ExprList* exprList) : Node(DISPATCH) {
      expr = e;
      type = t;
      this->id = id;
      this->exprList = exprList;
    }
    
    Node* getExpr() { return this->expr; }
    Node* getType() { return this->type; }
    Node* getID() { return this->id; }
    vector<Node*> getExprList() { return this->exprList->getChildren(); }
    
    void setExpr(Node* n) { this->expr = n; }
    void setType(Node* n) { this->type = n; }
    void setID(Node* n) { this->id = n; }
    void addToExprList(Node* n) { this->exprList->add(n); }
    void setExprList(ExprList* e) { this->exprList = e; }
    
    void accept(Visitor* v) { v->visit(this); }
    
  private:
    Node* expr = nullptr; // optional
    Node* type = nullptr; // optional
    
    Node* id;
    ExprList* exprList = nullptr;
    
    
  };
}

#endif