#pragma once
#include "Shape.h"

class PointShape : public Shape 
{
public:
	void Set(long x, long y, long _, long __);
	void Show(HDC);
};