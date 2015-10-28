
#include <iostream>
using namespace std;

#include "ast/node.h"
#include "ast/ast.h"
#include "ast/visitor.h"
using namespace bake_ast;

/*********** Helper functions ***********/

/**
 * Defines how to print out the inferred type
 * param pp: Reference to pretty printer that is printing this AST
 * param infType: The type ID of the type that should be printed.
 * note: I'd like to make this a method of the PrettyPrint visitor, but, afaik,
 *       there isn't a way to do that that avoids circular dependencies.
 */
void inferredType(PrettyPrint* pp, string* infType) {
  if(infType != nullptr) {
    pp->leadingOps();
    cout << "| = " << *infType << endl;
  }
}

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
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(Int8Val* n) {
  leadingOps();
  cout << "+ Char: " << (int) n->getValue() << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(Int64Val* n) {
  leadingOps();
  cout << "+ Long: " << n->getValue() << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(FloatVal* n) {
  leadingOps();
  cout << "+ Float: " << n->getValue() << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(StringVal* n) {
  leadingOps();
  cout << "+ String: " << *(n->getValue()) << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(BoolVal* n) {
  leadingOps();
  cout << "+ Boolean: " << n->getValue() << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(Id* n) {
  leadingOps();
  cout << "+ ID: " << *(n->getName()) << endl;
  inferredType(this, n->getInfType());
}

void PrettyPrint::visit(Type* n) {
  leadingOps();
  cout << "+ Type: " << *(n->getName()) << endl;
  inferredType(this, n->getInfType());
}

/*********** Unary operation implementations ***********/

void PrettyPrint::visit(LogicalNot* n) {
  leadingOps();
  cout << "+ LogicalNot" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(BitNot* n) {
  leadingOps();
  cout << "+ BitNot" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Isvoid* n) {
  leadingOps();
  cout << "+ Isvoid" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(New* n) {
  leadingOps();
  cout << "+ New" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->get()->accept(this);
  depth--;
}

/*********** Binary operation implementations ***********/

void PrettyPrint::visit(Plus* n) {
  leadingOps();
  cout << "+ Plus" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Minus* n) {
  leadingOps();
  cout << "+ Minus" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Multiply* n) {
  leadingOps();
  cout << "+ Multiply" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Divide* n) {
  leadingOps();
  cout << "+ Divide" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThan* n) {
  leadingOps();
  cout << "+ LessThan" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThanEqual* n) {
  leadingOps();
  cout << "+ LessThanEqual" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Equal* n) {
  leadingOps();
  cout << "+ Equal" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(Assign* n) {
  leadingOps();
  cout << "+ Assign" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

/*********** Misc ***********/

void PrettyPrint::visit(ExprList* n) {
  leadingOps();
  cout << "+ ExprList" << endl;
  inferredType(this, n->getInfType());

  depth++;
  for(auto curr : n->getChildren()) {
    curr->accept(this);
  }
  depth--;
}

void PrettyPrint::visit(WhileLoop* n){
  leadingOps();
  cout << "+ WhileLoop" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  depth--;
}

void PrettyPrint::visit(IfStatement* n){
  leadingOps();
  cout << "+ IfStatement" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  n->getElseBody()->accept(this);
  depth--;
}

void PrettyPrint::visit(CaseStatement* n){
  leadingOps();
  cout << "+ CaseStatement" << endl;
  inferredType(this, n->getInfType());
  
  depth++;
  n->getExpr()->accept(this);
  n->getCaseList()->accept(this);
  depth--;
}

void PrettyPrint::visit(FormalDeclare* n) {
  leadingOps();
  cout << "+ FormalDeclare" << endl;
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

  depth++;
  for(auto curr : n->getChildren()) {
    curr->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(Dispatch* n) {
  leadingOps();
  cout << "+ Dispatch" << endl;
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }


  depth--;
}

void PrettyPrint::visit(CaseList* n){
  leadingOps();
  cout << "+ CaseList" << endl;
  inferredType(this, n->getInfType());

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }

  depth--;
}

void PrettyPrint::visit(LetStatement* n){
  leadingOps();
  cout << "+ LetStatement" << endl;
  inferredType(this, n->getInfType());

  depth++;
  n->getList()->accept(this);
  n->getExpr()->accept(this);
  depth--;
}

void PrettyPrint::visit(Feature* n){
  leadingOps();
  cout << "+ Feature" << endl;
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

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
  inferredType(this, n->getInfType());

  depth++;
  for(auto curr : n->getList()) {
    curr->accept(this);
  }

  depth--;
}
