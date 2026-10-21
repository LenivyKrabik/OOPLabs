#include "MyEditor.h"

MyEditor::MyEditor() {
	pshape = new Shape * [N] {};
}

void MyEditor::OnPaint(HWND hWnd, HDC hdc) {
	for (int x = 0;x < NextShape;x++) {
		if (pshape[x]) pshape[x]->Show(hdc);
	}
}

void MyEditor::Start(Shape* newShape, int btnID) {
	if (CurrShape) delete CurrShape;
	CurrShape = newShape;
	CurrBtnID = btnID;
}

void MyEditor::OnLBdown(HWND hWnd) {
	if (CurrShape) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
	
		CurrShape->Set(pt.x, pt.y, pt.x, pt.y);
		CurrShape->ShowPreview(hWnd);
		LBPressed = TRUE;
	}
	
}

void MyEditor::OnLBup(HWND hWnd) {
	if (LBPressed) {
		pshape[NextShape++] = CurrShape;
		CurrShape = CurrShape->Replicate();
		InvalidateRect(hWnd, nullptr, TRUE);
		LBPressed = FALSE;
	}
}

void MyEditor::OnMouseMove(HWND hWnd) {
	if (CurrShape && LBPressed) {
		CurrShape->ShowPreview(hWnd);
	}
}

void MyEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam) {
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); //POPUP-меню Об'єкти
	int btnAmount = GetMenuItemCount(hSubMenu);
	
	if ((HMENU)wParam == hSubMenu && CurrShape)
	{
		for (int x = 0; x < btnAmount;x++) {
			int itemID = GetMenuItemID(hSubMenu, x);
			CheckMenuItem(hSubMenu, itemID, itemID == CurrBtnID ? MF_CHECKED : MF_UNCHECKED);
		}
	}
}