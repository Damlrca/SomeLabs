#include "AVLtree.h"
#include <iostream>
using namespace std;

int main() {
	AVLtree mytree;
	mytree.add_value(1);
	mytree._debug_write();
	mytree.add_value(1);
	mytree._debug_write();
	mytree.add_value(3);
	mytree._debug_write();
	mytree.add_value(2);
	mytree._debug_write();
	mytree.add_value(1);
	mytree._debug_write();
	mytree.add_value(5);
	mytree._debug_write();
	mytree.add_value(4);
	mytree._debug_write();
	cout << "is it work?" << endl;
	return 0;
}
