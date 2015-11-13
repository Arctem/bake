
#pragma once

#include "ir/ir_visitor.h"

namespace ir {
  class Op {
  public:
    int getSrc1() { return src1; }
    int getSrc2() { return src2; }
    int getDest() { return dest; }

    void setSrc1(int reg) { src1 = reg; }
    void setSrc2(int reg) { src2 = reg; }
    void setDest(int reg) { dest = reg; }

  private:
    int src1;
    int src2;
    int dest;
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