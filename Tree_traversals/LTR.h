#pragma once

#include <iostream>
#include <stack>
#include "Tree.h"
using namespace std;

// Left Top Right
// Центрированный обход
// In-order, LNR

// Рекурсивный способ обхода
void printLTR_rec(const Tree& t);
void printLTR_rec(Node* x);

// Мой универсальный нерекурсивный способ обхода использующий 2 стека
// Можно изменить способ обхода просто поменяв местами строки
void printLTR_non_rec_universal(const Tree& t);
void printLTR_non_rec_universal(Node* x);

// Нерекурсивный (итеративный) способ обхода
void printLTR_non_rec(const Tree& t);
void printLTR_non_rec(Node* x);

// Итератор основан на универсальном способе
class TreeIteratorLTR : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorLTR(const Tree& t) : TreeIteratorLTR(t.root) {}
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
