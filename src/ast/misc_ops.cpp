
#include "ast/misc_ops.h"
#include "ast/terminals.h"
using namespace bake_ast;

/** WhileLoop method definitions **/

WhileLoop::WhileLoop(Node* c, Node* b) : Node(WHILELOOP) {
  cond = c;
  body = b;
}

WhileLoop::~WhileLoop() {
  delete cond;
  delete body;
}

/** FormalDeclare method definitions **/

FormalDeclare::FormalDeclare(Id* i, Type* t, Node* e) : Node(FORMALDECLARE) {
  id = i;
  type = t;
  expr = e;
}

FormalDeclare::~FormalDeclare() {
  delete id;
  delete type;
  delete expr;
}

/** IfStatement method definitions **/

IfStatement::IfStatement(Node* c, Node* b, Node* e) : Node (IFSTATEMENT) {
  cond = c;
  body = b;
  elseBody = e;
}

IfStatement::~IfStatement() {
  delete cond;
  delete body;
  delete elseBody;
}

/** Case method definitions **/
Case::Case(Id* i, Type* t, Node* e) : Node(CASE) {
  id = i;
  type = t;
  expr = e;
}

Case::~Case() {
  delete id;
  delete type;
  delete expr;
}
