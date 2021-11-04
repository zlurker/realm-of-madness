#pragma once
#include "Vector2.h"
#include <vector>
#include <memory>

enum PointType { XMIN, XMAX, YMIN, YMAX };
enum BoundType { START, END };

class ElementPoint {
public:
	ElementPoint();

	// Need to find alternative for this.
	//int axisPos;
	float pointPosition;
	
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
	~MatrixElementBounds();

	BoundData operator[](int);

	
	int matrixLayer;
	BoundData* boundData;

	std::shared_ptr<std::pair<int,int>> parentLink;

	std::pair<int, int> parent;
	std::vector<std::shared_ptr<std::pair<int, int>>> child;
};



class MatrixElement {
public:
	MatrixElement(Vector2 c, Vector2 bD);
	//int* GetAxisPosition(int);
	void SetMatrixPosition(Vector2 c);
	void SetElementId(int id);

	template<class T>
	void BoundsChildOperation(int,void (T::*)(int,int));

	Vector2 coordinates;
	Vector2 boundDetails;
	ElementPoint* points;

	std::vector<MatrixElementBounds> matrixBounds;

private:
	int elementId;
};

