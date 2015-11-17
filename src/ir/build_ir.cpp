
#include "ir/build_ir.h"
#include "ast/ast.h"
#include "ir/class_list.h"

/******************/
/* Terminal nodes */

/**
 * Generate IR code for IntegerVal
 */
void ir::BuildIR::visit(bake_ast::IntegerVal*) {
    
}

/**
 * Generate IR code for Int8Val
 */
void ir::BuildIR::visit(bake_ast::Int8Val*) {

}

/**
 * Generate IR code for Int64Val
 */
void ir::BuildIR::visit(bake_ast::Int64Val*) {

}

/**
 * Generate IR code for FloatVal
 */
void ir::BuildIR::visit(bake_ast::FloatVal*) {

}

/**
 * Generate IR code for StringVal
 */
void ir::BuildIR::visit(bake_ast::StringVal*) {

}

/**
 * Generate IR code for BoolVal
 */
void ir::BuildIR::visit(bake_ast::BoolVal*) {

}

/**
 * Generate IR code for Id
 */
void ir::BuildIR::visit(bake_ast::Id*) {

}

/**
 * Generate IR code for Type
 */
void ir::BuildIR::visit(bake_ast::Type*) {

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

  int size; // Will hold the size that this variable needs to have allocated
  if(type_sizes.find(*n->getType()->getName()) == type_sizes.end()) { // If not found in list of explicit sizes, assume pointer
    size = 8;
  } else {
    size = type_sizes[*n->getType()->getName()];
  }

  if(not in_method) { // Check if we are in a class. If so, add this as an attribute.
    curr_class->addAttr(size);
  }
}

/**
 * Generate IR code for ClassStatement
 */
void ir::BuildIR::visit(bake_ast::ClassStatement* n) {
  n->getType()->accept(this);

  std::string class_name = *n->getType()->getName();
  ir::ClassDef* this_class = new ClassDef(class_name);

  setCurrClass(this_class);
  classlist->addClass(class_name, this_class);

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
  classlist = new ir::ClassList();

  for(auto child : n->getChildren()) {
    child->accept(this);
  }
}

/**
 * Generate IR code for Dispatch
 */
void ir::BuildIR::visit(bake_ast::Dispatch* n) {
  n->getID()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }

  if(n->getType() != nullptr) {
    n->getType()->accept(this);
  }

  if(n->getExprList() != nullptr) {
    n->getExprList()->accept(this);
  }
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
  in_method = true; // State that we are currently generating code for a method.

  /* Create first basic block for this method */
  curr_bb = new ir::BasicBlock();
  curr_class->addMethod(curr_bb);

  n->getID()->accept(this);

  if(n->getList() != nullptr) {
    n->getList()->accept(this);
  }

  n->getType()->accept(this);
  n->getExpr()->accept(this);

  in_method = false; // State that we're no longer in the method
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
