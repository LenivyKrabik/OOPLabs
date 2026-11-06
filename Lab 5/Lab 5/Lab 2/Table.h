#pragma once
#include <string>
#include <Windows.h>
#include <commctrl.h> // Header for ListView
#pragma comment(lib, "comctl32.lib")
#include "resource1.h"
#define N 150

struct ShapeInfo
{
	std::string name;
	long xs1;
	long ys1;
	long xs2;
	long ys2;
};

void setUpTable(HWND hTableWnd);
void addShapeToTable(ShapeInfo* shape);
void OpenTable(HWND);
INT_PTR CALLBACK TableProc(HWND hTableWnd, UINT message, WPARAM wParam, LPARAM lParam);

class MyTable {
private:
	ShapeInfo** Shapes;
	int ShapeAmount = 0;
	MyTable()
	{
		Shapes = new ShapeInfo * [N] {};
	};
	MyTable(const MyTable&);
	MyTable& operator=(MyTable&);
public:
	void Add(std::string, long, long, long, long);
	static MyTable& getInstance()
	{
		static MyTable instance;
		return instance;
	}
	ShapeInfo* GetShapeAt(int i);
	int GetShapeAmount();
	void PopShape(int i);
	void Wipeout();
};