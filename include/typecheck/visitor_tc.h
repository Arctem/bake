#ifndef __TYPE_NAZI__
#define __TYPE_NAZI__

#include <string>
using namespace std;

#include "ast/ast.h"
using namespace bake_ast;


namespace bake_tc{
  class TypeCheck : public Visitor {
  public:
    TypeCheck() : lVal("UNDEFTY"), rVal("UNDEFTY"), tmp("UNDEFTY") { };

    // Terminal nodes
    void visit(IntegerVal*);
    void visit(FloatVal*);
    void visit(Int8Val*);
    void visit(Int64Val*);
    void visit(StringVal*);
    void visit(BoolVal*);
    void visit(Id*);
    void visit(Type*);

    // Unary Operators
    void visit(LogicalNot*);
    void visit(BitNot*);
    void visit(Isvoid*);
    void visit(New*);

    // Binary Operators
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
    const string lVal;
    const string rVal;
    const string tmp;
    
    bool checkVals();
    NodeType stringToNodeType(string str);
  };
}

#endif