#include "RectangleShape.h"

void RectangleShape::Show(HDC hdc) {
	long x1 = 2 * xs1 - xs2;
	long y1 = 2 * ys1 - ys2;

	Rectangle(hdc, x1, y1, xs2, ys2);
}