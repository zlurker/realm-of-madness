#include "SingletonController.h"

ISingleton::ISingleton() {
	if (singletonControllerInstance->singletons.empty())
		singletonControllerInstance->singletons.push_back(new ISingleton());
}
