#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
	Node(int _val, Node* _left, Node* _right) : val(_val), left(_left), right(_right) {}
	~Node() { delete left; delete right; }
};

class Iterator {
public:
	virtual bool hasNext() = 0;
	virtual int next() = 0;
};

//
// Top Left Right
//

void printTLR_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	cout << x->val << " ";
	printTLR_rec(x->left);
	printTLR_rec(x->right);
	// </изменять порядок здесь>
}

void printTLR_non_rec(Node* x) {
	stack<Node*> s;
	stack<Node*> is;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		if (!is.empty() && is.top() == t) {
			is.pop();
			cout << t->val << " ";
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

// one stack version:
/*void printTLR_non_rec(Node* x) {
	stack<Node*> s;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		cout << t->val << " ";
		if (t->right)
			s.push(t->right);
		if (t->left)
			s.push(t->left);
	}
}*/

class TreeIteratorTLR : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
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

//
// Left Top Right
//

void printLTR_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLTR_rec(x->left);
	cout << x->val << " ";
	printLTR_rec(x->right);
	// </изменять порядок здесь>
}

void printLTR_non_rec(Node* x) {
	stack<Node*> s;
	stack<Node*> is;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		if (!is.empty() && is.top() == t) {
			is.pop();
			cout << t->val << " ";
		}
		else {
			is.push(t);
			// <изменять порядок здесь>
			if (t->right) s.push(t->right);
			s.push(t);
			if (t->left) s.push(t->left);
			// </изменять порядок здесь>
		}
	}
}

// one stack version:
/*void printLTR_non_rec(Node* root) {
	stack<Node*> st;
	Node* tmp = root;
	while (tmp) st.push(tmp), tmp = tmp->left;
	while (!st.empty()) {
		tmp = st.top(); st.pop();
		cout << tmp->val << " ";
		tmp = tmp->right;
		while (tmp) st.push(tmp), tmp = tmp->left;
	}
}*/

class TreeIteratorLTR : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
	TreeIteratorLTR(Node* x) {
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
				s.push(t);
				if (t->left) s.push(t->left);
				// </изменять порядок здесь>
			}
		}
	}
};

//
// Left Right Top
//

void printLRT_rec(Node* x) {
	if (x == nullptr)
		return;
	// <изменять порядок здесь>
	printLRT_rec(x->left);
	printLRT_rec(x->right);
	cout << x->val << " ";
	// </изменять порядок здесь>
}

void printLRT_non_rec(Node* x) {
	stack<Node*> s;
	stack<Node*> is;
	if (x) s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		if (!is.empty() && is.top() == t) {
			is.pop();
			cout << t->val << " ";
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

// another two stacks version:
/*void printLRT_non_rec(Node* x) {
	stack<Node*> res;
	stack<Node*> s;
	if (x)
		s.push(x);
	while (!s.empty()) {
		Node* t = s.top(); s.pop();
		res.push(t);
		if (t->left)
			s.push(t->left);
		if (t->right)
			s.push(t->right);
	}
	while (!res.empty()) {
		Node* x = res.top(); res.pop();
		cout << x->val << " ";
	}
}*/

class TreeIteratorLRT : public Iterator {
	stack<Node*> s;
	stack<Node*> is;
public:
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

int main() {
	//       1
	//      / \
	//     2   4
	//    /   / \
	//   3   5   8
	//      / \
	//     6   7
	Node* root = new Node(1);
	root->left = new Node(2);
	root->left->left = new Node(3);
	root->right = new Node(4);
	root->right->left = new Node(5);
	root->right->left->left = new Node(6);
	root->right->left->right = new Node(7);
	root->right->right = new Node(8);

	cout << "TLR:\n";
	printTLR_rec(root);
	cout << "\n";
	printTLR_non_rec(root);
	cout << "\n";
	Iterator* tlr = new TreeIteratorTLR(root);
	while (tlr->hasNext())
		cout << tlr->next() << " ";
	cout << "\n";

	cout << "LTR:\n";
	printLTR_rec(root);
	cout << "\n";
	printLTR_non_rec(root);
	cout << "\n";
	Iterator* ltr = new TreeIteratorLTR(root);
	while (ltr->hasNext())
		cout << ltr->next() << " ";
	cout << "\n";

	cout << "LRT:\n";
	printLRT_rec(root);
	cout << "\n";
	printLRT_non_rec(root);
	cout << "\n";
	Iterator* lrt = new TreeIteratorLRT(root);
	while (lrt->hasNext())
		cout << lrt->next() << " ";
	cout << "\n";

	return 0;
}
