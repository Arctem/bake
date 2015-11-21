
#pragma once

#include <unordered_map>
#include "ast/visitor.h"
#include "ir/class_list.h"

namespace ir {
  // Map from numeric types to their sizes. If a type isn't in this hash,
  // assume it should be stored as a pointer.
  static std::unordered_map<std::string, int> type_sizes({{std::string("Int8"), 8},
                                                          {std::string("Int"), 32},
                                                          {std::string("Int64"), 64},
                                                          {std::string("Float"), 64},
                                                          {std::string("Bool"), 8}
                                                         });

  /**
   * Symbol tree visitor responsible for deciding virtual offsets for attributes, stack variables, and methods
   */
  class CalcOffsets : bake_ast::Visitor {
  public:
    /* AST node corresponding to the root of the IR */
    virtual void visit(bake_ast::ClassList*);

    /* AST nodes defining new scopes */
    virtual void visit(bake_ast::LetStatement*);
    virtual void visit(bake_ast::ClassStatement*);
    virtual void visit(bake_ast::Feature*);

    /* AST nodes that define new variables */
    virtual void visit(bake_ast::FormalDeclare*);

    /* AST nodes that don't define a new scope */
    virtual void visit(bake_ast::LogicalNot*);
    virtual void visit(bake_ast::BitNot*);
    virtual void visit(bake_ast::Isvoid*);
    virtual void visit(bake_ast::New*);
    virtual void visit(bake_ast::Plus*);
    virtual void visit(bake_ast::Minus*);
    virtual void visit(bake_ast::Multiply*);
    virtual void visit(bake_ast::Divide*);
    virtual void visit(bake_ast::LessThan*);
    virtual void visit(bake_ast::LessThanEqual*);
    virtual void visit(bake_ast::Equal*);
    virtual void visit(bake_ast::Assign*);
    virtual void visit(bake_ast::ExprList*);
    virtual void visit(bake_ast::WhileLoop*);
    virtual void visit(bake_ast::IfStatement*);
    virtual void visit(bake_ast::CaseStatement*);
    virtual void visit(bake_ast::Case*);
    virtual void visit(bake_ast::CaseList*);
    virtual void visit(bake_ast::Dispatch*);
    virtual void visit(bake_ast::ListFormalDeclare*);
    virtual void visit(bake_ast::FeatureOption*);
    virtual void visit(bake_ast::FeatureList*);

    /* AST leaf nodes that don't need to do anything */
    virtual void visit(bake_ast::IntegerVal*) {  }
    virtual void visit(bake_ast::FloatVal*) {  }
    virtual void visit(bake_ast::Int8Val*) {  }
    virtual void visit(bake_ast::Int64Val*) {  }
    virtual void visit(bake_ast::StringVal*) {  }
    virtual void visit(bake_ast::BoolVal*) {  }
    virtual void visit(bake_ast::Id*) {  }
    virtual void visit(bake_ast::Type*) {  }

    ClassList* getClassList() { return class_list; }

  private:
    ir::ClassList* class_list; // List of all classes in this program
    ir::ClassDef* cur_class; // Reference to the IR Class object currently being generated
    ir::Method* cur_method; // Reference to the current IR Method object being generated
    bake_ast::LetStatement* cur_let; // Reference to the current AST LetStatement node being generated
    enum ScopeType { NOWHERE, INCLASS, INMETHOD, INLET } scope_type = NOWHERE; // Flag indicating what scope is currently being generated
  };
}