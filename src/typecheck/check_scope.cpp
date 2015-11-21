#include "typecheck/check_scope.h"

/********************** Visitor methods **********************/

/**
 * Check for scoping issues in Groot
 */
void typecheck::CheckScope::visit(typecheck::Groot* groot) {
  /* Register and visit all classes */
  for(auto cls_kv : groot->getClasses()) {
    string clsName = cls_kv.first;

    /* Register class, marking it as implemented */
    if(confirmedClasses.find(clsName) != confirmedClasses.end()) {
      confirmedClasses[clsName] = true;
    } else {
      confirmedClasses.insert(std::pair<string, bool>(clsName, true));
    }

    cls_kv.second->accept(this); // Forward visitor
  }

  /* Ensure that all registered classes have an implementation */
  for(auto cls_kv : confirmedClasses) {
    if(cls_kv.second == false) {
      std::stringstream msg;
      msg << "Error: Implementation for class '" << cls_kv.first << "' not found";

      throw ScopeCheckErr(msg.str().c_str());
    }
  }

  /* Second pass to check for inheritance problems */
  for(auto cls_kv : groot->getClasses()) {
    checkInheritanceCycles(cls_kv.second);
    checkValidInherit(cls_kv.second);
    checkMethods(cls_kv.second);
  }

  checkForMains(groot);
}

/**
 * Check for scoping issues in classes
 */
void typecheck::CheckScope::visit(typecheck::ClassNode* cls) {
  checkClass(cls);

  /* Forward visitor to children */
  for(auto method_kv : cls->getMethods()) {
    method_kv.second->accept(this);
  }
}

/********************** Helper methods **********************/

/**
 * Make sure there is a Main class with a main() method
 */
void typecheck::CheckScope::checkForMains(Groot* groot) {
  typecheck::ClassNode* mainClass = nullptr;
  typecheck::SymbolMethod* mainMethod = nullptr;

  /* Look for the Main class */
  for(auto cls_kv : groot->getClasses()) {
    if(cls_kv.first == "Main") {
      mainClass = cls_kv.second;
      break;
    }
  }

  /* Complain about missing Main */
  if(mainClass == nullptr) {
    std::stringstream msg;
    msg << "Error: No definition for class 'Main'" << endl;

    throw ScopeCheckErr(msg.str().c_str());
  }

  /* Look for the main() method */
  for(auto method_kv : mainClass->getMethods()) {
    if(method_kv.first == "main") {
      mainMethod = method_kv.second;
      break;
    }
  }

  /* Complain about missing main() */
  if(mainMethod == nullptr) {
    std::stringstream msg;
    msg << "Error: No definition for method 'main()' in class 'Main'" << std::endl;

    throw ScopeCheckErr(msg.str().c_str());
  }

  /* Check if our main has no arguments */
  if(mainMethod->getParamNames().size() != 0) {
    std::stringstream msg;
    msg << "Error: Method 'main()' in class 'Main' has " <<
      mainMethod->getParamNames().size() << " (0 expected)." << std::endl;

    throw ScopeCheckErr(msg.str().c_str());
  }

  groot->setMainClass(mainClass);
  groot->setMainMethod(mainMethod);
}

/**
 * Defines the requirements for a valid class scope
 * Throws a ScopeCheckErr exception if there's a problem.
 */
void typecheck::CheckScope::checkClass(typecheck::ClassNode* cls) {
  string* superName = cls->getSuper();
  if(superName == nullptr) {
    return;
  }

  /* Register the super class if it exists, but flag it as unimplemented.
     If the class already exists in the confirmedClasses map, don't reset
     it (we don't want to stomp a value of true with a value of false) */
  if(confirmedClasses.find(*superName) == confirmedClasses.end()) {
    confirmedClasses.insert(std::pair<string, bool>(*superName, false));
  }

  /* Make sure there aren't any attributes defined in this class that are also defined in its parent. */
  Groot* groot = cls->getLexParent();
  for(auto attr_kv : cls->getMembers()) {

    /* Step up the inheritance tree, checking for variables with similar names */
    while(superName != nullptr) {
      ClassNode* superClass = groot->getClasses()[*superName]; // Get the node for the symbol class. Note that cls->getLexParent() returns Groot.

      /* If the this super class has the same variable, throw error */
      if(superClass->getMembers().count(attr_kv.first) >= 1) {
        std::stringstream msg;
        msg << "Error: Instance variable '" << attr_kv.first << "' already exists in a super class '" << *superName << "'" << endl;
  
        throw ScopeCheckErr(msg.str().c_str());
      }

      superName = superClass->getSuper();
    }
  }
}


/**
 * Checks for inheritance cycles of classes.
 */
void typecheck::CheckScope::checkInheritanceCycles(typecheck::ClassNode* cls) {
  Groot* groot = cls->getLexParent();
  std::set<ClassNode*> visitedClasses;
  ClassNode* cur = cls;
  string* superName = cls->getSuper();

  while(superName != nullptr) {
    if(visitedClasses.find(cur) == visitedClasses.end()) {
      visitedClasses.insert(cur);
    } else {
      std::stringstream msg;
      msg << "Error: Class '" << *superName << "' is in an inheritance cycle." << endl;
      throw ScopeCheckErr(msg.str().c_str());
    }
    cur = groot->getClasses()[*superName];
    superName = cur->getSuper();
  }
}


/**
 * Checks for invalid methods (e.g., overloading vs. overriding)
 */
void typecheck::CheckScope::checkMethods(ClassNode* cls) {
  string* superName = cls->getSuper();
  if(superName == nullptr) {
    return;
  }
  Groot* groot = cls->getLexParent();

  /* For every method defined in this class... */
  for(auto method_kv : cls->getMethods()) {
    string methodSig = getMethodSig(cls, string(method_kv.first));

    /* Step up the inheritance tree, checking for another method with the same signature */
    while(superName != nullptr) {
      ClassNode* superClass = groot->getClasses()[*superName]; // Get the node for the symbol class. Note that cls->getLexParent() returns Groot.
      superName = superClass->getSuper();

      /* If this super doesn't have a method by the correct name, don't bother checking the signatures */
      if(superClass->getMethods().find(method_kv.first) == superClass->getMethods().end()) {
        continue;
      }

      if(methodSig != getMethodSig(superClass, method_kv.first)) {
        std::stringstream msg;
        msg << "Error: Method '" << method_kv.first << "' has a different signature from the super class";

        throw ScopeCheckErr(msg.str().c_str());
      }
    }
  }
}

/**
 * Ensures classes don't extend a primitive type.
 */
void typecheck::CheckScope::checkValidInherit(ClassNode* cls) {
  if(cls->getSuper() == nullptr) {
    return;
  }

  typecheck::ClassNode* superImpl = cls->getLexParent()->getClasses()[*cls->getSuper()]; // Get the node in the symbol table representing the super class
  if(superImpl->cantExtend()) {
    std::stringstream msg;
    msg << "Error: Attempt to extend a basic type '" << *cls->getSuper() << "'";

    throw ScopeCheckErr(msg.str().c_str());
  }
}

/**
 * Returns a string representing the signature of a method.
 * String is of the form "NRP1P2...Pn" where N is the method name,
 * R is the return type, and P1...Pn are the parameter types.
 */
string typecheck::CheckScope::getMethodSig(ClassNode* cls, string methodName) {
  std::stringstream sig;
  sig << methodName; 

  SymbolMethod* method = cls->getMethods()[methodName];

  sig << method->getRetType();
  for(auto param_name : method->getParamNames()) {
    sig << method->getParams()[param_name];
  }

  return sig.str();
}
