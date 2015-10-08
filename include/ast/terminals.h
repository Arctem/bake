
#ifndef __TERMINALS__
#define __TERMINALS__

#include <string.h>
#include "node.h"

namespace bake_ast {
  /**
   * Base class for terminal objects
   */
  class Leaf : public Node {
  public:
    Leaf(NodeType type) : Node(type) { };
  };

  /**
   * Represents an integer
   */
  class IntegerVal : public Leaf {
  public:
    IntegerVal(int val) : Leaf(INTEGERVAL), val(val) { }
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    int getValue() { return val; }

  private:
    int val;
  };

  /**
   * Represents a string.
   */
  class StringVal : public Leaf {
  public:
    StringVal(const char* val);
    virtual ~StringVal();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    char* getValue() { return val; }

  private:
    char* val;
  };

  /**
   * Represents a boolean.
   */
  class BoolVal : public Leaf {
  public:
    BoolVal(bool val) : Leaf(BOOLVAL), val(val) { };
    
    virtual ~BoolVal() {};
    
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    bool getValue() { return val; }

  private:
    bool val;
  };

  /**
   * Represents the ID of a variable
   */
  class Id : public Leaf {
  public:
    Id(const char* name);
    virtual ~Id();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    char* getName() { return this->name; }

  private:
    char* name;
  };

  /**
   * Represents the ID of a variable
   */
  class Type : public Leaf {
  public:
    Type(const char* name);
    virtual ~Type();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    char* getName() { return this->name; }

  private:
    char* name;
  };
}

#endif
