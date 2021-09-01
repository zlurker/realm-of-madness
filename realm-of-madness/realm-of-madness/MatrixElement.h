#pragma once
#include "Vector2.h"

class MatrixElement {
public:
	MatrixElement();
	int* GetAxisPosition(int);

	Vector2 coordinates;
	int xAxisPos;
	int yAxisPos;
	
};
