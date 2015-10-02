
#ifndef __THE_AWSOME__
#define __THE_AWSOME__

#include <vector>
using namespace std;
#include "node.h"
using namespace bake_ast;

namespace bake_ast {
	class ExprList : Node {
	public:
		ExprList() : Node(EXPRLIST) { };
		void add(Node*);
		vector<Node*> getChildren();
		virtual void accept(Visitor* v) {v->visit(this); };

	private:
		vector<Node*> children;
	};
  
  
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
  
  
}

#endif