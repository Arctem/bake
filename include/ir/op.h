
#pragma once

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
  class Nop : Op { };
  class Fnop : Op { };
  class Sub : Op { };
  class Mul : Op { };
  class Div : Op { };
  class Mod : Op { };
  class Fadd : Op { };
  class Fsub : Op { };
  class Fmul : Op { };
  class Fdiv : Op { };
  class Copy : Op { };
  class Fcopy : Op { };
  class Conv : Op { };
  class Fconv : Op { };
  class LoadI : Op { };
  class LoadO : Op { };
  class StoreI : Op { };
  class StoreO : Op { };
  class CmpLT : Op { };
  class CmpLE : Op { };
  class CmpEQ : Op { };
  class FcmpLT : Op { };
  class FcmpLE : Op { };
  class FcmpEQ : Op { };
  class Br : Op { };
  class Cbr : Op { };
  class Call : Op { };
  class Dcall : Op { };
  class Fcall : Op { };
  class Dfcall : Op { };
  class Push : Op { };
  class Fpush : Op { };
  class Pop : Op { };
  class Fpop : Op { };
  class Ccall : Op { };
  class Alloc : Op { };
  class Free : Op { } ;

  /* Built-ins */
  class Abort { };
  class TypeName { };
  class ShallowCopy { };
  class OutString { };
  class OutInt { };
  class InString { };
  class InInt { };
  class Length { };
  class Concat { };
  class Substr { };
}