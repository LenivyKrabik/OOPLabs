#pragma once
#include "ShapeEditor.h"
#include "RectangleShape.h"

class RectangleEditor : public ShapeEditor {
public:
	~RectangleEditor(void);
	Shape* OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND);
	void DrawPreviewContour(HDC hdc);
};