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
	int CreateNewMatrixElement(Vector2);
	void SetMatrixElementLocation(int, Vector2);
	int* GetElementsInRange(Vector2, Vector2);

private:
	int BinarySearch(int, int, float, int);
	int DetermineBinaryRange(int, float, int);
	int ReturnAxisElement(int, int);
	void MoveAxisElement(int, int, int);
	void InsertAxisElement(int, int, int);
	std::vector<int>* ReturnAxis(int);
};
