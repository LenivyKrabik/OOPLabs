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
	long x1 = 2 * startX - mouseX;
	long y1 = 2 * startY - mouseY;

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x1, mouseY);
	LineTo(hdc, mouseX, mouseY);
	LineTo(hdc, mouseX, y1);
	LineTo(hdc, x1, y1);
}