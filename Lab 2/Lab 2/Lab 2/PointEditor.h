#pragma once
#include "ShapeEditor.h"
#include "PointShape.h"

class PointEditor : public ShapeEditor {
	~PointEditor(void);
	Shape* OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND);
	void DrawPreviewContour(HDC hdc);
};