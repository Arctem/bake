#pragma once

#include "codegen/generator.h"
#include "codegen/allocator.h"
#include "ir/ir_visitor.h"
#include "ir/class_list.h"
#include "ir/basic_block.h"
#include "ir/op.h"

using namespace ir;

namespace codegen {
  class Generator;

  class CodegenVisitIr : IrVisitor {
  public:
    CodegenVisitIr();

    virtual void visit(ir::ClassList*);
    virtual void visit(ClassDef*);
    virtual void visit(BasicBlock*);
    virtual void visit(Method*);
    virtual void visit(Nop*);
    virtual void visit(Fnop*);
    virtual void visit(Add*);
    virtual void visit(Sub*);
    virtual void visit(Mul*);
    virtual void visit(Div*);
    virtual void visit(Mod*);
    virtual void visit(Fadd*);
    virtual void visit(Fsub*);
    virtual void visit(Fmul*);
    virtual void visit(Fdiv*);
    virtual void visit(Copy*);
    virtual void visit(Fcopy*);
    virtual void visit(Conv*);
    virtual void visit(Fconv*);
    virtual void visit(LoadI*);
    virtual void visit(LoadO*);
    virtual void visit(StoreI*);
    virtual void visit(StoreO*);
    virtual void visit(CmpLT*);
    virtual void visit(CmpLE*);
    virtual void visit(CmpEQ*);
    virtual void visit(FcmpLT*);
    virtual void visit(FcmpLE*);
    virtual void visit(FcmpEQ*);
    virtual void visit(Br*);
    virtual void visit(Cbr*);
    virtual void visit(Call*);
    virtual void visit(Dcall*);
    virtual void visit(Fcall*);
    virtual void visit(Dfcall*);
    virtual void visit(Push*);
    virtual void visit(Fpush*);
    virtual void visit(Pop*);
    virtual void visit(Fpop*);
    virtual void visit(Ccall*);
    virtual void visit(Alloc*);
    virtual void visit(Free*);
    virtual void visit(Abort*);
    virtual void visit(TypeName*);
    virtual void visit(ShallowCopy*);
    virtual void visit(OutString*);
    virtual void visit(OutInt*);
    virtual void visit(InString*);
    virtual void visit(InInt*);
    virtual void visit(Length*);
    virtual void visit(Concat*);
    virtual void visit(Substr*);

    ~CodegenVisitIr() { delete gen; }

  private:
    Generator* gen;

    ClassDef* mainClass;

    std::string getMethClass(std::string s);
  };
}
