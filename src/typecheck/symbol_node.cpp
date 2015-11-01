
#include <sstream>
using namespace std;

#include "typecheck/symbol_node.h"
using namespace typecheck;

/************ Groot method implementation ***********/

/**
 * Add a class to this program
 */
void Groot::addClass(string id, ClassNode* cls) {
  /* Check if already declared */
  if(classes.find(id) != classes.end()) {
    stringstream msg;
    msg << "Error: Multiple definitions found for class '" << id << "'" ;
    throw StBuildErr(msg.str().c_str());
  }

  classes.insert(pair<string, ClassNode*>(id, cls));
  cls->setLexParent(this);
}

/**
 * Destructor
 */
Groot::~Groot() {
  for(auto cls : classes) {
    delete cls.second;
  }
}

/**
 * Get the classes in this program
 */
unordered_map<string, ClassNode*> Groot::getClasses() {
  return classes;
}

/**
 * Get the lexical parent of this node.
 */
SymbolNode* Groot::getLexParent() {
  return nullptr;
}

/************ ClassNode method implementation ***********/

/**
 * Destructor
 */
ClassNode::~ClassNode() {
  delete cls_name;

  if(super != nullptr) {
    delete super;
  }

  for(auto method : methods) {
    delete method.second;
  }
}

void ClassNode::setSuper(const string cls) {
  super = new string(cls);
}

void ClassNode::setName(const string name) {
  cls_name = new string(name);
}

/**
 * Insert a new method into the class
 * @param id: Name of the method
 * @param method: Reference to the method namespace
 */
void ClassNode::addMethod(string id, SymbolMethod* method) {
  /* Check if already declared */
  if(methods.find(id) != methods.end()) {
    stringstream msg;
    msg << "Error: Multiple definitions found for method '" << id << "'";
    throw StBuildErr(msg.str().c_str());
  }

  methods.insert(pair<string, SymbolMethod*>(id, method));
  method->setLexParent(this);
}

/**
 * Insert a new element into the map of members of this scope
 * @param string id: Name of variable
 * @paraam string type: Name of type
 */
void ClassNode::addMember(string id, string type) {
  /* Check if already declared */
  if(members.find(id) != members.end()) {
    stringstream msg;
    msg << "Error: Multiple definitions found for class attribute '" << id << "'";
    throw StBuildErr(msg.str().c_str());
  }

  members.insert(pair<string, string>(id, type));
}

/**
 * Get the member instance variables
 */
unordered_map<string, string> ClassNode::getMembers() {
  return members;
}

/**
 * Get the methods in this class
 */
unordered_map<string, SymbolMethod*> ClassNode::getMethods() {
  return methods;
}

/**
 * Get the lexical ancestor of this node
 */
Groot* ClassNode::getLexParent() {
  return lex_parent;
}

/**
 * Set the lexical ancestor of this node
 */
void ClassNode::setLexParent(Groot* groot) {
  this->lex_parent = groot;
}

/**
 * Check whether this class is a subclass of parent
 * param parent: Name of the parent class to look for
 */
bool ClassNode::hasAncestor(string* parent) {
  Groot* groot = (Groot*) getLexParent(); // Lexical parent of a Class is always Groot

  ClassNode* curClass = this;
  if(*curClass->getName() == *parent) { // Are we already in the requested class?
    return true;
  }

  /* Walk along the inheritance tree until we hit the end of the tree */
  while(curClass->getSuper() != nullptr) {
    curClass = groot->getClasses()[*curClass->getSuper()];

    if(*curClass->getName() == *parent) { // When we find the correct class...
      return true;
    }
  }

  return false;
}

/************ SymbolMethod method implementation ***********/

/**
 * Destructor
 */
SymbolMethod::~SymbolMethod() {
  for(auto member : members) {
    delete member;
  }
}

/**
 * Get the member variables
 */
vector<SymbolAnon*> SymbolMethod::getMembers() {
  return members;
}

/**
 * Add a sub-scope
 */
void SymbolMethod::addMember(SymbolAnon* sub) {
  members.push_back(sub);
  sub->setLexParent(this);
}

/**
 * Add a parameter to this method
 * @param id: Name of the param
 * @param type: Name of the type
 */
void SymbolMethod::addParam(string id, string type) {
  /* Check if already declared */
  if(params.find(id) != params.end()) {
    stringstream msg;
    msg << "Error: Multiple definitions found for method parameter '" << id << "'";
    throw StBuildErr(msg.str().c_str());
  }

  param_names.push_back(id);
  params.insert(pair<string, string>(id, type));
}

/**
 * Get the lexical ancestor of this node.
 */
ClassNode* SymbolMethod::getLexParent() {
  return lex_parent;
}

/**
 * Set the lexical ancestor of this node
 */
void SymbolMethod::setLexParent(ClassNode* parent) {
  this->lex_parent = parent;
}

/************ SymbolAnon method implementation ***********/

SymbolAnon::~SymbolAnon() {
  for(auto sub : subs) {
    delete sub;
  } 
}

/**
 * Get the member variables
 */
unordered_map<string, string> SymbolAnon::getMembers() {
  return members;
}

/**
 * Insert a new element into the map of members of this scope
 * @param string id: Name of variable
 * @paraam string type: Name of type
 */
void SymbolAnon::addMember(string id, string type) {
  /* Check if already declared */
  if(members.find(id) != members.end()) {
    stringstream msg;
    msg << "Error: Multiple definitions found for let statement variable '" << id << "'";
    throw StBuildErr(msg.str().c_str());
  }

  members.insert(pair<string, string>(id, type));
}

/**
 * Get the lexical ancestor of this node.
 */
SymbolNode* SymbolAnon::getLexParent() {
  return lex_parent;
}

/**
 * Set the lexical ancestor of this node
 */
void SymbolAnon::setLexParent(SymbolNode* parent) {
  this->lex_parent = parent;
};

/**
 * Add a sub-scope
 */
void SymbolAnon::addSub(SymbolAnon* sub) {
  subs.insert(subs.begin(), sub);
  sub->setLexParent(this);
}
