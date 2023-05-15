#include <iostream>
#include <chrono>

constexpr int width = 1000;
constexpr int height = 1000;

void mandlebrot_without_pragma() {
	System::Drawing::Bitmap^ bm = gcnew System::Drawing::Bitmap(width, height);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 3.0 / width * i  - 2.0;
			double y = 3.0 / height * j - 1.5;
			double dx = x, dy = y;
			int cnt = 0;
			while (cnt < 1000 && dx * dx + dy * dy <= 4.0) {
				double tdx = dx * dx - dy * dy + x;
				double tdy = 2 * dx * dy + y;
				dx = tdx;
				dy = tdy;
				cnt++;
			}
			int t = cnt == 1000 ? 0 : 255;
			bm->SetPixel(i, j, System::Drawing::Color::FromArgb(t, t, t));
		}
	}
	bm->Save("mandel_without_pr.png");
}

void mandlebrot_with_pragma() {
	System::Drawing::Bitmap^ bm = gcnew System::Drawing::Bitmap(width, height);
	#pragma omp parallel for
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 3.0 / width * i - 2.0;
			double y = 3.0 / height * j - 1.5;
			double dx = x, dy = y;
			int cnt = 0;
			while (cnt < 1000 && dx * dx + dy * dy <= 4.0) {
				double tdx = dx * dx - dy * dy + x;
				double tdy = 2 * dx * dy + y;
				dx = tdx;
				dy = tdy;
				cnt++;
			}
			int t = cnt == 1000 ? 0 : 255;
			#pragma omp critical
			bm->SetPixel(i, j, System::Drawing::Color::FromArgb(t, t, t));
		}
	}
	bm->Save("mandel_with_pr.png");
}

int main() {
	auto start_time = std::chrono::system_clock::now();

	mandlebrot_without_pragma();
	auto without_pragma_time = std::chrono::system_clock::now();
	std::cout << "without_pragma_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(without_pragma_time - start_time).count() << "ms\n";

	mandlebrot_with_pragma();
	auto with_pragma_time = std::chrono::system_clock::now();
	std::cout << "with_pragma_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(with_pragma_time - without_pragma_time).count() << "ms\n";
	
	return 0;
}
