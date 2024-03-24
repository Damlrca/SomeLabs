// Дополнительно -> Свойства C++/CLR -> Поддержка CLR : /clr
// с++ -> Командная строка -> /Zc:twoPhase-
// ссылки -> System.Drawing

#include <iostream>
using namespace std;

using Bitmap = System::Drawing::Bitmap;

int main() {
	//Bitmap img(100, 100);
	//System::Drawing::Graphics::FromImage(%img);

	Bitmap^ img = gcnew Bitmap(100, 100);
	System::Drawing::Graphics^ gr = System::Drawing::Graphics::FromImage(img);
	gr->Clear(System::Drawing::Color::White);

	System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);
	System::Drawing::Brush^ br = gcnew System::Drawing::SolidBrush(System::Drawing::Color::GreenYellow);

	//gr->DrawLine(pen, 50, 25, 100, 100);

	System::Drawing::PointF p1(25.0f / 2.0f, 25.0f);
	System::Drawing::PointF p2(50.0f + 25.0f / 2.0f, 25.0f);
	System::Drawing::SizeF sF(25.0f, 25.0f);
	System::Drawing::RectangleF rf1(p1, sF);
	System::Drawing::RectangleF rf2(p2, sF);

	gr->FillEllipse(br, rf1);
	gr->DrawEllipse(pen, rf1);
	gr->FillEllipse(br, rf2);
	gr->DrawEllipse(pen, rf2);

	gr->FillPie(br, 25.0f, 25.0f + 25.0f / 2.0f, 50.f, 50.f, 0.f, 180.f);
	gr->DrawPie(pen, 25.0f, 25.0f + 25.0f / 2.0f, 50.f, 50.f, 0.f, 180.f);

	img->Save("myfile.png");
	cout << "saved\n";

	return 0;
}
