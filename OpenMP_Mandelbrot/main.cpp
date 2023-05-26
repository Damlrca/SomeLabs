// Sadikov Damir, 2023
// OpenMP_Mandelbrot
#include <iostream>
#include <chrono>
#include <algorithm>

constexpr int width = 3000;
constexpr int height = 3000;
constexpr int iterations = 3000;

// TEST DEBUG
// width: 3000
// height : 3000
// iterations : 3000
// without_pragma_time : 33102ms
// with_pragma_time : 8762ms

// TEST RELEASE
// width: 3000
// height : 3000
// iterations : 3000
// without_pragma_time : 13792ms
// with_pragma_time : 3523ms

void mandlebrot_without_pragma() {
	System::Drawing::Bitmap^ bm = gcnew System::Drawing::Bitmap(width, height);
	System::Drawing::Imaging::BitmapData^ bd = bm->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	char* scan = (char*)bd->Scan0.ToPointer();
	int stride = bd->Stride;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 3.0 / width * i  - 2.0;
			double y = 3.0 / height * j - 1.5;
			double dx = x, dy = y;
			int cnt = 0;
			while (cnt < iterations && dx * dx + dy * dy <= 4.0) {
				double tdx = dx * dx - dy * dy + x;
				double tdy = 2 * dx * dy + y;
				dx = tdx;
				dy = tdy;
				cnt++;
			}
			int b = cnt == iterations ? 0 : 255;
			int rg = cnt == iterations ? 0 : 255 - std::min(250 * cnt / 50, 255);

			char* curpos = scan + j * stride + i * 3;
			*curpos = b; curpos++;
			*curpos = rg; curpos++;
			*curpos = rg;
		}
	}
	bm->UnlockBits(bd);
	bm->Save("mandel_without_pr.png");
}

void mandlebrot_with_pragma() {
	System::Drawing::Bitmap^ bm = gcnew System::Drawing::Bitmap(width, height);
	System::Drawing::Imaging::BitmapData^ bd = bm->LockBits(
		System::Drawing::Rectangle(0, 0, width, height),
		System::Drawing::Imaging::ImageLockMode::WriteOnly,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	char* scan = (char*)bd->Scan0.ToPointer();
	int stride = bd->Stride;
	#pragma omp parallel for
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			double x = 3.0 / width * i - 2.0;
			double y = 3.0 / height * j - 1.5;
			double dx = x, dy = y;
			int cnt = 0;
			while (cnt < iterations && dx * dx + dy * dy <= 4.0) {
				double tdx = dx * dx - dy * dy + x;
				double tdy = 2 * dx * dy + y;
				dx = tdx;
				dy = tdy;
				cnt++;
			}
			int b = cnt == iterations ? 0 : 255;
			int rg = cnt == iterations ? 0 : 255 - std::min(250 * cnt / 50, 255);

			char* curpos = scan + j * stride + i * 3;
			*curpos = b; curpos++;
			*curpos = rg; curpos++;
			*curpos = rg;
		}
	}
	bm->UnlockBits(bd);
	bm->Save("mandel_with_pr.png");
}

int main() {
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;
	std::cout << "iterations: " << iterations << std::endl;
	auto start_time = std::chrono::system_clock::now();

	mandlebrot_without_pragma();
	auto without_pragma_time = std::chrono::system_clock::now();
	std::cout << "without_pragma_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(without_pragma_time - start_time).count() << "ms" << std::endl;

	mandlebrot_with_pragma();
	auto with_pragma_time = std::chrono::system_clock::now();
	std::cout << "with_pragma_time: " << std::chrono::duration_cast<std::chrono::milliseconds>(with_pragma_time - without_pragma_time).count() << "ms" << std::endl;
	
	return 0;
}
