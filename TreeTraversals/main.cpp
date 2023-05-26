// Sadikov Damir, 2023
// TreeTraversal
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

	Tree tree{};
	tree.root = new Node(1);
	tree.root->left = new Node(2);
	tree.root->left->left = new Node(3);
	tree.root->right = new Node(4);
	tree.root->right->left = new Node(5);
	tree.root->right->left->left = new Node(6);
	tree.root->right->left->right = new Node(7);
	tree.root->right->right = new Node(8);

	// TLR: 1 2 3 4 5 6 7 8
	cout << "TLR:\n";
	printTLR_rec(tree);
	cout << "\n";
	printTLR_non_rec_universal(tree);
	cout << "\n";
	Iterator* tlr = new TreeIteratorTLR(tree);
	while (tlr->hasNext())
		cout << tlr->next() << " ";
	cout << "\n";
	printTLR_non_rec(tree);
	cout << "\n";

	// LTR: 3 2 1 6 5 7 4 8
	cout << "LTR:\n";
	printLTR_rec(tree);
	cout << "\n";
	printLTR_non_rec_universal(tree);
	cout << "\n";
	Iterator* ltr = new TreeIteratorLTR(tree);
	while (ltr->hasNext())
		cout << ltr->next() << " ";
	cout << "\n";
	printLTR_non_rec(tree);
	cout << "\n";

	// LRT: 3 2 6 7 5 8 4 1
	cout << "LRT:\n";
	printLRT_rec(tree);
	cout << "\n";
	printLRT_non_rec_universal(tree);
	cout << "\n";
	Iterator* lrt = new TreeIteratorLRT(tree);
	while (lrt->hasNext())
		cout << lrt->next() << " ";
	cout << "\n";
	printLRT_non_rec(tree);
	cout << "\n";

	return 0;
}
