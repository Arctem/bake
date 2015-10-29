#pragma once

#include <unordered_map>
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <set>

#include "typecheck/symbol_node.h"
#include "typecheck/symbol_table_print.h"

namespace typecheck {
  /**
   * Visitor responsible for sanity checking the scope table.
   * For example, ensures all called functions exist in the current scope.
   */
  class CheckScope : public SymbolVisitor {
  public:
    virtual void visit(Groot* n);
    virtual void visit(ClassNode* n);
    virtual void visit(SymbolMethod* n) { };
    virtual void visit(SymbolAnon* n) { };

  private:
    std::unordered_map<std::string, bool> confirmedClasses; // Map recording which classes have been requested (via inheritance)
                                                            // and the classes that have actual implementations. The key is the class
                                                            // name. Value is True if an implementation has been found, false otherwise.

    void checkForMains(Groot*); // Make sure there is a Main class with a main() method
    void checkClass(ClassNode*); // Defines the requirements for a valid class scope
    void checkInheritanceCycles(ClassNode*); //Checks for cases of classes inheriting one another over multiple steps
    void checkMethods(ClassNode*); // Checks for invalid methods (e.g., overloading vs. overriding)
    void checkValidInherit(ClassNode*); // Ensures classes don't extend a primitive type.
    string getMethodSig(ClassNode*, string); // Returns a string representing the signature of a method (return type, name, and parameters)
  };

  /**
   * Thrown for all errors encountered when confirming that the scope table is correct
   */
  class ScopeCheckErr : public std::exception {
  public:
    ScopeCheckErr(const char* msg) { this->msg = msg; };

    virtual const char* what() const throw() {
      return msg;
    }

  private:
    const char* msg;
  };
}
