#pragma once
#include <vector>
#include <map>

class VariableData {
public:
	VariableData(const char* n);
	const char* name;
};

class NodeData {
public:
	NodeData(const char* identifier, void (*reflectionDataMethod)(NodeData*));
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
	static const char* identifier = IDENTIFIER;\
	void BuildReflectionData(NodeData* instance){ \
		T creationInstance; \
		instance->variables = {

#define REFLECT_VARIABLE(VARIABLE) \
		new VariableData(#VARIABLE), 

#define REFLECTION_END() \
		}; \
	} \

static NodeData* nodeData = new NodeData(identifier, BuildReflectionData);