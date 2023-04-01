#include "LTR.h"

void printLTR_rec(const Tree& t) {
	printLTR_rec(t.root);
}

void printLTR_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLTR_rec(x->left);
	cout << x->val << " ";
	printLTR_rec(x->right);
	// </изменять порядок здесь>
}

void printLTR_non_rec_universal(const Tree& t) {
	printLTR_non_rec_universal(t.root);
}

void printLTR_non_rec_universal(Node* x) {
	stack<Node*> s;
	stack<Node*> is;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		if (!is.empty() && is.top() == t) {
			is.pop();
			cout << t->val << " ";
		}
		else {
			is.push(t);
			// <изменять порядок здесь>
			if (t->right) s.push(t->right);
			s.push(t);
			if (t->left) s.push(t->left);
			// </изменять порядок здесь>
		}
	}
}
