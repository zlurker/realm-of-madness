#include "MatrixElement.h"

MatrixElement::MatrixElement(Vector2 bD) {
	//xAxisPos = -1;
	//yAxisPos = -1;
	boundDetails = Vector2(bD.x / 2, bD.y / 2);
	points = new ElementPoint[4];
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

ElementPoint::ElementPoint() {
	axisPos = -1;
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
