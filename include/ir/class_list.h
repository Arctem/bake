
#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "ir/basic_block.h"
#include "ast/ast.h"

namespace ir {

  class ClassList;
  class ClassDef;

  /**
   * The root of the IR. Contains a map from class names to references to MethodLists
   */
  class ClassList {
  public:
    virtual ~ClassList();

    void addClass(std::string, ClassDef*);
    std::unordered_map<std::string, ClassDef*> getClasses() { return classes; }

    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    std::unordered_map<std::string, ClassDef*> classes; // Classes in this program
  };

  /**
   * Describes a single class. Contains references to the methods for this class,
   * as well as the instance variables for it.
   */
  class ClassDef {
  public:
    ClassDef(std::string name) : name(name) {  };
    virtual ~ClassDef();

    void addMethod(Method* method, bool checkValid=true); // Add a method to this class. Returns the virtual offset into the vector of methods where this method is stored.
    void addAttr(int); // Add an attribute to this class. Returns the virtual offset for the attr.
    void setAst(bake_ast::ClassStatement* n) { ast = n; } // Set the AST node corresponding to this class

    std::vector<Method*> getMethods() { return methods; }
    std::vector<int> getAttrs() { return attrs; } // get the list of sizes of attributes
    std::string getName() { return name; }
    bake_ast::ClassStatement* getAst() { return ast; } // Return the AST node corresponding to this class

    int recordSize(); // Calculates the number of bytes to allocate for this object in each object record

    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    std::string name;
    std::vector<Method*> methods; // References to each of the methods defined in this class
    std::vector<int> attrs; // Vector containing the size of each attribute in this class
    bake_ast::ClassStatement* ast; // Reference to the AST node defining this class
  };
}
