#pragma once
#include "NodeReflectionManager.h"

class NodeClassTest
{
public:
	int test1;
	const char* test2;
	bool test3;
};


REFLECTION_START("NodeClassTest", NodeClassTest);
REFLECT_VARIABLE(creationInstance.test1);
};
}
static NodeData* nodeData = new NodeData("Test", BuildReflectionData);
