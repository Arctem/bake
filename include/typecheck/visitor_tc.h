#pragma once

#include <string>
#include <exception>
using namespace std;

#include "ast/ast.h"
using namespace bake_ast;

#include "symbol_node.h"
using namespace typecheck;


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
    TypeCheck(SymbolNode* node) : curScope(node) { groot = (Groot*) node; };

    // Terminal nodes.
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

    // Helper methods
    string* getTypeOfLast() { return typeOfLast; }
    void setTypeOfLast(string* s) { typeOfLast = s; }

    SymbolNode* getScope() { return curScope; }
    void setScope(SymbolNode* scope) { curScope = scope; }

  private:
    string* typeOfLast; // Reference to the string specifying the type of the last node that this visitor was in
    SymbolNode* curScope; // the current reference of the scope table
    string curClass;
    Groot* groot; // Reference to the global root.

    // Private helper methods
    bool isBuiltin(string* type); // Check whether the given string is the name of a built in type
    const char* numOrder(string* l, string* r); // returns the greatest of the 2 based on int/float order. returns nullptr on error.
    bool isInt(string* type); // checks if the string is an int
    const char* isNum(string* s);// returns what number it is, nullptr if it is not a number
    bool canAssign(string* l, string* r); // returns true if lhs >= rhs
    void checkDispatchParameters(Dispatch*, SymbolMethod*); // Checks whether the parameters match between a method declaration and dispatch.
  };
}
