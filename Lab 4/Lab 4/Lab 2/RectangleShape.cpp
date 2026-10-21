#include "RectangleShape.h"

void RectangleShape::Show(HDC hdc) {
	HBRUSH hBrush, hBrushOld;
	hBrush = (HBRUSH)CreateSolidBrush(RGB(255,255,0)); //новий пензль
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc

	Rectangle(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hBrushOld); //відновлюється пензль-попередник
	DeleteObject(hBrush); //створений пензль знищується

	
}

void RectangleShape::DrawPreviewContour(HDC hdc) {
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);
}

Shape* RectangleShape::Replicate() {
	return new RectangleShape();
}