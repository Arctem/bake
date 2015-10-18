
#include <iostream>
using namespace std;
#include "ast/ast.h"
using namespace bake_ast;

/*********** Pretty print methods ***********/

/**
 * What to do before visiting a node
 * Prints out whitespace according to the level this printer is currently on.
 */
void PrettyPrint::leadingOps() {
  for(int i = 0; i < depth; i++) {
    cout << "| ";
  }
}

/*********** Terminal implementations ***********/

void PrettyPrint::visit(IntegerVal* n) {
  leadingOps();
  cout << "+ Integer: " << n->getValue() << endl;
}

void PrettyPrint::visit(Int8Val* n) {
  leadingOps();
  cout << "+ Char: " << (int) n->getValue() << endl;
}

void PrettyPrint::visit(Int64Val* n) {
  leadingOps();
  cout << "+ Long: " << n->getValue() << endl;
}

void PrettyPrint::visit(FloatVal* n) {
  leadingOps();
  cout << "+ Float: " << n->getValue() << endl;
}

void PrettyPrint::visit(StringVal* n) {
  leadingOps();
  cout << "+ String: " << *(n->getValue()) << endl;
}

void PrettyPrint::visit(BoolVal* n) {
  leadingOps();
  cout << "+ Boolean: " << n->getValue() << endl;
}

void PrettyPrint::visit(Id* n) {
  leadingOps();
  cout << "+ ID: " << *(n->getName()) << endl;
}

void PrettyPrint::visit(Type* n) {
  leadingOps();
  cout << "+ Type: " << *(n->getName()) << endl;
}

/*********** Unary operation implementations ***********/

void PrettyPrint::visit(LogicalNot* n) {
  leadingOps();
  cout << "+ LogicalNot" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(BitNot* n) {
  leadingOps();
  cout << "+ BitNot" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Isvoid* n) {
  leadingOps();
  cout << "+ Isvoid" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(New* n) {
  leadingOps();
  cout << "+ New" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

/*********** Binary operation implementations ***********/

void PrettyPrint::visit(Plus* n) {
  leadingOps();
  cout << "+ Plus" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Minus* n) {
  leadingOps();
  cout << "+ Minus" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Multiply* n) {
  leadingOps();
  cout << "+ Multiply" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Divide* n) {
  leadingOps();
  cout << "+ Divide" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThan* n) {
  leadingOps();
  cout << "+ LessThan" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThanEqual* n) {
  leadingOps();
  cout << "+ LessThanEqual" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Equal* n) {
  leadingOps();
  cout << "+ Equal" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Assign* n) {
  leadingOps();
  cout << "+ Assign" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

/*********** Misc ***********/

void PrettyPrint::visit(ExprList* n) {
  leadingOps();
  cout << "+ ExprList" << endl;

  depth++;
  for(auto curr : n->getChildren()) {
    curr->accept(this);
  }
  depth--;
}

void PrettyPrint::visit(WhileLoop* n){
  leadingOps();
  cout << "+ WhileLoop" << endl;

  depth++;
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  depth--;
}

void PrettyPrint::visit(IfStatement* n){
  leadingOps();
  cout << "+ IfStatement" << endl;

  depth++;
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  n->getElseBody()->accept(this);
  depth--;
}

void PrettyPrint::visit(CaseStatement* n){
  leadingOps();
  cout << "+ CaseStatement" << endl;
  
  depth++;
  n->getExpr()->accept(this);
  n->getCaseList()->accept(this);
  depth--;
}

void PrettyPrint::visit(FormalDeclare* n) {
  leadingOps();
  cout << "+ FormalDeclare" << endl;

  depth++;
  n->getID()->accept(this);
  n->getType()->accept(this);

  // if there is an expression, visit it.
  if(n->getExpr() != nullptr)
    n->getExpr()->accept(this);

  depth--;
}

void PrettyPrint::visit(Case* n) {
  leadingOps();
  cout << "+ Case" << endl;

  depth++;
  n->getID()->accept(this);
  n->getType()->accept(this);

  // if there is an expression, visit it.
  if(n->getExpr() != nullptr)
    n->getExpr()->accept(this);

  depth--;
}

void PrettyPrint::visit(ClassStatement* n) {
  leadingOps();
  cout << "+ ClassStatement" << endl;

  depth++;
  n->getType()->accept(this);

  // if there is an inherited type, visit it.
  if(n->getInheritType() != nullptr)
    n->getInheritType()->accept(this);

  if(n->getList() != nullptr){
    // for(auto curr : n->getList()->getList()){
    //   curr->accept(this);
    // }
    n->getList()->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(ClassList* n) {
  leadingOps();
  cout << "+ ClassList" << endl;

  depth++;
  for(auto curr : n->getChildren()) {
    curr->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(Dispatch* n) {
  leadingOps();
  cout << "+ Dispatch" << endl;

  depth++;
  if(n->getExpr() != nullptr)
    n->getExpr()->accept(this);
  if(n->getType() != nullptr)
    n->getType()->accept(this);

  n->getID()->accept(this);
  if(n->getExprList() != nullptr){
    for(auto curr : n->getExprList()->getChildren()) {
      curr->accept(this);
    }
  }

  depth--;
}

void PrettyPrint::visit(ListFormalDeclare* n){
  leadingOps();
  cout << "+ ListFormalDeclare" << endl;

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }


  depth--;
}

void PrettyPrint::visit(CaseList* n){
  leadingOps();
  cout << "+ CaseList" << endl;

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(LetStatement* n){
  leadingOps();
  cout << "+ LetStatement" << endl;

  depth++;
  n->getList()->accept(this);
  n->getExpr()->accept(this);
  depth--;
}

void PrettyPrint::visit(Feature* n){
  leadingOps();
  cout << "+ Feature" << endl;

  depth++;
  n->getID()->accept(this);
  if(n->getList()) {
    for(auto curr : n->getList()->getList()) {
      curr->accept(this);
    }
  }
  n->getType()->accept(this);
  n->getExpr()->accept(this);

  depth--;
}

void PrettyPrint::visit(FeatureOption* n){
  leadingOps();
  cout << "+ FeatureOption" << endl;

  depth++;
  if(n->getFeat() != nullptr){
    n->getFeat()->accept(this);
  }else{
    n->getForm()->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(FeatureList* n){
  leadingOps();
  cout << "+ FeatureList" << endl;

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }

  depth--;
}
