#pragma once
#include "ShapeEditor.h"
#include "EllipseShape.h"

class EllipseEditor : public ShapeEditor {
public:
	~EllipseEditor(void);
	Shape* OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND);
	void DrawPreviewContour(HDC hdc);
};