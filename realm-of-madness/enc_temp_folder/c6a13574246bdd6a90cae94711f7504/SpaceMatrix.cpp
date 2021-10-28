#include "SpaceMatrix.h"

int pointsIndex[2][2] = {
	{PointType::XMIN, PointType::XMAX},
	{PointType::YMIN, PointType::YMAX}
};

SpaceMatrix::SpaceMatrix() {
	axisMatrix = new std::vector<std::vector<AxisAccessor>>[2];
}

int SpaceMatrix::CreateNewMatrixElement(Vector2 coord, Vector2 bounds)
{
	int id = matrixElements.size();
	matrixElements.push_back(MatrixElement(coord, bounds));
	CreateAxisMatrixBounds(id);
	return id;
}

/*void SpaceMatrix::SetMatrixElementLocation(int elementId, Vector2 newCoords) {
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

			/*if (!newElement)
				insertPos = MoveAxisElement(i, *axisPos, insertPos);
			else
				insertPos = InsertAxisElement(i, insertPos, AxisAccessor(elementId, currPtIndex));

			std::cout << "Axis: " << i << " Insert Pos: " << insertPos << " Value: " << newCoords[i] << std::endl;
			*axisPos = insertPos;
		}
}*/

void SpaceMatrix::GenerateMatrix(int axis) {
	for (int i = 0; i < axisMatrix[axis].size(); i++) {

		int currInMatrix = 0;

		std::cout << i << ":";

		for (int j = 0; j < 100; j++) {
			if (currInMatrix < axisMatrix[axis][i].size() && ReturnElementPoint(axisMatrix[axis][i][currInMatrix])->pointPosition == j) {
				while (currInMatrix < axisMatrix[axis][i].size() && ReturnElementPoint(axisMatrix[axis][i][currInMatrix])->pointPosition == j)
					currInMatrix++;
				std::cout << 'x';
			}
			else
				std::cout << '*';
		}

		std::cout << std::endl;

		for (int j = 0; j < axisMatrix[axis][i].size(); j++)
			std::cout << ReturnElementPoint(axisMatrix[axis][i][j])->pointPosition << ' ';

		std::cout << std::endl;
	}
}

void SpaceMatrix::CreateAxisMatrixBounds(int matrixElementId) {
	MatrixElement matrixEle = matrixElements[matrixElementId];
	std::cout << "creating bounds for " << matrixElementId << std::endl;
	for (int i = 0; i < 2; i++)
		MapBounds(i, matrixEle.points[pointsIndex[i][0]].pointPosition, matrixEle.points[pointsIndex[i][1]].pointPosition, matrixElementId);
}

void SpaceMatrix::MapBounds(int axis, float boundStart, float boundEnd, int matrixElementId) {
	int currAxisLevel = -1;
	int currPosInBound = 0;
	AxisAccessor* prevAxisAccessEnd = nullptr;
	AxisAccessor* curraxisAccessEnd = nullptr;
	AxisAccessor* curraxisAccessFront = nullptr;


	if (axis == 0)
		std::cout << "map bound start" << std::endl;
	// Search to find a empty bound range
	do {
		currAxisLevel += 1;

		PopulateAxisMatrix(axis, currAxisLevel);
		int axisLength = axisMatrix[axis][currAxisLevel].size();
		currPosInBound = BinarySearchAxisMatrix(axis, currAxisLevel, 0, axisLength - 1, boundStart);
		prevAxisAccessEnd = curraxisAccessEnd;
		curraxisAccessEnd = ReturnAxisAccessor(axis, currAxisLevel, currPosInBound);
		curraxisAccessFront = ReturnAxisAccessor(axis, currAxisLevel, currPosInBound - 1);

		if (axis == 0) {
			std::cout << "currPosInBound" << currPosInBound << std::endl;

			if (curraxisAccessFront != nullptr)
				std::cout << "front ptype: " << curraxisAccessFront->pType << "startingType: " << pointsIndex[axis][0] << std::endl;

			if (curraxisAccessEnd != nullptr)
				std::cout << "cb ptype: " << curraxisAccessEnd->pType << "startingType: " << pointsIndex[axis][0] << std::endl;

			if (prevAxisAccessEnd != nullptr)
				std::cout << "pb ptype: " << prevAxisAccessEnd->pType << "startingType: " << pointsIndex[axis][0] << std::endl;
		}
	} while (currPosInBound > 0 && curraxisAccessFront != nullptr && curraxisAccessFront->pType == pointsIndex[axis][0]);

	float boundEndPrev, boundEndCurr, usedBound;
	// Checks to see the ending of the current collided end in previous matrix layer.
	boundEndPrev = ReturnNextBoundValue(axis, prevAxisAccessEnd, pointsIndex[axis][1]);
	// Checks to see the next collided end in current matrix layer.
	boundEndCurr = ReturnNextBoundValue(axis, curraxisAccessEnd, pointsIndex[axis][0]);

	usedBound = boundEndPrev < boundEndCurr ? boundEndPrev : boundEndCurr;
	bool cutBound = usedBound < boundEnd;

	usedBound = cutBound ? usedBound : boundEnd;

	if (axis == 0)
		std::cout << "prev bound: " << boundEndPrev << " curr bound: " << boundEndCurr << "boundEnd: " << boundEnd << std::endl;

	matrixElements[matrixElementId].points[pointsIndex[axis][0]].pointPosition = boundStart;
	matrixElements[matrixElementId].points[pointsIndex[axis][1]].pointPosition = usedBound;

	InsertAxisElement(axis, currAxisLevel, currPosInBound, AxisAccessor(matrixElementId, pointsIndex[axis][0]));
	InsertAxisElement(axis, currAxisLevel, currPosInBound + 1, AxisAccessor(matrixElementId, pointsIndex[axis][1]));

	if (axis == 0)
		std::cout << "currentAxisLevel: " << currAxisLevel << " boundend: " << boundEnd << "bounds: " << matrixElements[matrixElementId].points[pointsIndex[axis][0]].pointPosition << " " << matrixElements[matrixElementId].points[pointsIndex[axis][1]].pointPosition << std::endl;

	if (cutBound)
		MapBounds(axis, usedBound, boundEnd, matrixElementId);
}

int SpaceMatrix::BinarySearchAxisMatrix(int axis, int matrixLevel, int rangeStart, int rangeEnd, float value) {
	if (axisMatrix[axis][matrixLevel].size() == 0)
		return 0;

	int axisCenterPoint = (rangeStart + rangeEnd) / 2;
	int processedCenterPoint = axisCenterPoint;

	//std::cout << "Before" << std::endl;

	int binaryRangeResult = DetermineAxisMatrixBinaryRange(axis, matrixLevel, axisCenterPoint, value);
	int l = 0, r = 0;

	//std::cout << "After" << std::endl;

	if (binaryRangeResult == 0) {
		l = rangeStart;
		r = processedCenterPoint - 1;
	}

	if (binaryRangeResult == 1) {
		l = processedCenterPoint + 1;
		r = rangeEnd;
	}

	if (r >= l)
		return BinarySearchAxisMatrix(axis, matrixLevel, l, r, value);

	if (axis == 0)
		std::cout << "center pt: " << axisCenterPoint << " rangeR: " << binaryRangeResult << " vlen: " << axisMatrix[axis][matrixLevel].size() << std::endl;
	return axisCenterPoint + binaryRangeResult;
}

int SpaceMatrix::DetermineAxisMatrixBinaryRange(int axis, int matrixLayer, int matrixLayerElementId, float value) {
	AxisAccessor* accessor = ReturnAxisAccessor(axis, matrixLayer, matrixLayerElementId);

	if (accessor == nullptr)
		return 0;

	ElementPoint* elePt = ReturnElementPoint(*accessor);

	//if (axis == 0)
		//std::cout << "pointpos: " << elePt->pointPosition << " compared val: " << value << " eleId: " << matrixLayerElementId << std::endl;

	if (elePt->pointPosition > value)
		return 0;
	//if (matrixElements[centerPoint].coordinates[axis] > value)
	return 1;
}

void SpaceMatrix::PopulateAxisMatrix(int axis, int matrixLength) {
	bool runPrint = false;
	while (axisMatrix[axis].size() <= matrixLength) {
		axisMatrix[axis].push_back(std::vector<AxisAccessor>());
		runPrint = true;
	}

	if (runPrint)
		for (int i = 0; i < axisMatrix[axis].size(); i++)
			std::cout << "matrix v: " << i << " len: " << axisMatrix[axis][i].size() << std::endl;
}

AxisAccessor* SpaceMatrix::ReturnAxisAccessor(int axis, int matrixLayer, int matrixLayerElementId) {
	if (axisMatrix[axis][matrixLayer].size() > matrixLayerElementId)
		return &axisMatrix[axis][matrixLayer][matrixLayerElementId];

	return nullptr;
}

MatrixElement* SpaceMatrix::ReturnElement(AxisAccessor accessor) {
	return &matrixElements[accessor.matrixEId];
}

ElementPoint* SpaceMatrix::ReturnElementPoint(AxisAccessor accessor) {
	return &matrixElements[accessor.matrixEId].points[accessor.pType];
}

float SpaceMatrix::ReturnNextBoundValue(int axis, AxisAccessor* accessor, int acceptedBound) {
	if (accessor == nullptr || accessor->pType != acceptedBound)
		return std::numeric_limits<float>::max();

	MatrixElement* prevElement = ReturnElement(*accessor);
	return prevElement->points[pointsIndex[axis][1]].pointPosition;
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

int SpaceMatrix::MoveAxisElement(int axis, int matrixLayer, int current, int next) {
	std::vector<AxisAccessor>* selectedAxis = &axisMatrix[axis][matrixLayer];

	if (next >= selectedAxis->size())
		next = selectedAxis->size() - 1;

	if (next < 0)
		next = 0;

	std::cout << "swap pos before " << current << " after " << next << std::endl;

	VectorHelpers::MoveVectorElement(selectedAxis, current, next);
	return next;
}

int SpaceMatrix::InsertAxisElement(int axis, int matrixLayer, int pos, AxisAccessor value) {

	std::vector<AxisAccessor>* selectedAxis = &axisMatrix[axis][matrixLayer];
	std::cout << "selected matrix: " << matrixLayer << " matrixLen:" << selectedAxis->size() << std::endl;
	//std::cout << "insert pos: " << pos << " axis size: " << selectedAxis->size() << std::endl;

	if (pos >= selectedAxis->size()) {
		//std::cout << "Pushing back element" << std::endl;
		selectedAxis->push_back(value);
		return selectedAxis->size() - 1;
	}

	//std::cout  << " Inserting at: " << pos << " value: " <<  std::endl;
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