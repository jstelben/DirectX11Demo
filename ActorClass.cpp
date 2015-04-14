#include "ActorClass.h"


ActorClass::ActorClass(void)
{
	Model = nullptr;
}


ActorClass::~ActorClass(void)
{
}

bool ActorClass::Initialize(ModelClass* model)
{
	bool result;
	Model = model;
	if(!Model)
	{
		return false;
	}
	return true;
}

void ActorClass::Shutdown()
{
	if(Model)
	{
		Model->Shutdown();
		delete Model;
		Model = nullptr;
	}
}
