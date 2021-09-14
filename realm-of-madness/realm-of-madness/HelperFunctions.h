#pragma once
#include <vector>

namespace VectorHelpers {

	template<class T>
	void MoveVectorElement(std::vector<T>* vector, int from, int to) {

		if (from < to)
			std::rotate(vector->begin() + from, vector->begin() + from + 1, vector->begin() + to + 1);
		else
			std::rotate(vector->rend() - from - 1, vector->rend() - from, vector->rend() - to);
	}
}
