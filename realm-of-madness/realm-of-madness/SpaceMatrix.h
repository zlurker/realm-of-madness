#pragma once
#include <vector>
#include "MatrixElement.h"

class SpaceMatrix
{
public:
	std::vector<int>* xAxis;
	std::vector<int>* yAxis;

	std::vector<MatrixElement> matrixElements;

	SpaceMatrix();
	int CreateNewMatrixElement();	
	void SetMatrixElementLocation(int elementId, Vector2 coordinates);	
	int* GetElementsInRange(Vector2 startRange, Vector2 endRange);

private:
	int BinarySearch(int rangeStart, int rangeEnd, float value, std::vector<int>* targetAxis);
	int DetermineBinaryRange(int centerPoint, float value);
};

