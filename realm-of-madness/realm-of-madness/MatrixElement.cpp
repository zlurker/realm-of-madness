#include "MatrixElement.h"

ElementPoint::ElementPoint() {
	//axisPos = -1;
}

BoundData::BoundData(float bP, int bI) {
	boundPoint = bP;
	boundIdentifier = bI;
}

MatrixElementBounds::MatrixElementBounds(int mL, float bPS, float bPE, int bIS, int bIE) {
	boundData = new BoundData[2]{
		BoundData(bPS, bIS),
		BoundData(bPE,bIE)
	};

	matrixLayer = mL;
	parent = std::make_pair(-1, -1);
}

MatrixElementBounds::~MatrixElementBounds() {
	parentLink.reset();
}

BoundData MatrixElementBounds::operator[](int index) {
	return boundData[index];
}



MatrixElement::MatrixElement(Vector2 c, Vector2 bD) {
	//xAxisPos = -1;
	//yAxisPos = -1;
	boundDetails = Vector2(bD.x / 2, bD.y / 2);
	points = new ElementPoint[4];
	SetMatrixPosition(c);
}

void MatrixElement::SetMatrixPosition(Vector2 c) {
	coordinates = c;

	points[PointType::XMIN].pointPosition = coordinates.x - boundDetails.x;
	points[PointType::XMAX].pointPosition = coordinates.x + boundDetails.x;
	points[PointType::YMIN].pointPosition = coordinates.y - boundDetails.y;
	points[PointType::YMAX].pointPosition = coordinates.y + boundDetails.y;
}

void MatrixElement::SetElementId(int id) {
	elementId = id;
}

template<class T>
void MatrixElement::BoundsChildOperation(int boundId, void (T::* f)(int, int)) {
	MatrixElementBounds* bounds = &matrixBounds[boundId];

	for (int i = bounds->child.size() - 1; i > -1; i--) {

		// Only performs on valid linked child
		if (bounds->child[i].use_count() > 1) {
			MatrixElementBounds* bound = bounds->child[i].get();
			(*f)(elementId,i);
		}

		// Removes any invalid linked child
		else
			bounds->child.erase(bounds->child.begin() + i);
	}
}


/*int* MatrixElement::GetAxisPosition(int axis) {
	switch (axis) {
	case 0: {
		return &xAxisPos;
	}break;
	case 1: {
		return &yAxisPos;
	}break;
	}

	return nullptr;
}*/
