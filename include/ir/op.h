
#pragma once

#include "ir/ir_visitor.h"

namespace ir {

  enum RegisterType { INT8 = 8, INT = 32, INT64 = 64, FLOAT = 64, BOOL = 8};

  class Op {
  public:
    int getSrc1Register() { return src1.first; }
    int getSrc2Register() { return src2.first; }
    int getDestRegister() { return dest.first; }

    RegisterType getSrc1Size() { return src1.second; }
    RegisterType getSrc2Size() { return src2.second; }
    RegisterType getDestSize() { return dest.second; }

    void setSrc1Register(int reg) { src1.first = reg; }
    void setSrc2Register(int reg) { src2.first= reg; }
    void setDestRegister(int reg) { dest.first = reg; }

    void setSrc1Size(RegisterType type) { src1.second = type; }
    void setSrc2Size(RegisterType type) { src2.second = type; }
    void setDestSize(RegisterType type) { dest.second = type; }

  private:
    std::pair <int,RegisterType> src1;
    std::pair <int,RegisterType> src2;
    std::pair <int,RegisterType> dest;

  };

  /* Placeholder classes meant to replace the need of Type enum. */
  class Nop : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fnop : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Sub : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mul : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Div : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mod : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fadd : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fsub : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fmul : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fdiv : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Copy : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fcopy : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Conv : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fconv : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadI : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadO : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class StoreI : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class StoreO : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLT : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLE : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpEQ : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLT : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLE : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpEQ : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Br : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Cbr : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Call : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Dcall : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fcall : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Dfcall : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Push : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpush : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Pop : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpop : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Ccall : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Alloc : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Free : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };


  /* Built-ins */
  class Abort {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class TypeName {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class ShallowCopy {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class OutString {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class OutInt {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class InString {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class InInt {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class Length {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class Concat {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
  class Substr {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
}
