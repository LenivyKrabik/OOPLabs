#include "ShapeObjectsEditor.h"


ShapeObjectsEditor::ShapeObjectsEditor(void) {
	pcshape = new Shape*[N]{};
}

ShapeObjectsEditor::~ShapeObjectsEditor(void) {
	if (editor) delete editor;
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new PointEditor();
}
void ShapeObjectsEditor::StartLineEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new LineEditor();
}
void ShapeObjectsEditor::StartRectEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new RectangleEditor();
}
void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new EllipseEditor();
}
void ShapeObjectsEditor::OnLBdown(HWND hWnd, LPARAM lParam) {
	if (editor) {
		editor->OnLBdown(hWnd);
	}
}
void ShapeObjectsEditor::OnLBup(HWND hWnd) {
	if (editor) {
		Shape* res = editor->OnLBup(hWnd);
		if (res) {
			pcshape[NextShape++] = res;
			InvalidateRect(hWnd, nullptr, TRUE);
		}
	}
}
void ShapeObjectsEditor::OnMouseMove(HWND hWnd, LPARAM lParam) {
	if (editor) {
		editor->OnMouseMove(hWnd);
	}
	
}
void ShapeObjectsEditor::OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	for (int x = 0;x < NextShape;x++) {
		if (pcshape[x]) pcshape[x]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
	if (editor) editor->OnPaint(hWnd);
}
void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); //POPUP-меню Об'єкти
		if ((HMENU)wParam == hSubMenu && editor)
		{
			CheckMenuItem(hSubMenu, GetMenuItemID(hSubMenu, 0), typeid(*editor) == typeid(PointEditor) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(hSubMenu, GetMenuItemID(hSubMenu, 1), typeid(*editor) == typeid(LineEditor) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(hSubMenu, GetMenuItemID(hSubMenu, 2), typeid(*editor) == typeid(RectangleEditor) ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(hSubMenu, GetMenuItemID(hSubMenu, 3), typeid(*editor) == typeid(EllipseEditor) ? MF_CHECKED : MF_UNCHECKED);
		}
}