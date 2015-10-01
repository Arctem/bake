
#ifndef __TERMINALS__
#define __TERMINALS__

#include <string>
using namespace std;
#include "node.h"

namespace bake_ast {
  /**
   * Base class for terminal objects
   */
  class Leaf : public Node { };

  /**
   * Represents an integer
   */
  class IntegerVal : public Leaf {
  public:
    NodeType type;

    IntegerVal(int val) : type(INTEGERVAL), value(val) { }
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    int getValue() { return value; }

  private:
    int value;
  };

  /**
   * Represents a string.
   */
  class StringVal : public Leaf {
  public:
    NodeType type;

    StringVal(const char* val);
    virtual ~StringVal();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    string* getValue() { return value; }

  private:
    string* value;
  };

  /**
   * Represents a boolean.
   */
  class BoolVal : public Leaf {
  public:
    NodeType type;

    BoolVal(bool val) : type(BOOLVAL), value(val) { };
    virtual ~BoolVal() {};
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    bool getValue() { return value; }

  private:
    bool value;
  };

  /**
   * Represents the ID of a variable
   */
  class Id : public Leaf {
  public:
    NodeType type;

    Id(const char* name);
    virtual ~Id();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    string* getName() { return this->name; }

  private:
    string* name;
  };

  /**
   * Represents the ID of a variable
   */
  class Type : public Leaf {
  public:
    NodeType type;

    Type(const char* name);
    virtual ~Type();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    string* getName() { return this->name; }

  private:
    string* name;
  };
}

#endif