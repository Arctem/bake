
#ifndef __CANARY__
#define __CANARY__

#include <vector>
using namespace std;
#include "node.h"
#include "misc_ops.h"

namespace bake_ast {
  class ExprList : public Node {
  public:
  ExprList() : Node(EXPRLIST) { };
    virtual ~ExprList() { 
      while(!children.empty()){
        auto tmp = children.back();
        children.pop_back();
        delete tmp;
      }   
    }
    
    void add(Node* n) { children.push_back(n); }
    vector<Node*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<Node*> children;
  };

  class ClassList : public Node {
  public:
  ClassList() : Node(CLASSLIST) { };
  ClassList(vector<Node*> c) : Node(CLASSLIST){
      children = c;
    }
    
    virtual ~ClassList() { 
      while(!children.empty()){
        auto tmp = children.back();
        children.pop_back();
        delete tmp;
      }  
    }

    void add(Node* n) { children.push_back(n); }
    vector<Node*> getChildren() { return children; }
    virtual void accept(Visitor* v) { v->visit(this); };

  private:
    vector<Node*> children;
  };

  class ListFormalDeclare : public Node {
  public:
  ListFormalDeclare() : Node(LISTFORMALDECLARE) {};
  ListFormalDeclare(vector<FormalDeclare*> l) : Node(LISTFORMALDECLARE) {
      list = l;
    }
    virtual ~ListFormalDeclare();

    void add(FormalDeclare* n);
    vector<FormalDeclare*> getList() { return list; }

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    vector<FormalDeclare*> list;
  };

  class CaseList : public Node {
  public:
  CaseList() : Node(CASELIST) {};
  CaseList(vector<Case*> l) : Node(CASELIST) {
      list = l;
    }
    virtual ~CaseList();

    void add(Case* n);
    vector<Case*> getList() { return list; }

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    vector<Case*> list;
  };


  class LetStatement : public Node {
  public:
  LetStatement() : Node(LETSTATEMENT) {};
  LetStatement(ListFormalDeclare* l, Node* e) : Node(LETSTATEMENT) {
      list = l;
      expr = e;
    }
    virtual ~LetStatement() { 
      delete list;
      delete expr; 
    }

    Node* getExpr() { return this->expr; }
    vector<FormalDeclare*> getList() { return this->list->getList(); }

    void setExpr(Node* n) { expr = n; }
    void addToIdList(FormalDeclare* n) { list->add(n); }


    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    ListFormalDeclare* list;
    Node* expr;

  };

  class CaseStatement : public Node {
  public:
  CaseStatement() : Node(CASESTATEMENT) {};
  CaseStatement(Node* c, ExprList* i, ExprList* t, ExprList* e) : Node(CASESTATEMENT) {
      caseExpr = c;
      idList = i;
      typeList = t;
      exprList = e;
    }
    virtual ~CaseStatement() { 
      delete caseExpr;
      delete idList;
      delete typeList;
      delete exprList;
    }

    Node* getCaseExpr() { return this->caseExpr; }
    vector<Node*> getIdList() { return this->idList->getChildren();}
    vector<Node*> getTypeList() { return this->typeList->getChildren(); }
    vector<Node*> getExprList() { return this->exprList->getChildren(); }

    void setCaseExpr(Node* n) { this->caseExpr = n; }
    void addToIdList(Node* n) { idList->add(n); }
    void addToTypeList(Node* n) { typeList->add(n); }
    void addToExprList(Node* n) { exprList->add(n); }
    
    virtual void accept(Visitor* v) { v->visit(this); }
  
  private:
    Node* caseExpr;

    // there will be at least one in each of these lists.
    ExprList* idList;
    ExprList* typeList;
    ExprList* exprList;
    
  };

  class Dispatch : public Node {
  public:
  Dispatch() : Node(DISPATCH) {};
  Dispatch(Node* e, Node* t, Node* id, ExprList* exprList) : Node(DISPATCH) {
      expr = e;
      type = t;
      this->id = id;
      this->exprList = exprList;
    }
    virtual ~Dispatch() { 
      delete exprList; 
      delete expr;
      delete type;
      delete id;
    }

    Node* getExpr() { return this->expr; }
    Node* getType() { return this->type; }
    Node* getID() { return this->id; }
    vector<Node*> getExprList() { return this->exprList->getChildren(); }

    void setExpr(Node* n) { this->expr = n; }
    void setType(Node* n) { this->type = n; }
    void setID(Node* n) { this->id = n; }
    void addToExprList(Node* n) { this->exprList->add(n); }
    void setExprList(ExprList* e) { this->exprList = e; }
    
    virtual void accept(Visitor* v) { v->visit(this); }
    
  private:
    Node* expr = nullptr; // optional
    Node* type = nullptr; // optional

    Node* id;
    ExprList* exprList = nullptr;


  };
  
  class Feature : public Node {
  public:
  Feature() : Node(FEATURE) {};
  Feature(Node* i, ListFormalDeclare* l, Node* t, Node* e) : Node (FEATURE) {
      id = i;
      list = l;
      type = t;
      expr = e;
    }
    virtual ~Feature() { 
      delete list;
      delete id;
      delete type;
      delete expr;  
    }
    
    Node* getID() { return id; }
    ListFormalDeclare* getList() { return list; }
    Node* getType() { return type; }
    Node* getExpr() { return expr; }
    
    void setID(Node* i) { id = i; }
    void setList(ListFormalDeclare* l) { list = l; }
    void setType(Node* t) { type = t; }
    void setExpr(Node* e) { expr = e; }

    virtual void accept(Visitor* v) { v->visit(this); }
    
  private:
    Node* id;
    ListFormalDeclare* list;
    Node* type;
    Node* expr;
  };
  
  class FeatureOption : public Node {
  public:
  FeatureOption() : Node(FEATUREOPTION){};
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
  
  class FeatureList : public Node {
  public:
  FeatureList() : Node(FEATURELIST) {};
  FeatureList(vector<Node*> v) : Node(FEATURELIST) { list = v; };
    virtual ~FeatureList() { 
      while(!list.empty()){
        auto tmp = list.back();
        list.pop_back();
        delete tmp;
      }  
    }
    
    vector<Node*> getList() {return list;}
    
    void add(Node* n) { list.push_back(n); }
    
    virtual void accept(Visitor* v) { v->visit(this); }
    
  private:
    vector<Node*> list;
  };

  class ClassStatement : public Node {
  public:
  ClassStatement() : Node(CLASSSTATEMENT) {};
  ClassStatement(Node* t, Node* i = nullptr, FeatureList* f = nullptr) : Node(CLASSSTATEMENT) {
      type = t;
      inheritType = i;
      list = f;
    }
    virtual ~ClassStatement();

    Node* getType() { return this->type; }
    Node* getInheritType() { return this->inheritType; }
    FeatureList* getList() { return this->list; }
    
    void setType(Node* n) { this->type = n; }
    void setInheritType(Node* n) { this->inheritType = n; }
    void setList(FeatureList* n) { this->list = n; }
    void add(FeatureOption* n);

    virtual void accept(Visitor* v) { v->visit(this); }

  private:
    Node* type;
    Node* inheritType = nullptr;

    FeatureList* list;
  };
}

#endif
