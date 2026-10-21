#pragma once
#include "PointShape.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include "EllipseShape.h"
#include "LineOOShape.h"
#include "CubeShape.h"
#define N 106

class MyEditor {
protected:
	Shape** pshape;
	int NextShape = 0;

	Shape* CurrShape;
	BOOL LBPressed = FALSE;
	int CurrBtnID = 0;
public:
	MyEditor();
	void Start(Shape* newShape, int btnID);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND hWnd, HDC hdc);
	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
};