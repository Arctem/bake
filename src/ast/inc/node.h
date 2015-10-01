
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
  enum NodeType { INTEGERVAL, STRINGVAL, BOOLVAL, ID, LOGICALNOT, BITNOT, ISVOID, NEW, TYPE };

  /**
   * Base class for all objects that can be placed in the AST
   */
  class Node {
  public:
    Node() {}
    virtual ~Node() { }
    
    virtual void accept(bake_ast::Visitor*) = 0;
  };
}

#endif