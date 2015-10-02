
#ifndef __THE_AWSOME__
#define __THE_AWSOME__

#include <vector>
using namespace std;
#include "node.h"
using namespace bake_ast;

namespace bake_ast {
	class ExprList : Node {
	public:
		ExprList() : Node(EXPRLIST) { };
		void add(Node*);
		vector<Node*> getChildren();
		virtual void accept(Visitor* v) {v->visit(this); };

	private:
		vector<Node*> children;
	};
}

#endif