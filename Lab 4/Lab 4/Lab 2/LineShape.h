#pragma once
#include "Shape.h"

class LineShape : virtual public Shape
{
public:
	void Set(long x1, long y1, long x2, long y2);
	void Show(HDC);
	void DrawPreviewContour(HDC hdc);
	Shape* Replicate();
};
