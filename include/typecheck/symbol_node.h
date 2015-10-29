#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <exception>
using namespace std;

#include "symbol_table_print.h"
using namespace typecheck;

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
    void setSuper(const string* cls);
    bool cantExtend() { return nonExtend; }

    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    Groot* lex_parent;
    string* super = nullptr;
    unordered_map<string, string> members; // Elements in this scope (instance variables).
    unordered_map<string, SymbolMethod*> methods; // Methods in this class
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
    SymbolAnon* nextMem() { return members[curMem++]; }
    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    string retType;
    ClassNode* lex_parent;
    unordered_map<string, string> params; // Parameters to this method. Key: param name. Value: param type
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

    unordered_map<string, string> getMembers();
    void addMember(string, string);
    
    vector<SymbolAnon*> getSubs() { return subs; };
    void addSub(SymbolAnon* sub);
    
    SymbolNode* getLexParent();
    void setLexParent(SymbolNode* parent);
    
    SymbolAnon* nextMem() { return subs[curMem++]; }

    virtual void accept(SymbolVisitor* v) { v->visit(this); }

  private:
    SymbolNode* lex_parent;
    unordered_map<string, string> members; // Elements in this scope (variables).
    vector<SymbolAnon*> subs; // Sub let statements
    int curMem = 0; // current point in members
  };
}
