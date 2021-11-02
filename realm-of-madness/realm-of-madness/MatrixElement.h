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


class BoundData {
public:
	BoundData(float, int);

	float boundPoint;
	int boundIdentifier;
};

class MatrixElementBounds {
public:
	MatrixElementBounds(int,float, float,int , int);
	BoundData operator[](int);
	int matrixLayer;
	BoundData* boundData;

	std::pair<int, int> parent;
	std::pair<int, int> child;
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

