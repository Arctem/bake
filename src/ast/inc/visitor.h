
#ifndef __VISITOR__
#define __VISITOR__

namespace bake_ast {
  class Node;
  class IntegerVal;
  class StringVal;
  class BoolVal;
  class Id;
  class Type;
  class BinaryOp;
  class UnaryOp;
  class LogicalNot;
  class BitNot;
  class Isvoid;
  class New;

  class Visitor {
  public:
    Visitor() {};
    virtual ~Visitor() {};

    virtual void visit(IntegerVal*) = 0;
    virtual void visit(StringVal*) = 0;
    virtual void visit(BoolVal*) = 0;
    virtual void visit(Id*) = 0;
    virtual void visit(Type*) = 0;
    virtual void visit(BinaryOp*) = 0;
    virtual void visit(UnaryOp*) = 0;
    virtual void visit(LogicalNot*) = 0;
    virtual void visit(BitNot*) = 0;
    virtual void visit(Isvoid*) = 0;
    virtual void visit(New*) = 0;
  };

  class PrettyPrint : public Visitor {
  public:
    PrettyPrint() : depth(0) {};
    void visit(IntegerVal*);
    void visit(StringVal*);
    void visit(BoolVal*);
    void visit(Id*);
    void visit(Type*);
    void visit(BinaryOp*);
    void visit(UnaryOp*);
    void visit(LogicalNot*);
    void visit(BitNot*);
    void visit(Isvoid*);
    void visit(New*);

  private:
    int depth; // Holds how many levels down the tree this print has gone

    /* What should the printer do before it visits every node (e.g., print leading whitespace, etc.) */
    void leadingOps();
  };
}

#endif