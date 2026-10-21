#pragma once
#include <Windows.h>

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	virtual ~Shape() = default;
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC hdc) = 0;
	void ShowPreview(HWND hWnd);
	virtual void DrawPreviewContour(HDC hdc) = 0;
	virtual Shape* Replicate() = 0;
};