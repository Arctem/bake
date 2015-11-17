
#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "ir/basic_block.h"

namespace ir {

  class ClassList;
  class ClassDef;

  /**
   * The root of the IR. Contains a map from class names to references to MethodLists
   */
  class ClassList {
  public:
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

    void addMethod(BasicBlock*);
    std::vector<BasicBlock*> getMethods() { return methods; }
    void addAttr(int);
    std::vector<int> getAttrs() { return attrs; }
    std::string getName() { return name; }
    virtual void accept(IrVisitor* v) { v->visit(this); }

  private:
    std::string name;
    std::vector<BasicBlock*> methods; // References to each of the methods defined in this class
    std::vector<int> attrs; // Vector containing the size of each attribute in this class
  };
}