#include "LineEditor.h"

LineEditor::~LineEditor(void) {

}

Shape* LineEditor::OnLBup(HWND) {
	if (LBPressed) {
		Shape* res = new LineShape();
		res->Set(startX, startY,mouseX, mouseY);
		LBPressed = FALSE;
		return res;
	}
	return 0;
}
void LineEditor::OnMouseMove(HWND hWnd) {
	if (LBPressed) {
		DrawPreview(hWnd);
	}
}
void LineEditor::OnPaint(HWND hWnd) {

}

void LineEditor::DrawPreviewContour(HDC hdc) {
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, mouseX, mouseY);
}