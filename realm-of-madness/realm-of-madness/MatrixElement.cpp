#include "MatrixElement.h"

MatrixElement::MatrixElement() {
	xAxisPos = -1;
	yAxisPos = -1;
	coordinates = Vector2();
}

int* MatrixElement::GetAxisPosition(int axis) {
	switch (axis) {
	case 0: {
		return &xAxisPos;
	}break;
	case 1: {
		return &yAxisPos;
	}break;
	}

	return nullptr;
}
