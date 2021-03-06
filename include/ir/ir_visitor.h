
#pragma once

namespace ir {
  class ClassList;
  class ClassDef;
  class BasicBlock;
  class Method;
  class Nop;
  class Fnop;
  class Add;
  class Sub;
  class Mul;
  class Div;
  class Mod;
  class Fadd;
  class Fsub;
  class Fmul;
  class Fdiv;
  class Copy;
  class Fcopy;
  class Conv;
  class Fconv;
  class LoadI;
  class LoadO;
  class StoreI;
  class StoreO;
  class CmpLT;
  class CmpLE;
  class CmpEQ;
  class FcmpLT;
  class FcmpLE;
  class FcmpEQ;
  class Br;
  class Cbr;
  class Call;
  class Dcall;
  class Fcall;
  class Dfcall;
  class Push;
  class Fpush;
  class Pop;
  class Fpop;
  class Ccall;
  class Alloc;
  class Free;
  class Abort;
  class TypeName;
  class ShallowCopy;
  class OutString;
  class OutInt;
  class InString;
  class InInt;
  class Length;
  class Concat;
  class Substr;
  class CreateObj;
  class LogNot;
  class BitNot;

  class IrVisitor {
  public:
    virtual void visit(ClassList*) = 0;
    virtual void visit(ClassDef*) = 0;
    virtual void visit(BasicBlock*) = 0;
    virtual void visit(Method*) = 0;
    virtual void visit(Nop*) = 0;
    virtual void visit(Fnop*) = 0;
    virtual void visit(Add*) = 0;
    virtual void visit(Sub*) = 0;
    virtual void visit(Mul*) = 0;
    virtual void visit(Div*) = 0;
    virtual void visit(Mod*) = 0;
    virtual void visit(Fadd*) = 0;
    virtual void visit(Fsub*) = 0;
    virtual void visit(Fmul*) = 0;
    virtual void visit(Fdiv*) = 0;
    virtual void visit(Copy*) = 0;
    virtual void visit(Fcopy*) = 0;
    virtual void visit(Conv*) = 0;
    virtual void visit(Fconv*) = 0;
    virtual void visit(LoadI*) = 0;
    virtual void visit(LoadO*) = 0;
    virtual void visit(StoreI*) = 0;
    virtual void visit(StoreO*) = 0;
    virtual void visit(CmpLT*) = 0;
    virtual void visit(CmpLE*) = 0;
    virtual void visit(CmpEQ*) = 0;
    virtual void visit(FcmpLT*) = 0;
    virtual void visit(FcmpLE*) = 0;
    virtual void visit(FcmpEQ*) = 0;
    virtual void visit(Br*) = 0;
    virtual void visit(Cbr*) = 0;
    virtual void visit(Call*) = 0;
    virtual void visit(Dcall*) = 0;
    virtual void visit(Fcall*) = 0;
    virtual void visit(Dfcall*) = 0;
    virtual void visit(Push*) = 0;
    virtual void visit(Fpush*) = 0;
    virtual void visit(Pop*) = 0;
    virtual void visit(Fpop*) = 0;
    virtual void visit(Ccall*) = 0;
    virtual void visit(Alloc*) = 0;
    virtual void visit(Free*) = 0;
    virtual void visit(Abort*) = 0;
    virtual void visit(TypeName*) = 0;
    virtual void visit(ShallowCopy*) = 0;
    virtual void visit(OutString*) = 0;
    virtual void visit(OutInt*) = 0;
    virtual void visit(InString*) = 0;
    virtual void visit(InInt*) = 0;
    virtual void visit(Length*) = 0;
    virtual void visit(Concat*) = 0;
    virtual void visit(Substr*) = 0;
    virtual void visit(CreateObj*) = 0;
    virtual void visit(BitNot*) = 0;
    virtual void visit(LogNot*) = 0;
  };

  class IrPrint : IrVisitor {
  public:
    void preops();
    void printRegPair(std::pair<int, int>);

    virtual void visit(ClassList*);
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
    virtual void visit(CreateObj*);
    virtual void visit(BitNot*);
    virtual void visit(LogNot*);

  private:
    int level = 0;
  };
}
