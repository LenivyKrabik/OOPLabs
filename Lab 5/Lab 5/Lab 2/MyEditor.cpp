#include "MyEditor.h"

void MyEditor::OnPaint(HWND hWnd, HDC hdc) {
	for (int x = 0;x < NextShape;x++) {
		if (pshape[x])
		{
			if (pshape[x]->selected) {
				HPEN hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
				HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

				pshape[x]->Show(hdc);

				SelectObject(hdc, hPenOld);
				DeleteObject(hPen);
				
			}
			else pshape[x]->Show(hdc);
		}

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
		PostMessage(hWnd, WM_COMMAND, ID_ADD_FIGURE, reinterpret_cast<LPARAM>(CurrShape->GetInfo()));
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




void MyEditor::SaveShapes() {
	FILE* fout;
	fopen_s(&fout, "saveFile.txt", "w");
	if (fout)
	{
		for (int x = 0;x < NextShape;x++) {
			fprintf(fout, (pshape[x]->GetShapeName() + ",").c_str());
			fprintf(fout, (pshape[x]->GetCoords() + "\n").c_str());
		}
		fclose(fout);
	}
}

void MyEditor::LoadShapes(HWND hWnd) {
	FILE* fin;
	fopen_s(&fin, "saveFile.txt", "r");
	if (fin)
	{
		//Deleting all off the previous stuff
		for (int x = 0; x < NextShape; x++) {
			delete pshape[x];
		}
		NextShape = 0;
		PostMessage(hWnd, WM_COMMAND, ID_WIPEOUT,0);

		char buf[4400];
		int c = 0;
		while (fgets(buf, 4400, fin))
		{
			char name[100] = { 0 };
			long x1 = 0, y1 = 0, x2 = 0, y2 = 0;

			int parsedCount = sscanf_s(buf, "%99[^,],%ld,%ld,%ld,%ld",
				name, (unsigned)_countof(name),
				&x1, &y1, &x2, &y2);

			if (parsedCount == 5) {
				Shape* shape = ShapeFactory::getShape(name);
				shape->Set(x1, y1, x2, y2);
				pshape[c++] = shape;
				PostMessage(hWnd, WM_COMMAND, ID_ADD_FIGURE, reinterpret_cast<LPARAM>(shape->GetInfo()));
			}
			
		}
		fclose(fin);
		NextShape = c;
		InvalidateRect(hWnd, nullptr, TRUE);
	}
}

void MyEditor::SelectShape(HWND hWnd, int i) {
	pshape[i]->selected = TRUE;
	InvalidateRect(hWnd, nullptr, TRUE);
}

void MyEditor::DeselectShape(HWND hWnd, int i) {
	pshape[i]->selected = FALSE;
	InvalidateRect(hWnd, nullptr, TRUE);
}

void MyEditor::PopShape(HWND hWnd, int i) {
	if (pshape[i]) {
		delete pshape[i];
		for (int x = i; x < NextShape - 1; x++) {
			pshape[x] = pshape[x + 1];
		}
		NextShape--;
	}
	InvalidateRect(hWnd, nullptr, TRUE);
}