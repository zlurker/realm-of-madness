#include "SpaceMatrix.h"

SpaceMatrix::SpaceMatrix() {
	xAxis = new std::vector<int>();
	yAxis = new std::vector<int>();
}

int SpaceMatrix::CreateNewMatrixElement()
{
	int id = matrixElements.size();
	matrixElements.push_back(MatrixElement());
	return id;
}

void SpaceMatrix::SetMatrixElementLocation(int elementId, Vector2 coordinates) {
	MatrixElement matrixEle = matrixElements[elementId];
	float currCoords[2] = { matrixEle.coordinates.x,matrixEle.coordinates.y };
	float newCoords[2] = { coordinates.x,coordinates.y };
	int axisPos[2] = { matrixEle.xAxisPos,matrixEle.yAxisPos };
	int axisLths[2] = { xAxis->size(),yAxis->size() };
	std::vector<int>* axises[2] = { xAxis,yAxis };

	for (int i = 0; i < 2; i++) {
		int rangeStart, rangeEnd;

		if (currCoords[i] > newCoords[i]) {
			rangeStart = 0;
			rangeEnd = axisPos[i];
		}
		else {
			rangeStart = axisPos[i];
			rangeEnd = axisLths[i];
		}

		int insertPos = BinarySearch(rangeStart, rangeEnd, newCoords[i], axises[i]);
	}
}

int SpaceMatrix::BinarySearch(int rangeStart, int rangeEnd, float value, std::vector<int>* targetAxis) {
	int difference = (rangeEnd - rangeStart) / 2;

	if (difference == 0)
		return rangeStart + DetermineBinaryRange(rangeStart, value);

	int axisCenterPoint = rangeStart + difference;
	int binaryRangeResult = DetermineBinaryRange((*targetAxis)[axisCenterPoint], value);

	if (binaryRangeResult == -1)
		return BinarySearch(rangeStart, axisCenterPoint, value, targetAxis);

	return BinarySearch(axisCenterPoint, rangeEnd, value, targetAxis);
}

int SpaceMatrix::DetermineBinaryRange(int centerPoint, float value) {
	if (matrixElements[centerPoint]. > value)
		return -1;

	return 1;
}

