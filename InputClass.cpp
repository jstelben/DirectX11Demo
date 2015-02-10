#include "InputClass.h"


InputClass::InputClass(void)
{
}

InputClass::InputClass(const InputClass& other)
{

}

InputClass::~InputClass(void)
{
}

void InputClass::Initialize()
{
	for(int i = 0; i<256; i++)
	{
		keys[i] = false;
	}
}

void InputClass::KeyUp(unsigned int input)
{
	keys[input] = false;
}

void InputClass::KeyDown(unsigned int input)
{
	keys[input] = true;
}

bool InputClass::IsKeyDown(unsigned int key)
{
	return keys[key];
}