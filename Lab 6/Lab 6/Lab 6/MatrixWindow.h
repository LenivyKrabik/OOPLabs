#pragma once
#include "Windows.h"
#include "resource.h"
#include <string>

void MakeMatrixWindow(HWND hWnd, HWND _obj2);
std::wstring GetEditText(HWND hWnd, int ID);

LRESULT CALLBACK MatrixWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);