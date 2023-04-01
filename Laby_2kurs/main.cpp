#include <iostream>
#include <stack>
#include "Tree.h"
#include "TLR.h"
#include "LTR.h"
#include "LRT.h"
using namespace std;

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
