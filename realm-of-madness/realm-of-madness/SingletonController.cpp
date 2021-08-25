#include "SingletonController.h"

SingletonController* SingletonController::instance;

SingletonController::SingletonController() {
}

SingletonController* SingletonController::GetInstance()
{
	if (instance == nullptr)
		instance = new SingletonController();

	return instance;
}

void SingletonController::AddSingletonToController(ISingleton* singleton) {
	singletons.push_back(singleton);
}
