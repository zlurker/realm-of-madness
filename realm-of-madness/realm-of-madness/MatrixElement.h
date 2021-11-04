#pragma once
#include "Vector2.h"
#include <vector>
#include <memory>
#include <iostream>
#include "HelperFunctions.h"

enum PointType { XMIN, XMAX, YMIN, YMAX };
enum BoundType { START, END };

class ElementPoint {
public:
	ElementPoint();

	// Need to find alternative for this.
	//int axisPos;
	float pointPosition;
	
};


class BoundData: public VectorHelpers::VectorBase {
public:
	BoundData(float);
	void SetIdentifier(int);

	int boundPoint;
};

class MatrixElementBounds {
public:
	MatrixElementBounds(int,int,float, float);
	~MatrixElementBounds();

	BoundData operator[](int);
	void SetMatrixLayer(int);
	// To be replaced with a macro
	void SanitiseChildVector();
	
	int matrixLayer;
	int axis;
	BoundData* boundData;

	std::shared_ptr<std::pair<int,int>> parentLink;

	std::pair<int, int> parent;
	std::vector<std::shared_ptr<std::pair<int, int>>> child;
};



class MatrixElement {
public:
	MatrixElement(Vector2 c, Vector2 bD);
	//int* GetAxisPosition(int);
	void SetMatrixPosition(Vector2 c);
	void SetElementId(int id);
	

	template<class T>
	void BoundsChildOperation(int boundId, T* instance, void (T::*f)(int, int)) {
		MatrixElementBounds* bounds = &matrixBounds[boundId];

		for (int i = bounds->child.size() - 1; i > -1; i--) {

			// Only performs on valid linked child
			if (bounds->child[i].use_count() > 1) {
				std::pair<int, int> child = *bounds->child[i].get();
				//MatrixElementBounds* bound = bounds->child[i].get();
				//std::cout << "eid: " << elementId << std::endl;
				(instance->*f)(child.first, child.second);
			}

			// Removes any invalid linked child
			else
				bounds->child.erase(bounds->child.begin() + i);
		}
	};

	Vector2 coordinates;
	Vector2 boundDetails;
	ElementPoint* points;

	std::vector<MatrixElementBounds> matrixBounds;

//private:
	//int elementId;
};

