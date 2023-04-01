#include "LRT.h"

void printLRT_rec(const Tree& t) {
	printLRT_rec(t.root);
}

void printLRT_rec(Node* x) {
	if (x == nullptr)
		return;
	// <�������� ������� �����>
	printLRT_rec(x->left);
	printLRT_rec(x->right);
	cout << x->val << " ";
	// </�������� ������� �����>
}

void printLRT_non_rec_universal(const Tree& t) {
	printLRT_non_rec_universal(t.root);
}

void printLRT_non_rec_universal(Node* x) {
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
			// <�������� ������� �����>
			s.push(t);
			if (t->right) s.push(t->right);
			if (t->left) s.push(t->left);
			// </�������� ������� �����>
		}
	}
}
