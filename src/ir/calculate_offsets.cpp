
#include <iostream>
#include <string>
#include "ir/calculate_offsets.h"
#include "ast/ast.h"

/**
 * Create IR root and forward visitor
 */
void ir::CalcOffsets::visit(bake_ast::ClassList* n) {
  class_list = new ir::ClassList();

  for(auto child : n->getChildren()) {
    /* Get class info (name) */
    std::string id = *child->getType()->getName();

    /* Create class definition */
    ir::ClassDef* cls = new ir::ClassDef(id);
    class_list->addClass(id, cls);
    cls->setAst(child);

    /* State that we are currently inspecting a class */
    scope_type = INCLASS;
    cur_class = cls;

    /* Forward to the actual class */
    child->accept(this);
  }
}

/**
 * Assign virtual offsets for definitions in ClassStatement nodes
 */
void ir::CalcOffsets::visit(bake_ast::ClassStatement* n) {
  /* Copy superclass into this class */
  if(n->getScope()->getSuper() != nullptr) {
    n->getScope()->getSuperObj()->getAst()->accept(this); // Forward this visitor back up to the super class
                                                          // Note that because cur_class is the new class, the visitor will
                                                          // save into this class, not the super. Not efficient, but easy.
  }

  scope_type = INCLASS;

  /* Forward visitor */
  if(n->getList() != nullptr) {
    n->getList()->accept(this);
  }
}

/**
 * Assign virtual offsets for definitions in Feature nodes
 */
void ir::CalcOffsets::visit(bake_ast::Feature* n) {
  /* Get method details (name) */
  std::string id = *n->getID()->getName();

  /* Create new method object */
  scope_type = INMETHOD;
  Method* method = new Method(id);
  cur_method = method;
  method->setAst(n);

  /* Add to list of methods */
  cur_class->addMethod(method);

  /* Forward to parameter list */
  if(n->getList() != nullptr) {
    n->getList()->accept(this);
  }

  n->getExpr()->accept(this);
}

/**
 * Assign virtual offsets for definitions in LetStatement nodes
 */
void ir::CalcOffsets::visit(bake_ast::LetStatement* n) {

  ScopeType prev_type = scope_type;
  scope_type = INLET;

  bake_ast::LetStatement* prev_let = cur_let;
  cur_let = n;

  n->getList()->accept(this);
  n->getExpr()->accept(this);

  scope_type = prev_type;
  cur_let = prev_let;
}

/**
 * Create new variable for the given scope
 */
void ir::CalcOffsets::visit(bake_ast::FormalDeclare* n) {
  /* Get the details for this var (name, type) */
  std::string id = *n->getID()->getName();
  std::string type = *n->getType()->getName();

  int size; // Will hold the size that this variable needs to have allocated
  if(type_sizes.find(type) == type_sizes.end()) { // If not found in list of explicit sizes, assume pointer
    size = 8;
  } else {
    size = type_sizes[type];
  }

  if(scope_type == INCLASS) {
    cur_class->addAttr(size);
    cur_class->getAst()->getScope()->setAttrOffset(id, cur_class->getAttrs().size());
  } else if(scope_type == INMETHOD) {
    cur_method->addStackVar(size);
    cur_method->getAst()->getScope()->setStackOffset(id, cur_method->getStackVars().size());
  } else if(scope_type == INLET) {
    cur_method->addStackVar(size);
    cur_let->getScope()->setLVarOffset(id, cur_method->getStackVars().size());
  }
}

/**
 * Forward visitor through FeatureList nodes
 */
void ir::CalcOffsets::visit(bake_ast::FeatureList* n) {
  for(auto el : n->getList()) {
    el->accept(this);
  }
}

/**
 * Forward visitor through FeatureOption nodes
 */
void ir::CalcOffsets::visit(bake_ast::FeatureOption* n) {
  if(n->getFeat() != nullptr) {
    n->getFeat()->accept(this);
  }else if(n->getForm() != nullptr) {
    n->getForm()->accept(this);
  }
}

/**
 * Forward visitor through ListFormalDeclare nodes
 */
void ir::CalcOffsets::visit(bake_ast::ListFormalDeclare* n) {
  for(auto var : n->getList()) {
    var->accept(this);
  }
}

/**
 * Forward visitor through ExprList nodes
 */
void ir::CalcOffsets::visit(bake_ast::ExprList* n) {
  for(auto expr : n->getChildren()) {
    expr->accept(this);
  }
}

/**
 * Forward visitor through LogicalNot nodes
 */
void ir::CalcOffsets::visit(bake_ast::LogicalNot* n) {
  n->get()->accept(this);
}

/**
 * Forward visitor through BitNot nodes
 */
void ir::CalcOffsets::visit(bake_ast::BitNot* n) {
  n->get()->accept(this);
}

/**
 * Forward visitor through Isvoid nodes
 */
void ir::CalcOffsets::visit(bake_ast::Isvoid* n) {
  n->get()->accept(this);
}

/**
 * Forward visitor through New nodes
 */
void ir::CalcOffsets::visit(bake_ast::New* n) {
  n->get()->accept(this);
}


/**
 * Forward visitor through Plus nodes
 */
void ir::CalcOffsets::visit(bake_ast::Plus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through Minus nodes
 */
void ir::CalcOffsets::visit(bake_ast::Minus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through Multiply nodes
 */
void ir::CalcOffsets::visit(bake_ast::Multiply* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through Divide nodes
 */
void ir::CalcOffsets::visit(bake_ast::Divide* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through LessThan nodes
 */
void ir::CalcOffsets::visit(bake_ast::LessThan* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through LessThanEqual nodes
 */
void ir::CalcOffsets::visit(bake_ast::LessThanEqual* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through Equal nodes
 */
void ir::CalcOffsets::visit(bake_ast::Equal* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through Assign nodes
 */
void ir::CalcOffsets::visit(bake_ast::Assign* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
}

/**
 * Forward visitor through WhileLoop
 */
void ir::CalcOffsets::visit(bake_ast::WhileLoop* n) {
  n->getCond()->accept(this);
  n->getBody()->accept(this);
}

/**
 * Forward visitor through IfStatement nodes
 */
void ir::CalcOffsets::visit(bake_ast::IfStatement* n) {
  n->getCond()->accept(this);
  n->getBody()->accept(this);
  n->getElseBody()->accept(this);
}

/**
 * Forward visitor through CaseStatement nodes
 */
void ir::CalcOffsets::visit(bake_ast::CaseStatement* n) {
  n->getExpr()->accept(this);
  n->getCaseList()->accept(this);
}

/**
 * Forward visitor through CaseList nodes
 */
void ir::CalcOffsets::visit(bake_ast::CaseList* n) {
  for(auto el : n->getList()) {
    el->accept(this);
  }
}

/**
 * Forward visitor through Case nodes
 */
void ir::CalcOffsets::visit(bake_ast::Case* n) {
  n->getID()->accept(this);
  n->getType()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }
}

/**
 * Forward visitor through Dispatch nodes
 */
void ir::CalcOffsets::visit(bake_ast::Dispatch* n) {
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