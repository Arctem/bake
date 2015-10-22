
#ifndef __TERMINALS__
#define __TERMINALS__

#include <string>
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
  * Represents an Float
  */
  class FloatVal : public Leaf {
  public:
    FloatVal(double val) : Leaf(FLOATVAL), val(val) { }
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    double getValue() { return val; }

  private:
    double val;
  };

  /**
   * Represents a string.
   */
  class StringVal : public Leaf {
  public:
    StringVal(const std::string* val);
    virtual ~StringVal();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    const std::string* getValue() { return val; }

  private:
    const std::string* val;
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
    Id(const std::string* name);
    virtual ~Id();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    const std::string* getName() { return this->name; }

  private:
    const std::string* name;
  };

  /**
   * Represents the ID of a variable
   */
  class Type : public Leaf {
  public:
    Type(const std::string* name);
    virtual ~Type();
    void accept(bake_ast::Visitor* v) { v->visit(this); }
    const std::string* getName() { return this->name; }

  private:
    const std::string* name;
  };
}

#endif
