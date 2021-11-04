#pragma once
#include <vector>
#include <iostream>

namespace VectorHelpers {

	class VectorBase {
	public:
		VectorBase();
		VectorBase(int);
		VectorBase* GetAddress();
		bool operator==(const VectorBase&);
		int baseId;
	};

	template<class T>
	inline void MoveVectorElement(std::vector<T>* vector, int from, int to) {

		if (from < to)
			std::rotate(vector->begin() + from, vector->begin() + from + 1, vector->begin() + to + 1);
		else
			std::rotate(vector->rend() - from - 1, vector->rend() - from, vector->rend() - to);
	}

	// To add a new binary search function
	inline int GetVectorPosition(std::vector<VectorBase>* vector, VectorBase* item) {
		auto it = std::find(vector->begin(), vector->end(), *item);

		if (it != vector->end())
		{
			int index = it - vector->begin();
			std::cout << index << std::endl;
			return index;
		}
		
		return -1;
	}

	inline void RemoveVectorElement(std::vector<VectorBase>* vector, VectorBase* item) {		
		int index = GetVectorPosition(vector,item);
		vector->erase(vector->begin() + index);
	}
}
