#include "MatrixElement.h"

ElementPoint::ElementPoint() {
	//axisPos = -1;
}

BoundData::BoundData(float bP) {
	boundPoint = bP;
}

void BoundData::SetIdentifier(int bI) {
	std::cout << "changed from " << baseId << " to " << bI << std::endl;
	baseId = bI;
}

MatrixElementBounds::MatrixElementBounds(int a, int mL, float bPS, float bPE) {
	boundData = new BoundData[2]{
		BoundData(bPS),
		BoundData(bPE)
	};

	axis = a;
	matrixLayer = mL;
	parent = std::make_pair(-1, -1);
}

MatrixElementBounds::~MatrixElementBounds() {
	parentLink.reset();
}

void MatrixElementBounds::SetMatrixLayer(int layer) {
	std::cout << boundData[0].baseId << " " << boundData[1].baseId << " set to " << layer << std::endl;
	matrixLayer = layer;
}

BoundData MatrixElementBounds::operator[](int index) {
	return boundData[index];
}

void MatrixElementBounds::SanitiseChildVector() {
	for (int i = child.size() - 1; i > -1; i--)

		// Removes invalid linked child
		if (!(child[i].use_count() > 1))
			child.erase(child.begin() + i);
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

	points[(int)PointType::XMIN].pointPosition = coordinates.x - boundDetails.x;
	points[(int)PointType::XMAX].pointPosition = coordinates.x + boundDetails.x;
	points[(int)PointType::YMIN].pointPosition = coordinates.y - boundDetails.y;
	points[(int)PointType::YMAX].pointPosition = coordinates.y + boundDetails.y;
}

void MatrixElement::SetElementId(int id) {
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