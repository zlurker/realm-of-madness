#include "SpaceMatrix.h"

SpaceMatrix::SpaceMatrix() {
	xAxis = new std::vector<AxisAccessor>();
	yAxis = new std::vector<AxisAccessor>();

	axisMatrix = new std::vector<std::vector<AxisAccessor>>[2];
}

int SpaceMatrix::CreateNewMatrixElement(Vector2 coord)
{
	int id = matrixElements.size();
	matrixElements.push_back(MatrixElement(Vector2(1, 1)));
	SetMatrixElementLocation(id, coord);
	return id;
}

void SpaceMatrix::SetMatrixElementLocation(int elementId, Vector2 newCoords) {
	MatrixElement* matrixEle = &(matrixElements[elementId]);

	int pointsIndex[2][2] = {
		{PointType::XMIN, PointType::XMAX},
		{PointType::YMIN, PointType::YMAX}
	};

	float prevPointCoordinates[4] = {
		matrixEle->points[PointType::XMIN].pointPosition,
		matrixEle->points[PointType::XMAX].pointPosition,
		matrixEle->points[PointType::YMIN].pointPosition,
		matrixEle->points[PointType::YMAX].pointPosition
	};

	matrixEle->SetMatrixPosition(newCoords);

	int axisLths[2] = { xAxis->size(),yAxis->size() };

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) {
			int rangeStart, rangeEnd, axisLength;
			int currPtIndex = pointsIndex[i][j];

			rangeStart = 0;
			axisLength = axisLths[i] == 0 ? 0 : axisLths[i] - 1;
			rangeEnd = axisLength;

			int* axisPos = &(matrixEle->points[currPtIndex].axisPos);// ->GetAxisPosition(i);
			bool newElement = *axisPos == -1;

			float newPtPos = matrixEle->points[currPtIndex].pointPosition;

			if (!newElement)
				if (prevPointCoordinates[currPtIndex] > newPtPos)
					rangeEnd = *axisPos;
				else
					rangeStart = *axisPos;

			int insertPos = BinarySearch(rangeStart, rangeEnd, newPtPos, i);

			std::cout << "After Search";

			// Can only standardise this part for insertpos. For pos > size, move and insert handles differently and as such, we will handle it in its function.
			if (0 > insertPos)
				insertPos = 0;

			if (!newElement)
				insertPos = MoveAxisElement(i, *axisPos, insertPos);
			else
				insertPos = InsertAxisElement(i, insertPos, AxisAccessor(elementId, currPtIndex));

			std::cout << "Axis: " << i << " Insert Pos: " << insertPos << " Value: " << newCoords[i] << std::endl;
			*axisPos = insertPos;
		}
}

void SpaceMatrix::CreateAxisMatrixBounds(int matrixElementId) {
	MatrixElement matrixEle = matrixElements[matrixElementId];

	int pointsIndex[2][2] = {
		{PointType::XMIN, PointType::XMAX},
		{PointType::YMIN, PointType::YMAX}
	};

	for (int i = 0; i < 2; i++)
		MapBounds(i, matrixEle.coordinates[pointsIndex[i][0]], matrixEle.coordinates[pointsIndex[i][1]]);
}

void SpaceMatrix::MapBounds(int axis, float boundStart, float boundEnd) {

}

int SpaceMatrix::BinarySearchAxisMatrix(int axis, int matrixLevel, float value) {

}

int SpaceMatrix::DetermineAxisMatrixBinaryRange(int axis, int matrixLayer, int matrixLayerElementId, float value) {
	ElementPoint elePt = ReturnAxisPointFromMatrix(axis, matrixLayer, matrixLayerElementId);

	if (elePt.pointPosition > value)
		return -1;
	//if (matrixElements[centerPoint].coordinates[axis] > value)

	return 1;
}

ElementPoint SpaceMatrix::ReturnAxisPointFromMatrix(int axis,int matrixLayer, int matrixLayerElementId) {
	AxisAccessor accessor = axisMatrix[axis][matrixLayer][matrixLayerElementId];
	return matrixElements[accessor.matrixEId].points[accessor.pType];
}




int* SpaceMatrix::GetElementsInRange(Vector2 startRange, Vector2 endRange) {
	int min[2];
	int max[2];

	for (int i = 0; i < 2; i++)
		if (startRange[i] > endRange[i]) {
			min[i] = endRange[i];
			max[i] = startRange[i];
		}
		else
		{
			min[i] = startRange[i];
			max[i] = endRange[i];
		}

	return min;
}

int SpaceMatrix::BinarySearch(int rangeStart, int rangeEnd, float value, int axis) {
	//int difference = (rangeEnd - rangeStart) / 2;

	if (ReturnAxis(axis)->size() == 0)
		return 0;

	std::cout << "RS: " << rangeStart << " RE: " << rangeEnd << std::endl;

	int axisCenterPoint = (rangeStart + rangeEnd) / 2;
	int processedCenterPoint = axisCenterPoint;

	std::cout << "Before" << std::endl;

	int binaryRangeResult = DetermineBinaryRange(axisCenterPoint, value, axis);
	int l = 0, r = 0;

	std::cout << "After" << std::endl;

	if (binaryRangeResult == -1) {
		l = rangeStart;
		r = processedCenterPoint - 1;
	}

	if (binaryRangeResult == 1) {
		l = processedCenterPoint + 1;
		r = rangeEnd;
	}

	if (r >= l)
		return BinarySearch(l, r, value, axis);

	std::cout << axisCenterPoint << std::endl;
	return axisCenterPoint + DetermineBinaryRange(axisCenterPoint, value, axis);
}

int SpaceMatrix::DetermineBinaryRange(int centerPoint, float value, int axis) {

	ElementPoint elementPoint = ReturnAxisPoint(axis, centerPoint);

	if (elementPoint.pointPosition > value)
		return -1;
	//if (matrixElements[centerPoint].coordinates[axis] > value)

	return 1;
}

ElementPoint SpaceMatrix::ReturnAxisPoint(int axis, int axisId) {
	//std::cout << elementId << (*xAxis).size() << std::endl;

	AxisAccessor accessor;

	if (axis == 0)
		accessor = (*xAxis)[axisId];
	else
		accessor = (*yAxis)[axisId];

	return matrixElements[accessor.matrixEId].points[accessor.pType];
}

int SpaceMatrix::MoveAxisElement(int axis, int current, int next) {
	std::vector<AxisAccessor>* selectedAxis = ReturnAxis(axis);

	if (next >= selectedAxis->size())
		next = selectedAxis->size() - 1;

	if (next < 0)
		next = 0;

	std::cout << "swap pos before " << current << " after " << next << std::endl;

	VectorHelpers::MoveVectorElement(selectedAxis, current, next);
	return next;
}

int SpaceMatrix::InsertAxisElement(int axis, int pos, AxisAccessor value) {

	std::vector<AxisAccessor>* selectedAxis = ReturnAxis(axis);
	std::cout << "insert pos: " << pos << " axis size: " << selectedAxis->size() << std::endl;

	if (pos >= selectedAxis->size()) {
		//std::cout << "Pushing back element" << std::endl;
		selectedAxis->push_back(value);
		return selectedAxis->size() - 1;
	}

	std::cout << "Axis: " << axis << " Inserting at: " << pos << std::endl;
	selectedAxis->insert(selectedAxis->begin() + pos, value);
	return pos;
}

std::vector<AxisAccessor>* SpaceMatrix::ReturnAxis(int axis) {
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

void SpaceMatrix::SanitiseValue(int* value, int min, int max) {
	if (*value < min)
		*value = min;

	if (*value > max)
		*value = max;
}

AxisAccessor::AxisAccessor(int mId, int pT) {
	matrixEId = mId;
	pType = pT;
}

AxisAccessor::AxisAccessor() {

}