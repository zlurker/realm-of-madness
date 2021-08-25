#pragma once
#include "NodeReflectionManager.h"

NodeData::VariableData::VariableData(const char* n) {
	name = n;
}

NodeData::NodeData(char* identifier, void (*reflectionDataMethod)(NodeData*)) {
	reflectionDataMethod(this);
	NodeReflectionManager::GetInstance()->AddNodeDataToManager(identifier, this);
}

