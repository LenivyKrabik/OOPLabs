#include "PointEditor.h"

PointEditor::~PointEditor(void) {
}

Shape* PointEditor::OnLBup(HWND) {
	if (LBPressed) {
		Shape* res = new PointShape();
		res->Set(mouseX, mouseY, 0, 0);
		return res;
	}
	LBPressed = FALSE;
	return 0;
}
void PointEditor::OnMouseMove(HWND hWnd) {
	if (LBPressed) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		mouseX = pt.x;
		mouseY = pt.y;
	}
}
void PointEditor::OnPaint(HWND hWnd) {

}

void PointEditor::DrawPreviewContour(HDC hdc) {
	SetPixel(hdc, mouseX, mouseY, RGB(255, 128, 0));
}