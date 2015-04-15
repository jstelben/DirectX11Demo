#pragma once
#include "ModelClass.h";
class ActorClass
{
public:
	ActorClass(void);
	~ActorClass(void);
	bool Initialize(ModelClass*);
	void Shutdown();

private:
	ModelClass* Model;
};

