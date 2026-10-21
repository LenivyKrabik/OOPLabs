#include "LineOOShape.h"

void LineOOShape::Show(HDC hdc) {
	LineShape::Show(hdc);
	long _xs1 = xs1;
	long _ys1 = ys1;
	long _xs2 = xs2;
	long _ys2 = ys2;
	xs2 = xs1 + r;
	ys2 = ys1 + r;
	EllipseShape::Show(hdc);
	xs1 = _xs2;
	ys1 = _ys2;
	xs2 = xs1 + r;
	ys2 = ys1 + r;
	EllipseShape::Show(hdc);
	xs1 = _xs1;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = _ys2;

}
void LineOOShape::DrawPreviewContour(HDC hdc) {
	LineShape::DrawPreviewContour(hdc);
	long _xs1 = xs1;
	long _ys1 = ys1;
	long _xs2 = xs2;
	long _ys2 = ys2;
	xs2 = xs1 + r;
	ys2 = ys1 + r;
	EllipseShape::DrawPreviewContour(hdc);
	xs1 = _xs2;
	ys1 = _ys2;
	xs2 = xs1 + r;
	ys2 = ys1 + r;
	EllipseShape::DrawPreviewContour(hdc);
	xs1 = _xs1;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = _ys2;
	
}
Shape* LineOOShape::Replicate() {
	return new LineOOShape();
}