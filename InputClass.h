#pragma once
class InputClass
{
public:
	InputClass(void);
	InputClass(const InputClass&);
	~InputClass(void);

	void Initialize(void);

	void KeyUp(unsigned int);
	void KeyDown(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool keys[256];
};

