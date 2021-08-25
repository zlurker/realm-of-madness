#pragma once
#include <vector>
#include <map>

class NodeData {

	class VariableData {
	public:
		VariableData(const char* n);
		const char* name;
	};

public:
	NodeData(char* identifier, void (*reflectionDataMethod)(NodeData*));
	std::vector<VariableData*> variables;
};

class NodeReflectionManager
{
public:
	NodeReflectionManager();
	static NodeReflectionManager* GetInstance();
	void AddNodeDataToManager(const char* identifier, NodeData* node);

private:
	static NodeReflectionManager* instance;
	std::map<const char*, NodeData*> nodeData;
};

#define REFLECTION_START(IDENTIFIER, T) \
static NodeData* nodeData = new NodeData(IDENTIFIER); \
void BuildReflectionData(NodeData* instance){ \
	instance->variables = {

#define REFLECT_VARIABLE(VARIABLE) \
	new NodeData::VariableData(#VARIABLE),

#define REFLECTION_END() \
	}; \
} \


