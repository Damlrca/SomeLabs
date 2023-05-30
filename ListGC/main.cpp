// Sadikov Damir, 2023
// ListGC
#include <iostream>
#include "ListGC.h"

using namespace std;

int main() {
	Node::init(10); // Предвыделение памяти под 10 Node;
	// Нужно ли освобождать эту память? Но при этом все List будут в некоректном состоянии
	// Здесь освобождение предвыделенной памяти не реализовано
	
	// В текущей реализации подразумевается что есть всего 1 List
	// (т.к. Node::gc(Node*) получает указатель на первый Node из List)

	List l;
	for (int i = 0; i < 20; i++) {
		l.addFirst(i);
		l.delFirst();
	}
	return 0;
}
