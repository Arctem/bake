
#pragma once

#include <unordered_map>
#include "typecheck/symbol_table_print.h"
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
  class CalcOffsets : typecheck::SymbolVisitor {
  public:
    virtual void visit(typecheck::Groot*);
    virtual void visit(typecheck::ClassNode*);
    virtual void visit(typecheck::SymbolMethod*) { }
    virtual void visit(typecheck::SymbolAnon*) { }

    ClassList* getClassList() { return class_list; }

  private:
    ClassList* class_list; // List of all classes in this program
  };
}