// Sadikov Damir, 2023
// TreeTraversal
#pragma once

#include <iostream>
#include <stack>
#include "Tree.h"
using namespace std;

// Left Right Top
// Обратный обход
// Post-order, LRN

// Рекурсивный способ обхода
void printLRT_rec(const Tree& t);
void printLRT_rec(Node* x);

// Мой универсальный нерекурсивный способ обхода использующий 2 стека
// Можно изменить способ обхода просто поменяв местами строки
void printLRT_non_rec_universal(const Tree& t);
void printLRT_non_rec_universal(Node* x);

// Нерекурсивный (итеративный) способ обхода
void printLRT_non_rec(const Tree& t);
void printLRT_non_rec(Node* x);

// Итератор основан на универсальном способе
class TreeIteratorLRT : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorLRT(const Tree& t) : TreeIteratorLRT(t.root) {}
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
