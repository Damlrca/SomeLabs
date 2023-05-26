// Sadikov Damir, 2023
// AVLtree
#pragma once
#include <iostream>
#include <algorithm>
#include <stack>

struct Node {
	Node* left;
	Node* right;
	int height;
	int value;
	Node(int _val) : Node(_val, nullptr, nullptr) {}
	Node(int _val, Node* _left, Node* _right) : value(_val), left(_left), right(_right) {
		height = 0;
		if (left)
			height = std::max(height, left->height);
		if (right)
			height = std::max(height, right->height);
		height++;
	}
	Node(const Node& _node) {
		value = _node.value;
		height = _node.height;
		if (_node.left)
			left = new Node(*_node.left);
		else
			left = nullptr;
		if (_node.right)
			right = new Node(*_node.right);
		else
			right = nullptr;
	}
	~Node() {
		delete left;
		delete right;
	}
};

class AVLtree {
private:
	Node* root = nullptr;
	Node* _small_right_rotation(Node* cur);
	Node* _small_left_rotation(Node* cur);
	Node* _big_right_rotation(Node* cur);
	Node* _big_left_rotation(Node* cur);
	int get_balance(Node* cur);
	void balance(std::stack<Node*>& path, Node* cur);
	void _debug_write(Node* n) {
		if (n) {
			_debug_write(n->left);
			std::cout << n->value << " ";
			_debug_write(n->right);
		}
	}
public:
	AVLtree() : root(nullptr) {}
	AVLtree(const AVLtree& tr) : root(nullptr) {}
	void add_value(int value) {
		if (root) {
			std::stack<Node*> path;
			path.push(root);
			while (true)
			{
				if (value < path.top()->value) {
					if (path.top()->left) {
						path.push(path.top()->left);
					}
					else {
						path.top()->left = new Node(value);
						balance(path, path.top()->left);
						return;
					}
				}
				else if (value > path.top()->value) {
					if (path.top()->right) {
						path.push(path.top()->right);
					}
					else {
						path.top()->right = new Node(value);
						balance(path, path.top()->right);
						return;
					}
				}
				else { // path.top()->value == value
					return;
				}
			}
		}
		else {
			root = new Node(value);
		}
	}
	void _debug_write() {
		_debug_write(root);
		std::cout << std::endl;
	}
	void clear() {
		delete root;
		root = nullptr;
	}
	~AVLtree() {
		clear();
	}
};
