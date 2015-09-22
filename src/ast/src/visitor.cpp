
#include <iostream>
using namespace std;
#include "visitor.h"
#include "node.h"
#include "terminals.h"
#include "binary_ops.h"
using namespace bake_ast;

/*********** Pretty print methods ***********/

/**
 * What to do before visiting a node
 * Prints out whitespace according to the level this printer is currently on.
 */
void PrettyPrint::leadingOps() {
  for(int i = 0; i < depth; i++) {
    cout << "| ";
  }
}

void PrettyPrint::visit(Integer* n) {
  leadingOps();
  cout << "+ Value: " << n->getValue() << endl;
}

void PrettyPrint::visit(BinaryOp* n) {
  leadingOps();
  cout << "+ BinaryOp" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}
