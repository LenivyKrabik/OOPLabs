#pragma once
#include <Windows.h>
#include "resource.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

class ToolbarHandler {
protected:
	HWND hwndToolBar;
public:
	ToolbarHandler(HWND hWnd, HINSTANCE hInst);
	void OnSizeChange(HWND hWnd);
	void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
};