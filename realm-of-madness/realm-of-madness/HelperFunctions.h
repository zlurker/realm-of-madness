#pragma once
#include <vector>
#include <iostream>

namespace VectorHelpers {

	class VectorBase {
	public:
		VectorBase(int);
		VectorBase* GetAddress();
		bool operator==(const VectorBase&);
		int baseId;
	};

	template<class T>
	void MoveVectorElement(std::vector<T>* vector, int from, int to) {

		if (from < to)
			std::rotate(vector->begin() + from, vector->begin() + from + 1, vector->begin() + to + 1);
		else
			std::rotate(vector->rend() - from - 1, vector->rend() - from, vector->rend() - to);
	}

	template<class T>
	int GetVectorPosition(std::vector<T>* vector, T* item) {
		auto it = std::find(vector->begin(), vector->end(), *item);

		if (it != vector->end())
		{
			// calculating the index
			// of K
			int index = it - vector->begin();
			std::cout << index << std::endl;
			return index;
		}
		
		return -1;
	}

	template<class T>
	void RemoveVectorElement(std::vector<T>* vector, T* item) {
		
		int index = GetVectorPosition(vector,item);
		vector->erase(vector->begin() + index);
	}
}
