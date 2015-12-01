#include "ir/basic_block.h"

void ir::BasicBlock::addOp(Op* op, int pos) {
  // -1 is the default value.
  if(pos == -1) {
    ops.push_back(op);
  } else {
    ops.insert(ops.begin() + pos, op);
  }
}

string* ir::BasicBlock::getLabel() {
  return label = new string("L" + std::to_string((unsigned long int) this));
}
/**
 * Deconstructor
 */
ir::BasicBlock::~BasicBlock(){
   if(brOnTrue != nullptr){
     delete brOnTrue;
   }

   if(brOnFalse != nullptr){
     delete brOnFalse;
   }

   for(auto op : getOps()){
      //delete op;
   }
}


/**
 * Add Stack Var
 */
void ir::Method::addStackVar(int size) {
  stack_vars.push_back(size);
}
