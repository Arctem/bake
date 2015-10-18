
#include "ast/terminals.h"
using namespace bake_ast;

/*********** StringVal methods ***********/

/**
 * Constructor.
 * Note that the character string passed to this parameter is
 * copied into a separate string object inside the StringVal.
 * This was done in the interest of simplifying memory management.
 */
StringVal::StringVal(const std::string* val) : Leaf(STRINGVAL) {
  this->val = val;
}

StringVal::~StringVal() {
  delete this->val;
}

/*********** Id methods ***********/

Id::Id(const std::string* name) : Leaf(IDVAL) {
  this->name = name;
}

Id::~Id() {
  delete this->name;
}

/*********** Type methods ***********/

Type::Type(const std::string* name) : Leaf(TYPEVAL) {
  this->name = name;
}

Type::~Type() {
  delete this->name;
}
