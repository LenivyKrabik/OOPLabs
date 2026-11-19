#pragma once

#include <string>
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <commctrl.h> // Header for ListView
#pragma comment(lib, "comctl32.lib")

#define cellWidth 60
#define cellHeight 17

void setUpMatrix(HWND hWnd, HWND hMainWnd, int n, int minVal, int maxVal);
int randomNumber(int min, int max);
int CopyMatrixToClipboard(HWND hWnd, int** src, int n);