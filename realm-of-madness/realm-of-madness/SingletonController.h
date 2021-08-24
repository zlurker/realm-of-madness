#pragma once
#include <vector>

class ISingleton
{
public:
	ISingleton();
};

class SingletonController
{
public:
	SingletonController();
	std::vector<ISingleton*> singletons;
};

static SingletonController* singletonControllerInstance = new SingletonController();

#define SINGLETON(T) \
static T* instance = new T(); \
//singletonControllerInstance->singletons.push_back((ISingleton)instance); \


