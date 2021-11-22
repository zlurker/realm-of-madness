#pragma once
#pragma once
#include <map>
#include <vector>

class AxisAccessorPair {
public:
	AxisAccessorPair();
	AxisAccessorPair(int, int);

	int start;
	int end;
};

class MatrixSpaceMerger
{
public:
	MatrixSpaceMerger();

	void DeleteMergeSection(int, int, int, int);
	void InsertMergeSection(int, int, int, int);
	
	std::vector<AxisAccessorPair> boundsPair;
	std::map<std::tuple<int, int, int>, int> boundsLookup;

private:
	bool KeyExist(std::tuple<int, int, int>);
};

