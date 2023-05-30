// Sadikov Damir, 2023
// ListGC
#include <iostream>
#include "ListGC.h"

using namespace std;

int main() {
	Node::init(100); // Предвыделение памяти под 100 Node;
	// Нужно ли освобождать эту память? Но при этом все List будут в некоректном состоянии
	// Здесь освобождение предвыделенной памяти не реализовано
	
	List l;
	l.addFirst(1);
	l.delFirst();
	return 0;
}
