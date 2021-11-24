#pragma once
#pragma once
#include <vector>
#include "MatrixElement.h"
#include "HelperFunctions.h"
#include "IDGenerator.h"
#include "MatrixSpaceMerger.h"
#include <iostream>
#include <limits>
#include <tuple>

enum class MatrixLayerType { UP, CONTINUE, DOWN };
enum class BoundCollisionType { DIFFERENT, SAME, NONE };

class AxisAccessor {
public:
	AxisAccessor();
	AxisAccessor(int, int);

	int matrixElementId;
	int boundId;
	//int boundType;
	//int uniqueId;
};

class MatrixSpaceMarker {
public:
	MatrixSpaceMarker(float);

	AxisAccessor end;
	AxisAccessor start;

	AxisAccessor GetAxisAccessor(BoundType);
	void SetAxisAccessor(BoundType, int, int);
	float ReturnMarkerPosition();

private:
	float markerPos;
};


class AxisAccessorPlacement {
public:
	AxisAccessorPlacement();

	int axis;
	int matrixLayer;
	int position;
};

class SpaceMatrix
{
public:
	std::vector<AxisAccessor>* xAxis;
	std::vector<AxisAccessor>* yAxis;

	std::vector<std::vector<MatrixSpaceMarker>>* axisMatrix;

	std::vector<MatrixElement> matrixElements;

	MatrixSpaceMerger matrixMerger;

	SpaceMatrix();
	int CreateNewMatrixElement(Vector2, Vector2);
	void SetMatrixElementLocation(int, Vector2);
	int* GetElementsInRange(Vector2, Vector2);
	void CreateAxisMatrixBounds(int);
	void GenerateMatrix(int);

private:
	MatrixSpaceMerger groupBoundsMerger;

	void ShiftBoundsUp(int elementId, int boundId, int targetAxis, int matrixLayer = -1, int insertionPoint = -1);
	//bool Comparision(AxisAccessor accessor);
	void MapBounds(int, float, float, int);
	//int BinarySearchAxisMatrix(int, int, int, int, float);
	AxisAccessor* ReturnAxisAccessor(int, int, int, BoundType);
	MatrixElement* ReturnElement(AxisAccessor);
	MatrixElementBounds* ReturnBound(AxisAccessor accessor);
	float ReturnBoundValue(AxisAccessor);
	float ReturnNextBoundValue(int, AxisAccessor*, int);
	int DetermineAxisMatrixBinaryRange(int, int, int, float);
	void PopulateAxisMatrix(int, int);
	void MapParentChildBounds(AxisAccessor*, AxisAccessor);
	//std::pair<AxisAccessor, AxisAccessor> CreateAxisAccessorForElement(int, int, int, int, int);
	int CreateMarker(int, int, int, int);
	float ReturnBoundValue(int, int, int, BoundType);

	//int BinarySearch(int, int, float, int);
	//int DetermineBinaryRange(int, float, int);
	int MoveAxisElement(int, int, int, int);
	int GetSpaceMarker(int, int, float);
	int GetOrCreateSpaceMarker(int, int, float);
	void SanitiseValue(int*, int, int);
	std::vector<AxisAccessor>* ReturnAxis(int);
	void MergeBound(int, BoundCollisionType, int, int);
	BoundCollisionType CheckCollisionType(int, int, int);
	int GetBoundPosition(int, int, int);


};

