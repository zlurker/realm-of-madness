#pragma once
#include <vector>
#include <iostream>
#include <functional>

namespace VectorHelpers {

	class VectorBase {
	public:
		VectorBase();
		VectorBase(int);
		VectorBase* GetAddress();
		bool operator==(const int&);
		int baseId;
	};

	template<class T>
	inline void MoveVectorElement(std::vector<T>* vector, int from, int to) {

		if (from < to)
			std::rotate(vector->begin() + from, vector->begin() + from + 1, vector->begin() + to + 1);
		else
			std::rotate(vector->rend() - from - 1, vector->rend() - from, vector->rend() - to);
	}

	// To add a new binary search function. & captures everything by reference (?)
	template<class T1, class T2>
	inline int GetVectorPosition(std::vector<T1>* vector, T2 item) {
		auto it = std::find(vector->begin(), vector->end(), item);

		if (it != vector->end())
		{
			int index = it - vector->begin();
			std::cout << index << std::endl;
			return index;
		}

		return -1;
	}

	inline int DetermineBinaryRange(float vectorValue, float value) {
		//AxisAccessor* accessor = ReturnAxisAccessor(axis, matrixLayer, matrixLayerElementId);

		//if (accessor == nullptr)
			//return 0;

		//float boundValue = ReturnBoundValue(*accessor);

		//if (axis == 0)
			//std::cout << "pointpos: " << elePt->pointPosition << " compared val: " << value << " eleId: " << matrixLayerElementId << std::endl;

		if (vectorValue > value)
			return 0;
		//if (matrixElements[centerPoint].coordinates[axis] > value)
		return 1;
	}

	template<class T1>
	inline int BinarySearch(std::vector<T1>* vector, int rangeStart, int rangeEnd, float value, float (T1::* valueF)()) {
		//instance->*valueF();

		int axisCenterPoint = (rangeStart + rangeEnd) / 2;
		int processedCenterPoint = axisCenterPoint;

		//std::cout << "Before" << std::endl;

		int binaryRangeResult = DetermineBinaryRange((*vector)[processedCenterPoint].*valueF(), value);
		int l = 0, r = 0;

		//std::cout << "After" << std::endl;

		if (binaryRangeResult == 0) {
			l = rangeStart;
			r = processedCenterPoint - 1;
		}

		if (binaryRangeResult == 1) {
			l = processedCenterPoint + 1;
			r = rangeEnd;
		}

		if (r >= l)
			return BinarySearch(vector, l, r, value, valueF);

		//if (axis == 0)
			//std::cout << "center pt: " << axisCenterPoint << " rangeR: " << binaryRangeResult << " vlen: " << axisMatrix[axis][matrixLevel].size() << std::endl;
		return axisCenterPoint + binaryRangeResult;
	}	

	template<class T1, class T2>
	inline void RemoveVectorElement(std::vector<T1>* vector, T2 item) {
		int index = GetVectorPosition(vector, item);
		vector->erase(vector->begin() + index);
	}
}
