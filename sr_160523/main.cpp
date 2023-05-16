#include <iostream>
#include <utility>
#include <list>
#include <vector>
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
// классы Node и Tree скопированы из TreeTraversals/Tree.h

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
// максимум середи сумм элементов на пути среди всевозможных путей от корня дерева до его листьев

int max_fullpaths_sum(Node* node) {
	if (node->left == nullptr && node->right == nullptr) // лист
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
// максимум середи сумм элементов на всевозможных подпутях
// (в данном случае чтобы из путя получить подпуть нужно убрать некоторое кол-во элементов из начала и конца пути)
// всевозможных путей от корня дерева до его листьев

// Возвращает сумму на максимальном подпути начинающемся в вершине node
int max_subpaths_sum(Node* node, int& ans) {
	if (node->left == nullptr && node->right == nullptr) { // лист
		ans = max(ans, node->val);
		return node->val;
	}
	int sum = 0; // Нет смысла брать отрицательные подпути пути, поэтому = 0
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
// максимум середи сумм элементов на пути среди всевозможных путей в дереве!

// Возвращает сумму на максимальном подпути начинающемся в вершине node
int max_paths_sum(Node* node, int& ans) {
	if (node->left == nullptr && node->right == nullptr) { // лист
		ans = max(ans, node->val);
		return node->val;
	}
	int sum = 0; // Нет смысла брать отрицательные подпути пути, поэтому = 0
	int double_sum = 0; // Cумма и левого и правого подпутей
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
	double_sum += node->val; // считаем что node объединяет левый и правый подпуть в один путь
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

// max_paths_sum_and_path
// максимум середи сумм элементов на пути среди всевозможных путей в дереве
// и этот путь!

// Возвращает
// first - подпуть с максимальной суммой
// second - максимальная сумма
pair<list<Node*>, int> max_paths_sum_and_path(Node* node, int& ans,
	Node*& path_root, list<Node*>& path_left, list<Node*>& path_right) {
	// C++17 for this feature
	if (node->left == nullptr && node->right == nullptr) // лист
		return { list<Node*>{node}, node->val };
	pair<list<Node*>, int> left{};
	pair<list<Node*>, int> right{};
	if (node->left)
		left = max_paths_sum_and_path(node->left, ans, path_root, path_left, path_right);
	if (node->right)
		right = max_paths_sum_and_path(node->right, ans, path_root, path_left, path_right);
	// update ans
	if (left.second > 0 && right.second > 0) {
		if (int t = left.second + right.second + node->val; t > ans) {
			ans = t;
			path_root = node;
			path_left = left.first;
			path_right = right.first;
		}
	}
	else if (left.second > 0) {
		if (int t = left.second + node->val; t > ans) {
			ans = t;
			path_root = node;
			path_left = left.first;
			path_right = list<Node*>{};
		}
	}
	else if (right.second > 0) {
		if (int t = right.second + node->val; t > ans) {
			ans = t;
			path_root = node;
			path_left = list<Node*>{};
			path_right = right.first;
		}
	}
	else {
		if (int t = node->val; t > ans) {
			ans = t;
			path_root = node;
			path_left = list<Node*>{};
			path_right = list<Node*>{};
		}
	}
	// return
	if (left.second > 0 && left.second >= right.second) {
		list<Node*> path = move(left.first);
		path.push_front(node);
		return { path, node->val + left.second };
	}
	else if (right.second > 0) {
		list<Node*> path = move(right.first);
		path.push_front(node);
		return { path, node->val + right.second };
	}
	else {
		list<Node*> path{};
		path.push_front(node);
		return { path, node->val };
	}
}

pair<int, vector<Node*>> max_paths_sum_and_path(const Tree& tree) {
	if (tree.root == nullptr)
		throw "empty tree!\n";
	int ans = INT_MIN;
	Node* root = nullptr;
	list<Node*> left;
	list<Node*> right;
	max_paths_sum_and_path(tree.root, ans, root, left, right);
	vector<Node*> path;
	for (auto it = left.rbegin(); it != left.rend(); it++)
		path.push_back(*it);
	path.push_back(root);
	for (auto it = right.begin(); it != right.end(); it++)
		path.push_back(*it);
	return { ans, path };
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
	auto v = max_paths_sum_and_path(tree);
	cout << "   paths+: " << v.first << "; path: ";
	for (auto i : v.second)
		cout << i->val << " ";
	cout << endl;
	// fullpaths: 4
	//  subpaths: 9
	//     paths: 10
	//    paths+: 10; path: 5 4 1
#endif // TREE
	return 0;
}
