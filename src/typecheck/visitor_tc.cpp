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
  // SymbolAnon
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
  if(*subtype== "Bool") {
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
  

  if(canAssign(type, exprType)){
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
    msg << "Error: If condition must be a Boolean Expression not " << *cond << "";

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
  // set new scope
  // can come from a let (SymbolAnon) or a method (SymbolMethod)
  if(curScope->getType() == SYMBOLMETHOD) {
    curScope = ((SymbolMethod*) curScope)->nextMem();
  } else { // SymbolAnon
    curScope = ((SymbolAnon*) curScope)->nextMem();
  }

  // visit expr and set the return type
  node->getExpr()->accept(this);
  node->setInfType(getTypeOfLast()->c_str());
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
  node->getID()->accept(this);
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
 * TODO: Dispatch needs to handle self type.
 * TODO: add hard coded convert methods
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
  string* exprType = getTypeOfLast();

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
  int lorder;
  int rorder;

  // find the ordering of the left
  if(*l == "Int64")
    lorder = 3;
  else if(*l == "Float")
    lorder = 4;
  else if(*l == "Int8")
    lorder = 1;
  else if(*l == "Int")
    lorder = 2;
  else
    return nullptr;


  // find the ordering of the right
  if(*r == "Int64")
    rorder = 3;
  else if(*r == "Float")
    rorder = 4;
  else if(*r == "Int8")
    rorder = 1;
  else if(*r == "Int")
    rorder = 2;
  else
    return nullptr;

  // use the larger of the 2
  if(lorder < rorder){
    switch(rorder){
      case 1:
        return "Int8";
      case 2:
        return "Int";
      case 3:
        return "Int64";
      case 4:
        return "Float";
    }
  }
  else{
    switch(lorder){
      case 1:
        return "Int8";
      case 2:
        return "Int";
      case 3:
        return "Int64";
      case 4:
        return "Float";
    }
  } 
}

bool TypeCheck::isInt(string* type) {
  if(*type == "Int64")
    return true;
  else if(*type == "Int8")
    return true;
  else if(*type == "Int")
    return true;
  else
    return false;
}

// checks if rhs <= lhs
bool TypeCheck::canAssign(string* l, string* r){
  int lorder;
  int rorder;

  // find the ordering of the left
  if(*l == "Int64")
    lorder = 3;
  else if(*l == "Float")
    lorder = 4;
  else if(*l == "Int8")
    lorder = 1;
  else if(*l == "Int")
    lorder = 2;
  else
    return false;


  // find the ordering of the right
  if(*r == "Int64")
    rorder = 3;
  else if(*r == "Float")
    rorder = 4;
  else if(*r == "Int8")
    rorder = 1;
  else if(*r == "Int")
    rorder = 2;
  else
    return false;

  // use the larger of the 2
  if(lorder >= rorder){
    return true;
  }
  return false;
}
