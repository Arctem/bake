#pragma once

#include <string>
#include "ast/visitor.h"
#include "ast/node.h"
#include "ir/class_list.h"
#include "typecheck/symbol_node.h"

namespace ir {
  class BuildIR : bake_ast::Visitor {
  public:
    BuildIR(typecheck::Groot* groot);

    ClassList* getClassList() { return classlist; }
    ClassDef* getCurrClass() { return curr_class; }

    void setCurrClass(ClassDef* cls);

    // Terminal nodes
    void visit(bake_ast::IntegerVal*);
    void visit(bake_ast::Int8Val*);
    void visit(bake_ast::Int64Val*);
    void visit(bake_ast::FloatVal*);
    void visit(bake_ast::StringVal*);
    void visit(bake_ast::BoolVal*);
    void visit(bake_ast::Id*);
    void visit(bake_ast::Type*);

    // Unary Operators
    void visit(bake_ast::LogicalNot*);
    void visit(bake_ast::BitNot*);
    void visit(bake_ast::Isvoid*);
    void visit(bake_ast::New*);

    // Binary Operators
    void visit(bake_ast::Plus*);
    void visit(bake_ast::Minus*);
    void visit(bake_ast::Multiply*);
    void visit(bake_ast::Divide*);
    void visit(bake_ast::LessThan*);
    void visit(bake_ast::LessThanEqual*);
    void visit(bake_ast::Equal*);
    void visit(bake_ast::Assign*);

    // Misc
    void visit(bake_ast::ExprList*);
    void visit(bake_ast::WhileLoop*);
    void visit(bake_ast::IfStatement*);
    void visit(bake_ast::LetStatement*);
    void visit(bake_ast::CaseStatement*);
    void visit(bake_ast::CaseList*);
    void visit(bake_ast::Case*);
    void visit(bake_ast::FormalDeclare*);
    void visit(bake_ast::ClassStatement*);
    void visit(bake_ast::ClassList*);
    void visit(bake_ast::Dispatch*);
    void visit(bake_ast::ListFormalDeclare*);
    void visit(bake_ast::Feature*);
    void visit(bake_ast::FeatureOption*);
    void visit(bake_ast::FeatureList*);

  private:
    ClassList* classlist;
    
    typecheck::Groot* symbol_tree; // Reference to the root of the symbol tree (i.e., Groot)
    typecheck::SymbolNode* curScope; // Reference to the current scope being generated
    ClassDef* curr_class; // Reference to the current class being compiled
    BasicBlock* curr_bb; // Reference to the current basic block being compiled
    int reg_count = 0; // Number of virtual registers that have been created. The next register that should be created is reg_count + 1
    int throwup = reg_count; // Used to specify which register the result of an operation is stored in. 
    bool in_method = false; // Flag indicating whether we are currently generating code for a method. This is messy, disgusting, and icky. Oh, and did I mention dangerous? If you have a better idea, please, please implement it.
  };
}