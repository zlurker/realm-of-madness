#include "HelperFunctions.h"

namespace VectorHelpers {
	VectorBase::VectorBase(int id) {
		baseId = id;
	}

	VectorBase* VectorBase::GetAddress() {
		return this;
	}

	bool VectorBase::operator==(const VectorBase& value){
		return value.baseId == baseId;
	}
}