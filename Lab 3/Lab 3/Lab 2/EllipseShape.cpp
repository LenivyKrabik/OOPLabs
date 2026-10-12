#include "EllipseShape.h"

void EllipseShape::Show(HDC hdc) {
	long x1 = 2 * xs1 - xs2;
	long y1 = 2 * ys1 - ys2;

	Ellipse(hdc, x1, y1, xs2, ys2);
}