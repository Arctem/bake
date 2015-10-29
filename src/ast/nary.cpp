
#include "ast/terminals.h"
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

void ClassList::add(ClassStatement* n) {
  vector<ClassStatement *>::iterator it = children.begin();
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

void FeatureList::add(FeatureOption* n) {
  vector<FeatureOption *>::iterator it = list.begin();
  list.insert(it, n);
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
CaseStatement::CaseStatement(Node* expr, CaseList* cases) : Node(CASESTATEMENT) {
  setExpr(expr);
  setCaseList(cases);
}

CaseStatement::~CaseStatement() {
  delete caseExpr;
  delete cases;
}

/******* Feature methods *******/
Feature::Feature(Id* id, ListFormalDeclare* l, Type* type, Node* e) : Node (FEATURE) {
  this->id = id;
  list = l;
  this->type = type;
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

ClassStatement::ClassStatement(Type* t, Type* i, FeatureList* f) : Node(CLASSSTATEMENT) {
  typeId = t;
  inheritType = i;
  list = f;
}

ClassStatement::~ClassStatement() {
  delete inheritType;
  delete typeId;
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
