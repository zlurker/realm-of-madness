#include "SingletonController.h"

ISingleton::ISingleton() {
	SingletonController::GetInstance()->AddSingletonToController(this);
}
