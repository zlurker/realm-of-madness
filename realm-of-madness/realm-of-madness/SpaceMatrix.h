#pragma once
#include <vector>
#include "MatrixElement.h"
#include "HelperFunctions.h"
#include <iostream>
#include <limits>
#include <tuple>

enum MatrixLayerType { UP, CONTINUE, DOWN };

class AxisAccessor {
public:
	AxisAccessor();
	AxisAccessor(int, int);

	int matrixEId;
	int pType;
};

class SpaceMatrix
{
public:
	std::vector<AxisAccessor>* xAxis;
	std::vector<AxisAccessor>* yAxis;

	std::vector<std::vector<AxisAccessor>>* axisMatrix;

	std::vector<MatrixElement> matrixElements;

	SpaceMatrix();
	int CreateNewMatrixElement(Vector2, Vector2);
	//void SetMatrixElementLocation(int, Vector2);
	int* GetElementsInRange(Vector2, Vector2);
	void CreateAxisMatrixBounds(int);
	void GenerateMatrix(int);

private:
	void MapBounds(int,float,float,int);
	int BinarySearchAxisMatrix(int, int, int, int, float);
	AxisAccessor* ReturnAxisAccessor(int, int, int);
	MatrixElement* ReturnElement(AxisAccessor);
	ElementPoint* ReturnElementPoint(AxisAccessor);
	float ReturnNextBoundValue(int,AxisAccessor*, int);
	int DetermineAxisMatrixBinaryRange(int, int, int, float);
	void PopulateAxisMatrix(int,int);

	int BinarySearch(int, int, float, int);
	int DetermineBinaryRange(int, float, int);
	ElementPoint ReturnAxisPoint(int, int);
	int MoveAxisElement(int, int,int, int);
	int InsertAxisElement(int,int, int, AxisAccessor);
	void SanitiseValue(int*, int, int);
	std::vector<AxisAccessor>* ReturnAxis(int);
};

