#include "ShapeObjectsEditor.h"

ShapeObjectsEditor::ShapeObjectsEditor(void) {

}

ShapeObjectsEditor::~ShapeObjectsEditor(void) {
	if (editor) delete editor;
}

void ShapeObjectsEditor::StartPointEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new PointEditor();
	SetWindowText(hWnd, L"Режим редагування: Точка");
}
void ShapeObjectsEditor::StartLineEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new LineEditor();
	SetWindowText(hWnd, L"Режим редагування: Лінія");
}
void ShapeObjectsEditor::StartRectEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new RectangleEditor();
	SetWindowText(hWnd, L"Режим редагування: Прямокутник");
}
void ShapeObjectsEditor::StartEllipseEditor(HWND hWnd) {
	if (editor) delete editor;
	editor = new EllipseEditor();
	SetWindowText(hWnd, L"Режим редагування: Еліпс");
}
void ShapeObjectsEditor::OnLBdown(HWND hWnd, LPARAM lParam) {
	if (editor) {
		editor->OnLBdown(hWnd);
	}
}
void ShapeObjectsEditor::OnLBup(HWND hWnd) {
	if (editor) {
		Shape* res = editor->OnLBup(hWnd);
		pcshape[NextShape++] = res;
		InvalidateRect(hWnd, nullptr, TRUE);
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
	for (int x = 0;x < N;x++) {
		if (pcshape[x]) pcshape[x]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
	if (editor) editor->OnPaint(hWnd);
}