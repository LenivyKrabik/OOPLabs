#include "EllipseEditor.h"

EllipseEditor::~EllipseEditor(void) {

}

Shape* EllipseEditor::OnLBup(HWND) {
	if (LBPressed) {
		Shape* res = new EllipseShape();
		res->Set(startX, startY, mouseX, mouseY);
		LBPressed = FALSE;
		return res;
	}
	return 0;
}
void EllipseEditor::OnMouseMove(HWND hWnd) {
	if (LBPressed) {
		DrawPreview(hWnd);
	}
}
void EllipseEditor::OnPaint(HWND hWnd) {

}

void EllipseEditor::DrawPreviewContour(HDC hdc) {
	Arc(hdc, startX, startY, mouseX, mouseY, 0, 0, 0, 0);
}