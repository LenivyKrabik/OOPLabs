#pragma once
#include "PointShape.h"
#include "LineShape.h"
#include "RectangleShape.h"
#include "EllipseShape.h"
#include "LineOOShape.h"
#include "CubeShape.h"
#include <stdio.h>
#include <fstream>
#include <shobjidl.h>
#define N 106
#define ID_ADD_FIGURE 32771
#define ID_WIPEOUT 32772

class MyEditor {
private:
	MyEditor() {
		pshape = new Shape* [N] {};
	}
	MyEditor(const MyEditor&);
	MyEditor& operator=(MyEditor&);
protected:
	Shape** pshape;
	int NextShape = 0;

	Shape* CurrShape;
	BOOL LBPressed = FALSE;
	int CurrBtnID = 0;
public:
	static MyEditor& getInstance()
	{
		static MyEditor instance;
		return instance;
	}
	void Start(Shape* newShape, int btnID);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND hWnd);
	void OnPaint(HWND hWnd, HDC hdc);
	void OnInitMenuPopup(HWND hWnd, WPARAM wParam);
	void SaveShapes();
	void LoadShapes(HWND hWnd);
	void SelectShape(HWND hWnd, int i);
	void DeselectShape(HWND hWnd, int i);
	void PopShape(HWND hWnd, int i);
};