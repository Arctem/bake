
#ifndef __BUILD_ST__
#define __BUILD_ST__

#include "ast/visitor.h"
#include "ast/ast.h"
using namespace bake_ast;
#include "typecheck/symbol_node.h"

namespace typecheck {
  class BuildST : public Visitor {
  public:
    BuildST();
    ~BuildST() { delete curr_scope; };

    SymbolNode* getCurrScope() { return curr_scope; }   // Get the scope that the visitor is currently at.
                                                        // After this visitor is finished visiting the AST, this will return Groot.

    /** Terminals **/
    void visit(IntegerVal*) { };
    void visit(FloatVal*) { };
    void visit(Int8Val*) { };
    void visit(Int64Val*) { };
    void visit(StringVal*) { };
    void visit(BoolVal*) { };
    void visit(Id*) { };
    void visit(Type*) { };

    /** AST nodes that need to forward the BuildST visitor to their children **/
    void visit(UnaryOp* n) { n->get()->accept(this); };
    void visit(LogicalNot* n) { visit((UnaryOp*) n); };
    void visit(BitNot* n) { visit((UnaryOp*) n); };
    void visit(Isvoid* n) { visit((UnaryOp*) n); };
    void visit(New* n) { visit((UnaryOp*) n); };

    void visit(BinaryOp* n) { n->getLhs()->accept(this); n->getRhs()->accept(this); };
    void visit(Plus* n) { visit((BinaryOp*) n);};
    void visit(Minus* n) { visit((BinaryOp*) n); };
    void visit(Multiply* n) { visit((BinaryOp*) n); };
    void visit(Divide* n) { visit((BinaryOp*) n); };
    void visit(LessThan* n) { visit((BinaryOp*) n); };
    void visit(LessThanEqual* n) { visit((BinaryOp*) n); };
    void visit(Equal* n) { visit((BinaryOp*) n); };
    void visit(Assign* n) { n->getRhs()->accept(this); };

    void visit(ExprList* n);
    void visit(WhileLoop* n);
    void visit(IfStatement*  n);
    void visit(CaseStatement* n);
    void visit(CaseList* n);
    void visit(Case* n) { };
    void visit(FormalDeclare* n);
    void visit(ClassList* n);
    void visit(Dispatch* n) { };
    void visit(ListFormalDeclare* n);
    void visit(FeatureOption* n) { };
    void visit(FeatureList* n);

    /** AST nodes that have their own namespace **/
    void visit(LetStatement*);
    void visit(ClassStatement*);
    void visit(Feature*);

  private:
    SymbolNode* curr_scope;
  };
}

#endif