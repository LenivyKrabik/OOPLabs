#include "Shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void Shape::ShowPreview(HWND hWnd) {
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;

	hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	DrawPreviewContour(hdc);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xs2 = pt.x;
	ys2 = pt.y;

	DrawPreviewContour(hdc);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}