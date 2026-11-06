#include "Shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

std::string Shape::GetCoords() {
	return std::to_string(xs1) + "," + std::to_string(ys1) + "," + std::to_string(xs2) + "," + std::to_string(ys2);
}

ShapeDesc* Shape::GetInfo() {
	ShapeDesc* desc = new ShapeDesc{ name = name, xs1 = xs1, ys1 = ys1, xs2 = xs2, ys2 = ys2 };
	return desc;
}

void Shape::ShowPreview(HWND hWnd) {
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;

	hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	DrawPreviewContour(hdc);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xs2 = pt.x;
	ys2 = pt.y;

	DrawPreviewContour(hdc);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}


void ShapeFactory::registerShape(std::string name, Shape* shape) {
	std::unordered_map<std::string, Shape*>&  storage = getStorage();
	if (storage.find(name) == storage.end()) {
		storage[name] = shape;
	}
		
}

Shape* ShapeFactory::getShape(std::string name) {
	if (getStorage().find(name) != getStorage().end()) return getStorage()[name]->Replicate();
}