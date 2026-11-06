#pragma once
#include "Shape.h"

class PointShape : public Shape 
{
public:
	PointShape();
	void Set(long x1, long y1, long x2, long y2);
	void Show(HDC);
	void DrawPreviewContour(HDC hdc);
	Shape* Replicate();
};