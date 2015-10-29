
/*
*   Authors:        AJ Burns, Will Rosenberger
*   Date:           Sept. 22nd, 2015
*   Description:    Interface to the AST
*   Bugs:           None known
*/

#include "ast/node.h"
using namespace bake_ast;

/**
 * Sets the type of this AST node
 * Method copies the string and handles memory cleanup for itself.
 */
void Node::setInfType(char const* t) {
  if(infType != nullptr) {
    delete infType;
  }
  
  infType = new string(t);
}

Node::~Node() {
  if(infType != nullptr) {
    delete infType;
  }
}