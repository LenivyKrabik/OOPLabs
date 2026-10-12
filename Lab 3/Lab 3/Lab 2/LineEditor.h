#pragma once
#include "ShapeEditor.h"
#include "LineShape.h"

class LineEditor : public ShapeEditor {
public:
	~LineEditor(void);
	Shape* OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND);
	void DrawPreviewContour(HDC hdc);
};