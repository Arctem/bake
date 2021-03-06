#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <exception>
using namespace std;

#include "symbol_table_print.h"
using namespace typecheck;

/* Need this because we can't just include ast/ast.h due to circular dependencies. */
namespace bake_ast {
  class ClassStatement;
}

namespace typecheck {
  class Groot;
  class ClassNode;
  class SymbolMethod;
  class SymbolAnon;

  enum NodeType { GROOT, CLASSNODE, SYMBOLMETHOD, SYMBOLANON };

  /**
   * Thrown for all errors encountered when building the symbol tree
   */
  class StBuildErr : public exception {
  public:
    StBuildErr(const char* msg) { this->msg = msg; };

    virtual const char* what() const throw() {
      return msg;
    }

  private:
    const char* msg;
  };

  /**
   * Base class for nodes that can be placed in the symbol tree
   */
  class SymbolNode {
  public:
    SymbolNode(NodeType type) : type(type) { };
    virtual ~SymbolNode() { };

    bool isA(NodeType type) { return type == this->type; };
    NodeType getType() { return type; };
    virtual SymbolNode* getLexParent() = 0; // Get the lexical parent of this namespace
    virtual void accept(SymbolVisitor*) = 0;

  private:
    NodeType type;
  };

  /**
   * The global root of the symbol tree
   */
  class Groot : public SymbolNode {
  public:
    Groot() : SymbolNode(GROOT) { };
    virtual ~Groot();

    unordered_map<string, ClassNode*> getClasses();
    void addClass(string, ClassNode*);
    SymbolNode* getLexParent();
    void setMainClass(ClassNode* n) { mainClass = n; }
    ClassNode* getMainClass() { return mainClass; }
    void setMainMethod(SymbolMethod* n) { mainMethod = n; }
    SymbolMethod* getMainMethod() { return mainMethod; }
    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    unordered_map<string, ClassNode*> classes; // Classes in this program
    ClassNode* mainClass = nullptr; // Reference to the Main class
    SymbolMethod* mainMethod = nullptr; // Reference to the main() method.
  };

  /**
   * Represents a single class.
   */
  class ClassNode : public SymbolNode {
  public:
    ClassNode(bool cantExtend) : SymbolNode(CLASSNODE), nonExtend(cantExtend) { };
    virtual ~ClassNode();

    unordered_map<string, string> getMembers();
    void addMember(string, string);

    unordered_map<string, SymbolMethod*> getMethods();
    void addMethod(string, SymbolMethod*);

    Groot* getLexParent();
    void setLexParent(Groot* groot);

    string* getSuper() { return super; };
    ClassNode* getSuperObj() { return lex_parent->getClasses()[*getSuper()]; } // Convert from the plain-text super name to the actual ClassNode object corresponding to the super.
    void setSuper(const string cls);
    bool cantExtend() { return nonExtend; }

    string* getName() { return cls_name; }
    void setName(const string name);

    unordered_map<string, int> getAttrOffsets() { return attr_offsets; }
    void setAttrOffset(string attr_name, int offset);

    unordered_map<string, int> getMethodOffsets() { return method_offsets; }
    void setMethodOffset(string method_name, int offset);

    bake_ast::ClassStatement* getAst();
    void setAst(bake_ast::ClassStatement*);

    bool hasAncestor(string* parent); // Check whether this class is a subclass of parent

    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    Groot* lex_parent;
    string* super = nullptr; // Name of parent class
    string* cls_name; // Name of this class
    unordered_map<string, string> members; // Elements in this scope (instance variables).
    unordered_map<string, int> attr_offsets; // map from attribute names to the index into the IR's vector of attributes for this class
    unordered_map<string, SymbolMethod*> methods; // Methods in this class
    unordered_map<string, int> method_offsets; // map from method name to the index into the IR's vector of methods for this class
    bake_ast::ClassStatement* ast; // Reference to the AST node for this class
    bool nonExtend;
  };

  /**
   * Represents a method in a class
   */
  class SymbolMethod : public SymbolNode {
  public:
    SymbolMethod() : SymbolNode(SYMBOLMETHOD) { };
    virtual ~SymbolMethod();

    string getRetType() { return retType; };
    void setRetType(string type) { retType = type; };

    vector<SymbolAnon*> getMembers();
    void addMember(SymbolAnon*);

    ClassNode* getLexParent();
    void setLexParent(ClassNode* parent);

    unordered_map<string, string> getParams() { return params; };
    void addParam(string id, string type);

    vector<string> getParamNames() { return param_names; }

    SymbolAnon* nextMem() { return members[curMem++]; }

    unordered_map<string, int> getStackOffsets() { return stack_offsets; }
    void setStackOffset(string, int);

    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    string retType;
    ClassNode* lex_parent;
    vector<string> param_names; // List of parameter names, in the order they are specified in the method declaration. Use the params map to determine the types.
    unordered_map<string, string> params; // Parameters to this method. Key: param name. Value: param type
    unordered_map<string, int> stack_offsets; // map from parameter name to the index into the IR's vector of parameters for this method
    vector<SymbolAnon*> members; // Sub scopes (e.g., let statement)
    int curMem = 0; // current point in members
  };

  /**
   * An anonymous namespace (e.g., let statements)
   */
  class SymbolAnon : public SymbolNode {
  public:
    SymbolAnon() : SymbolNode(SYMBOLANON) { };
    virtual ~SymbolAnon();

    SymbolMethod* getOwningMethod();

    unordered_map<string, string> getMembers();
    void addMember(string, string);

    unordered_map<string, int> getLVarOffsets() { return lvar_offsets; }
    void setLVarOffset(string, int);

    vector<SymbolAnon*> getSubs() { return subs; };
    void addSub(SymbolAnon* sub);

    SymbolNode* getLexParent();
    void setLexParent(SymbolNode* parent);

    SymbolAnon* nextMem() { return subs[curMem++]; }

    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    SymbolNode* lex_parent;
    unordered_map<string, string> members; // Elements in this scope (variables).
    unordered_map<string, int> lvar_offsets; // map from local variable name to the index into the IR's vector of variables for this method
    vector<SymbolAnon*> subs; // Sub let statements
    int curMem = 0; // current point in members
  };
}
