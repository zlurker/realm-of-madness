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

	std::cout << "Before loop" << std::endl;

	for (int i = 0; i < 2; i++) {
		int rangeStart, rangeEnd;
		rangeStart = 0;
		rangeEnd = axisLths[i] == 0 ? 0 : axisLths[i] - 1;

		int* axisPos = matrixEle->GetAxisPosition(i);
		bool newElement = *axisPos == -1;

		if (!newElement) {
			std::cout << "existing element" << std::endl;
			if (currCoords[i] > newCoords[i])
				rangeEnd = *axisPos;
			else
				rangeStart = *axisPos;
		}
		else
			std::cout << "new element" << std::endl;

		std::cout << "Range start: " << rangeStart << " Range End: " << rangeEnd << std::endl;
		int insertPos = BinarySearch(rangeStart, rangeEnd, newCoords[i], i);
		//std::cout << "Exited search" << std::endl;

		if (!newElement)
			insertPos = MoveAxisElement(i, *axisPos, insertPos);
		else
			insertPos = InsertAxisElement(i, insertPos, elementId);

		std::cout << "Axis: " << i << " Insert Pos: " << insertPos << " Value: " << newCoords[i] << std::endl;

		*axisPos = insertPos;
	}

	matrixEle->coordinates = newCoords;
}

int* SpaceMatrix::GetElementsInRange(Vector2 startRange, Vector2 endRange) {
	int min[2];
	int max[2];

	// Wait for array accesor
	if (startRange.x > endRange.x) {

	}

	return min;
}

int SpaceMatrix::BinarySearch(int rangeStart, int rangeEnd, float value, int axis) {
	int difference = (rangeEnd - rangeStart) / 2;
	//std::cout << "RS: " << rangeStart << " RE: " << rangeEnd << std::endl;

	if (rangeEnd - rangeStart <= 1)
		return rangeStart + DetermineBinaryRange(rangeStart, value, axis);

	int axisCenterPoint = rangeStart + difference;
	int binaryRangeResult = DetermineBinaryRange(ReturnAxisElement(axis, axisCenterPoint), value, axis);

	if (binaryRangeResult == -1)
		return BinarySearch(rangeStart, axisCenterPoint, value, axis);

	return BinarySearch(axisCenterPoint, rangeEnd, value, axis);
}

int SpaceMatrix::DetermineBinaryRange(int centerPoint, float value, int axis) {
	if (matrixElements[centerPoint].coordinates[axis] > value)
		return -1;

	return 1;
}

int SpaceMatrix::ReturnAxisElement(int axis, int elementId) {
	//std::cout << elementId << (*xAxis).size() << std::endl;

	if (axis == 0)
		return (*xAxis)[elementId];

	return (*yAxis)[elementId];
}

int SpaceMatrix::MoveAxisElement(int axis, int current, int next) {
	std::vector<int>* selectedAxis = ReturnAxis(axis);

	if (0 > next)
		next = 0;

	if (next >= selectedAxis->size())
		next = selectedAxis->size() - 1;

	VectorHelpers::MoveVectorElement(selectedAxis, current, next);
	return next;
	//std::rotate()
}

int SpaceMatrix::InsertAxisElement(int axis, int pos, int value) {

	std::vector<int>* selectedAxis = ReturnAxis(axis);
	std::cout << "insert pos: " << pos << " axis size: " << selectedAxis->size() << std::endl;

	// Compares if it is negative first as we are comparing against unsigned.
	if (0 > pos) {
		std::cout << "Appending element to front" << std::endl;
		selectedAxis->insert(selectedAxis->begin(), value);
		return 0;
	}

	if (pos >= selectedAxis->size()) {
		std::cout << "Pushing back element" << std::endl;
		selectedAxis->push_back(value);
		return selectedAxis->size() - 1;
	}

	std::cout << "Axis: " << axis << " Inserting at: " << pos << std::endl;
	selectedAxis->insert(selectedAxis->begin() + pos, value);
	return pos;
}

std::vector<int>* SpaceMatrix::ReturnAxis(int axis) {
	switch (axis) {
	case 0: {
		return xAxis;
	}break;
	case 1: {
		return yAxis;
	}break;
	}

	return nullptr;
}