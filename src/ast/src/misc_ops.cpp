
#include "misc_ops.h"

void ExprList::add(Node* n) {
	children.push_back(n);
}

vector<Node*> ExprList::getChildren() {
	return children;
}