
#include "ir/class_list.h"

/**
 * Add a class to the class list
 */
void ir::ClassList::addClass(std::string id, ir::ClassDef* cls) {
  classes.insert(std::pair<std::string, ir::ClassDef*>(id, cls));
}

/**
 * Adds a method to the end of the list of methods for this class
 */
void ir::ClassDef::addMethod(ir::BasicBlock* method) {
  methods.push_back(method);
}

/**
 * Adds a new attribute to this method. Only the size of the variable needs to be recorded.
 */
void ir::ClassDef::addAttr(int attr_size) {
  attrs.push_back(attr_size);
}