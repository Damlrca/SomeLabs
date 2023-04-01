#pragma once

#include <iostream>
#include <stack>
#include "Tree.h"
using namespace std;

//
// Left Right Top
//

void printLRT_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLRT_rec(x->left);
	printLRT_rec(x->right);
	cout << x->val << " ";
	// </изменять порядок здесь>
}

void printLRT_non_rec(Node* x) {
	stack<Node*> s;
	stack<Node*> is;
	if (x) s.push(x);
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

// another two stacks version:
/*void printLRT_non_rec(Node* x) {
	stack<Node*> res;
	stack<Node*> s;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		res.push(t);
		if (t->left)
			s.push(t->left);
		if (t->right)
			s.push(t->right);
	}
	while (!res.empty()) {
		Node* x = res.top(); res.pop();
		cout << x->val << " ";
	}
}*/

class TreeIteratorLRT : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorLRT(Node* x) {
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
				s.push(t);
				if (t->right) s.push(t->right);
				if (t->left) s.push(t->left);
				// </изменять порядок здесь>
			}
		}
	}
};
