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

// I want to find a way to stop depending on this macro. Maybe create a map.
#define SINGLETON(T) \
static T* instance = new T(); \
//singletonControllerInstance->singletons.push_back((ISingleton)instance); \


