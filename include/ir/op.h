#pragma once

#include <utility>
#include "ir/ir_visitor.h"

namespace ir {

  enum RegisterType { INT8 = 8, INT = 32, INT64 = 64, FLOAT = 64, BOOL = 8, EMPTY = -1, CONSTANT = -2};

  enum OpType { NOP, FNOP, ADD, SUB, MUL, DIV, MOD, FADD, FSUB, FMUL, FDIV, COPY, FCOPY, CONV, FCONV,
                LOADI, LOADO, STOREI, STOREO, CMPLT, CMPLE, CMPEQ, FCMPLT, FCMPLE, FCMPEQ, BR, CBR,
                CALL, DCALL, FCALL, DFCALL, PUSH, FPUSH, POP, FPOP, CCALL, ALLOC, FREE, ABORT, TYPENAME,
                SHALLOWCOPY, OUTSTRING, OUTINT, INSTRING, ININT, LENGTH, CONCAT, SUBSTR };

  class Op {
  public:
    Op(OpType ot, std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : src1(src1), src2(src2), dest(dest), op_type(ot) { };
    Op(OpType ot) : op_type(ot) { };

    int getSrc1Register() { return src1.first; }
    int getSrc2Register() { return src2.first; }
    int getDestRegister() { return dest.first; }

    RegisterType getSrc1Size() { return src1.second; }
    RegisterType getSrc2Size() { return src2.second; }
    RegisterType getDestSize() { return dest.second; }

    void setSrc1Register(int reg) { src1.first = reg; }
    void setSrc2Register(int reg) { src2.first = reg; }
    void setDestRegister(int reg) { dest.first = reg; }

    void setSrc1Size(RegisterType type) { src1.second = type; }
    void setSrc2Size(RegisterType type) { src2.second = type; }
    void setDestSize(RegisterType type) { dest.second = type; }

    OpType getOpType() { return op_type; }

    virtual void accept(IrVisitor* v); // Check the type of this op cast it before forwarding the visitor

  protected:
    std::pair <int,RegisterType> src1;
    std::pair <int,RegisterType> src2;
    std::pair <int,RegisterType> dest;

    OpType op_type;
  };

  /* Placeholder classes meant to replace the need of Type enum. */
  class Nop : public Op {
  public:
    Nop() : Op(NOP, std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fnop : public Op {
  public:
    Fnop() : Op(FNOP, std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY),std::make_pair(-1, EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Add : public Op {
  public:
    Add(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(ADD, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Sub : public Op {
  public:
    Sub(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(SUB, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mul : public Op {
  public:
    Mul(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(MUL, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Div : public Op {
  public:
    Div(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(DIV, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Mod : public Op {
  public:
    Mod(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(MOD, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fadd : public Op {
  public:
    Fadd(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(FADD, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fsub : public Op {
  public:
    Fsub(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(FSUB, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fmul : public Op {
  public:
    Fmul(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(FMUL, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fdiv : public Op {
  public:
    Fdiv(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
        : Op(FDIV, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Copy : public Op {
  public:
    Copy(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
        : Op(COPY, src, std::make_pair(-1, EMPTY), dest) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO: How are we going to do fcopy??
  class Fcopy : public Op {
  public:
    Fcopy(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
        : Op(FCOPY, src, std::make_pair(-1, EMPTY), dest) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Conv : public Op {
  public:
    Conv(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(CONV, src, std::make_pair(-1,EMPTY), dest) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fconv : public Op {
  public:
    Fconv(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(FCONV, src, std::make_pair(-1,EMPTY), dest) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadI : public Op {
  public:
    LoadI(std::pair<int,RegisterType> base, int offset, std::pair<int,RegisterType> dest)
      : Op(LOADI, base, std::make_pair(offset, CONSTANT), dest) {};

      // Load Base
      int getLoadBaseRegister() { return src1.first; }
      RegisterType getLoadBaseSize() { return src1.second; }
      void setLoadBaseRegister(int reg) { src1.first = reg; }
      void setLoadBaseSize(RegisterType type) { src1.second = type; }

      // Load Offset
      int getLoadOffsetRegister() { return src2.first; }
      RegisterType getLoadOffsetSize() { return src2.second; }
      void setLoadOffsetRegister(int reg) { src2.first = reg; }
      void setLoadOffsetSize(RegisterType type) { src2.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class LoadO : public Op {
  public:
    LoadO(std::pair<int,RegisterType> base, std::pair<int,RegisterType> regOffset, std::pair<int,RegisterType> dest)
      : Op(LOADO, base, regOffset, dest) {};

    // Load Base
    int getLoadBaseRegister() { return src1.first; }
    RegisterType getLoadBaseSize() { return src1.second; }
    void setLoadBaseRegister(int reg) { src1.first = reg; }
    void setLoadBaseSize(RegisterType type) { src1.second = type; }

    // Load Offset
    int getLoadOffsetRegister() { return src2.first; }
    RegisterType getLoadOffsetSize() { return src2.second; }
    void setLoadOffsetRegister(int reg) { src2.first = reg; }
    void setLoadOffsetSize(RegisterType type) { src2.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class StoreI : public Op {
  public:
    StoreI(std::pair<int,RegisterType> src, std::pair<int,RegisterType> base, int offset)
        : Op(STOREI, src, base, std::make_pair(offset, CONSTANT)) { };

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    // Store Base
    int getStoreBaseRegister() { return src2.first; }
    RegisterType getStoreBaseSize() { return src2.second; }
    void setStoreBaseRegister(int reg) { src2.first = reg; }
    void setStoreBaseSize(RegisterType type) { src2.second = type; }

    // Store Offset
    int gestStoreOffsetRegister() { return dest.first; }
    RegisterType gestStoreOffsetSize() { return dest.second; }
    void sestStoreOffsetRegister(int reg) { dest.first = reg; }
    void sestStoreOffsetSize(RegisterType type) { dest.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };


  class StoreO : public Op {
  public:
    StoreO(std::pair<int,RegisterType> src, std::pair<int,RegisterType> base, std::pair<int,RegisterType> regOffset)
      : Op(STOREO, src, base, regOffset) { };

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    // Store Base
    int getStoreBaseRegister() { return src2.first; }
    RegisterType getStoreBaseSize() { return src2.second; }
    void setStoreBaseRegister(int reg) { src2.first = reg; }
    void setStoreBaseSize(RegisterType type) { src2.second = type; }

    // Store Offset
    int gestStoreOffsetRegister() { return dest.first; }
    RegisterType gestStoreOffsetSize() { return dest.second; }
    void sestStoreOffsetRegister(int reg) { dest.first = reg; }
    void sestStoreOffsetSize(RegisterType type) { dest.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLT : public Op {
  public:
    CmpLT(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(CMPLT, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpLE : public Op {
  public:
    CmpLE(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(CMPLE, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class CmpEQ : public Op {
  public:
    CmpEQ(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(CMPEQ, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLT : public Op {
  public:
    FcmpLT(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(FCMPLT, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpLE : public Op {
  public:
    FcmpLE(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(FCMPLE, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class FcmpEQ : public Op {
  public:
    FcmpEQ(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(FCMPEQ, src1, src2, dest) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Br : public Op {
  public:
    Br() : Op(BR, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Cbr : public Op {
  public:
    Cbr(std::pair<int,RegisterType> src)
      : Op(CBR, src, std::make_pair(-1, EMPTY), std::make_pair(-1, EMPTY)) { };

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO: Ask russell about what type of parameters
  class Call : public Op {
  public:
    Call() : Op(CALL) { };
    virtual void accept(IrVisitor* v) { v->visit(this); }

    // Function Offset
    int getFunctionOffsetRegister() { return src1.first; }
    RegisterType getFunctionOffsetSize() { return src1.second; }
    void setFunctionOffsetRegister(int reg) { src1.first = reg; }
    void setFunctionOffsetSize(RegisterType type) { src1.second = type; }
  };

  class Dcall : public Op {
  public:
    Dcall() : Op(DCALL) { }

    virtual void accept(IrVisitor* v) { v->visit(this); }

    // Function Offset
    int getFunctionOffsetRegister() { return src1.first; }
    RegisterType getFunctionOffsetSize() { return src1.second; }
    void setFunctionOffsetRegister(int reg) { src1.first = reg; }
    void setFunctionOffsetSize(RegisterType type) { src1.second = type; }

    // Object Offset
    int getObjectOffsetRegister() { return src2.first; }
    RegisterType getObjectOffsetSize() { return src2.second; }
    void setObjectOffsetRegister(int reg) { src2.first = reg; }
    void setObjectOffsetSize(RegisterType type) { src2.second = type; }
  };

  class Fcall : public Op {
  public:
    Fcall() : Op(FCALL) { }

    virtual void accept(IrVisitor* v) { v->visit(this); }

    // Function Offset
    int getFunctionOffsetRegister() { return src1.first; }
    RegisterType getFunctionOffsetSize() { return src1.second; }
    void setFunctionOffsetRegister(int reg) { src1.first = reg; }
    void setFunctionOffsetSize(RegisterType type) { src1.second = type; }
  };

  class Dfcall : public Op {
  public:
    Dfcall() : Op(DFCALL) { }

    virtual void accept(IrVisitor* v) { v->visit(this); }

    // Function Offset
    int getFunctionOffsetRegister() { return src1.first; }
    RegisterType getFunctionOffsetSize() { return src1.second; }
    void setFunctionOffsetRegister(int reg) { src1.first = reg; }
    void setFunctionOffsetSize(RegisterType type) { src1.second = type; }

    // Object Offset
    int getObjectOffsetRegister() { return src2.first; }
    RegisterType getObjectOffsetSize() { return src2.second; }
    void setObjectOffsetRegister(int reg) { src2.first = reg; }
    void setObjectOffsetSize(RegisterType type) { src2.second = type; }
  };

  class Push : public Op {
  public:
    Push(std::pair<int,RegisterType> src)
      : Op(PUSH, src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

     virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpush : public Op {
  public:
    Fpush(std::pair<int,RegisterType> src)
      : Op(FPUSH, src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};

    int getSrcRegister() { return src1.first; }
    RegisterType getSrcSize() { return src1.second; }
    void setSrcRegister(int reg) { src1.first = reg; }
    void setSrcSize(RegisterType type) { src1.second = type; }

    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Pop : public Op {
  public:
    Pop(std::pair<int,RegisterType> dest)
      : Op(POP, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Fpop : public Op {
  public:
    Fpop(std::pair<int,RegisterType> dest)
      : Op(FPOP, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO: Do we need this?
  class Ccall : public Op {
  public:
    Ccall() : Op(CCALL) { }
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Alloc : public Op {
  public:
    Alloc(int size, std::pair<int,RegisterType> dest)
      : Op(ALLOC, std::make_pair(size,CONSTANT), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class Free : public Op {
  public:
    Free(std::pair<int,RegisterType> src)
      : Op(FREE, src, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY)) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO the built in
  /* Built-ins */
  class Abort : public Op {
  public:
    Abort(std::pair<int,RegisterType> dest)
      : Op(ABORT, std::make_pair(-1, EMPTY),std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class TypeName : public Op {
  public:
    TypeName(std::pair<int,RegisterType> dest)
      : Op(TYPENAME, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class ShallowCopy : public Op {
  public:
    ShallowCopy(std::pair<int,RegisterType> dest)
      : Op(SHALLOWCOPY, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO figure out if the register can do strints
  class OutString : public Op {
  public:
    OutString(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(OUTSTRING, src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class OutInt : public Op {
  public:
    OutInt(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(OUTINT, src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO make sure this is how to return strings
  class InString : public Op {
  public:
    InString(std::pair<int,RegisterType> dest)
      : Op(INSTRING, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  class InInt : public Op {
  public:
    InInt(std::pair<int,RegisterType> dest)
      : Op(ININT, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : check strings
  class Length : public Op {
  public:
    Length(std::pair<int,RegisterType> dest)
      : Op(LENGTH, std::make_pair(-1,EMPTY), std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : Check strings
  class Concat : public Op {
  public:
    Concat(std::pair<int,RegisterType> src, std::pair<int,RegisterType> dest)
      : Op(CONCAT, src, std::make_pair(-1,EMPTY), dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };

  // TODO : Check strings
  class Substr : public Op {
  public:
    Substr(std::pair<int,RegisterType> src1, std::pair<int,RegisterType> src2, std::pair<int,RegisterType> dest)
      : Op(SUBSTR, src1, src2, dest) {};
    virtual void accept(IrVisitor* v) { v->visit(this); }
  };
}
