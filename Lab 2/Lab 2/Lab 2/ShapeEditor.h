#pragma once
#include "Shape.h"

class ShapeEditor
{
protected:
	BOOL LBPressed = FALSE;
	int mouseX;
	int mouseY;
	int startX;
	int startY;
public:
	//ShapeEditor(void);
	void OnLBdown(HWND hWnd);
	virtual Shape* OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND hWnd) = 0;
	virtual void OnPaint(HWND) = 0;
	virtual void DrawPreviewContour(HDC hdc) = 0;
	void DrawPreview(HWND hWnd);
	//void OnInitMenuPopup(HWND, WPARAM); //додатковий інтерфейсний метод
};