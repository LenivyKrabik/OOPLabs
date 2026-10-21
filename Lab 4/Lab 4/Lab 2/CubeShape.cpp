#include "CubeShape.h"

void CubeShape::Show(HDC hdc) {
	long _xs1 = xs1;
	long _ys1 = ys1;
	long _xs2 = xs2;
	long _ys2 = ys2;

	long extraCorner1x = (_xs1 + distanceCoef * _xs2) / (1 + distanceCoef);
	long extraCorner1y = (_ys1 + distanceCoef * _ys2) / (1 + distanceCoef);

	xs1 = extraCorner1x;
	ys1 = extraCorner1y;
	RectangleShape::Show(hdc);
	xs1 = _xs1;
	ys1 = _ys1;


	long extraCorner2x = (_xs2 + distanceCoef * _xs1) / (1 + distanceCoef);
	long extraCorner2y = (_ys2 + distanceCoef * _ys1) / (1 + distanceCoef);
	xs2 = extraCorner2x;
	ys2 = extraCorner2y;
	RectangleShape::Show(hdc);

	xs1 = _xs1;
	ys1 = extraCorner2y;
	xs2 = extraCorner1x;
	ys2 = _ys2;
	LineShape::Show(hdc);

	xs1 = extraCorner2x;
	ys1 = extraCorner2y;
	xs2 = _xs2;
	ys2 = _ys2;
	LineShape::Show(hdc);

	xs1 = extraCorner2x;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = extraCorner1y;
	LineShape::Show(hdc);


	xs1 = _xs1;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = _ys2;
}
void CubeShape::DrawPreviewContour(HDC hdc) {
	long _xs1 = xs1;
	long _ys1 = ys1;
	long _xs2 = xs2;
	long _ys2 = ys2;

	long extraCorner1x = (_xs1 + distanceCoef * _xs2) / (1 + distanceCoef);
	long extraCorner1y = (_ys1 + distanceCoef * _ys2) / (1 + distanceCoef);

	xs1 = extraCorner1x;
	ys1 = extraCorner1y;
	RectangleShape::DrawPreviewContour(hdc);
	xs1 = _xs1;
	ys1 = _ys1;


	long extraCorner2x = (_xs2 + distanceCoef * _xs1) / (1 + distanceCoef);
	long extraCorner2y = (_ys2 + distanceCoef * _ys1) / (1 + distanceCoef);
	xs2 = extraCorner2x;
	ys2 = extraCorner2y;
	RectangleShape::DrawPreviewContour(hdc);

	xs1 = _xs1;
	ys1 = extraCorner2y;
	xs2 = extraCorner1x;
	ys2 = _ys2;
	LineShape::DrawPreviewContour(hdc);

	xs1 = extraCorner2x;
	ys1 = extraCorner2y;
	xs2 = _xs2;
	ys2 = _ys2;
	LineShape::DrawPreviewContour(hdc);

	xs1 = extraCorner2x;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = extraCorner1y;
	LineShape::DrawPreviewContour(hdc);

	xs1 = _xs1;
	ys1 = _ys1;
	xs2 = extraCorner1x;
	ys2 = extraCorner1y;
	LineShape::DrawPreviewContour(hdc);


	xs1 = _xs1;
	ys1 = _ys1;
	xs2 = _xs2;
	ys2 = _ys2;

}
Shape* CubeShape::Replicate() {
	return new CubeShape();
}