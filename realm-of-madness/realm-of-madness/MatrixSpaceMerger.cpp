#include "MatrixSpaceMerger.h"

AxisAccessorPair::AxisAccessorPair() {
	//axis = a;
	//matrixLayer = mL;
}

AxisAccessorPair::AxisAccessorPair(int s, int e) {
	//axis = a;
	//matrixLayer = mL;
}

MatrixSpaceMerger::MatrixSpaceMerger() {

}

void MatrixSpaceMerger::DeleteMergeSection(int boundStart, int boundEnd, int axis, int matrixLayer) {
	std::tuple<int, int, int> startKey = std::make_tuple(axis, matrixLayer, boundStart);
	std::tuple<int, int, int> endKey = std::make_tuple(axis, matrixLayer, boundEnd);

	if (KeyExist(startKey))
		return;

	int splitFirst, splitSecond, diffFirstH, diffSecondH;

	AxisAccessorPair* pair = &boundsPair[boundsLookup[startKey]];

	splitFirst = boundStart - 1;
	splitSecond = boundEnd + 1;

	diffFirstH = splitFirst - pair->start;
	diffSecondH = pair->end - splitSecond;

	int rangeChangeStart, rangeChangeEnd;

	rangeChangeStart = pair->start;
	rangeChangeEnd = pair->end;

	// If second section is bigger, will just move pair start up
	// After that we will mark the new range. The one with the smaller range will 
	if (diffFirstH < diffSecondH) {
		pair->start = splitSecond;
		rangeChangeEnd = splitFirst;
	}
	else {
		pair->end = splitFirst;
		rangeChangeStart = splitSecond;
	}

	if (rangeChangeStart >= pair->start && rangeChangeEnd <= pair->end) {
		int newPairId = boundsPair.size();

		boundsPair.push_back(AxisAccessorPair(rangeChangeStart, rangeChangeEnd));

		for (int i = rangeChangeStart; i <= rangeChangeEnd; i++) {
			std::tuple<int, int, int> key = std::make_tuple(axis, matrixLayer, i);

			if (KeyExist(key))
				boundsLookup[key] = newPairId;
		}
	}

}

void MatrixSpaceMerger::InsertMergeSection(int boundEndIntersect, int boundStartIntersect, int axis, int matrixLayer) {
	int rangeStart, rangeEnd;
	std::vector<int> pairs;
	std::tuple<int, int, int> bEIKey = std::make_tuple(axis, matrixLayer, boundEndIntersect);

	// Handles retrival of start of bound 1
	if (KeyExist(bEIKey))
		rangeStart = boundEndIntersect - 1;
	else {
		int boundStartPairId = boundsLookup[bEIKey];
		rangeStart = boundsPair[boundStartPairId].start;

		pairs.push_back(boundStartPairId);
	}

	std::tuple<int, int, int> bSIKey = std::make_tuple(axis, matrixLayer, boundStartIntersect);

	// Handles retrival of end of bound 2
	if (KeyExist(bSIKey))
		rangeEnd = boundStartIntersect + 1;
	else {
		int boundEndPairId = boundsLookup[bSIKey];
		rangeEnd = boundsPair[boundEndPairId].end;

		pairs.push_back(boundEndPairId);
	}

	int pairId;

	// Gets the pair to modify
	if (pairs.size() > 0) {
		pairId = pairs[0];

		if (pairs.size() > 1) {
			boundsPair[pairs[1]].start = -1;
			boundsPair[pairs[1]].end = -1;
		}
	}
	else {
		pairId = boundsPair.size();
		boundsPair.push_back(AxisAccessorPair(axis, matrixLayer));
	}

	boundsPair[pairId].start = rangeStart;
	boundsPair[pairId].end = rangeEnd;

	// Replaces boundslookup with the correct pair id
	std::tuple<int, int, int> boundsRange[2] = { std::make_tuple(axis, matrixLayer, rangeStart), std::make_tuple(axis, matrixLayer, rangeEnd) };

	for (int i = 0; i < 2; i++)
		if (boundsLookup.find(boundsRange[i]) == boundsLookup.end())
			boundsLookup.insert(std::pair<std::tuple<int, int, int>, int>(boundsRange[i], pairId));
		else
			boundsLookup[boundsRange[i]] = pairId;
}

bool MatrixSpaceMerger::KeyExist(std::tuple<int, int, int> key) {
	return boundsLookup.find(key) == boundsLookup.end();
}