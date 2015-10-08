
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
  list.push_back(n);
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
