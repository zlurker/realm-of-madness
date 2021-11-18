#pragma once
#include <map>
#include <vector>

class AxisAccessorPair {
public: 
	AxisAccessorPair();

	int axis;
	int matrixLayer;
	int start;
	int end;
};

class MatrixSpaceMerger
{
public:
	MatrixSpaceMerger();
	
	std::vector<AxisAccessorPair> boundsPair;
	std::map<int, int> boundsLookup;
};

