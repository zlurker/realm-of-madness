#include "SpaceMatrix.h"

SpaceMatrix::SpaceMatrix() {
	xAxis = new std::vector<int>();
	yAxis = new std::vector<int>();
}

int SpaceMatrix::CreateNewMatrixElement(Vector2 coord)
{
	int id = matrixElements.size();
	matrixElements.push_back(MatrixElement());
	SetMatrixElementLocation(id, coord);
	return id;
}

void SpaceMatrix::SetMatrixElementLocation(int elementId, Vector2 newCoords) {
	MatrixElement* matrixEle = &(matrixElements[elementId]);
	Vector2 currCoords = matrixEle->coordinates;
	int axisLths[2] = { xAxis->size(),yAxis->size() };

	for (int i = 0; i < 2; i++) {
		int rangeStart, rangeEnd;
		int* axisPos = matrixEle->GetAxisPosition(i);

		if (currCoords[i] > newCoords[i]) {
			rangeStart = 0;
			rangeEnd = *axisPos;
		}
		else {
			rangeStart = *axisPos;
			rangeEnd = axisLths[i];
		}

		int insertPos = BinarySearch(rangeStart, rangeEnd, newCoords[i], i);
		// need to set the axis positions here
		

		if (axisPos[i] > -1) {

		}

		*axisPos = insertPos;
	}
}

int* SpaceMatrix::GetElementsInRange(Vector2 startRange, Vector2 endRange) {
	int min[2];
	int max[2];

	// Wait for array accesor
	if (startRange.x > endRange.x) {

	}

}

int SpaceMatrix::BinarySearch(int rangeStart, int rangeEnd, float value, int axis) {
	int difference = (rangeEnd - rangeStart) / 2;

	if (difference == 0)
		return rangeStart + DetermineBinaryRange(rangeStart, value, axis);

	int axisCenterPoint = rangeStart + difference;
	int binaryRangeResult = DetermineBinaryRange(ReturnAxisElement(axis, axisCenterPoint), value, axis);

	if (binaryRangeResult == -1)
		return BinarySearch(rangeStart, axisCenterPoint, value, axis);

	return BinarySearch(axisCenterPoint, rangeEnd, value, axis);
}

int SpaceMatrix::DetermineBinaryRange(int centerPoint, float value, int axis) {
	// Wait for array accesor
	if (matrixElements[centerPoint].coordinates[axis] > value)
		return -1;

	return 1;
}

int SpaceMatrix::ReturnAxisElement(int axis, int elementId) {
	if (axis == 0)
		return (*xAxis)[elementId];

	return (*yAxis)[elementId];
}

void SpaceMatrix::MoveAxisElement(int axis, int current, int next) {

}

void SpaceMatrix::InsertAxisElement(int axis, int pos, int value) {

}

