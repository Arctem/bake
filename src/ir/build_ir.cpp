
#include <iostream>
#include "ir/build_ir.h"
#include "ast/ast.h"
#include "ir/class_list.h"
#include "ir/calculate_offsets.h"

/**
 * Constructor.
 * Generates the virtual offsets then automatically runs the BuildIR visitor
 */
ir::BuildIR::BuildIR(bake_ast::ClassList* ast_root) {
  /* Assign virtual offsets */
  ir::CalcOffsets offset_visitor;
  offset_visitor.visit(ast_root);

  classlist = offset_visitor.getClassList();

  /* Build the IR */
  visit(ast_root);
}

/**
 * Deconstructor
 */
 ir::BuildIR::~BuildIR(){
   if(classlist != nullptr){
     delete classlist;
   }
 }

/******************/
/* Terminal nodes */

/**
 * Generate IR code for IntegerVal
 */
void ir::BuildIR::visit(bake_ast::IntegerVal* n) {
    throwup = getRegCount();
    curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), std::make_pair(throwup, INT)));
}

/**
 * Generate IR code for Int8Val
 */
void ir::BuildIR::visit(bake_ast::Int8Val* n) {
  throwup = getRegCount();
  curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), std::make_pair(throwup, INT8)));
}

/**
 * Generate IR code for Int64Val
 */
void ir::BuildIR::visit(bake_ast::Int64Val* n) {
  throwup = getRegCount();
  curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), std::make_pair(throwup, INT64)));
}

/**
 * Generate IR code for FloatVal
 */
void ir::BuildIR::visit(bake_ast::FloatVal* n) {
  // TODO Float away
}

/**
 * Generate IR code for StringVal
 */
void ir::BuildIR::visit(bake_ast::StringVal* n) {
  /* Get the string itself */
  string value = *n->getValue();
  int str_len = value.length();

  /* Find string size */
  int size = classlist->getClasses()["String"]->recordSize() + str_len * 8; // Get string size
  size -= 64; // Remove excess space due to placeholder variable in the AST

  /* Allocate for the string */
  int strLoc = reserveReg();
  ir::CreateObj* cobj = new ir::CreateObj("String", size, std::make_pair(strLoc, INT64));
  curr_bb->addOp(cobj);

  /* Reserve register for storing character to save to memory. */
  int charReg = reserveReg();

  /* Copy each character into memory */
  int offset = 0;
  for(auto chr : value) {
    ir::Copy* copy = new Copy(std::make_pair((int) chr, CONSTANT), std::make_pair(charReg, INT8));
    curr_bb->addOp(copy);

    ir::StoreI* schar = new ir::StoreI(std::make_pair(charReg, INT8), std::make_pair(strLoc, INT8), offset);
    curr_bb->addOp(schar);

    offset += 8;
  }

  /* Add null terminator */
  ir::Copy* copy = new Copy(std::make_pair(0, CONSTANT), std::make_pair(charReg, INT8));
  curr_bb->addOp(copy);

  ir::StoreI* schar = new ir::StoreI(std::make_pair(charReg, INT8), std::make_pair(strLoc, INT8), offset);
  curr_bb->addOp(schar);
}

/**
 * Generate IR code for BoolVal
 */
void ir::BuildIR::visit(bake_ast::BoolVal* n) {
  throwup = getRegCount();

  if(n->getValue() == true){
    curr_bb->addOp(new Copy(std::make_pair(1, CONSTANT), std::make_pair(throwup, BOOL)));
  }else if(n->getValue() == false){
    curr_bb->addOp(new Copy(std::make_pair(0, CONSTANT), std::make_pair(throwup, BOOL)));
  }

}

/**
 * Generate IR code for Id
 */
void ir::BuildIR::visit(bake_ast::Id* n) {

}

/**
 * Generate IR code for Type
 */
void ir::BuildIR::visit(bake_ast::Type* n) {

}

/*******************/
/* Unary Operators */

/**
 * Generate IR code for LogicalNot
 */
void ir::BuildIR::visit(bake_ast::LogicalNot* n) {
  n->get()->accept(this);
}

/**
 * Generate IR code for BitNot
 */
void ir::BuildIR::visit(bake_ast::BitNot* n) {
  n->get()->accept(this);
}

/**
 * Generate IR code for Isvoid
 */
void ir::BuildIR::visit(bake_ast::Isvoid* n) {
  n->get()->accept(this);
}

/**
 * Generate IR code for New
 */
void ir::BuildIR::visit(bake_ast::New* n) {
  n->get()->accept(this);
}

/********************/
/* Binary Operators */

/**
 * Generate IR code for Plus
 */
void ir::BuildIR::visit(bake_ast::Plus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for Minus
 */
void ir::BuildIR::visit(bake_ast::Minus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for Multiply
 */
void ir::BuildIR::visit(bake_ast::Multiply* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for Divide
 */
void ir::BuildIR::visit(bake_ast::Divide* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for LessThan
 */
void ir::BuildIR::visit(bake_ast::LessThan* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for LessThanEqual
 */
void ir::BuildIR::visit(bake_ast::LessThanEqual* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for Equal
 */
void ir::BuildIR::visit(bake_ast::Equal* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Generate IR code for Assign
 */
void ir::BuildIR::visit(bake_ast::Assign* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/********/
/* Misc */

/**
 * Generate IR code for ExprList
 */
void ir::BuildIR::visit(bake_ast::ExprList* n) {
  for(auto child : n->getChildren()) {
    child->accept(this);
  }
}

/**
 * Generate IR code for WhileLoop
 */
void ir::BuildIR::visit(bake_ast::WhileLoop* n) {
  n->getCond()->accept(this);
  n->getBody()->accept(this);
}

/**
 * Generate IR code for IfStatement
 */
void ir::BuildIR::visit(bake_ast::IfStatement* n) {
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  n->getElseBody()->accept(this);
}

/**
 * Generate IR code for LetStatement
 */
void ir::BuildIR::visit(bake_ast::LetStatement* n) {
  n->getList()->accept(this); // Forward the visitor
  n->getExpr()->accept(this); // Forward to substatements
}

/**
 * Generate IR code for CaseStatement
 */
void ir::BuildIR::visit(bake_ast::CaseStatement* n) {
  n->getExpr()->accept(this);
  n->getCaseList()->accept(this);
}

/**
 * Generate IR code for CaseList
 */
void ir::BuildIR::visit(bake_ast::CaseList* n) {
  for(auto el : n->getList()) {
    el->accept(this);
  }
}

/**
 * Generate IR code for Case
 */
void ir::BuildIR::visit(bake_ast::Case* n) {
  n->getID()->accept(this);
  n->getType()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }
}

/**
 * Generate IR code for FormalDeclare
 */
void ir::BuildIR::visit(bake_ast::FormalDeclare* n) {
  n->getID()->accept(this);
  n->getType()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }
}

/**
 * Generate IR code for ClassStatement
 */
void ir::BuildIR::visit(bake_ast::ClassStatement* n) {
  n->getType()->accept(this);

  std::string class_name = *n->getType()->getName();
  curr_class = classlist->getClasses()[class_name];

  if(n->getInheritType() != nullptr) {
    n->getInheritType()->accept(this);
  }

  if(n->getList() != nullptr) {
    n->getList()->accept(this);
  }
}

/**
 * Generate IR code for ClassList
 */
void ir::BuildIR::visit(bake_ast::ClassList* n) {
  /* Get main class and main method */
  ir::ClassDef* main_class = classlist->getClasses()["Main"];
  int virtual_offset = main_class->getAst()->getScope()->getMethodOffsets()["main"];
  curr_bb = main_class->getMethods()[virtual_offset];

  for(auto child : n->getChildren()) {
    child->accept(this);
  }
}

/**
 * Generate IR code for Dispatch
 */
void ir::BuildIR::visit(bake_ast::Dispatch* n) {
  string id = *n->getID()->getName();
  if(id == "out_string") {
    visitOutstring(n);
    return;
  }

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }

  if(n->getExprList() != nullptr) {
    n->getExprList()->accept(this);
  }
}

/**
 * Generate IR code for printing a string
 */
void ir::BuildIR::visitOutstring(bake_ast::Dispatch* n) {
  n->getExprList()->accept(this); // First, forward to the parameter list to get the string we need to print
  int string_reg = throwup;

  ir::OutString* os = new ir::OutString(std::make_pair(string_reg, REF), std::make_pair(-1, EMPTY));
  curr_bb->addOp(os);
}

/**
 * Generate IR code for ListFormalDeclare
 */
void ir::BuildIR::visit(bake_ast::ListFormalDeclare* n) {
  for(auto decl : n->getList()) {
    decl->accept(this);
  }
}

/**
 * Generate IR code for Feature
 */
void ir::BuildIR::visit(bake_ast::Feature* n) {
  if(n->getList() != nullptr) {
    n->getList()->accept(this);
  }

  n->getType()->accept(this);
  n->getExpr()->accept(this);
}

/**
 * Generate IR code for FeatureOption
 */
void ir::BuildIR::visit(bake_ast::FeatureOption* n) {
  if(n->getFeat() != nullptr) {
    n->getFeat()->accept(this);
  }

  if(n->getForm() != nullptr) {
    n->getForm()->accept(this);
  }
}

/**
 * Generate IR code for FeatureList
 */
void ir::BuildIR::visit(bake_ast::FeatureList* n) {
  for(auto feature : n->getList()) {
    feature->accept(this);
  }
}
