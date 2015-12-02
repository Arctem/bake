
#ifndef __CANARY__
#define __CANARY__

#include <vector>
using namespace std;
#include "node.h"
#include "misc_ops.h"
#include "typecheck/symbol_node.h"

namespace bake_ast {

  /***** Begin Base Lists *****/


  /*** List For Expression ***/

  class ExprList : public Node {
  public:
    ExprList() : Node(EXPRLIST) { };
    virtual ~ExprList();

    void add(Node* n);
    void addToFront(Node* n);
    vector<Node*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<Node*> children;
  };


  /*** List For Classes ***/

  class ClassList : public Node {
  public:
    ClassList() : Node(CLASSLIST) { };
    ClassList(vector<ClassStatement*> c) : Node(CLASSLIST) { children = c; }
    virtual ~ClassList();

    void add(ClassStatement* n);
    void consume(ClassList* n);
    vector<ClassStatement*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<ClassStatement*> children;
  };

  /*** List for Formal Declares ***/

  class ListFormalDeclare : public Node {
  public:
    ListFormalDeclare() : Node(LISTFORMALDECLARE) {};
    ListFormalDeclare(vector<FormalDeclare*> l) : Node(LISTFORMALDECLARE) { list = l; }
    virtual ~ListFormalDeclare();

    void add(FormalDeclare* n);
    void addToFront(FormalDeclare* n);
    vector<FormalDeclare*> getList() { return list; }

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    vector<FormalDeclare*> list;
  };


  /*** List for Cases ***/

  class CaseList : public Node {
  public:
    CaseList() : Node(CASELIST) {};
    CaseList(vector<Case*> l) : Node(CASELIST) { list = l; }
    virtual ~CaseList();

    void add(Case* n);
    vector<Case*> getList() { return list; }
    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    vector<Case*> list;
  };


  /*** List for Features ***/

  class FeatureList : public Node {
  public:
    FeatureList() : Node(FEATURELIST) { };
    virtual ~FeatureList();

    vector<FeatureOption*> getList() { return list; }
    void add(FeatureOption* n);
    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    vector<FeatureOption*> list;
  };


  /***** Begin Statements that Contain Lists *****/


  /*** Let Statement - contains ListFormalDeclare ***/

  class LetStatement : public Node {
  public:
    LetStatement() : Node(LETSTATEMENT) {};
    LetStatement(ListFormalDeclare* l, Node* e);
    virtual ~LetStatement();

    Node* getExpr() { return this->expr; }
    ListFormalDeclare* getList() { return this->list; }

    void setExpr(Node* n) { expr = n; }
    void addToIdList(FormalDeclare* n) { list->add(n); }

    typecheck::SymbolAnon* getScope() { return scope; } // Get the symbol tree node corresponding to this scope
    void setScope(typecheck::SymbolAnon* s) { scope = s; } // Get the symbol tree node corresponding to this scope

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    ListFormalDeclare* list;
    Node* expr;
    typecheck::SymbolAnon* scope = nullptr; // Reference to the Symbol Tree ClassNode corresponding to this scope
  };


  /*** Case Statement - Contains 3 ExprLists ***/

  class CaseStatement : public Node {
  public:
    CaseStatement() : Node(CASESTATEMENT) { };
    CaseStatement(Node*, CaseList*);
    virtual ~CaseStatement();

    Node* getExpr() { return caseExpr; };
    void setExpr(Node* n) { caseExpr = n; };
    CaseList* getCaseList() { return cases; };
    void setCaseList(CaseList* caseList) { cases = caseList; };
    virtual void accept(bake_ast::Visitor* v) { v->visit(this); };

  private:
    Node* caseExpr;
    CaseList* cases;
  };


  /*** Dispatch - Contains an ExprList ***/

  class Dispatch : public Node {
  public:
    Dispatch();
    Dispatch(Node* e, Type* t, Id* id, ExprList* exprList);
    virtual ~Dispatch();

    Node* getExpr() { return this->expr; }
    Type* getType() { return this->type; }
    Id* getID() { return this->id; }
    ExprList* getExprList() { return this->exprList; }

    void setExpr(Node* n) { this->expr = n; }
    void setType(Type* n) { this->type = n; }
    void setID(Id* n) { this->id = n; }
    void setExprList(ExprList* e) { this->exprList = e; }

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    Node* expr = nullptr; // optional
    Type* type = nullptr; // optional

    Id* id;
    ExprList* exprList = nullptr; // optional
  };


  /*** Feature - Contains ListFormalDeclare ***/
  class Feature : public Node {
  public:
    Feature();
    Feature(Id* i, ListFormalDeclare* l, Type* t, Node* e);
    virtual ~Feature();

    Id* getID() { return id; }
    ListFormalDeclare* getList() { return list; }
    Type* getType() { return type; }
    Node* getExpr() { return expr; }
    typecheck::SymbolMethod* getScope() { return scope; } // Get the symbol tree node corresponding to this method

    void setID(Id* i) { id = i; }
    void setList(ListFormalDeclare* l) { list = l; }
    void setType(Type* t) { type = t; }
    void setExpr(Node* e) { expr = e; }
    void setScope(typecheck::SymbolMethod* s) { scope = s; } // Get the symbol tree node corresponding to this method

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    Id* id; // Name of method
    ListFormalDeclare* list = nullptr; // Parameters
    Type* type; // Return type
    Node* expr; // Body

    typecheck::SymbolMethod* scope = nullptr; // Symbol tree node corresponding to this method
  };

  /*** Feature Option - Contains list of Features***/
  // TODO : You can have method xor attrbute  features
  class FeatureOption : public Node {
  public:
    FeatureOption() : Node(FEATUREOPTION) { };
    FeatureOption(Feature* f) : Node(FEATUREOPTION) { feat = f; }
    FeatureOption(FormalDeclare* f) : Node(FEATUREOPTION) { form = f; }
    virtual ~FeatureOption();

    Feature* getFeat() { return feat; }
    FormalDeclare* getForm() { return form; }

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    Feature* feat = nullptr;
    FormalDeclare* form = nullptr;
  };

  /*** Class Statement - contains FeatureList ***/

  class ClassStatement : public Node {
  public:
    ClassStatement() : Node(CLASSSTATEMENT) {};
    ClassStatement(Type* t, Type* i = nullptr, FeatureList* f = nullptr, bool cantExtend = false);
    virtual ~ClassStatement();

    Type* getType() { return this->typeId; }
    Type* getInheritType() { return this->inheritType; }
    FeatureList* getList() { return this->list; }
    typecheck::ClassNode* getScope() { return scope; } // Get the symbol tree node corresponding to this method
    bool cantExtend() { return nonExtend; }

    void setType(Type* n) { this->typeId = n; }
    void setInheritType(Type* n) { this->inheritType = n; }
    void setList(FeatureList* n) { this->list = n; }
    void add(FeatureOption* n);
    void setScope(typecheck::ClassNode* s) { scope = s; } // Get the symbol tree node corresponding to this method

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    Type* typeId; // Name of this class (that is, the name of the type defined by this class)
    Type* inheritType = nullptr;
    FeatureList* list = nullptr;
    typecheck::ClassNode* scope = nullptr; // Reference to the Symbol Tree ClassNode corresponding to this class
    bool nonExtend;
  };
}

#endif
