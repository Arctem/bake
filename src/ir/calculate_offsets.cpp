
#include <iostream>
#include "ir/calculate_offsets.h"
#include "typecheck/symbol_node.h"

void ir::CalcOffsets::visit(typecheck::Groot* n) {
  class_list = new ir::ClassList();

  for(auto cls_p : n->getClasses()) {
    cls_p.second->accept(this);
  }
}

void ir::CalcOffsets::visit(typecheck::ClassNode* n) {
  /* Create class definition */
  ir::ClassDef* cls = new ir::ClassDef(*n->getName());
  class_list->addClass(*n->getName(), cls);

  /* Add attributes */
  for(auto attr_p : n->getMembers()) {

    int size; // Will hold the size that this variable needs to have allocated
    if(type_sizes.find(attr_p.second) == type_sizes.end()) { // If not found in list of explicit sizes, assume pointer
      size = 8;
    } else {
      size = type_sizes[attr_p.second];
    }

    cls->addAttr(size); // Add attribute
    int offset = cls->getAttrs().size() - 1;
    n->setAttrOffset(attr_p.first, offset); // Set attribute's virtual offset
  }
}