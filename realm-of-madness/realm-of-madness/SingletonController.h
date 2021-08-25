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
	static SingletonController* GetInstance();

	void AddSingletonToController(ISingleton* singleton);

private:
	static SingletonController* instance;
	std::vector<ISingleton*> singletons;
};

#define SINGLETON(T) \
static T* instance = new T(); \
//singletonControllerInstance->singletons.push_back((ISingleton)instance); \


