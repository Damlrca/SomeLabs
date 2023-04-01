#include "LRT.h"

void printLRT_rec(const Tree& t) {
	printLRT_rec(t.root);
}

void printLRT_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLRT_rec(x->left);
	printLRT_rec(x->right);
	cout << x->val << " ";
	// </изменять порядок здесь>
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
			// <изменять порядок здесь>
			s.push(t);
			if (t->right) s.push(t->right);
			if (t->left) s.push(t->left);
			// </изменять порядок здесь>
		}
	}
}

void printLRT_non_rec(const Tree& t) {
	printLRT_non_rec(t.root);
}

void printLRT_non_rec(Node* x) {
	stack<Node*> s;
	Node* t = x;
	Node* lastVis = nullptr;
	while (!s.empty() || t != nullptr) {
		if (t != nullptr) {
			s.push(t);
			t = t->left;
		}
		else {
			Node* top = s.top();
			if (top->right != nullptr && lastVis != top->right) {
				t = top->right;
			}
			else {
				cout << top->val << " ";
				lastVis = s.top(); s.pop();
			}
		}
	}
}
