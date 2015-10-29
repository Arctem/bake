
#include <string.h>
#include <sstream>
using namespace std;

#include "typecheck/visitor_tc.h"
using namespace typecheck;



/********** Terminals ************/

/**
 * Initialize the IntegerVal terminal
 */
void TypeCheck::visit(IntegerVal* n) {
  n->setInfType("Int");
  setTypeOfLast(n->getInfType());
}

/**
 * Initialize the FloatVal terminal
 */
void TypeCheck::visit(FloatVal* n) {
  n->setInfType("Float");
  setTypeOfLast(n->getInfType());
}

/**
 * Initialize the Int8Val terminal
 */
void TypeCheck::visit(Int8Val* n) {
  n->setInfType("Int8");
  setTypeOfLast(n->getInfType());
}

/**
 * Initialize the Int64Val terminal
 */
void TypeCheck::visit(Int64Val* n) {
  n->setInfType("Int64");
  setTypeOfLast(n->getInfType());
}

/**
 * Initialize the StringVal terminal
 */
void TypeCheck::visit(StringVal* n) {
  n->setInfType("String");
  setTypeOfLast(n->getInfType());
}

/**
 * Initialize the BoolVal terminal
 */
void TypeCheck::visit(BoolVal* n) {
  n->setInfType("Bool");
  setTypeOfLast(n->getInfType());
}



/********** Unary ops ************/

/**
 * Typecheck the logical not operator
 */
void TypeCheck::visit(LogicalNot* node) {
  node->setInfType("Bool"); // Return type is guaranteed to be a Bool

  /* Get the type of the expression */
  node->get()->accept(this);
  string* subtype = getTypeOfLast();

  /* Check type */
  if(strcmp(subtype->c_str(), "Bool") != 0) {
    stringstream msg;
    msg << "Error: Logical not cannot operate on type '" << *subtype << "'";

    throw TypeErr(msg.str().c_str());
  }
}

/**
 * Typecheck the bitwise not operator
 */
void TypeCheck::visit(BitNot* node) {
  node->get()->accept(this);
}

/**
 * Typecheck the Isvoid operator
 */
void TypeCheck::visit(Isvoid* node) {
  node->setInfType("Bool"); // Return type is guaranteed to be a Bool

  /* Get the type of the expression */
  node->get()->accept(this);
  string* subtype = getTypeOfLast();
}

/**
 * Typecheck the New operator
 */
void TypeCheck::visit(New* node) {
  node->get()->accept(this);
}



/********** Binary ops ************/

/**
 * Typecheck the addition operator
 */
void TypeCheck::visit(Plus* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the subtraction operator
 */
void TypeCheck::visit(Minus* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the multiplication operator
 */
void TypeCheck::visit(Multiply* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the division operator
 */
void TypeCheck::visit(Divide* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the < operator
 */
void TypeCheck::visit(LessThan* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the <= operator
 */
void TypeCheck::visit(LessThanEqual* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the = operator
 */
void TypeCheck::visit(Equal* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}

/**
 * Typecheck the <- operator
 */
void TypeCheck::visit(Assign* node) {
  node->getLhs()->accept(this);
  node->getRhs()->accept(this);
}



/********** Misc ops ************/

/**
 * Typecheck ExprList
 */
void TypeCheck::visit(ExprList* node) {
  for(auto child : node->getChildren()) {
    child->accept(this);
  }
}

/**
 * Typecheck WhileLoop
 */
void TypeCheck::visit(WhileLoop* node) {
  node->getCond()->accept(this);
  node->getBody()->accept(this);
}

/**
 * Typecheck IfStatement
 */
void TypeCheck::visit(IfStatement* node) {
  node->getCond()->accept(this);
  node->getBody()->accept(this);
  node->getElseBody()->accept(this);
}

/**
 * Typecheck LetStatement
 */
void TypeCheck::visit(LetStatement* node) {
  node->getExpr()->accept(this);
  node->getList()->accept(this);
}

/**
 * Typecheck CaseStatement
 */
void TypeCheck::visit(CaseStatement* node) {
  node->getExpr()->accept(this);
  node->getCaseList()->accept(this);
}

/**
 * Typecheck CaseList
 */
void TypeCheck::visit(CaseList* node) {
  for(auto cse : node->getList()) {
    cse->accept(this);
  }
}

/**
 * Typecheck Case
 */
void TypeCheck::visit(Case* node) {
  node->getID()->accept(this);
  node->getType()->accept(this);

  if(node->getExpr() != nullptr) {
    node->getExpr()->accept(this);
  }
}

/**
 * Typecheck FormalDeclare
 */
void TypeCheck::visit(FormalDeclare* node) {
  node->getID()->accept(this);
  node->getType()->accept(this);

  if(node->getExpr() != nullptr) {
    node->getExpr()->accept(this);
  }
}

/**
 * Typecheck ClassStatement
 */
void TypeCheck::visit(ClassStatement* node) {
  node->getType()->accept(this);

  if(node->getList() != nullptr) {
    node->getList()->accept(this);
  }

  if(node->getInheritType() != nullptr) {
    node->getInheritType()->accept(this);
  }
}

/**
 * Typecheck ClassList
 */
void TypeCheck::visit(ClassList* node) {
  for(auto cls : node->getChildren()) {
    cls->accept(this);
  }
}

/**
 * Typecheck Dispatch
 */
void TypeCheck::visit(Dispatch* node) {
  node->getID()->accept(this);

  if(node->getExpr() != nullptr) {
    node->getExpr()->accept(this);
  }

  if(node->getType() != nullptr) {
    node->getType()->accept(this);
  }

  if(node->getExprList() != nullptr) {
    node->getExprList()->accept(this);
  }
}

/**
 * Typecheck ListFormalDeclare
 */
void TypeCheck::visit(ListFormalDeclare* node) {
  for(auto decl : node->getList()) {
    decl->accept(this);
  }
}

/**
 * Typecheck Feature
 */
void TypeCheck::visit(Feature* node) {
  node->getID()->accept(this);
  node->getType()->accept(this);
  node->getExpr()->accept(this);

  if(node->getList() != nullptr) {
    node->getList()->accept(this);
  }
}

/**
 * Typecheck FeatureOption
 */
void TypeCheck::visit(FeatureOption* node) {
  if(node->getFeat() != nullptr) {
    node->getFeat()->accept(this);
  }

  if(node->getForm() != nullptr) {
    node->getForm()->accept(this);
  }
}

/**
 * Typecheck FeatureList
 */
void TypeCheck::visit(FeatureList* node) {
  for(auto feature : node->getList()) {
    feature->accept(this);
  }
}
