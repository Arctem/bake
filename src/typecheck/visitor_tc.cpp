#include <string.h>
#include <sstream>
using namespace std;
#include "iostream"

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

/**
 * symbol table lookup of Id
 */
void TypeCheck::visit(Id* id) {
  // check cur scope.
  // if it doesn't exist, check parent scopes
  
  // if self
  if(*(id->getName()) == "self") {
    id->setInfType(curClass.c_str());
    setTypeOfLast(id->getInfType());
  }
  // Symbol Method
  else if(curScope->getType() == SYMBOLMETHOD) {
    SymbolMethod* cur = (SymbolMethod*) curScope;
    
    try{
      string typeName = cur->getParams().at(*(id->getName()));
      // if its self type, resolve it
      if(typeName == "SELF_TYPE") {
        id->setInfType(curClass.c_str());
      } else {
        id->setInfType(typeName.c_str());
      }
      setTypeOfLast(id->getInfType());
    }
    catch(std::out_of_range oor) { // otherwise, try and find it more
      SymbolNode* tmp = curScope;  // save the current scope
      
      typeOfLast = nullptr;
      curScope = curScope->getLexParent();
      
      visit(id);
      curScope = tmp; // set scope back to normal
      // if found, return
      if(typeOfLast != nullptr)
        return;
      
      stringstream msg;
      msg << "Error: Variable '" << *(id->getName()) << "' doesn't exist.";

      throw TypeErr(msg.str().c_str());
    }
  }
  // SymbolAnon (let statements, etc)
  else if(curScope->getType() == SYMBOLANON) {
    SymbolAnon* cur = (SymbolAnon*)curScope;

    // check if it exists, if it does, return it
    try{
      string typeName = cur->getMembers().at(*(id->getName()));
      // if its self type, resolve it
      if(typeName == "SELF_TYPE") {
        id->setInfType(curClass.c_str());
      } else {
        id->setInfType(typeName.c_str());
      }
      setTypeOfLast(id->getInfType());
    }
    catch(std::out_of_range oor) { // otherwise, try and find it more
      SymbolNode* tmp = curScope;  // save the current scope
      
      typeOfLast = nullptr;
      curScope = curScope->getLexParent();
      
      visit(id);
      curScope = tmp; // set scope back to normal
      // if found, return
      if(typeOfLast != nullptr)
        return;
      
      stringstream msg;
      msg << "Error: Variable '" << *(id->getName()) << "' doesn't exist.";

      throw TypeErr(msg.str().c_str());
    }
  }
  // Class
  else if(curScope->getType() == CLASSNODE) {
    ClassNode* cur = (ClassNode*) curScope;
    
    try {
      string typeName;
      //TODO: Not this
      if(cur->getMethods().find(*id->getName()) != cur->getMethods().end()) {
	      typeName = cur->getMethods().at(*(id->getName()))->getRetType();
      } else {
	      typeName = cur->getMembers().at(*(id->getName()));
      }
      // if its self type, resolve it
      if(typeName == "SELF_TYPE") {
        id->setInfType(curClass.c_str());
      } else {
        id->setInfType(typeName.c_str());
      }
      setTypeOfLast(id->getInfType());
    }
    catch(std::out_of_range oor) { // otherwise, try and find it more
      SymbolNode* tmp = curScope; // save the current scope
      
      typeOfLast = nullptr;
      if(cur->getSuper()) {
	      curScope = cur->getLexParent()->getClasses()[*cur->getSuper()];
      
	      visit(id);
      }
      curScope = tmp; // set scope back to normal
      // if found, return
      if(typeOfLast != nullptr)
        return;
      
      stringstream msg;
      msg << "Error: Item '" << *(id->getName()) << "' doesn't exist.";

      throw TypeErr(msg.str().c_str());
    }
  }
  // base case for recursion
  else
    return;
}

void TypeCheck::visit(Type* type){
  // check if self type
  if(*(type->getName()) == "SELF_TYPE"){
    type->setInfType(curClass.c_str());
    setTypeOfLast(type->getInfType());
  }
  // otherwise, make sure it eexists
  // goto groot, loop through for existential problems
  else{
    SymbolNode* tmp = curScope;
    while(tmp->getType() != GROOT){
      tmp = tmp->getLexParent();
    }
    for(auto c : ((Groot*)tmp)->getClasses()){
      if(c.first == *(type->getName())){
        type->setInfType(c.first.c_str());
        setTypeOfLast(type->getInfType());
        return;
      }
    }
    stringstream msg;
    msg << "Error: type '" << *(type->getName()) << "' doesn't exist.";

   throw TypeErr(msg.str().c_str());
  }
}

/********** Unary ops ************/

/**
 * Typecheck the logical not operator
 */
void TypeCheck::visit(LogicalNot* node) {
  node->setInfType("Bool"); // Return type is guaranteed to be a Bool
  setTypeOfLast(node->getInfType());

  /* Get the type of the expression */
  node->get()->accept(this);
  string* subtype = getTypeOfLast();

  /* Check type */
  if(*subtype != "Bool") {
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
  string* type = getTypeOfLast();
  
  if(isInt(type)){
    node->setInfType(type->c_str());
    setTypeOfLast(node->getInfType());
  }else{
    stringstream msg;
    msg << "Error: Bit not cannot operate on type '" << *type << "'";

    throw TypeErr(msg.str().c_str());
  }
}

/**
 * Typecheck the Isvoid operator
 */
void TypeCheck::visit(Isvoid* node) {
  node->setInfType("Bool"); // Return type is guaranteed to be a Bool
  setTypeOfLast(node->getInfType());

  /* Get the type of the expression */
  node->get()->accept(this);
}

/**
 * Typecheck the New operator
 */
void TypeCheck::visit(New* node) {
  node->get()->accept(this);
  node->setInfType(getTypeOfLast()->c_str()); 
  setTypeOfLast(node->getInfType());
}



/********** Binary ops ************/

/**
 * Typecheck the addition operator
 */
void TypeCheck::visit(Plus* node) {
  string* l;
  string* r;
  const char* result;

  // recursion through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // check if they are valid
  result = numOrder(l,r);

  // bad type(s)
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Addition cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType(result);
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the subtraction operator
 */
void TypeCheck::visit(Minus* node) {
  string* l;
  string* r;
  const char* result;

  // recursion through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // check if they are valid
  result = numOrder(l,r);

  // bad type(s)
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Subtraction cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType(result);
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the multiplication operator
 */
void TypeCheck::visit(Multiply* node) {
  string* l;
  string* r;
  const char* result;

  // recursion through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // check if they are valid
  result = numOrder(l,r);

  // bad type(s)
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Multiplication cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType(result);
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the division operator
 */
void TypeCheck::visit(Divide* node) {
  string* l;
  string* r;
  const char* result;

  // recursion through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // check if they are valid
  result = numOrder(l,r);

  // bad type(s)
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Division cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType(result);
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the < operator
 */
void TypeCheck::visit(LessThan* node) {
  string* l;
  string* r;
  const char* result;

  // Recurse through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // check which type to implicitly cast too.
  result = numOrder(l,r);

  // bad types
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Comparision cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType("Bool");
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the <= operator
 */
void TypeCheck::visit(LessThanEqual* node) {
  string* l;
  string* r;
  const char* result;

  // Recurse through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // If num
  result = numOrder(l,r);

  // bad types
  if(result == nullptr){
    stringstream msg;
    msg << "Error: Comparision cannot operate on '" << *l << "' and '" << *r <<"'";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType("Bool");
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the = operator
 */
void TypeCheck::visit(Equal* node) {
  string* l;
  string* r;
  const char* result;

  // Recurse through both sides
  node->getLhs()->accept(this);
  l = getTypeOfLast();

  node->getRhs()->accept(this);
  r = getTypeOfLast();

  // if number
  if(isNum(l) || isNum(r)){

      // Checks both are numbers and both valid
      if(numOrder(l,r) == nullptr){
        stringstream msg;
        msg << "Error: Eqaulity Comparision cannot operate on '" << *l << "' and a  '" << *r <<"'";

        throw TypeErr(msg.str().c_str());
      }

  } else if(*l == "String" || *r == "String"){
      if(!(*l == "String" && *r == "String")){
        stringstream msg;
        msg << "Error: Eqaulity Comparision '" << *l << "' and a  '" << *r <<" must both be strings";

        throw TypeErr(msg.str().c_str());
      }
  }else if(*l == "Bool" || *r == "Bool"){
      if(!(*l == "Bool" && *r == "Bool")){
        stringstream msg;
        msg << "Error: Eqaulity Comparision '" << *l << "' and a  '" << *r <<" must both be booleans";

        throw TypeErr(msg.str().c_str());
      }
  }

  // Good types!
  node->setInfType("Bool");
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck the <- operator
 */
void TypeCheck::visit(Assign* node) {
  node->getLhs()->accept(this);
  string* type = getTypeOfLast();
  node->getRhs()->accept(this);
  string* exprType = getTypeOfLast();
  
  /* Get the class node that corresponds to the type of the left and right sides */
  string* lhsType = node->getLhs()->getInfType();
  string* rhsType = node->getRhs()->getInfType();
  ClassNode* rhsClass = groot->getClasses()[*node->getRhs()->getInfType()];

  if (canAssign(lhsType, rhsType)) {
    node->setInfType(lhsType->c_str());
  } else {
    stringstream msg;
    msg << "RHS (type: '" << *rhsType << "') is not a subclass of the LHS (type: '" << *lhsType << "')";
    throw TypeErr(msg.str().c_str());
  }
}


/********** Misc ops ************/

/**
 * Typecheck ExprList
 */
void TypeCheck::visit(ExprList* node) {
  string* x;

  for(auto child : node->getChildren()) {
    child->accept(this);
  }

  x = getTypeOfLast();

  // Good types!
  node->setInfType(x->c_str());
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck WhileLoop
 */
void TypeCheck::visit(WhileLoop* node) {
  string* cond;

  // Get the condition and body
  node->getCond()->accept(this);
  cond = getTypeOfLast();

  // Since this doesn't save we just need to recurse through
  node->getBody()->accept(this);

  if(*cond != "Bool"){
    stringstream msg;
    msg << "Error: While condition must be a Boolean Expression not " << *cond << "";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType("Object");
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck IfStatement
 */
void TypeCheck::visit(IfStatement* node) {
  string* cond;
  string* bodyExpr;
  string* elseExpr;

  node->getCond()->accept(this);
  cond = getTypeOfLast();

  node->getBody()->accept(this);
  bodyExpr = getTypeOfLast();

  node->getElseBody()->accept(this);
  elseExpr = getTypeOfLast();

  if(*cond != "Bool"){
    stringstream msg;
    msg << "Error: If condition must be a Boolean Expression not " << *cond << "";

    throw TypeErr(msg.str().c_str());
  }

  if(*bodyExpr != *elseExpr){
    stringstream msg;
    msg << "Error: If statements cannot operate on '" << *bodyExpr << "' in the body and   '" << *elseExpr <<" in the else '";

    throw TypeErr(msg.str().c_str());
  }

  // Good types!
  node->setInfType(bodyExpr->c_str());
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck LetStatement
 * *** New Scope ***
 */
void TypeCheck::visit(LetStatement* node) {
  string* type;
  // set new scope
  // can come from a let (SymbolAnon) or a method (SymbolMethod)
  if(curScope->getType() == SYMBOLMETHOD) {
    curScope = ((SymbolMethod*) curScope)->nextMem();
  } else { // SymbolAnon
    curScope = ((SymbolAnon*) curScope)->nextMem();
  }

  // visit expr and set the return type
  node->getExpr()->accept(this);

  type = getTypeOfLast();
  node->setInfType(type->c_str());
  setTypeOfLast(node->getInfType());

  node->getList()->accept(this);

  // exit scope
  curScope = curScope->getLexParent();
}

/**
 * Typecheck CaseStatement
 */
void TypeCheck::visit(CaseStatement* node) {
  string* type;
  node->getExpr()->accept(this);
  node->getCaseList()->accept(this);
  type = getTypeOfLast();
  // Good types!
  node->setInfType(type->c_str());
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck CaseList
 */
void TypeCheck::visit(CaseList* node) {
  for(auto cse : node->getList()) {
    cse->accept(this);
  }

  // TODO: Need find which is the highest possible parent
  node->setInfType("Object");
  setTypeOfLast(node->getInfType());
}

/**
 * Typecheck Case
 */
void TypeCheck::visit(Case* node) {
  // set new scope
  // can come from a let (SymbolAnon) or a method (SymbolMethod)
  if(curScope->getType() == SYMBOLMETHOD) {
    curScope = ((SymbolMethod*) curScope)->nextMem();
  } else { // SymbolAnon
    curScope = ((SymbolAnon*) curScope)->nextMem();
  }
  
  string* type;
  node->getID()->accept(this);
  node->getType()->accept(this);

  node->getExpr()->accept(this);

  type = getTypeOfLast();

  // Good types!
  node->setInfType(type->c_str());
  setTypeOfLast(node->getInfType());

  //exit scope
  curScope = curScope->getLexParent();
}

/**
 * Typecheck FormalDeclare
 * If an attibute see if ID has ever been named in the inheritance tree before hand.
 * Either way make sure that rhs => lhs
 */
void TypeCheck::visit(FormalDeclare* node) {
  // no need to visit the ID, its already in the symbol table.

  node->getType()->accept(this);
  string* type = getTypeOfLast();

  if(node->getExpr() != nullptr) {
    node->getExpr()->accept(this);
    string* exprType = getTypeOfLast();
    
    bool cani = canAssign(type, exprType);
    if(cani){
      node->setInfType(type->c_str());
      setTypeOfLast(node->getInfType());
    }
    else{
      SymbolNode* tmp = curScope;
      if(*type == *exprType){
        // done
        node->setInfType(type->c_str());
        setTypeOfLast(node->getInfType());
        return;
      }
      
      // get to groot
      while(tmp->getType() != GROOT){
        tmp = tmp->getLexParent();
      }
      try{
        ClassNode* cls = ((Groot*)tmp)->getClasses().at(*exprType);
        
        while(cls->getSuper() != nullptr){
          if(*(cls->getSuper()) == *type){
            node->setInfType(type->c_str());
            setTypeOfLast(node->getInfType());
            return;
          }
          cls = ((Groot*)tmp)->getClasses().at(*(cls->getSuper()));
        }
        if("Object" == *exprType){
          node->setInfType("Object");
          setTypeOfLast(node->getInfType());
          return;
        }
        
        stringstream msg;
        msg << "Error: Class '" << *exprType << "' cannot be assigned to '" << *type << "'";

        throw TypeErr(msg.str().c_str());
      }
      catch (std::out_of_range oor){
        stringstream msg;
        msg << "Error: Class '" << *exprType << "' doesn't exist";

        throw TypeErr(msg.str().c_str());
      }
    }
  }
  string* exprType = getTypeOfLast();

  // compare the variable type and the expr type
  // no need to propogate anything

  // check if valid numbers
  if (canAssign(type, exprType)) {
    return;
  }
  // not numbers
  else {
    // check if they are equal
    if (*type == *exprType) {
      return;
    }
    // if not, check parents to see if it is valid
    else {
      ClassNode* rhsClass = groot->getClasses()[*exprType];
      if (rhsClass->hasAncestor(type)) {
        // it is possible to do!
        return;
      }
      else {
        stringstream msg;
        msg << "RHS (type: '" << *exprType << "') is not a subclass of the LHS (type: '" << *type << "') In a formal declare.";
        throw TypeErr(msg.str().c_str());
      }
    }
  }
}

/**
 * Typecheck ClassStatement
 * *** New Scope ***
 */
void TypeCheck::visit(ClassStatement* node) {
  // enter new scope (Going to be groot)
  curScope = ((Groot*)curScope)->getClasses().at(*(node->getType()->getName()));
  curClass = *(node->getType()->getName());
  
  node->getType()->accept(this);

  if(node->getList() != nullptr) {
    node->getList()->accept(this);
  }

  if(node->getInheritType() != nullptr) {
    node->getInheritType()->accept(this);
  }

  // leave new scope
  curScope = curScope->getLexParent();
}

/**
 * Typecheck ClassList
 * Scope of Groot (AKA "I am Groot")
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
  // Forward to expression
  if(node->getExpr() != nullptr) {
    node->getExpr()->accept(this);
  }

  // Forward to type specifier
  if(node->getType() != nullptr) {
    node->getType()->accept(this);
  }

  // Forward to list of parameters
  if(node->getExprList() != nullptr) {
    node->getExprList()->accept(this);
  }

  const string* methodName = ((Id*) node->getID())->getName(); // Get the name of the method that is being called

  /* Walk up the symbol tree until the first class is found */
  SymbolNode* step = getScope();
  while(step->getLexParent()->getLexParent() != nullptr) { // Classes are always on the second level of the scope tree. So, the grandparent of a class should always be null.
    step = step->getLexParent();
  }

  /* Find the class that this method _should_ be a member of */
  ClassNode* curClass = nullptr;
  Groot* groot = (Groot*) step->getLexParent();
  if(node->getExpr() != nullptr) { // If this dispatch is attached to an expression (e.g., x.foo()), find the type of x
    string* oftype = node->getExpr()->getInfType();
    curClass = groot->getClasses()[*oftype];
  } else { // If this dispatch is not attached to an expression (e.g., foo()), simply use the class that the current scope is a member of.
    curClass = (ClassNode*) step;
  }

  /* Get the name of the class that this dispatch is a lexical member of */
  string* className = curClass->getName();

  /* If a cast type is specified, walk across the inheritance tree until we hit that type */
  if(node->getType() != nullptr) { // If a cast type is specified ...
    while(curClass->getSuper() != nullptr) {
      if(*curClass->getName() == *node->getType()->getInfType()) { // When we find the specified cast type, break out of the loop
        break;
      }

      curClass = groot->getClasses()[*curClass->getSuper()];
    }

    // Check if we actually found the right class, or if we just walked off the edge of the inheritance tree 
    if(*curClass->getName() != *node->getType()->getInfType()) {
      stringstream msg;
      msg << "Error: class '" << *className << "' does not extend '" << *node->getType()->getInfType() << "'";

      throw TypeErr(msg.str().c_str());
    }
  }

  /* Walk across the inheritance tree, looking for the correct method */
  while(curClass->getSuper() != nullptr) {
    if(curClass->getMethods().find(*methodName) != curClass->getMethods().end()) { // Check if this class has the requested method
      break;
    }

    curClass = groot->getClasses()[*curClass->getSuper()];
  }

  /* If we didn't find a class with the correct method, complain */
  if(curClass->getMethods().find(*methodName) == curClass->getMethods().end()) {
    stringstream msg;
    msg << "Error: method '" << *methodName << "' not visible in current scope";

    throw TypeErr(msg.str().c_str());
  }
  SymbolMethod* methodObj = curClass->getMethods()[*methodName]; // Get the SymbolMethod object itself

  /* Check parameter types */
  bool noParamsInDef = methodObj->getParamNames().empty(); // Are there any parameters in the method definition?
  bool noParamsInDisp = node->getExprList() == nullptr; // Are there any parameters in the dispatch?
  if(noParamsInDef && !noParamsInDisp) { // If parameters are listed in the definition but not in the dispatch...
    stringstream msg;
    msg << "Error: Dispatch provides parameters to a parameterless method";

    throw TypeErr(msg.str().c_str());
  } else if(!noParamsInDef && noParamsInDisp) { // If parameters are listed in the dispatch but not in the definition...
    stringstream msg;
    msg << "Error: Dispatch does not specify required parameters";

    throw TypeErr(msg.str().c_str());
  } else if(!noParamsInDef && !noParamsInDisp) { // If both the dispatch and definition specify parameters...
    checkDispatchParameters(node, methodObj);
  }

  node->setInfType(methodObj->getRetType().c_str());
  setTypeOfLast(node->getInfType());
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
 * *** New Scope ***
 * TODO: method, check return type with last expression. Handle SELF_TYPE
 */
void TypeCheck::visit(Feature* node) {
  // enter new scope
  // Coming from a class scope
  curScope = ((ClassNode*)curScope)->getMethods().at(*(node->getID()->getName()));
  
  // don't check id!
  node->getType()->accept(this);
  string* type = getTypeOfLast();
  node->getExpr()->accept(this);

  if(node->getList() != nullptr) {
    node->getList()->accept(this);
  }
  
  // exit scope
  curScope = curScope->getLexParent();
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

const char* TypeCheck::isNum(string* s){
  if(*s == "Int64")
    return s->c_str();
  else if(*s == "Float")
    return s->c_str();
  else if(*s == "Int8")
    return s->c_str();
  else if(*s == "Int")
    return s->c_str();
  else
    return nullptr;
}

/**
 * returns the greatest of 2 numbers.
 * nullptr on error.
 */
const char* TypeCheck::numOrder(string* l, string* r){
  int maxType = max(getNumOrder(l), getNumOrder(r));

  switch(maxType) {
  case 1:
    return "Int8";
  case 2:
    return "Int";
  case 3:
    return "Int64";
  case 4:
    return "Float";
  default:
    return nullptr;
  }

}

bool TypeCheck::isInt(string* type) {
  int order = getNumOrder(type);
  return order == 1 || order == 2 || order == 3;
}


/**
 * Checks whether the parameters match between a method declaration and dispatch.
 */
void TypeCheck::checkDispatchParameters(Dispatch* node, SymbolMethod* methodObj) {
  /* collect all of the types given and expected */
  vector<string*> given;
  vector<string> expected;

  for(auto param : node->getExprList()->getChildren()) {
    given.push_back(param->getInfType());
  }

  for(auto param_name : methodObj->getParamNames()) {
    expected.push_back(methodObj->getParams()[param_name]);
  }

  if(given.size() != expected.size()) {
    stringstream msg;
    msg << "Error: Method " << node->getID() << " expects " << expected.size() <<
      " args but got " << given.size();

    throw TypeErr(msg.str().c_str());
  } else {
    for(int i = 0; i < given.size(); i++) {
      if(!canAssign(&expected[i], given[i])) {
	stringstream msg;
	msg << "Error: Method " << node->getID() << " expected " << expected[i] <<
	  " but received " << *given[i] << " for parameter #" << i;

	throw TypeErr(msg.str().c_str());
      }
    }
  }
}

/*
 * returns true if r can be store in l, otherwise false.
 * takes into account Int type weirdness
 */
bool TypeCheck::canAssign(string* l, string* r) {
  int lorder = getNumOrder(l);
  int rorder = getNumOrder(r);

  // Check if both are num types.
  if(lorder && rorder) {
    return lorder >= rorder;
  } else {
    // If at least one isn't a num then check ancestors
    ClassNode* rhsClass = groot->getClasses()[*r];
    return rhsClass->hasAncestor(l);
  }
}

/*
 * Returns the order of a number type (Int and Float types) or 0 if not one of those.
 * Lower numbers may be assigned to higher numbers.
 */
int TypeCheck::getNumOrder(string* type) {
  if(*type == "Float") {
    return 4;
  } else if(*type == "Int64") {
    return 3;
  } else if(*type == "Int" || *type == "Int32") {
    return 2;
  } else if(*type == "Int8") {
    return 1;
  } else {
    return 0;
  }
}
