
#include <iostream>
using namespace std;

#include "typecheck/symbol_table_print.h"
#include "typecheck/symbol_node.h"
using namespace typecheck;

/**
 * Responsible for printing the leading characters for every line in the tree.
 */
void SymbolTablePrint::leadingOps() {
  for(int i = 0; i < level; i++) {
    cout << "| ";
  }
}

/**
 * Print Groot
 */
void SymbolTablePrint::visit(Groot* groot) {
  leadingOps();
  cout << "+ I am Groot." << endl;

  leadingOps();
  cout << "|\\ [Classes]" << endl;
  level++;
  for(auto cls : groot->getClasses()) {
    leadingOps();
    cout << "+ " << cls.first << endl;

    cls.second->accept(this);
  }
  level--;

  leadingOps();
  cout << "|/" << endl;
}

/**
 * Print ClassNode
 */
void SymbolTablePrint::visit(ClassNode* cls) {
  leadingOps();
  cout << "|\\ [Inherits]" << endl;

  if(cls->getSuper() != nullptr) {
    leadingOps();
    cout << "| " << *cls->getSuper() << endl;
  }

  leadingOps();
  cout << "|/" << endl;

  leadingOps();
  cout << "|\\ [members]" << endl;

  level++;
  for(auto member : cls->getMembers()) {
    leadingOps();
    cout << member.first << " : " << member.second;

    if(cls->getAttrOffsets().find(member.first) != cls->getAttrOffsets().end()) {
      cout << " @ " << cls->getAttrOffsets()[member.first];
    }
    cout << endl;
  }
  level--;

  leadingOps();
  cout << "|/" << endl;
  leadingOps();
  cout << "|\\ [methods]" << endl;
  level++;
  for(auto method : cls->getMethods()) {
    leadingOps();
    cout << "+ " << method.first;

    int method_offset = cls->getMethodOffsets()[method.first];
    if(method_offset != -1) {
      cout << " @ " << method_offset;
    }
    cout << endl;

    method.second->accept(this);
  }
  level--;
  leadingOps();
  cout << "|/" << endl;
}

/**
 * Print SymbolMethod
 */
void SymbolTablePrint::visit(SymbolMethod* method) {
  leadingOps();
  cout << "|\\ [Returns]" << endl;
  leadingOps();
  cout << "| " << method->getRetType() << endl;
  leadingOps();
  cout << "|/" << endl;

  leadingOps();
  cout << "|\\ [parameters]" << endl;

  level++;
  for(auto param : method->getParams()) {
    leadingOps();
    cout << param.first << " : " << param.second;

    if(method->getStackOffsets().find(param.first) != method->getStackOffsets().end()) {
      cout << " @ " << method->getStackOffsets()[param.first];
    }
    cout << endl;
  }
  level--;
  leadingOps();
  cout << "|/" << endl;

  leadingOps();
  cout << "|\\ [sub-spaces]" << endl;

  level++;
  for(auto sub : method->getMembers()) {
    sub->accept(this);
  }
  level--;

  leadingOps();
  cout << "|/" << endl;
}

/**
 * Print SymbolAnon
 */
void SymbolTablePrint::visit(SymbolAnon* let) {
  leadingOps();
  cout << "|\\ [Let]" << endl;

  level++;
  for(auto var_kv : let->getMembers()) {
    leadingOps();
    cout << var_kv.first << " : " << var_kv.second;

    if(let->getLVarOffsets().find(var_kv.first) != let->getLVarOffsets().end()) {
      cout << " @ " << let->getLVarOffsets()[var_kv.first];
    }
    cout << endl;
  }
  level--;
  leadingOps();
  cout << "|/" << endl;

  leadingOps();
  cout << "|\\ [sub-spaces]" << endl;

  level++;
  for(auto sub : let->getSubs()) {
    sub->accept(this);
  }
  level--;

  leadingOps();
  cout << "|/" << endl;
}