#pragma once

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
	Node(int _val, Node* _left, Node* _right) : val(_val), left(_left), right(_right) {}
	Node(const Node& t) : val(t.val) {
		if (t.left)
			left = new Node(*t.left);
		else
			left = nullptr;
		if (t.right)
			right = new Node(*t.right);
		else
			right = nullptr;
	}
	~Node() { delete left; delete right; }
};

struct Tree {
	Node* root = nullptr;
	Tree(Node* _root = nullptr) : root(_root) {}
	explicit Tree(const Tree& t) {
		if (t.root)
			root = new Node(*t.root);
		else
			root = nullptr;
	}
	Tree& operator=(const Tree& t) {
		if (this == &t)
			return *this;
		delete root;
		if (t.root)
			root = new Node(*t.root);
		else
			root = nullptr;
		return *this;
	}
	~Tree() { delete root; }
};

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual int next() = 0;
};
