// Sadikov Damir, 2023
// SmartPointer
#include<iostream>
using namespace std;

template<class T>
class SmartPointer {
	struct base_ptr {
		T* ptr;
		int cnt;
	};
	base_ptr* base;
public:
	SmartPointer(T* _ptr) {
		base = new base_ptr(_ptr, 1);
	}
	SmartPointer(const SmartPointer& p) {
		base = p.base;
		base->cnt++;
	}
	SmartPointer(SmartPointer&& p) {
		base = p.base;
		p.base = new base_ptr(nullptr, p.base->cnt);
	}
	SmartPointer& operator=(const SmartPointer& p) {
		if (this == &p)
			return *this;

		base->cnt--;
		if (base->cnt == 0) {
			delete base->ptr;
			delete base;
		}
		
		base = p.base;
		base->cnt++;
		return *this;
	}
	SmartPointer& operator=(SmartPointer&& p) {
		if (this == &p)
			return *this;

		base->cnt--;
		if (base->cnt == 0) {
			delete base->ptr;
			delete base;
		}

		base = p.base;
		p.base = new base_ptr(nullptr, p.base->cnt);
		return *this;
	}
	T* operator->() {
		return base->ptr;
	}
	~SmartPointer() {
		base->cnt--;
		if (base->ptr) {
			delete base->obj;
			delete base;
		}
	}
};

int main() {
	
	return 0;
}
