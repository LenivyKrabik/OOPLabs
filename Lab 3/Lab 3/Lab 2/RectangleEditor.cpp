#include "RectangleEditor.h"

RectangleEditor::~RectangleEditor(void) {

}

Shape* RectangleEditor::OnLBup(HWND) {
	if (LBPressed) {
		Shape* res = new RectangleShape();
		res->Set(startX, startY, mouseX, mouseY);
		LBPressed = FALSE;
		return res;
	}
	return 0;
}
void RectangleEditor::OnMouseMove(HWND hWnd) {
	if (LBPressed) {
		DrawPreview(hWnd);
	}
}
void RectangleEditor::OnPaint(HWND hWnd) {

}

void RectangleEditor::DrawPreviewContour(HDC hdc) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, startX, mouseY);
	LineTo(hdc, mouseX, mouseY);
	LineTo(hdc, mouseX, startY);
	LineTo(hdc, startX, startY);
}