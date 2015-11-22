/*
*   Authors:        AJ Burns, Will Rosenberger
*   Date:           Sept. 22nd, 2015
*   Description:    Interface to the AST
*   Bugs:           None known
*/

#pragma once

#include <string>
#include <iostream>

#include "visitor.h"

namespace bake_ast {
  // Enum used to describe the types of the AST node objects at run time
  enum NodeType { INTEGERVAL, INT8VAL, INT64VAL, FLOATVAL, STRINGVAL, BOOLVAL, IDVAL, LOGICALNOT, BITNOT, VOID, NEWVAL, TYPEVAL, 
                  PLUS, MINUS, MULTIPLY, DIVIDE, LESSTHAN, LESSTHANEQUAL, EQUAL, ASSIGN,
                  EXPRLIST, WHILELOOP, IFSTATEMENT, LETSTATEMENT, CASESTATEMENT, FORMALDECLARE,
                  CLASSSTATEMENT, CLASSLIST, DISPATCH, LISTFORMALDECLARE, FEATURELIST,
                  FEATUREOPTION, FEATURE, CASE, CASELIST };

  /**
   * Base class for all objects that can be placed in the AST
   */
  class Node {
  public:
    NodeType type;

    Node(NodeType type) : type(type) { }
    virtual ~Node();

    void setInfType(char const* t);
    std::string* getInfType() { return infType; }
    virtual void accept(Visitor*) = 0;

  private:
    std::string* infType = nullptr; // The inferred type of this node. If nullptr, this node's type has not been resolved.
  };
}
