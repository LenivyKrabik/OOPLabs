#include "ShapeEditor.h"

void ShapeEditor::DrawPreview(HWND hWnd) {
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;

	hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	DrawPreviewContour(hdc);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	mouseX = pt.x;
	mouseY = pt.y;

	DrawPreviewContour(hdc);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void ShapeEditor::OnLBdown(HWND hWnd) {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	startX = pt.x;
	startY = pt.y;
	mouseX = pt.x;
	mouseY = pt.y;
	LBPressed = TRUE;
}