#include "SingletonController.h"

ISingleton::ISingleton() {
	if (singletonControllerInstance == nullptr)
		singletonControllerInstance = new SingletonController();

	singletonControllerInstance->singletons.push_back(this);
}
