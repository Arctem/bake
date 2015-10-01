
#include <iostream>
using namespace std;
#include "ast.h"
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

void PrettyPrint::visit(IntegerVal* n) {
  leadingOps();
  cout << "+ Integer: " << n->getValue() << endl;
}

void PrettyPrint::visit(StringVal* n) {
  leadingOps();
  cout << "+ String: " << *(n->getValue()) << endl;
}

void PrettyPrint::visit(BoolVal* n) {
  leadingOps();
  cout << "+ Boolean: " << n->getValue() << endl;
}

void PrettyPrint::visit(Id* n) {
  leadingOps();
  cout << "+ ID: " << *(n->getName()) << endl;
}

void PrettyPrint::visit(Type* n) {
  leadingOps();
  cout << "+ ID: " << *(n->getName()) << endl;
}

void PrettyPrint::visit(BinaryOp* n) {
  leadingOps();
  cout << "+ BinaryOp" << endl;

  depth++;
  n->getLhs()->accept(this);
  n->getRhs()->accept(this);
  depth--;
}

void PrettyPrint::visit(UnaryOp* n) {
  leadingOps();
  cout << "+ UnaryOp" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(LogicalNot* n) {
  leadingOps();
  cout << "+ LogicalNot" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(BitNot* n) {
  leadingOps();
  cout << "+ BitNot" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Isvoid* n) {
  leadingOps();
  cout << "+ Isvoid" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(New* n) {
  leadingOps();
  cout << "+ New" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Plus* n) {
  leadingOps();
  cout << "+ Plus" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Minus* n) {
  leadingOps();
  cout << "+ Minus" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Multiply* n) {
  leadingOps();
  cout << "+ Multiply" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Divide* n) {
  leadingOps();
  cout << "+ Divide" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThan* n) {
  leadingOps();
  cout << "+ LessThan" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(LessThanEqual* n) {
  leadingOps();
  cout << "+ LessThanEqual" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Equal* n) {
  leadingOps();
  cout << "+ Equal" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}

void PrettyPrint::visit(Assign* n) {
  leadingOps();
  cout << "+ Assign" << endl;

  depth++;
  n->get()->accept(this);
  depth--;
}