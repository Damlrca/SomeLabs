#include <iostream>
#include <utility>
#include <list>
using namespace std;

//#define ADD_ITH
#define TREE

#ifdef ADD_ITH
struct Node {
	Node* next;
	int val;
	Node(int v, Node* n = nullptr) : val(v), next(n) {}
	Node(const Node& n) {
		val = n.val;
		if (n.next) {
			next = new Node(*n.next);
		}
		else {
			next = nullptr;
		}
	}
	void print() {
		cout << val << " ";
		if (next)
			next->print();
	}
	~Node() { delete next; }
};

class List {
	Node* root;
public:
	List() : root(nullptr) {}
	List(const List& l) : root(new Node(*l.root)) {}
	int add_i_th(int i, int val) {
		if (i < 0)
			throw "wrong index!\n";
		if (i == 0) {
			root = new Node(val, root);
		}
		else {
			int next_id = 1;
			Node* now = root;
			while (now != nullptr && next_id < i)
			{
				now = now->next;
				next_id++;
			}
			if (now == nullptr) {
				throw "wrong index!\n";
			}
			else {
				now->next = new Node(val, now->next);
			}
		}
	}
	void print() {
		if (root)
			root->print();
		cout << endl;
	}
	void clear() {
		delete root;
		root = nullptr;
	}
	~List() { clear(); }
};
#endif // ADD_ITH

#ifdef TREE
// ������ Node � Tree ����������� �� TreeTraversals/Tree.h

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

// max_fullpaths_sum
// �������� ������ ���� ��������� �� ���� ����� ������������ ����� �� ����� ������ �� ��� �������

int max_fullpaths_sum(Node* node) {
	if (node->left == nullptr && node->right == nullptr) // ����
		return node->val;
	int sum = INT_MIN;
	if (node->left)
		sum = max(sum, max_fullpaths_sum(node->left));
	if (node->right)
		sum = max(sum, max_fullpaths_sum(node->right));
	sum += node->val;
	return sum;
}

int max_fullpaths_sum(const Tree& tree) {
	if (tree.root == nullptr)
		throw "empty tree!\n";
	return max_fullpaths_sum(tree.root);
}

// max_subpaths_sum
// �������� ������ ���� ��������� �� ������������ ��������
// (� ������ ������ ����� �� ���� �������� ������� ����� ������ ��������� ���-�� ��������� �� ������ � ����� ����)
// ������������ ����� �� ����� ������ �� ��� �������

// ���������� ����� �� ������������ ������� ������������ � ������� node
int max_subpaths_sum(Node* node, int& ans) {
	if (node->left == nullptr && node->right == nullptr) { // ����
		ans = max(ans, node->val);
		return node->val;
	}
	int sum = 0; // ��� ������ ����� ������������� ������� ����, ������� = 0
	if (node->left) {
		int left = max_subpaths_sum(node->left, ans);
		sum = max(sum, left);
	}
	if (node->right) {
		int right = max_subpaths_sum(node->right, ans);
		sum = max(sum, right);
	}
	sum += node->val;
	ans = max(ans, sum);
	return sum;
}

int max_subpaths_sum(const Tree& tree) {
	if (tree.root == nullptr)
		throw "empty tree!\n";
	int ans = INT_MIN;
	max_subpaths_sum(tree.root, ans);
	return ans;
}

// max_paths_sum
// �������� ������ ���� ��������� �� ���� ����� ������������ ����� � ������!

// ���������� ����� �� ������������ ������� ������������ � ������� node
int max_paths_sum(Node* node, int& ans) {
	if (node->left == nullptr && node->right == nullptr) { // ����
		ans = max(ans, node->val);
		return node->val;
	}
	int sum = 0; // ��� ������ ����� ������������� ������� ����, ������� = 0
	int double_sum = 0; // C���� � ������ � ������� ��������
	if (node->left) {
		int left = max_paths_sum(node->left, ans);
		sum = max(sum, left);
		if (left > 0)
			double_sum += left;
	}
	if (node->right) {
		int right = max_paths_sum(node->right, ans);
		sum = max(sum, right);
		if (right > 0)
			double_sum += right;
	}
	sum += node->val;
	double_sum += node->val; // ������� ��� node ���������� ����� � ������ ������� � ���� ����
	ans = max(ans, double_sum);
	return sum;
}

int max_paths_sum(const Tree& tree) {
	if (tree.root == nullptr)
		throw "empty tree!\n";
	int ans = INT_MIN;
	max_paths_sum(tree.root, ans);
	return ans;
}

// first - ����
// second - max summ
pair<list<Node*>, int> max_sum_of_subpath_value2_WITH_PATH(Node* node, int& ans, Node*& path_root, list<Node*>& path_left, list<Node*>& path_right) {
	if (node->left == nullptr && node->right == nullptr) {
		if (node->val > ans) {
			ans = node->val;
			path_root = node;
			path_left = list<Node*>{};
			path_right = list<Node*>{};
		}
		return { list<Node*>{node}, node->val };
	}
	if (node->left) {
		pair<list<Node*>, int> left = max_sum_of_subpath_value2_WITH_PATH(node->left, ans, path_root, path_left, path_right);
		if (left.second > 0) {
			list<Node*> path = std::move(left.first);
			if (left.second + node->val > ans) {
				ans = left.second + node->val;
				path_root = node;
				path_left = path;
				path_right = list<Node*>{};
			}
			path.push_front(node);
			return { move(path), left.second + node->val };
		}
		else {
			if (node->val > ans) {
				ans = node->val;
				path_root = node;
				path_left = list<Node*>{};
				path_right = list<Node*>{};
			}
			return { list<Node*>{node}, node->val };
		}
	}
	if (node->right) {
		pair<list<Node*>, int> right = max_sum_of_subpath_value2_WITH_PATH(node->right, ans, path_root, path_left, path_right);
		if (right.second > 0) {
			list<Node*> path = std::move(right.first);
			if (right.second + node->val > ans) {
				ans = right.second + node->val;
				path_root = node;
				path_left = list<Node*>{};
				path_right = path;
			}
			path.push_front(node);
			return { move(path), right.second + node->val };
		}
		else {
			if (node->val > ans) {
				ans = node->val;
				path_root = node;
				path_left = list<Node*>{};
				path_right = list<Node*>{};
			}
			return { list<Node*>{node}, node->val };
		}
	}
	{ // node->left != nullptr && node->right != nullptr
		pair<list<Node*>, int> left = max_sum_of_subpath_value2_WITH_PATH(node->left, ans, path_root, path_left, path_right);
		pair<list<Node*>, int> right = max_sum_of_subpath_value2_WITH_PATH(node->right, ans, path_root, path_left, path_right);
		if (left.second > 0 && right.second > 0) {
			if (left.second + right.second + node->val > ans) {
				ans = left.second + right.second + node->val;
				path_root = node;
				path_left = left.first;
				path_right = right.first;
			}
		}
		if (left.second > 0 && left.second >= right.second) {
			list<Node*> path = std::move(left.first);
			if (left.second + node->val > ans) {
				ans = left.second + node->val;
				path_root = node;
				path_left = path;
				path_right = list<Node*>{};
			}
			path.push_front(node);
			return { move(path), left.second + node->val };
		}
		else if (right.second > 0) {
			list<Node*> path = std::move(right.first);
			if (node->val > ans) {
				ans = node->val;
				path_root = node;
				path_left = list<Node*>{};
				path_right = list<Node*>{};
			}
			path.push_front(node);
			return { move(path), right.second + node->val };
		}
		else {
			if (node->val > ans) {
				ans = node->val;
				path_root = node;
				path_left = list<Node*>{};
				path_right = list<Node*>{};
			}
			return { list<Node*>{node}, node->val };
		}
	}
}

void max_sum_of_subpath_value2_WITH_PATH(const Tree& tree) {
	if (tree.root == nullptr)
		throw "empty tree";
	int ans = tree.root->val;
	Node* root = tree.root;
	list<Node*> left;
	list<Node*> right;
	max_sum_of_subpath_value2_WITH_PATH(tree.root, ans, root, left, right);
	cout << ans << ": ";
}
#endif // TREE

int main() {
#ifdef ADD_ITH
	List mylist;
	while (true)
	{
		cout << "list: ";
		mylist.print();
		int id, val;
		cin >> id >> val;
		try {
			mylist.add_i_th(id, val);
		}
		catch (const char* c) {
			cout << "error: " << c << endl;
		}
	}
#endif // ADD_ITH

#ifdef TREE
	//      -1
	//      / \
	//    -2   4
	//    /   / \
	//  -3   5   1
	//      / \
	//    -6  -7

	Tree tree{};
	tree.root = new Node(-1);
	tree.root->left = new Node(-2);
	tree.root->left->left = new Node(-3);
	tree.root->right = new Node(4);
	tree.root->right->left = new Node(5);
	tree.root->right->left->left = new Node(-6);
	tree.root->right->left->right = new Node(-7);
	tree.root->right->right = new Node(1);

	cout << "fullpaths: " << max_fullpaths_sum(tree) << endl;
	cout << " subpaths: " << max_subpaths_sum(tree) << endl;
	cout << "    paths: " << max_paths_sum(tree) << endl;
	//max_sum_of_subpath_value2_WITH_PATH(tree);
#endif // TREE
	return 0;
}
