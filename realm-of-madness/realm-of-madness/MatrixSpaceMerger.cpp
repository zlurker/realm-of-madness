#include "MatrixSpaceMerger.h"

AxisAccessorPair::AxisAccessorPair(int a, int mL) {
	axis = a;
	matrixLayer = mL;
}

MatrixSpaceMerger::MatrixSpaceMerger() {

}

void MatrixSpaceMerger::InsertMergeSection(std::pair<int, int> boundEndIntersect, std::pair<int, int> boundStartIntersect, int axis, int matrixLayer) {
	int rangeStart, rangeEnd;
	std::vector<int> pairs;

	// Handles retrival of start of bound 1
	if (boundsLookup.find(boundEndIntersect.second) == boundsLookup.end())
		rangeStart = boundEndIntersect.second - 1;
	else {
		int boundStartPairId = boundsLookup[boundEndIntersect.first];
		rangeStart = boundsPair[boundStartPairId].start;

		pairs.push_back(boundStartPairId);
	}

	// Handles retrival of end of bound 2
	if (boundsLookup.find(boundStartIntersect.second) == boundsLookup.end())
		rangeEnd = boundStartIntersect.second + 1;
	else {
		int boundEndPairId = boundsLookup[boundStartIntersect.first];
		rangeEnd = boundsPair[boundEndPairId].end;

		pairs.push_back(boundEndPairId);
	}

	int pairId;

	// Gets the pair to modify
	if (pairs.size() > 0) {
		pairId = pairs[0];

		if (pairs.size() > 1) {
			boundsPair[pairs[1]].axis = -1;
		}
	}
	else {
		pairId = boundsPair.size();
		boundsPair.push_back(AxisAccessorPair(axis, matrixLayer));
	}

	boundsPair[pairId].start = rangeStart;
	boundsPair[pairId].end = rangeEnd;
}