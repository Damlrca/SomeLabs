#include "TLR.h"

void printTLR_rec(const Tree& t) {
	printTLR_rec(t.root);
}

void printTLR_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	cout << x->val << " ";
	printTLR_rec(x->left);
	printTLR_rec(x->right);
	// </изменять порядок здесь>
}

void printTLR_non_rec_universal(const Tree& t) {
	printTLR_non_rec_universal(t.root);
}

void printTLR_non_rec_universal(Node* x) {
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
			if (t->left) s.push(t->left);
			s.push(t);
			// </изменять порядок здесь>
		}
	}
}

void printTLR_non_rec(const Tree& t) {
	printTLR_non_rec(t.root);
}

void printTLR_non_rec(Node* x) {
	stack<Node*> s;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		cout << t->val << " ";
		if (t->right)
			s.push(t->right);
		if (t->left)
			s.push(t->left);
	}
}
