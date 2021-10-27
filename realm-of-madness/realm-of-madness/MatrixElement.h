#pragma once
#include "Vector2.h"

enum PointType { XMIN, XMAX, YMIN, YMAX };

class ElementPoint {
public:
	ElementPoint();

	// Need to find alternative for this.
	//int axisPos;
	float pointPosition;
	int elementId;
};



class MatrixElement {
public:
	MatrixElement(Vector2 c,Vector2 bD);
	//int* GetAxisPosition(int);
	void SetMatrixPosition(Vector2 c);
	void SetElementId(int id);

	Vector2 coordinates;
	Vector2 boundDetails;
	ElementPoint* points;
};

