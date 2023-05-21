#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
	int n; // Размер выборки
	cout << "n: " << flush; cin >> n;
	int k; // Кол-во интервалов
	cout << "k: " << flush; cin >> k;
	// vector<pair<z[i], m[i]>> // Представитель интервала + Абсолютная частота
	vector<pair<double, double>> v(k);
	for (int i = 0; i < k; i++) {
		cout << "z[" << i + 1 << "], m[" << i + 1 << "]: " << flush;
		cin >> v[i].first >> v[i].second;
 	}
	double X{}; // Среднее выборочное
	double S{}; // Выборочная дисперсия
	for (int i = 0; i < k; i++) {
		X += v[i].first * v[i].second;
	}
	X /= n;
	for (int i = 0; i < k; i++) {
		S += v[i].first * v[i].first * v[i].second;
	}
	S /= n;
	S -= X * X;
	cout << fixed; cout.precision(10);
	cout << "X: " << X << "\nS: " << S << endl;
	return 0;
}
