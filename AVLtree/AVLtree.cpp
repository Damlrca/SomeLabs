// Sadikov Damir, 2023
// AVLtree
#include "AVLtree.h"

//  small right rotation
//     cur       l
//     / \      / \
//    l   C -> A  cur
//   / \          / \
//  A   B        B   C

Node* AVLtree::_small_right_rotation(Node* cur) {
	Node* l = cur->left;
	Node* A = l->left;
	Node* B = l->right;
	Node* C = cur->right;

	l->left = A;
	l->right = cur;
	cur->left = B;
	cur->right = C;

	int temp = 0;
	if (B) temp = B->height;
	if (C) temp = std::max(temp, C->height);
	cur->height = temp + 1;
	temp = cur->height;
	if (A) temp = std::max(temp, A->height);
	l->height = temp + 1;

	return l;
}

//  small left rotation
//   cur           r
//   / \          / \
//  A   r   ->  cur  C
//     / \      / \
//    B   C    A   B

Node* AVLtree::_small_left_rotation(Node* cur) {
	Node* r = cur->right;
	Node* A = cur->left;
	Node* B = r->left;
	Node* C = r->right;

	r->left = cur;
	r->right = C;
	cur->left = A;
	cur->right = B;

	int temp = 0;
	if (A) temp = A->height;
	if (B) temp = std::max(temp, B->height);
	cur->height = temp + 1;
	temp = cur->height;
	if (C) temp = std::max(temp, C->height);
	r->height = temp + 1;

	return r;
}

Node* AVLtree::_big_right_rotation(Node* cur) {
	cur->left = _small_left_rotation(cur->left);
	return _small_right_rotation(cur);
}

Node* AVLtree::_big_left_rotation(Node* cur) {
	cur->right = _small_right_rotation(cur->right);
	return _small_left_rotation(cur);
}

int AVLtree::get_balance(Node* cur) {
	int left_h = 0;
	int right_h = 0;
	if (cur->left)
		left_h = cur->left->height;
	if (cur->right)
		right_h = cur->right->height;
	return right_h - left_h;
}

void AVLtree::balance(std::stack<Node*>& path, Node* cur) {
	while (!path.empty()) {
		Node* parent = path.top(); path.pop();
		int b = get_balance(cur);
		Node* tmp = cur;
		if (b == 2) {
			int b_r = get_balance(cur->right);
			if (b_r > 0)
				tmp = _small_left_rotation(cur);
			else
				tmp = _big_left_rotation(cur);
		}
		else if (b == -2) {
			int b_l = get_balance(cur->left);
			if (b_l < 0)
				tmp = _small_right_rotation(cur);
			else
				tmp = _big_right_rotation(cur);
		}
		if (parent->right == cur)
			parent->right = tmp;
		else
			parent->left = tmp;
		cur = parent;
	}

	int b = get_balance(root);
	if (b == 2) {
		int b_r = get_balance(root->right);
		if (b_r > 0)
			root = _small_left_rotation(root);
		else
			root = _big_left_rotation(root);
	}
	else if (b == -2) {
		int b_l = get_balance(root->left);
		if (b_l < 0)
			root = _small_right_rotation(root);
		else
			root = _big_right_rotation(root);
	}
}
