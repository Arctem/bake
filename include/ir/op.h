
#pragma once

#include "ir/ir_visitor.h"

namespace ir {

  enum RegisterType { INT8 = 8, INT = 32, INT64 = 64, FLOAT = 64, BOOL = 8, EMPTY = -1, CONSTANT = -2};

  class Op {
  public:
    Op(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : src1(src1), src2(src2), dest(dest){};

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

    // Aliased Registers getters
    int getLoadBaseRegister() { return src1.first; }
    int getLoadOffsetRegister() { return src2.first; }
    int getStoreBaseRegister() { return src2.first; }
    int gestStoreOffsetRegister() { return dest.first; }
    int getSrcRegister() { return src1.first; }
    int getFunctionOffsetRegister() { return src1.first; }
    int getObjectOffsetRegister() { return src2.first; }

    // Alliased Register Sizes getters
    RegisterType getLoadBaseSize() { return src1.second; }
    RegisterType getLoadOffsetSize() { return src2.second; }
    RegisterType getStoreBaseSize() { return src2.second; }
    RegisterType gestStoreOffsetSize() { return dest.second; }
    RegisterType getSrcSize() { return src1.second; }
    RegisterType getFunctionOffsetSize() { return src1.second; }
    RegisterType getObjectOffsetSize() { return src2.second; }

    // Aliased Registers setters
    void setLoadBaseRegister(int reg) { src1.first = reg; }
    void setLoadOffsetRegister(int reg) { src2.first = reg; }
    void setStoreBaseRegister(int reg) { src2.first = reg; }
    void sestStoreOffsetRegister(int reg) { dest.first = reg; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setFunctionOffsetRegister(int reg) { src1.first = reg; }
    void setObjectOffsetRegister(int reg) { src2.first = reg; }

    // Alliased Register Sizes setters
    void setLoadBaseSize(RegisterType type) { src1.second = type; }
    void setLoadOffsetSize(RegisterType type) { src2.second = type; }
    void setStoreBaseSize(RegisterType type) { src2.second = type; }
    void sestStoreOffsetSize(RegisterType type) { dest.second = type; }(RegisterType type) { src1.second = type; }(RegisterType type) { src1.second = type; }
    void setSrcSize(RegisterType type) { src1.second = type; }(RegisterType type) { src1.second = type; }
    void setFunctionOffsetSize(RegisterType type) { src1.second = type; }
    void setObjectOffsetSize(RegisterType type) { src2.second = type; }

  private:
    std::pair <int,RegisterType> src1;
    std::pair <int,RegisterType> src2;
    std::pair <int,RegisterType> dest;

  };

  /* Placeholder classes meant to replace the need of Type enum. */
  class Nop : Op {
  public:
    Nop() : Op(std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fnop : Op {
  public:
    Fnop() : Op(std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Sub : Op {
  public:
    Sub(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mul : Op {
  public:
    Mul(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Div : Op {
  public:
    Div(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mod : Op {
  public:
    Mod(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fadd : Op {
  public:
    Fadd(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fsub : Op {
  public:
    Fsub(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fmul : Op {
  public:
    Fmul(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fdiv : Op {
  public:
    Fdiv(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Copy : Op {
  public:
    Copy(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
        : Op(src, std::make_pair(-1, EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fcopy : Op {
  public:
    Fcopy(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
        : Op(src, std::make_pair(-1, EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Conv : Op {
  public:
    Conv(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fconv : Op {
  public:
    Fconv(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadI : Op {
  public:
    LoadI(std::pair<int,RegisterType> base, int offset, std::pair<int,RegisterType> dest)
      : Op(base, std::make_pair(offset, CONSTANT), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadO : Op {
  public:
    LoadO(std::pair<int,RegisterType> base, std::pair<int,RegisterType> regOffset, std::pair<int,RegisterType> dest)
      : Op(base, regOffset, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class StoreI : Op {
  public:
    StoreI(std::pair<int,RegisterType> src, std::pair<int,RegisterType> base, int offset)
        : Op(src, base, std::make_pair(offset, CONSTANT)) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class StoreO : Op {
  public:
    StoreO(std::pair<int,RegisterType> src, std::pair<int,RegisterType> base, std::pair<int,RegisterType> regOffset)
      : Op(src, base, regOffset) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLT : Op {
  public:
    CmpLT(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLE : Op {
  public:
    CmpLE(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpEQ : Op {
  public:
    CmpEQ(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLT : Op {
  public:
    FcmpLT(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLE : Op {
  public:
    FcmpLE(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpEQ : Op {
  public:
    FcmpEQ(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Br : Op {
  public:
    Br() : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Cbr : Op {
  public:
    Cbr(std::pair<int,RegisterType> src)
      : Op(src,std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY)) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO: Ask russell about what type of parameters
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
    Push(std::pair<int,RegisterType> src)
      : Op(src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
     virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpush : Op {
  public:
    Fpush(std::pair<int,RegisterType> src)
      : Op(src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Pop : Op {
  public:
    Pop(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpop : Op {
  public:
    Fpop(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO: Do we need this?
  class Ccall : Op {
  public:
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Alloc : Op {
  public:
    Alloc(int size, std::pair<int,RegisterType> dest)
      : Op(std::make_pair(size,CONSTANT), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Free : Op {
  public:
    Free(std::pair<int,RegisterType> src)
      : Op(src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO the built in
  /* Built-ins */
  class Abort : Op {
  public:
    Abort(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1, EMPTY),std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class TypeName : Op {
  public:
    TypeName(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class ShallowCopy : Op {
  public:
    ShallowCopy(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO figure out if the register can do strints
  class OutString : Op {
  public:
    OutString(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class OutInt : Op {
  public:
    OutInt(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO make sure this is how to return strings
  class InString : Op {
  public:
    InString(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class InInt : Op {
  public:
    InInt(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : check strings
  class Length : Op {
  public:
    Length(std::pair<int,RegisterType> dest)
      : Op(std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : Check strings
  class Concat : Op {
  public:
    Concat(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : Check strings
  class Substr : Op {
  public:
    Substr(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
}
