#pragma once

#include <iostream>
#include <stack>
#include "Tree.h"
using namespace std;

//
// Left Top Right
//

void printLTR_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLTR_rec(x->left);
	cout << x->val << " ";
	printLTR_rec(x->right);
	// </изменять порядок здесь>
}

void printLTR_non_rec(Node* x) {
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

// one stack version:
/*void printLTR_non_rec(Node* root) {
	stack<Node*> st;
	Node* tmp = root;
	while (tmp) st.push(tmp), tmp = tmp->left;
	while (!st.empty()) {
		tmp = st.top(); st.pop();
		cout << tmp->val << " ";
		tmp = tmp->right;
		while (tmp) st.push(tmp), tmp = tmp->left;
	}
}*/

class TreeIteratorLTR : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorLTR(Node* x) {
		if (x)
			s.push(x);
	}
	bool hasNext() {
		return !s.empty();
	}
	int next() {
		if (!hasNext()) throw - 1;
		while (!s.empty()) {
			Node* t = s.top(); s.pop();
			if (!is.empty() && is.top() == t) {
				is.pop();
				return t->val;
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
};
