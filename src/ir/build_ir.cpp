
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

    /* Updates to the next register and copies constant to the register */
    int reg = getRegCount();
    throwup = std::make_pair(reg, INT);
    curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), throwup));
}

/**
 * Generate IR code for Int8Val
 */
void ir::BuildIR::visit(bake_ast::Int8Val* n) {

  /* Updates to the next register and copies constant to the register */
  int reg = getRegCount();
  throwup = std::make_pair(reg, INT8);
  curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), throwup));
}

/**
 * Generate IR code for Int64Val
 */
void ir::BuildIR::visit(bake_ast::Int64Val* n) {

  /* Updates to the next register and copies constant to the register */
  int reg = getRegCount();
  throwup = std::make_pair(reg, INT64);
  curr_bb->addOp(new Copy(std::make_pair(n->getValue(), CONSTANT), throwup));
}

/**
 * Generate IR code for FloatVal
 */
void ir::BuildIR::visit(bake_ast::FloatVal* n) {
  // TODO Floats will be implemented as a feature in a later version
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
  int reg = getRegCount();    // Updates to the next register, and sends up to next node
  throwup = std::make_pair(reg, BOOL);
  /* Converts boolean ot c-style boolean and copies to a register */
  if(n->getValue() == true){
    curr_bb->addOp(new Copy(std::make_pair(1, CONSTANT), throwup));
  }else if(n->getValue() == false){
    curr_bb->addOp(new Copy(std::make_pair(0, CONSTANT), throwup));
  }

}

/**
 * Generate IR code for Id
 */
void ir::BuildIR::visit(bake_ast::Id* n) {

    int voff;                            // virtual offset
    string var = *n->getName();          // name of the variable
    int reg;

    // Check to see if the method has a SymbolAnon (let or a case) that we are in
    if(scopeFlag == ANON){
      SymbolAnon* temp_scope = symbolAnon;  // if so get the current scope

      // Check each scope for the variable until we hit the top of the method (no more lets or cases)
      do {

          // If var is in this scope, copy to a register and throwup
          if(temp_scope->getMembers().find(var) != temp_scope->getMembers().end()){
              voff = temp_scope->getLVarOffsets()[var];
              reg = getRegCount();    // Updates to the next register, and sends up to next node
              throwup = std::make_pair(reg, LOCALADDR);
              curr_bb->addOp(new Copy(std::make_pair(voff, INT64), throwup));
              return;
            }

            // Other wise move up the scope
      } while(temp_scope->getLexParent() != symbolMethod);
    }

    // If var is in the Method Parameter, copy to a register and throwup
    if(symbolMethod->getParams().find(var) != symbolMethod->getParams().end()){
        voff = symbolMethod->getStackOffsets()[var];
        reg = getRegCount();    // Updates to the next register, and sends up to next node
        throwup = std::make_pair(reg, LOCALADDR);
        curr_bb->addOp(new Copy(std::make_pair(voff, INT64), throwup));
        return;
    }

    // If var is in the Class Attribute Scope, copy to a register and throwup
    if(classNode->getMembers().find(var) != classNode->getMembers().end()){
        voff = classNode->getAttrOffsets()[var];
        reg = getRegCount();    // Updates to the next register, and sends up to next node
        throwup = std::make_pair(reg, ATTRADDR);
        curr_bb->addOp(new Copy(std::make_pair(voff, INT64), throwup));
        return;
    }

}

/**
 * Generate IR code for Type
 */
void ir::BuildIR::visit(bake_ast::Type* n) {
  // These are calculated in calculated_offsets, do nothing
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

  // just check if null, return 1 if true, 0 if false
  // coordinate this with the while loop though
}

/**
 * Generate IR code for New
 */
void ir::BuildIR::visit(bake_ast::New* n) {

  // gather TYPE name by hand (one down on the AST)
  // getClasses()
  // index this off the name of the TYPE
  // Call recordSize, this returns number of bits for the object
  // createObj to instruction list
  // create register, throwup, blah, blah, blah

}

/********************/
/* Binary Operators */

/**
 * Generate IR code for Plus
 */
void ir::BuildIR::visit(bake_ast::Plus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // If address, load it
  // do binary op
  // throwup the registers
}

/**
 * Generate IR code for Minus
 */
void ir::BuildIR::visit(bake_ast::Minus* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // If address, load it
  // do binary op
  // throwup the registers

}

/**
 * Generate IR code for Multiply
 */
void ir::BuildIR::visit(bake_ast::Multiply* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // If address, load it
  // do binary op
  // throwup the registers
}

/**
 * Generate IR code for Divide
 */
void ir::BuildIR::visit(bake_ast::Divide* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  // grab registers from both sides
  // If address, load it
  // do binary op
  // throwup the registers
}

/**
 * Generate IR code for LessThan
 */
void ir::BuildIR::visit(bake_ast::LessThan* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // If address, load it
  // add the cmp to op
  // throwup the registers


}

/**
 * Generate IR code for LessThanEqual
 */
void ir::BuildIR::visit(bake_ast::LessThanEqual* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // If address, load it
  // add the cmp to op
  // throwup the registers
}

/**
 * Generate IR code for Equal
 */
void ir::BuildIR::visit(bake_ast::Equal* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // grab registers from both sides
  // do a reverse lookup from address to variable type in ST
  // if TYPE is bool or _Num (ignore floats for now)
    // load values from thrown up registers
    // cmp with values
  // if Type is String
    // Figure out later
  // If Type is anything else
    // cmp with throwun up registers (memory address)
  // throwup the registers
}

/**
 * Generate IR code for Assign
 */
void ir::BuildIR::visit(bake_ast::Assign* n) {
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);

  // check if rhs register is a constant or an address
  // if address load the value
  // store rhs in lhs (using register address)
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

  // we will need two BB due to while loops conditions at top
    // one BB to the bod

  // create a new BB
  // br on false itself
  // br on true goes to next basic BasicBlock
  // set curr_bb to the next basic block here
  // visit ccurr_bb
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

  /* Change the scope to this method */
  scopeFlag = ANON;
  symbolAnon = n->getScope();

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

  //TODO - this code wasn't implemented int eh AST
  /* Change the scope to this method */
  //scopeFlag = ANON;
  //symbolAnon = n->getScope();

  //n->getID()->accept(this);
  n->getType()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }
}

/**
 * Generate IR code for FormalDeclare
 */
void ir::BuildIR::visit(bake_ast::FormalDeclare* n) {
  //n->getID()->accept(this);
  n->getType()->accept(this);

  if(n->getExpr() != nullptr) {
    n->getExpr()->accept(this);
  }

  // TODO how to deal with initliation i.e. x : Int <- 1
    // throwup the register address
    // But, how do we do this for every new object
}

/**
 * Generate IR code for ClassStatement
 */
void ir::BuildIR::visit(bake_ast::ClassStatement* n) {

  /* Change the scope to this class */
  scopeFlag = CLASS;
  classNode = n->getScope();

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
  } else if(id == "out_int") {
    visitOutint(n);
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
  int string_reg = throwup.first;

  ir::OutString* os = new ir::OutString(std::make_pair(string_reg, REF), std::make_pair(-1, EMPTY));
  curr_bb->addOp(os);
}

/**
 * Generate IR code for printing an int
 */
void ir::BuildIR::visitOutint(bake_ast::Dispatch* n) {
  n->getExprList()->accept(this); // First, forward to the parameter list to get the string we need to print
  int out_reg = throwup.first;

  ir::OutInt* os = new ir::OutInt(std::make_pair(out_reg, REF), std::make_pair(-1, EMPTY));
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

  /* Change the scope to this method */
  scopeFlag = METHOD;
  symbolMethod = n->getScope();

  string name = *n->getID()->getName();
  int voff = curr_class->getAst()->getScope()->getMethodOffsets()[name];
  curr_method = curr_class->getMethods()[voff];

  if(n->getList() != nullptr) {
    n->getList()->accept(this);       // Method Parameters
  }

  n->getType()->accept(this);         // Return TYPE TODO: This is wasted code here i believe
  n->getExpr()->accept(this);         // Body of the method
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
