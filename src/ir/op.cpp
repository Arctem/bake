
#include "ir/op.h"

void ir::Op::accept(IrVisitor* v) {
  switch(getOpType()) {
  case NOP:
    ((Nop*) this)->accept(v);
    break;
  case FNOP:
    ((Fnop*) this)->accept(v);
    break;
  case ADD:
    ((Add*) this)->accept(v);
    break;
  case SUB:
    ((Sub*) this)->accept(v);
    break;
  case MUL:
    ((Mul*) this)->accept(v);
    break;
  case DIV:
    ((Div*) this)->accept(v);
    break;
  case MOD:
    ((Mod*) this)->accept(v);
    break;
  case FADD:
    ((Fadd*) this)->accept(v);
    break;
  case FSUB:
    ((Fsub*) this)->accept(v);
    break;
  case FMUL:
    ((Fmul*) this)->accept(v);
    break;
  case FDIV:
    ((Fdiv*) this)->accept(v);
    break;
  case COPY:
    ((Copy*) this)->accept(v);
    break;
  case FCOPY:
    ((Fcopy*) this)->accept(v);
    break;
  case CONV:
    ((Conv*) this)->accept(v);
    break;
  case FCONV:
    ((Fconv*) this)->accept(v);
    break;
  case LOADI:
    ((LoadI*) this)->accept(v);
    break;
  case LOADO:
    ((LoadO*) this)->accept(v);
    break;
  case STOREI:
    ((StoreI*) this)->accept(v);
    break;
  case STOREO:
    ((StoreO*) this)->accept(v);
    break;
  case CMPLT:
    ((CmpLT*) this)->accept(v);
    break;
  case CMPLE:
    ((CmpLE*) this)->accept(v);
    break;
  case CMPEQ:
    ((CmpEQ*) this)->accept(v);
    break;
  case FCMPLT:
    ((FcmpLT*) this)->accept(v);
    break;
  case FCMPLE:
    ((FcmpLE*) this)->accept(v);
    break;
  case FCMPEQ:
    ((FcmpEQ*) this)->accept(v);
    break;
  case BR:
    ((Br*) this)->accept(v);
    break;
  case CBR:
    ((Cbr*) this)->accept(v);
    break;
  case CALL:
    ((Call*) this)->accept(v);
    break;
  case DCALL:
    ((Dcall*) this)->accept(v);
    break;
  case FCALL:
    ((Fcall*) this)->accept(v);
    break;
  case DFCALL:
    ((Dfcall*) this)->accept(v);
    break;
  case PUSH:
    ((Push*) this)->accept(v);
    break;
  case FPUSH:
    ((Fpush*) this)->accept(v);
    break;
  case POP:
    ((Pop*) this)->accept(v);
    break;
  case FPOP:
    ((Fpop*) this)->accept(v);
    break;
  case CCALL:
    ((Ccall*) this)->accept(v);
    break;
  case ALLOC:
    ((Alloc*) this)->accept(v);
    break;
  case FREE:
    ((Free*) this)->accept(v);
    break;
  case ABORT:
    ((Abort*) this)->accept(v);
    break;
  case TYPENAME:
    ((TypeName*) this)->accept(v);
    break;
  case SHALLOWCOPY:
    ((ShallowCopy*) this)->accept(v);
    break;
  case OUTSTRING:
    ((OutString*) this)->accept(v);
    break;
  case OUTINT:
    ((OutInt*) this)->accept(v);
    break;
  case INSTRING:
    ((InString*) this)->accept(v);
    break;
  case ININT:
    ((InInt*) this)->accept(v);
    break;
  case LENGTH:
    ((Length*) this)->accept(v);
    break;
  case CONCAT:
    ((Concat*) this)->accept(v);
    break;
  case SUBSTR:
    ((Substr*) this)->accept(v);
    break;
  case CREATEOBJ:
    ((CreateObj*) this)->accept(v);
    break;
  case BITNOT:
    ((BitNot*) this)->accept(v);
    break;
  case LOGNOT:
    ((LogNot*) this)->accept(v);
    break;
  }
}
