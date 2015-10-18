
#include "ast/binary_ops.h"
using namespace bake_ast;

BinaryOp::~BinaryOp() {
  delete lhs;
  delete rhs;
}