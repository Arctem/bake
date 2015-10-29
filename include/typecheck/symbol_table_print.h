
#ifndef __SYMBOL_TABLE_TABLE__
#define __SYMBOL_TABLE_TABLE__

namespace typecheck {
  class Groot;
  class ClassNode;
  class SymbolMethod;
  class SymbolAnon;

  // TODO: Move this class to a more logical place
  class SymbolVisitor {
  public:
    SymbolVisitor() { };
    ~SymbolVisitor() { };

    virtual void visit(Groot*) = 0;
    virtual void visit(ClassNode*) = 0;
    virtual void visit(SymbolMethod*) = 0;
    virtual void visit(SymbolAnon*) = 0;
  };

  class SymbolTablePrint : public SymbolVisitor {
  public:
    virtual void visit(Groot* n);
    virtual void visit(ClassNode* n);
    virtual void visit(SymbolMethod* n);
    virtual void visit(SymbolAnon* n);

  private:
    void leadingOps(); // What the printer should do before it visits every node (e.g., print leading whitespace, etc.)

    int level = 0;
  };
}

#endif