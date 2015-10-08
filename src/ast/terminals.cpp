
#include "ast/terminals.h"
using namespace bake_ast;

/*********** StringVal methods ***********/

/**
 * Constructor.
 * Note that the character string passed to this parameter is
 * copied into a separate string object inside the StringVal.
 * This was done in the interest of simplifying memory management.
 */
StringVal::StringVal(const char* val) : Leaf(STRINGVAL) {
  this->val = new string(val);
}

StringVal::~StringVal() {
  delete this->val;
}

/*********** Id methods ***********/

Id::Id(const char* name) : Leaf(IDVAL) {
  this->name = new string(name);
}

Id::~Id() {
  delete this->name;
}

/*********** Type methods ***********/

Type::Type(const char* name) : Leaf(TYPEVAL) {
  this->name = new string(name);
}

Type::~Type() {
  delete this->name;
}
