#ifndef __TYPE_NAZI__
#define __TYPE_NAZI__

#include <string>
#include <exception>
using namespace std;

#include "ast/ast.h"
using namespace bake_ast;


namespace typecheck {
  /**
   * Thrown for all errors encountered when building the symbol tree
   */
  class TypeErr : public exception {
  public:
    TypeErr(const char* msg) { this->msg = msg; };

    virtual const char* what() const throw() {
      return msg;
    }

  private:
    const char* msg;
  };

  class TypeCheck : public Visitor {
  public:
    // Terminal nodes.
    void visit(IntegerVal*);
    void visit(FloatVal*);
    void visit(Int8Val*);
    void visit(Int64Val*);
    void visit(StringVal*);
    void visit(BoolVal*);
    void visit(Id*) { }; // TODO: Needs proper implementation
    void visit(Type*) { };

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

    // Helper methods
    string* getTypeOfLast() { return typeOfLast; }
    void setTypeOfLast(string* s) { typeOfLast = s; }
  private:
    string* typeOfLast; // Reference to the string specifying the type of the last node that this visitor was in

    // Private helper methods
    bool isBuiltin(string* type); // Check whether the given string is the name of a built in type
  };
}

#endif