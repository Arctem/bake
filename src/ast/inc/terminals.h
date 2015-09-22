
#ifndef __TERMINALS__
#define __TERMINALS__

#include "node.h"

namespace bake_ast {
  class Node;

  /**
   * Base class for terminal objects
   */
  class Leaf : public Node { };

  class Integer : public Leaf {
  public:
    NodeType type;

    Integer(int val) : type(INTEGER), value(val) { }
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    int getValue() { return this->value; }

  private:
    int value;
  };
}

#endif