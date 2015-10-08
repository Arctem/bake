
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
  class Plus;
  class Minus;
  class Multiply;
  class Divide;
  class LessThan;
  class LessThanEqual;
  class Equal;
  class Assign;
  class ExprList;
  class WhileLoop;
  class IfStatement;
  class LetStatement;
  class CaseStatement;
  class CaseList;
  class Case;
  class ClassStatement;
  class ClassList;
  class Dispatch;
  class ListFormalDeclare;
  class LetStatement;
  class Feature;
  class FeatureOption;
  class FeatureList;
  class FormalDeclare;

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
    virtual void visit(Plus*) = 0;
    virtual void visit(Minus*) = 0;
    virtual void visit(Multiply*) = 0;
    virtual void visit(Divide*) = 0;
    virtual void visit(LessThan*) = 0;
    virtual void visit(LessThanEqual*) = 0;
    virtual void visit(Equal*) = 0;
    virtual void visit(Assign*) = 0;
    virtual void visit(ExprList*) = 0;
    virtual void visit(WhileLoop*) = 0;
    virtual void visit(IfStatement*) = 0;
    virtual void visit(LetStatement*) = 0;
    virtual void visit(CaseStatement*) = 0;
    virtual void visit(CaseList*) = 0;
    virtual void visit(Case*) = 0;
    virtual void visit(FormalDeclare*) = 0;
    virtual void visit(ClassStatement*) = 0;
    virtual void visit(ClassList*) = 0;
    virtual void visit(Dispatch*) = 0;
    virtual void visit(ListFormalDeclare*) = 0;
    virtual void visit(Feature*) = 0;
    virtual void visit(FeatureOption*) = 0;
    virtual void visit(FeatureList*) = 0;
  };

  class PrettyPrint : public Visitor {
  public:
    PrettyPrint() : depth(0) {};
    void visit(IntegerVal*);
    void visit(StringVal*);
    void visit(BoolVal*);
    void visit(Id*);
    void visit(Type*);

    // Unary Operators
    void visit(UnaryOp*);
    void visit(LogicalNot*);
    void visit(BitNot*);
    void visit(Isvoid*);
    void visit(New*);

    // Binary Operators
    void visit(BinaryOp*);
    void visit(Plus*);
    void visit(Minus*);
    void visit(Multiply*);
    void visit(Divide*);
    void visit(LessThan*);
    void visit(LessThanEqual*);
    void visit(Equal*);
    void visit(Assign*);

    // Misc
    void visit(ExprList*);
    void visit(WhileLoop*);
    void visit(IfStatement*);
    void visit(LetStatement*);
    void visit(CaseStatement*);
    void visit(CaseList*);
    void visit(Case*);
    void visit(FormalDeclare*);
    void visit(ClassStatement*);
    void visit(ClassList*);
    void visit(Dispatch*);
    void visit(ListFormalDeclare*);
    void visit(Feature*);
    void visit(FeatureOption*);
    void visit(FeatureList*);

  private:
    int depth; // Holds how many levels down the tree this print has gone

    /* What should the printer do before it visits every node (e.g., print leading whitespace, etc.) */
    void leadingOps();
  };
}

#endif
