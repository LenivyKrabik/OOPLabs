#pragma once
#include "LineShape.h"
#include "RectangleShape.h"
#define distanceCoef 0.5

class CubeShape : public LineShape, public RectangleShape {
	void Set(long x1, long y1, long x2, long y2);
	void Show(HDC);
	void DrawPreviewContour(HDC hdc);
	Shape* Replicate();
};