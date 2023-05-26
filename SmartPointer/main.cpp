// Sadikov Damir, 2023
// SmartPointer
#include<iostream>
#include <stack>
using namespace std;

template<class T>
class SmartPointer {
	struct SmartPointerBase {
		T* ptr;
		int cnt;
		SmartPointerBase(T* _ptr, int _cnt) : ptr(_ptr), cnt(_cnt) {}
		~SmartPointerBase() { delete ptr; }
	};
	SmartPointerBase* base;
public:
	SmartPointer(T* _ptr) {
		base = new SmartPointerBase(_ptr, 1);
	}
	SmartPointer(const SmartPointer& p) {
		base = p.base;
		base->cnt++;
	}
	SmartPointer& operator=(const SmartPointer& p) {
		if (this == &p)
			return *this;

		base->cnt--;
		if (base->cnt == 0)
			delete base;
		
		base = p.base;
		base->cnt++;

		return *this;
	}
	T* operator->() { return base->ptr; }
	T& operator*() { return *base->ptr; }
	T& operator[](int i) { return base->ptr[i]; }
	~SmartPointer() {
		base->cnt--;
		if (base->cnt == 0)
			delete base;
	}
};

// Нужно ли вообще в этом классе реализовывать
// SmartPointer(SmartPointer&& p)
// SmartPointer& operator=(SmartPointer&& p)
// На что должен указывать p после этого?
// Какой вообще смысл в перемещении в этом классе?

int main() {
	SmartPointer<int> a(new int[10]);
	for (int i = 0; i < 10; i++)
		a[i] = i;
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
