#pragma once
#include "LineShape.h"
#include "EllipseShape.h"
#define r 25

class LineOOShape : public LineShape, public EllipseShape {
	void Set(long x1, long y1, long x2, long y2);
	void Show(HDC);
	void DrawPreviewContour(HDC hdc);
	Shape* Replicate();
};