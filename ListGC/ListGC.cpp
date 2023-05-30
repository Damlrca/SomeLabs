// Sadikov Damir, 2023
// ListGC
#include "ListGC.h"
#include <new>
#include <set>

Node* Node::mem = nullptr;
Node* Node::firstFree = nullptr;
size_t Node::memSize = 0;

void Node::gc() {
	std::set<size_t> s; // Можно обойтись без std::set
	Node* temp = firstFree;
	while (temp) {
		s.insert(temp - mem);
		temp = temp->next;
	}
	for (size_t i = 0; i < memSize; i++) {
		if (s.find(i) == s.end()) {
			delete(mem + i);
		}
	}
}

void Node::init(size_t _memSize) {
	if (mem != nullptr) {
		// Функция init уже вызывалась
		// В этой реализации считается что init вызывается один раз
		throw 1;
	}
	if (_memSize == 0) {
		throw 1;
	}
	mem = static_cast<Node*>(::operator new(sizeof(Node) * _memSize));
	memSize = _memSize;
	firstFree = mem;
	for (size_t i = 0; i + 1 < memSize; i++)
		mem[i].next = mem + i + 1;
	mem[memSize - 1].next = nullptr;
}

void* Node::operator new(size_t t) {
	if (firstFree == nullptr)
		throw std::bad_alloc{};
	Node* p = firstFree;
	firstFree = firstFree->next;
	return p;
}

void Node::operator delete(void* p) {
	Node* t = static_cast<Node*>(p);
	t->next = firstFree;
	firstFree = t;
}
