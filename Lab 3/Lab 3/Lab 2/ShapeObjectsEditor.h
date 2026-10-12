#pragma once
#include <typeinfo>
#include "PointEditor.h"
#include "LineEditor.h"
#include "RectangleEditor.h"
#include "EllipseEditor.h"
#define N 106

//NOT FINISHED
class ShapeObjectsEditor
{
protected:
	Shape* *pcshape;
	ShapeEditor* editor = 0;
	int NextShape = 0;
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void StartPointEditor(HWND hWnd);
	void StartLineEditor(HWND hWnd);
	void StartRectEditor(HWND hWnd);
	void StartEllipseEditor(HWND hWnd);
	void OnLBdown(HWND hWnd, LPARAM lParam);
	void OnLBup(HWND hWnd);
	void OnMouseMove(HWND hWnd, LPARAM lParam);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};