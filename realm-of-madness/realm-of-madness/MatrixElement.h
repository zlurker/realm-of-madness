#pragma once
#include "Vector2.h"
#include <vector>

enum PointType { XMIN, XMAX, YMIN, YMAX };
enum BoundType { START, END };

class ElementPoint {
public:
	ElementPoint();

	// Need to find alternative for this.
	//int axisPos;
	float pointPosition;
	int elementId;
};

class MatrixElementBounds {
public:
	MatrixElementBounds(float bS, float bE);
	float operator[](int);

	float boundStart;
	float boundEnd;
};



class MatrixElement {
public:
	MatrixElement(Vector2 c, Vector2 bD);
	//int* GetAxisPosition(int);
	void SetMatrixPosition(Vector2 c);
	void SetElementId(int id);

	Vector2 coordinates;
	Vector2 boundDetails;
	ElementPoint* points;

	std::vector<MatrixElementBounds> matrixBounds;
};

