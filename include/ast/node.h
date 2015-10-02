
/*
*   Authors:        AJ Burns, Will Rosenberger
*   Date:           Sept. 22nd, 2015
*   Description:    Interface to the AST
*   Bugs:           None known
*/

#ifndef __AST_NODE__
#define __AST_NODE__

#include "visitor.h"

namespace bake_ast {
  enum NodeType { INTEGERVAL, STRINGVAL, BOOLVAL, ID, LOGICALNOT, BITNOT, ISVOID, NEW, TYPE, 
                  PLUS, MINUS, MULTIPLY, DIVIDE, LESSTHAN, LESSTHANEQUAL, EQUAL, ASSIGN, 
                  EXPRLIST, WHILELOOP, IFSTATEMENT, LETSTATEMENT, CASESTATEMENT, FORMALDECLARE};

  /**
   * Base class for all objects that can be placed in the AST
   */
  class Node {
  public:
  	NodeType type;

    Node(NodeType type) : type(type) {}
    virtual ~Node() { }
    
    virtual void accept(bake_ast::Visitor*) = 0;
  };
}

#endif