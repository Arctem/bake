
#ifndef __NARY__
#define __NARY__

#include <vector>
using namespace std;
#include "node.h"

namespace bake_ast {
  class ExprList : Node {
    public:
      ExprList() : Node(EXPRLIST) { };
      void add(Node* n) { children.push_back(n); }
      vector<Node*> getChildren() { return children; }
      virtual void accept(Visitor* v) { v->visit(this); };

    private:
      vector<Node*> children;
  };
}

#endif