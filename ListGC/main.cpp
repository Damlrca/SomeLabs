// Sadikov Damir, 2023
// ListGC
#include <iostream>
#include "ListGC.h"

using namespace std;

int main() {
	Node::init(10); // ������������� ������ ��� 10 Node;
	// ����� �� ����������� ��� ������? �� ��� ���� ��� List ����� � ����������� ���������
	// ����� ������������ �������������� ������ �� �����������
	
	List l;
	for (int i = 0; i < 20; i++) {
		l.addFirst(i);
		l.delFirst();
	}
	return 0;
}
