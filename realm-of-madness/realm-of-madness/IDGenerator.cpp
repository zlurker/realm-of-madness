#include "IDGenerator.h"

namespace IDGenerator {

	int IDGenerator::GenerateIdForGroup(std::string group) {
		if (ids.find(group) == ids.end())
			ids.insert(std::pair<std::string, int>(group, 0));

		int id = ids[group];
		ids[group] = id + 1;
		return id;
	}
}