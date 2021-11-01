#pragma once
#include <map>
#include <string>
#include "SingletonController.h"

namespace IDGenerator {
	class IDGenerator : public ISingleton
	{
	public:
		int GenerateIdForGroup(std::string group);
		std::map<std::string, int> ids;

	};

	// Hmm i wanna find a way to use it without this macro
	SINGLETON(IDGenerator);
}

