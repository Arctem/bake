
#ifndef __VISITOR__
#define __VISITOR__

namespace bake_ast {
	class Node;
  class Integer;
  class BinaryOp;

	class Visitor {
	public:
		Visitor() {};
		virtual ~Visitor() {};

    virtual void visit(Integer*) = 0;
    virtual void visit(BinaryOp*) = 0;
	};

  class PrettyPrint : public Visitor {
  public:
    PrettyPrint() : depth(0) {};
    void visit(Integer*);
    void visit(BinaryOp*);

  private:
    int depth; // Holds how many levels down the tree this print has gone

    /* What should the printer do before it visits every node (e.g., print leading whitespace, etc.) */
    void leadingOps();
  };
}

#endif