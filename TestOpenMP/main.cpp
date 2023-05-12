#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

constexpr int N = 1000;

int main() {
	std::vector<std::vector<int>> m1(N, std::vector<int>(N));
	std::vector<std::vector<int>> m2(N, std::vector<int>(N));

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			m1[i][j] = (i + j * 2) % 28;
			m2[i][j] = (i * 21 + j * 3) % 37;
		}

	std::vector<std::vector<int>> res(N, std::vector<int>(N));

	auto start_time = std::chrono::system_clock::now();

	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int t = 0;
			for (int k = 0; k < N; k++) {
				t += m1[i][k] * m2[k][j];
			}
			res[i][j] = t;
		}
	}

	auto end_time = std::chrono::system_clock::now();
	std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "\n";
	return 0;
}
