#include "ir/class_list.h"

/**
 * Deconstructor
 */
ir::ClassDef::~ClassDef() {
  for(auto method : getMethods()) {
    delete method;
  }
}

/**
 * Deconstructor
 */
ir::ClassList::~ClassList() {
  for(auto class_kv : getClasses()){
    delete class_kv.second;
  }
}

/**
 * Add a class to the class list
 */
void ir::ClassList::addClass(std::string id, ir::ClassDef* cls) {
  classes.insert(std::pair<std::string, ir::ClassDef*>(id, cls));
}

/**
 * Adds a method to the end of the list of methods for this class
 * Returns true if a method was overridden and false if this is a brand-new method
 */
void ir::ClassDef::addMethod(ir::Method* method, bool checkValid) {
  if(checkValid) {
    /* First, check to see whether a method with the same name was copied from the superclass */
    vector<ir::Method*> tmp = getMethods();
    for(int i = 0; i < tmp.size(); i++) {
      if(tmp[i]->getName() == method->getName()) { // If we find a method by the same name, stomp it.
        methods[i] = method;
        this->getAst()->getScope()->setMethodOffset(method->getName(), i + 1); // Set method offset to what it was in the super method

        return;
      }
    }

    this->getAst()->getScope()->setMethodOffset(method->getName(), this->getMethods().size()); // Set method offset
  }
  methods.push_back(method);
}

/**
 * Adds a new attribute to this method. Also records and returns the virtual offset.
 */
void ir::ClassDef::addAttr(int attr_size) {
  attrs.push_back(attr_size);
}

/**
 * Calculates the number of bytes to allocate for this object in each object record
 */
int ir::ClassDef::recordSize() {
  int sum = 0;

  for(auto attr : getAttrs()) {
    sum += attr;
  }

  return sum;
}
