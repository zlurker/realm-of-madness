#include "HelperFunctions.h"

namespace VectorHelpers {

	VectorBase::VectorBase() {

	}
	VectorBase::VectorBase(int id) {
		baseId = id;
		std::cout << "id generated: " << id << std::endl;
	}

	VectorBase* VectorBase::GetAddress() {
		return this;
	}

	bool VectorBase::operator==(const VectorBase& value){
		return value.baseId == baseId;
	}
}