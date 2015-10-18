#include "typecheck/visitor_tc.h"
using namespace bake_tc;

/** Visit functions for AST nodes that have a corresponding node in the symbol tree.
    That is, nodes that have their own scope. **/

// visit each item
void TypeCheck::visit(LetStatement*) {
  
}
void TypeCheck::visit(ClassStatement*) {
  
}
void TypeCheck::visit(Feature*) {
  
}

/** Terminal nodes **/

// set tmp type as INT
void TypeCheck::visit(IntegerVal*) {
  
}
// set tmp type as FLOAT
void TypeCheck::visit(FloatVal*) {
  
}
// set tmp type as INT8VAL
void visit(Int8Val*) {

}
// set tmp type as INT64VAL
void visit(Int64Val*) {

}
// set tmp type as STR
void TypeCheck::visit(StringVal*) {
  
}
// set tmp type as BOOL
void TypeCheck::visit(BoolVal*) {
  
}
// needs to do a lookup of type and set tmp variable
void TypeCheck::visit(Id*) {
  
}
// needs to set tmp variable
void TypeCheck::visit(Type*) {
  
}

/** Unary Operators **/
// check for boolean
void TypeCheck::visit(LogicalNot*) {
  
}
// check for int?
void TypeCheck::visit(BitNot*) {
  
}
// check for variable
void TypeCheck::visit(Isvoid*) {
  
}
void TypeCheck::visit(New*) {
  
}

/** Binary Operators **/
// visit left and get type
// visit right and get type
// check types

void TypeCheck::visit(Plus*) {
  
}
void TypeCheck::visit(Minus*) {
  
}
void TypeCheck::visit(Multiply*) {
  
}
void TypeCheck::visit(Divide*) {
  
}
// set tmp as bool
void TypeCheck::visit(LessThan*) {
  
}
// set tmp as bool
void TypeCheck::visit(LessThanEqual*) {
  
}
// set tmp as bool
void TypeCheck::visit(Equal*) {
  
}
void TypeCheck::visit(Assign*) {
  
}

/** Miscellaneous other nodes **/

void TypeCheck::visit(ExprList*) {
  
}
// check to make sure final expression is bool
void TypeCheck::visit(WhileLoop*) {
  
}
// check to make sure if is bool
void TypeCheck::visit(IfStatement*) {
  
}

// visit each item
void TypeCheck::visit(CaseStatement*) {
  
}
// visit each item
void TypeCheck::visit(CaseList*) {
  
}

void TypeCheck::visit(Case*) {
  
}
void TypeCheck::visit(FormalDeclare*) {
  
}

// visit each item.
void TypeCheck::visit(ClassList*) {
  
}
void TypeCheck::visit(Dispatch*) {
  
}
void TypeCheck::visit(ListFormalDeclare*) {
  
}

void TypeCheck::visit(FeatureOption*) {
  
}
void TypeCheck::visit(FeatureList*) {
  
}

bool TypeCheck::checkVals() {
  return true; // Placeholder
}