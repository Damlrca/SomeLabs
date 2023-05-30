// Sadikov Damir, 2023
// ListGC
#pragma once

class Node {
	// Предвыделенная память

	static Node* mem; // Указатель на начало предвыделенной памяти
	static Node* firstFree; // Указатель на первый не занятый элемент в предвыделенной памяти
	static size_t memSize; // Размер предвыделенной памяти
public:
	static void gc(); // garbage clean
	static void init(size_t _memSize); // инициализация предвыделенной памяти
	
	// Node
	Node* next; // next node
	int val; // value
	Node(int _val, Node* _next) : val(_val), next(_next) {}
	~Node() { delete next; }

	// operator new, operator delete

	void* operator new(size_t t);
	void operator delete(void* p);
};

class List {
	Node* first;
public:
	List() : first(nullptr) {}
	~List() {
		while (first) {
			Node* t = first->next;
			delete first;
			first = t;
		}
	}
	void addFirst(int v) {
		try {
			first = new Node(v, first);
		}
		catch(...) {
			Node::gc();
			first = new Node(v, first);
		}
	}
	void delFirst() {
		if (first == nullptr)
			throw 1;
		Node* t = first->next;
		delete first;
		first = t;
	}
};
