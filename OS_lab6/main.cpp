// Sadikov Damir, 2023
// OS_lab6
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <locale>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
using namespace std;

const int quantum = 2; // Размер кванта

struct thread { // Поток
	int size = 0; // Кол-во временных интервалов выполнения потока
	string s; // Диаграмма выполнения потока
	int id = 0; // Индекс текущего интервала

	bool started = false; // Флаг начал ли поток выполнение
	int end_takt = 0; // Номер такта, на котором поток завершил выполнение
	int last_wait_takt = -1; // Номер последнего такта, на котором поток находился в состоянии ожидания
	                         // (-1 если на последнем такте поток находился в состоянии "выполнение")
};

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	wstring input_filename, output_filename;
	wcout << L"Имя входного файла: ";
	wcin >> input_filename;
	ifstream in(input_filename);
	if (!in.is_open()) {
		wcout << L"Не удалось открыть входной файл" << endl;
		return -1;
	}

	wcout << L"Имя выходного файла: ";
	wcin >> output_filename;
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
	wofstream out(output_filename);
	out.imbue(utf8_locale);
	if (!out.is_open()) {
		wcout << L"Не удалось открыть выходной файл" << endl;
		return -1;
	}

	int n; // Кол-во потоков
	in >> n;
	vector<thread> v(n); // Вектор потоков
	queue<int> q; // Очередь потоков, готовых к выполнению
	for (auto& t : v)
		in >> t.size;
	for (auto& t : v)
		in >> t.s;
	for (int i = 0; i < n; i++)
		q.push(i);

	int takt_num = 1; // Номер текущего такта
	int good_takts = 0; // Кол-во непростаивающих тактов
	int last_thr_id = -1; // Индекс последнего выполняющегося потока
	int switch_num = 0; // Кол-во переключений контекста
	vector<int> wait_time; // для подсчёта времени ожидания

	auto all_thr_finished = [&v]()->bool { // Функция для проверки, что все потоки завершили выполнение
		for (auto& o : v)
			if (o.id < o.size)
				return false;
		return true;
	};

	while (!all_thr_finished()) {
		if (q.empty()) { // Нет потоков, готовых к выполнению
			out << takt_num << L"\t";
			for (int i = 0; i < n; i++) {
				auto& t = v[i];
				if (t.started) {
					if (t.id < t.size) {
						if (t.s[t.id] == '0') {
							wcout << L"unexpected '0'\n";
							return -1;
						}
						else if (t.s[t.id] == '-') {
							out << L"|\t";
							t.id++;
							if (t.id < t.size && t.s[t.id] == '0')
								q.push(i);
							if (t.id == t.size)
								t.end_takt = takt_num;
							t.last_wait_takt = takt_num;
						}
					}
					else {
						out << L"x\t";
					}
				}
				else {
					wcout << L"unexpected not started thread\n";
					return -1;
				}
			}
			out << L"\n";
			takt_num++;
		}
		else { // Есть поток(и), готовый(ые) к выполнению
			int id_now = q.front(); q.pop();
			v[id_now].started = 1;
			auto& t_now = v[id_now];
			for (int j = 0; j < quantum && t_now.id < t_now.size && t_now.s[t_now.id] == '0'; j++) { // выполняем до quant тактов
				out << takt_num << L"\t";
				for (int i = 0; i < n; i++) {
					auto& t = v[i];
					if (i == id_now) {
						out << L"0\t";
						t.id++;
						if (t.id == t.size)
							t.end_takt = takt_num;
						if (t.last_wait_takt != -1)
							wait_time.push_back(takt_num - t.last_wait_takt - 1);
						t.last_wait_takt = -1;
						if (last_thr_id != id_now) {
							last_thr_id = id_now;
							switch_num++;
						}
					}
					else {
						if (t.started) {
							if (t.id < t.size) {
								if (t.s[t.id] == '0') {
									out << L".\t";
								}
								else if (t.s[t.id] == '-') {
									out << L"|\t";
									t.id++;
									if (t.id < t.size && t.s[t.id] == '0')
										q.push(i);
									if (t.id == t.size)
										t.end_takt = takt_num;
									t.last_wait_takt = takt_num;
								}
							}
							else {
								out << L"x\t";
							}
						}
						else {
							out << L".\t";
						}
					}
				}
				out << L"\n";
				takt_num++;
				good_takts++;
			}
			if (t_now.id < t_now.size && t_now.s[t_now.id] == '0')
				q.push(id_now);
		}
	}

	out << L"Пропускная способность: " << n << L" / " << takt_num - 1 << L"\n";
	out << L"Оборотное время: (";
	for (int i = 0; i < n; i++) {
		out << v[i].end_takt;
		if (i + 1 != n)
			out << L" + ";
	}
	out << L") / " << n << L"\n";
	out << L"Эффективность: " << good_takts << L" / " << takt_num - 1 << L"\n";
	out << L"Время ожидания: (";
	for (int i = 0; i < wait_time.size(); i++) {
		out << wait_time[i];
		if (i + 1 != wait_time.size())
			out << L" + ";
	}
	out << L") / " << wait_time.size() << L"\n";
	out << L"Число переключений контекста: " << switch_num - 1 << L"\n";

	wcout << L"Файл " << output_filename << L" успешно сохранён" << endl;
	return 0;
}
