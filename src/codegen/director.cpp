#include "codegen/director.h"
#include "codegen/visit_ir.h"
#include <iostream>
#include <fstream>

// set the initial state of the instance
codegen::Director* codegen::Director::instance = nullptr;

void codegen::Director::generateCode(ir::ClassList* classes) {
  getInstance()->generateDataFromIR(classes);
  getInstance()->generateBlocksFromIR(classes);
}

void codegen::Director::generateBlocksFromIR(ir::ClassList* classes) {
  CodegenVisitIr v;
  v.visit(classes);
}

void codegen::Director::generateDataFromIR(ir::ClassList* classes) {

}


// get the instance of the singleton class
codegen::Director* codegen::Director::getInstance() {
  if (instance == nullptr) {
    instance = new Director();
  }
  return instance;
}

void codegen::Director::reset() {
  delete instance;
  instance = nullptr;
}

void codegen::Director::writeFile(string filename) {
  std::ofstream file;
  file.open(filename);

  // generate declarations
  file << *Generator::generateBuiltInClassList() << std::endl;
  for (auto data : dataList) {
    file << *data << std::endl;
  }

  // generate definitions
  file << *Generator::generateBuiltInMethods() << std::endl;
  
  file << ".globl start\n_start:\n.globl main\nmain:" << std::endl;

  for (std::string* block : blockList) {
    file << *block << std::endl;
  }
  file << "call exit" << std::endl;
}
