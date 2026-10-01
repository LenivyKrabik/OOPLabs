#include "PointShape.h"

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs1, ys1, RGB(255, 128, 0));
}