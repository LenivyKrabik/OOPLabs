#pragma once
#include <Windows.h>
#include <string>
#include <unordered_map>

struct ShapeDesc
{
	std::string name;
	long xs1;
	long ys1;
	long xs2;
	long ys2;
};

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
	std::string name;
public:
	BOOL selected = FALSE;

	virtual ~Shape() = default;
	void Set(long x1, long y1, long x2, long y2);
	std::string GetCoords();
	ShapeDesc* GetInfo();
	std::string GetShapeName() const {
		return name;
	}
	virtual void Show(HDC hdc) = 0;
	void ShowPreview(HWND hWnd);
	virtual void DrawPreviewContour(HDC hdc) = 0;
	virtual Shape* Replicate() = 0;
};

class ShapeFactory {
private:
public:
	static std::unordered_map<std::string, Shape*>& getStorage() {
		static std::unordered_map<std::string, Shape*> storage;
		return storage;
	}
	static void registerShape(std::string name, Shape* shape);
	static Shape* getShape(std::string name);
};