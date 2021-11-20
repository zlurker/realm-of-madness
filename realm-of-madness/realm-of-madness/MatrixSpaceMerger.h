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

	void InsertMergeSection(std::pair<int, int>, std::pair<int, int>,int,int);
	
	std::vector<AxisAccessorPair> boundsPair;
	std::map<int, int> boundsLookup;
};

