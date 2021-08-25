#include "NodeReflectionManager.h"

NodeReflectionManager::NodeReflectionManager() {

}

NodeReflectionManager* NodeReflectionManager::GetInstance()
{
	if (instance == nullptr)
		instance = new NodeReflectionManager();

	return instance;
}

void NodeReflectionManager::AddNodeDataToManager(const char* identifier, NodeData* node) {
	nodeData.insert(std::pair<const char*, NodeData*>(identifier, node));
}
