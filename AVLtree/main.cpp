#include <algorithm>
#include <stack>
using namespace std;

struct Node {
	Node* left;
	Node* right;
	int h;
	int key;
};

Node* rotate_sr(Node* cur) {
	Node* l = cur->left;
	Node* a = l->left;
	Node* b = l->right;
	Node* c = cur->right;
	l->left = a;
	l->right = cur;
	cur->left = b;
	cur->right = c;

	int th = 0;
	if (b) th = b->h;
	if (c) th = std::max(th, c->h);
	cur->h = th + 1;

	if (a) th = std::max(th, a->h);
	th++;
	l->h = th;

	return l;
}

Node* rotate_sl(Node* cur) {
	// TODO йоу чё-нибудь сделай уже
	return nullptr;
}

Node* rotate_br(Node* cur) {
	cur->left = rotate_sl(cur->left);
	Node* ret = rotate_sr(cur);
	return ret;
}

Node* rotate_bl(Node* cur) {
	// TODO
	return nullptr;
}

int get_balance(Node* cur) {
	int left_h = 0;
	int right_h = 0;
	if (cur->left)
		left_h = cur->left->h;
	if (cur->right)
		right_h = cur->right->h;
	int b = get_balance(cur);
	return right_h - left_h;
}

void balance(stack<Node*> path, Node* cur) {
	while (!path.empty()) {}
	{
		Node* parent = path.top(); path.pop();
		int b = get_balance(cur);
		Node* tmp = cur;
		if (b == 2) {
			int b_r = get_balance(cur->right);
			if (b_r > 0)
				tmp = rotate_sl(cur);
			else
				tmp = rotate_bl(cur);
		}
		else if (b == -2) {
			int b_l = get_balance(cur->left);
			if (b_l < 0)
				tmp = rotate_sr(cur);
			else
				tmp = rotate_br(cur);
		}
		if (parent->right = cur)
			parent->right = tmp;
		else
			parent->left = tmp;
		cur = parent;
	}

	int b = get_balance(root);
	if (b == 2) {
		int b_r = get_balance(root->right);
		if (b_r > 0)
			root = rotate_sl(root);
		else
			root = rotate_bl(root);
	}
	else if (b == -2) {
		int b_l = get_balance(root->left);
		if (b_l < 0)
			root = rotate_sr(root);
		else
			root = rotate_br(root);
	}
}

int main() {

	return 0;
}
