#include "codegen/visit_ir.h"

namespace codegen {
  CodegenVisitIr::CodegenVisitIr() { gen = new Generator(); }
  
  void CodegenVisitIr::visit(ir::ClassList* c) {
    std::cout << "Visiting classlist" << std::endl; // TEST 
    for (auto cls : c->getClasses()) {
      cls.second->accept(this);
    }
  }
  
  void CodegenVisitIr::visit(ClassDef* n) {
    std::cout << "Visiting classdef" << std::endl; // TEST

    std::vector<std::string*> table;
    std::string name = n->getName();
    std::string tmp;
    std::string tmp2;

    table.push_back(new std::string(".globl " + name + "..vtable\n" + name + "..vtable:"));

    for (auto method : n->getMethods()) {
      tmp = ".quad ";

      // call function for built-in information
      if ((tmp2 = getMethClass(method->getName())) == "") {
        table.push_back(new std::string(".quad " + *method->getLabel()));
      }
      else {
        tmp += tmp2 + ".";

        tmp += method->getName();
        // add to the vector
        table.push_back(new string(tmp));
      }

      method->accept(this);
    }

    // add them all to the data list
    for (auto s : table) {
      gen->addToDataList(s);
    }
  }
  
  // basic block loops through its ops, visiting each one.
  // visits the next block after done.
  void CodegenVisitIr::visit(BasicBlock* bb) {
    std::cout << "Visiting BB" << std::endl; // TEST 

    gen->genLabel(*bb->getLabel());

    for (auto op : bb->getOps()) {
      op->accept(this);
    }

    //both null == return
    //only true == jmp
    //both == conditional jump

    if(bb->getBrOnTrue() == nullptr && bb->getBrOnFalse() == nullptr) {
      //TODO: return (how does that work? lol I dunno)
    } else if(bb->getBrOnFalse() == nullptr) {
      //Only True exists
      gen->genJmp(*bb->getBrOnTrue()->getLabel());
    } else {
      //Both exist
      //gen->genCbr(*bb->getBrOnTrue()->getLabel(), *bb->getBrOnFalse()->getLabel());
    }

    if(bb->getBrOnTrue() != nullptr) {
      bb->getBrOnTrue()->accept(this);
    }
    if(bb->getBrOnFalse() != nullptr) {
      bb->getBrOnFalse()->accept(this);
    }
  }
  
  void CodegenVisitIr::visit(Method* m) {
    std::cout << "Visiting methods" << std::endl; // TEST
    Allocator alloc = Allocator(m);

    gen->genLabel(*m->getLabel());

    for (auto op : m->getOps()) {
      op->accept(this);
    }

    if(m->getBrOnTrue() == nullptr && m->getBrOnFalse() == nullptr) {
      //TODO: return (how does that work? lol I dunno)
    } else if(m->getBrOnFalse() == nullptr) {
      //Only True exists
      gen->genJmp(*m->getBrOnTrue()->getLabel());
    } else {
      //Both exist
      //gen->genCbr(*bb->getBrOnTrue()->getLabel(), *bb->getBrOnFalse()->getLabel());
    }

    if(m->getBrOnTrue() != nullptr) {
      m->getBrOnTrue()->accept(this);
    }
    if(m->getBrOnFalse() != nullptr) {
      m->getBrOnFalse()->accept(this);
    }

  }
  // generate code for noop
  void CodegenVisitIr::visit(Nop*) {
    std::cout << "Visiting nop" << std::endl; // TEST
    gen->genNoOp();
  }
  
  void CodegenVisitIr::visit(Fnop*) {
    std::cout << "visiting fnop" << std::endl; // TEST
    gen->fnop();
  }

  // generate addition code
  void CodegenVisitIr::visit(Add* a) {
    std::cout << "Visiting add" << std::endl; // TEST

    //need to compare dest to the inputs
    std::string r1 = Allocator::getRegister(a->getSrc1Register());
    std::string r2 = Allocator::getRegister(a->getSrc2Register());
    std::string dest = Allocator::getRegister(a->getDestRegister());

    if(dest == r1) {
      gen->genAdd(r2, r1);
    } else if(dest == r2) {
      gen->genAdd(r1, r2);
    } else {
      gen->genMov(r2, dest);
      gen->genAdd(r1, dest);
    }
  }

  void CodegenVisitIr::visit(Sub* a) {
    std::cout << "Visiting sub" << std::endl; // TEST

    //need to compare dest to the inputs
    std::string r1 = Allocator::getRegister(a->getSrc1Register());
    std::string r2 = Allocator::getRegister(a->getSrc2Register());
    std::string dest = Allocator::getRegister(a->getDestRegister());

    if(dest == r1) {
      gen->genSub(r2, r1);
    } else if(dest == r2) {
      gen->genSub(r1, r2);
      gen->genNeg(r2);
    } else {
      gen->genMov(r1, dest);
      gen->genSub(r2, dest);
    }

  }
  
  void CodegenVisitIr::visit(Mul* a) {
    std::cout << "Visiting mul" << std::endl; // TEST

    std::string s1 = Allocator::getRegister(a->getSrc1Register());
    std::string s2 = Allocator::getRegister(a->getSrc2Register());
    std::string dest = Allocator::getRegister(a->getDestRegister()); // needs to be rax

    // since ignoring overflow, save rdx and restore at end
    gen->genPush("%rdx");

    // no storing necessary!
    if (dest == "%rax") {
      // s1 is RAX! joyous times!
      if (s1 == dest) {
        gen->genMul(s2);
      }
      // s2 is RAX! Life is good!
      else if (s2 == dest) {
        gen->genMul(s1);
      }
      // ugh...more work
      else {
        gen->genMov(s1, "%rax");
        gen->genMul(s2);
      }
    }

    // so you want to do this the hard way huh?!?
    // so...
    // push rax
    // mov s1 into rax
    // mul s2
    // mov rax into dest
    // pop rax
    else {
      gen->genPush("%rax");
      gen->genMov(s1, "%rax");
      gen->genMul(s2);
      gen->genMov("%rax", dest);
      gen->genPop("%rax");
    }

    gen->genPop("%rdx"); // restore rdx
  }
  
  void CodegenVisitIr::visit(Div* a) {
    std::cout << "Visiting div" << std::endl; // TEST
    
    std::string s1 = Allocator::getRegister(a->getSrc1Register());
    std::string s2 = Allocator::getRegister(a->getSrc2Register());
    std::string dest = Allocator::getRegister(a->getDestRegister()); // needs to be rax

    // since ignoring remainder, save rdx and restore at end
    gen->genPush("%rdx");

    // no storing necessary!
    if (dest == "%rax") {
      // s1 is rax, need to swap with s2
      if (s1 == dest) {
        gen->genXchg(s1, s2);
        gen->genDiv(s2);
      }
      // s2 is RAX! Life is good!
      else if (s2 == dest) {
        gen->genDiv(s1);
      }
      // ugh...more work
      else {
        gen->genMov(s1, "%rax");
        gen->genDiv(s2);
      }
    }

    // so you want to do this the hard way huh?!?
    // so...
    // push rax
    // mov s1 into rax
    // div s2
    // mov rax into dest
    // pop rax
    else {
      gen->genPush("%rax");
      gen->genMov(s1, "%rax");
      gen->genDiv(s2);
      gen->genMov("%rax", dest);
      gen->genPop("%rax");
    }

    gen->genPop("%rdx"); // restore rdx
  }
  
  void CodegenVisitIr::visit(Mod*) {
    std::cerr << "Error, no modulus supported" << std::endl;
  }
  
  void CodegenVisitIr::visit(Fadd*) {

  }
  
  void CodegenVisitIr::visit(Fsub*) {

  }
  
  void CodegenVisitIr::visit(Fmul*) {

  }
  
  void CodegenVisitIr::visit(Fdiv*) {

  }
  
  void CodegenVisitIr::visit(Copy* op) {
    std::string con = "$" + std::to_string(op->getSrc1Register());
    std::string dest = Allocator::getRegister(op->getDestRegister());

    gen->genMov(con, dest);
  }
  
  void CodegenVisitIr::visit(Fcopy*) {

  }
  
  void CodegenVisitIr::visit(Conv*) {

  }
  
  void CodegenVisitIr::visit(Fconv*) {

  }
  
  void CodegenVisitIr::visit(LoadI* op) {
    std::cout << "Visiting loadi" << std::endl; // TEST

    std::string base = Allocator::getRegister(op->getSrc1Register());
    std::string offset = "$" + std::to_string(op->getSrc2Register());
    std::string dest = Allocator::getRegister(op->getDestRegister());

    if(offset == "$0") {
      gen->genMov("(" + base + ")", dest);
    } else {
      gen->genMov(base, dest);
      gen->genAdd(offset, dest);
      gen->genMov("(" + dest + ")", dest);
    }
  }
  
  void CodegenVisitIr::visit(LoadO*) {

  }
  
  void CodegenVisitIr::visit(StoreI* op) {
    std::cout << "Visiting storei" << std::endl; // TEST

    std::string src = Allocator::getRegister(op->getSrc1Register());
    std::string dest = Allocator::getRegister(op->getSrc2Register());
    std::string offset = "$" + std::to_string(op->getDestRegister());

    gen->genAdd(offset, dest);
    gen->genMov(src, "(" + dest + ")");
    gen->genSub(offset, dest);
  }
  
  void CodegenVisitIr::visit(StoreO*) {

  }
  
  void CodegenVisitIr::visit(CmpLT*) {

  }
  
  void CodegenVisitIr::visit(CmpLE*) {

  }
  
  void CodegenVisitIr::visit(CmpEQ*) {

  }
  
  void CodegenVisitIr::visit(FcmpLT*) {

  }
  
  void CodegenVisitIr::visit(FcmpLE*) {

  }
  
  void CodegenVisitIr::visit(FcmpEQ*) {

  }
  
  void CodegenVisitIr::visit(Br*) {

  }
  
  void CodegenVisitIr::visit(Cbr*) {

  }
  
  void CodegenVisitIr::visit(Call*) {

  }
  
  void CodegenVisitIr::visit(Dcall*) {

  }
  
  void CodegenVisitIr::visit(Fcall*) {

  }
  
  void CodegenVisitIr::visit(Dfcall*) {

  }
  
  void CodegenVisitIr::visit(Push* op) {
    std::cout << "Visiting push" << std::endl; // TEST

    std::string src = Allocator::getRegister(op->getSrc1Register());

    gen->genPush(src);
  }
  
  void CodegenVisitIr::visit(Fpush*) {

  }
  
  void CodegenVisitIr::visit(Pop* op) {
    std::cout << "Visiting pop" << std::endl; // TEST

    std::string dest = Allocator::getRegister(op->getDestRegister());

    gen->genPop(dest);
  }
  
  void CodegenVisitIr::visit(Fpop*) {

  }
  
  void CodegenVisitIr::visit(Ccall*) {

  }
  
  void CodegenVisitIr::visit(Alloc* op) {
    std::cout << "Visiting alloc" << std::endl; // TEST

    std::string bytes = "$" + std::to_string(op->getSrc1Register() / 8);
    std::string dest = Allocator::getRegister(op->getDestRegister());

    /**
     * Move the amount to allocate to rdi, run call malloc, retval is in rax.
     * I don't think anything is clobbered but can't find evidence for sure either way.
     */
    gen->genPush("%rdi");
    if("%rax" != dest) {
      gen->genPush("%rax");
    }
    gen->genMov(bytes, "%rdi");
    gen->genCall("malloc");
    if("%rax" != dest) {
      gen->genMov("%rax", dest);
      gen->genPop("%rax");
    }
    gen->genPop("%rdi");
  }
  
  void CodegenVisitIr::visit(Free* op) {
    std::cout << "Visiting free" << std::endl;

    std::string tofree = Allocator::getRegister(op->getSrc1Register());

    if(tofree != "%rdi") {
      gen->genPush("%rdi");
      gen->genMov(tofree, "%rdi");
    }
    gen->genCall("free");
    if(tofree != "%rdi") {
      gen->genPop("%rdi");
    }
  }
  
  void CodegenVisitIr::visit(Abort*) {

  }
  
  void CodegenVisitIr::visit(TypeName*) {

  }
  
  void CodegenVisitIr::visit(ShallowCopy*) {

  }
  
  void CodegenVisitIr::visit(OutString*) {

  }
  
  void CodegenVisitIr::visit(OutInt* n) {
    // push r12, r13, r14 to save them
    gen->pushAll();

    // push the arguments in reverse order
    // the arguments are the self and the integer value.

    gen->genPush("%rbp");
    gen->genPush(Allocator::getRegister(n->getDestRegister()));
    

    // call outint HARDCODED!!! TODO: Not hard coded lol
    gen->genMov("$IO.out_int", "%r14");
    gen->genCall("*%r14");
    

    // pop the arguments
    gen->genPop(Allocator::getRegister(n->getDestRegister()));
    gen->genPop("%rbp");


    // pop r12, r13, r14
    gen->popAll();

    // win
  }
  
  void CodegenVisitIr::visit(InString*) {

  }
  
  void CodegenVisitIr::visit(InInt*) {

  }
  
  void CodegenVisitIr::visit(Length*) {

  }
  
  void CodegenVisitIr::visit(Concat*) {

  }
  
  void CodegenVisitIr::visit(Substr*) {

  }

  // determine if a class is a built-in or not and yeah
  std::string CodegenVisitIr::getMethClass(std::string s) {
    // object
    if (s == "abort") {
      return "Object";
    }
    else if (s == "copy") {
      return "Object";
    }
    else if (s == "type_name") {
      return "Object";
    }

    // IO
    else if (s == "in_int") {
      return "IO";
    }
    else if (s == "in_string") {
      return "IO";
    }
    else if (s == "out_int") {
      return "IO";
    }
    else if (s == "out_string") {
      return "IO";
    }

    // string
    else if (s == "concat") {
      return "String";
    }
    else if (s == "length") {
      return "String";
    }
    else if (s == "substr") {
      return "String";
    }
    
    return "";
  }
}
