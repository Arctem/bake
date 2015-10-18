
#include "ast/nary.h"
using namespace bake_ast;

/******* ExprList methods *******/
ExprList::~ExprList() {
  while(!children.empty()){
    auto tmp = children.back();
    children.pop_back();
    delete tmp;
  }
}

void ExprList::add(Node* n) {
  vector<Node *>::iterator it = children.begin();
  children.insert(it, n);
}

/******* ClassList methods *******/

ClassList::~ClassList() {
  while(!children.empty()){
    auto tmp = children.back();
    children.pop_back();
    delete tmp;
  }
}

void ClassList::add(Node* n) {
  vector<Node *>::iterator it = children.begin();
  children.insert(it, n);
}

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

/******* FeatureList methods *******/

FeatureList::~FeatureList() {
  while (!list.empty()) {
    auto tmp = list.back();
    list.pop_back();
    delete tmp;
  }
}

/******* LetStatement methods *******/
LetStatement::LetStatement(ListFormalDeclare* l, Node* e) : Node(LETSTATEMENT) {
  list = l;
  expr = e;
}

LetStatement::~LetStatement() {
  delete list;
  delete expr;
}

/******* CaseStatement methods *******/
CaseStatement::CaseStatement(Node* c, ExprList* i, ExprList* t, ExprList* e) : Node(CASESTATEMENT) {
  caseExpr = c;
  idList = i;
  typeList = t;
  exprList = e;
}

CaseStatement::~CaseStatement() {
  delete caseExpr;
  delete idList;
  delete typeList;
  delete exprList;
}

/******* Feature methods *******/
Feature::Feature(Node* i, ListFormalDeclare* l, Node* t, Node* e) : Node (FEATURE) {
  id = i;
  list = l;
  type = t;
  expr = e;
}

Feature::~Feature() {
  delete list;
  delete id;
  delete type;
  delete expr;
}

/******* FeatureOption methods *******/

FeatureOption::~FeatureOption() { 
  delete feat;
  delete form;  
}

/******* ClassStatement methods *******/

ClassStatement::ClassStatement(Node* t, Node* i, FeatureList* f) : Node(CLASSSTATEMENT) {
  type = t;
  inheritType = i;
  list = f;
}

ClassStatement::~ClassStatement() {
  delete inheritType;
  delete type;
  delete list;
}

void ClassStatement::add(FeatureOption* n) {
  list->add(n);
}

/******* Dispatch methods *******/

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
