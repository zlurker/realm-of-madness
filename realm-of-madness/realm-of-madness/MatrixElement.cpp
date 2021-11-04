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
	parent = nullptr;
}

MatrixElementBounds::~MatrixElementBounds() {
	parentLink.reset();
}

BoundData MatrixElementBounds::operator[](int index) {
	return boundData[index];
}

template<class T>
void MatrixElementBounds::ChildOperation(void (T::*f)(MatrixElementBounds*)) {
	for (int i = child.size() - 1; i > -1; i--) {

		// Only performs on valid linked child
		if (child[i].use_count() > 1) {
			(*f)(*child[i].get());
		}

		// Removes any invalid linked child
		else
			child.erase(child.begin() + i);
	}
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
	for (int i = 0; i < 4; i++)
		points[i].elementId = id;
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
