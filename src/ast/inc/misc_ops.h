
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
}

#endif