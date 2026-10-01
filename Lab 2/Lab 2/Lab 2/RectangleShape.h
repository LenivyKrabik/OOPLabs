#pragma once
#include "Shape.h"

class RectangleShape : public Shape
{
public:
	void Set(long x1, long y1, long x2, long y2);
	void Show(HDC);
};
