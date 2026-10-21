#include "PointShape.h"

void PointShape::Show(HDC hdc) {
	SetPixel(hdc, xs2, ys2, RGB(0, 0, 0));
}

void PointShape::DrawPreviewContour(HDC hdc) {
	SetPixel(hdc, xs2, ys2, RGB(255, 128, 0));
}

Shape* PointShape::Replicate() {
	return new PointShape();
}