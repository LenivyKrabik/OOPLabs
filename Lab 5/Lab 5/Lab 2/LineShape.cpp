#include "LineShape.h"

void LineShape::Show(HDC hdc) {
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void LineShape::DrawPreviewContour(HDC hdc) {
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

Shape* LineShape::Replicate() {
	return new LineShape();
}

LineShape::LineShape() {
	name = "Line";
}

namespace {
	BOOL registered = []() {
		ShapeFactory::registerShape("Line", new LineShape());
		return true;
		}();
}