#include <iostream>
#include <omp.h>
using namespace std;

int main() {
	int test = 0;
	#pragma omp parallel for
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++)
			test++;
	}
	cout << test << "\n";
	return 0;
}
