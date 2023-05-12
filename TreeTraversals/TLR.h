#pragma once

#include <iostream>
#include <stack>
#include "Tree.h"
using namespace std;

// Top Left Right
// Прямой обход
// Pre-order, NLR

// Рекурсивный способ обхода
void printTLR_rec(const Tree& t);
void printTLR_rec(Node* x);

// Мой универсальный нерекурсивный способ обхода использующий 2 стека
// Можно изменить способ обхода просто поменяв местами строки
void printTLR_non_rec_universal(const Tree& t);
void printTLR_non_rec_universal(Node* x);

// Нерекурсивный (итеративный) способ обхода
void printTLR_non_rec(const Tree& t);
void printTLR_non_rec(Node* x);

// Итератор основан на универсальном способе
class TreeIteratorTLR : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorTLR(const Tree& t) : TreeIteratorTLR(t.root) {}
	TreeIteratorTLR(Node* x) {
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
				if (t->left) s.push(t->left);
				s.push(t);
				// </изменять порядок здесь>
			}
		}
	}
};
