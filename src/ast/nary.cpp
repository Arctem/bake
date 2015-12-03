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

void ExprList::addToFront(Node* n) {
  children.push_back(n);
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

/* Eats up another ClassList, basically merging two into one. */
void ClassList::consume(ClassList* n) {
  children.reserve(children.size() + n->children.size());
  children.insert(children.end(), n->children.begin(), n->children.end());
  n->children.clear();
  delete n;
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

void ListFormalDeclare::addToFront(FormalDeclare* n) {
  list.push_back(n);
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
Feature::Feature() : Node(FEATURE) {
  list = new ListFormalDeclare();
  list->addToFront(new FormalDeclare(new Id(new string("self")), new Type(new string("SELF_TYPE"))));
};

Feature::Feature(Id* id, ListFormalDeclare* l, Type* type, Node* e) : Node (FEATURE) {
  this->id = id;
  list = l;
  this->type = type;
  expr = e;

  if(list == nullptr) {
    list = new ListFormalDeclare();
  }

  list->add(new FormalDeclare(new Id(new string("self")), new Type(new string("SELF_TYPE"))));
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

ClassStatement::ClassStatement(Type* t, Type* i, FeatureList* f, bool cantExtend) : Node(CLASSSTATEMENT), nonExtend(cantExtend) {
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

Dispatch::Dispatch() : Node(DISPATCH) {
  FormalDeclare* self_var = new FormalDeclare(new Id(new std::string("self")), new Type(new std::string("SELF_TYPE")));

  setExprList(new ExprList());
  getExprList()->add(self_var);
};

Dispatch::Dispatch(Node* e, Type* t, Id* id, ExprList* exprList) : Node(DISPATCH) {
  setExpr(e);
  setType(t);
  setID(id);
  setExprList(exprList);

  if(getExprList() == nullptr) {
    setExprList(new ExprList());
  }
  FormalDeclare* self_var = new FormalDeclare(new Id(new std::string("self")), new Type(new std::string("SELF_TYPE")));
  getExprList()->add(self_var);
}

Dispatch::~Dispatch() {
  delete exprList;
  delete expr;
  delete type;
  delete id;
}
