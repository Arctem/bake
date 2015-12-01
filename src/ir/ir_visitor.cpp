#include <iostream>

#include "ir/ir_visitor.h"
#include "ir/class_list.h"
#include "ir/basic_block.h"
#include "ir/op.h"

void ir::IrPrint::preops() {
  for(int i = 0; i < level; i++) {
    std::cout << "  ";
  }
}

/**
 * Pretty print the IR for ClassList
 */
void ir::IrPrint::visit(ClassList* n) {
  for(auto cls : n->getClasses()) {
    cls.second->accept(this);
  }
}

/**
 * Pretty print the IR for ClassDef
 */
void ir::IrPrint::visit(ClassDef* n) {
  preops();
  std::cout << "[ " << n->getName();

  if(n->getAttrs().size() != 0) {
    std::cout << ": ";
  } else {
    std::cout << " ";
  }

  for(auto attr : n->getAttrs()) {
    preops();
    std::cout << attr << " ";
  }
  std::cout << "]" << std::endl;

  level++;
  for(auto method : n->getMethods()) {
    method->accept(this);
  }
  level--;
}

/**
 * Pretty print the IR for BasicBlock
 */
void ir::IrPrint::visit(BasicBlock* n) {

}

/**
 * Pretty print the IR for Method
 */
void ir::IrPrint::visit(Method* n) {
  preops();

  std::cout << " ( " << n->getName();

  if(n->getStackVars().size() != 0) {
    std::cout << ": ";
  } else {
    std::cout << " ";
  }

  for(auto var : n->getStackVars()) {
    std::cout << var << " ";
  }
  std::cout << ")" << std::endl;

  level += 2;
  for(auto op : n->getOps()) {
    op->accept(this);
  }
  level -= 2;
}

/**
 * Pretty print the IR for Nop
 */
void ir::IrPrint::visit(Nop* n) {

}

/**
 * Pretty print the IR for Fnop
 */
void ir::IrPrint::visit(Fnop* n) {

}

/**
 * Pretty print the IR for Add
 */
void ir::IrPrint::visit(Add* n) {

}


/**
 * Pretty print the IR for Sub
 */
void ir::IrPrint::visit(Sub* n) {

}



/**
 * Pretty print the IR for Mul
 */
void ir::IrPrint::visit(Mul* n) {

}

/**
 * Pretty print the IR for Div
 */
void ir::IrPrint::visit(Div* n) {

}

/**
 * Pretty print the IR for Mod
 */
void ir::IrPrint::visit(Mod* n) {

}

/**
 * Pretty print the IR for Fadd
 */
void ir::IrPrint::visit(Fadd* n) {

}

/**
 * Pretty print the IR for Fsub
 */
void ir::IrPrint::visit(Fsub* n) {

}

/**
 * Pretty print the IR for Fmul
 */
void ir::IrPrint::visit(Fmul* n) {

}

/**
 * Pretty print the IR for Fdiv
 */
void ir::IrPrint::visit(Fdiv* n) {

}

/**
 * Pretty print the IR for Copy
 */
void ir::IrPrint::visit(Copy* n) {
  preops();
  std::cout << "| copy " << (char) n->getSrcRegister(); // Print source value
  std::cout << " -> r" << n->getDestRegister() << "(" << n->getDestSize() << ")" << std::endl;
}

/**
 * Pretty print the IR for Fcopy
 */
void ir::IrPrint::visit(Fcopy* n) {

}

/**
 * Pretty print the IR for Conv
 */
void ir::IrPrint::visit(Conv* n) {

}

/**
 * Pretty print the IR for Fconv
 */
void ir::IrPrint::visit(Fconv* n) {

}

/**
 * Pretty print the IR for LoadI
 */
void ir::IrPrint::visit(LoadI* n) {

}

/**
 * Pretty print the IR for LoadO
 */
void ir::IrPrint::visit(LoadO* n) {

}

/**
 * Pretty print the IR for StoreI
 */
void ir::IrPrint::visit(StoreI* n) {
  preops();
  std::cout << "| storeI r" << n->getSrcRegister() << "(" << n->getSrcSize() << ")"; // Print source
  std::cout << " -> r" << n->getStoreBaseRegister() << "(" << n->getStoreBaseSize() << ")"; // Print base address
  std::cout << " + " << n->getStoreOffsetRegister() << std::endl; // Print offset
}

/**
 * Pretty print the IR for StoreO
 */
void ir::IrPrint::visit(StoreO* n) {

}

/**
 * Pretty print the IR for CmpLT
 */
void ir::IrPrint::visit(CmpLT* n) {

}

/**
 * Pretty print the IR for CmpLE
 */
void ir::IrPrint::visit(CmpLE* n) {

}

/**
 * Pretty print the IR for CmpEQ
 */
void ir::IrPrint::visit(CmpEQ* n) {

}

/**
 * Pretty print the IR for FcmpLT
 */
void ir::IrPrint::visit(FcmpLT* n) {

}

/**
 * Pretty print the IR for FcmpLE
 */
void ir::IrPrint::visit(FcmpLE* n) {

}

/**
 * Pretty print the IR for FcmpEQ
 */
void ir::IrPrint::visit(FcmpEQ* n) {

}

/**
 * Pretty print the IR for Br
 */
void ir::IrPrint::visit(Br* n) {

}

/**
 * Pretty print the IR for Cbr
 */
void ir::IrPrint::visit(Cbr* n) {

}

/**
 * Pretty print the IR for Call
 */
void ir::IrPrint::visit(Call* n) {

}

/**
 * Pretty print the IR for Dcall
 */
void ir::IrPrint::visit(Dcall* n) {

}

/**
 * Pretty print the IR for Fcall
 */
void ir::IrPrint::visit(Fcall* n) {

}

/**
 * Pretty print the IR for Dfcall
 */
void ir::IrPrint::visit(Dfcall* n) {

}

/**
 * Pretty print the IR for Push
 */
void ir::IrPrint::visit(Push* n) {

}

/**
 * Pretty print the IR for Fpush
 */
void ir::IrPrint::visit(Fpush* n) {

}

/**
 * Pretty print the IR for Pop
 */
void ir::IrPrint::visit(Pop* n) {

}

/**
 * Pretty print the IR for Fpop
 */
void ir::IrPrint::visit(Fpop* n) {

}

/**
 * Pretty print the IR for Ccall
 */
void ir::IrPrint::visit(Ccall* n) {

}

/**
 * Pretty print the IR for Alloc
 */
void ir::IrPrint::visit(Alloc* n) {
  preops();
  std::cout << "| alloc " << n->getSrc1Register(); // Print size to allocate
  std::cout << " -> r" << n->getDestRegister() << "(" << n->getDestSize() << ")" << std::endl;
}

/**
 * Pretty print the IR for Free
 */
void ir::IrPrint::visit(Free* n) {

}

/**
 * Pretty print the IR for Abort
 */
void ir::IrPrint::visit(Abort* n) {

}

/**
 * Pretty print the IR for TypeName
 */
void ir::IrPrint::visit(TypeName* n) {

}

/**
 * Pretty print the IR for ShallowCopy
 */
void ir::IrPrint::visit(ShallowCopy* n) {

}

/**
 * Pretty print the IR for OutString
 */
void ir::IrPrint::visit(OutString* n) {

}

/**
 * Pretty print the IR for OutInt
 */
void ir::IrPrint::visit(OutInt* n) {

}

/**
 * Pretty print the IR for InString
 */
void ir::IrPrint::visit(InString* n) {

}

/**
 * Pretty print the IR for InInt
 */
void ir::IrPrint::visit(InInt* n) {

}

/**
 * Pretty print the IR for Length
 */
void ir::IrPrint::visit(Length* n) {

}

/**
 * Pretty print the IR for Concat
 */
void ir::IrPrint::visit(Concat* n) {

}

/**
 * Pretty print the IR for Substr
 */
void ir::IrPrint::visit(Substr* n) {

}
