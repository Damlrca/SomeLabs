// Sadikov Damir, 2023
// ListGC
#include <iostream>
#include "ListGC.h"

using namespace std;

int main() {
	Node::init(100); // ������������� ������ ��� 100 Node;
	// ����� �� ����������� ��� ������? �� ��� ���� ��� List ����� � ����������� ���������
	// ����� ������������ �������������� ������ �� �����������
	
	List l;
	l.addFirst(1);
	l.delFirst();
	return 0;
}
