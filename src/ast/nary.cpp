
#include "ast/nary.h"
using namespace bake_ast;


/******* ListFormalDeclare methods *******/

ListFormalDeclare::~ListFormalDeclare() { 
  while(!list.empty()){
    auto tmp = list.back();
    list.pop_back();
    delete tmp;
  }   
}

void ListFormalDeclare::add(FormalDeclare* n) {
  vector<FormalDeclare *>::iterator it = list.begin();
  list.insert(it, n);
}

/******* CaseList methods *******/

CaseList::~CaseList() { 
 while(!list.empty()){
    auto tmp = list.back();
    list.pop_back();
    delete tmp;
  } 
}

void CaseList::add(Case* n) {
  vector<Case *>::iterator it = list.begin();
  list.insert(it, n);
}

/******* FeatureOption methods *******/

FeatureOption::~FeatureOption() { 
  delete feat;
  delete form;  
}

/******* ClassStatement methods *******/

ClassStatement::~ClassStatement() {
  delete inheritType;
  delete type;
  delete list;
}

void ClassStatement::add(FeatureOption* n) {
  list->add(n);
}

Dispatch::Dispatch(Node* e, Node* t, Node* id, ExprList* exprList) : Node(DISPATCH) {
  setExpr(e);
  setType(t);
  setID(id);
  setExprList(exprList);
}

Dispatch::~Dispatch() {
  delete exprList;
  delete expr;
  delete type;
  delete id;
}
