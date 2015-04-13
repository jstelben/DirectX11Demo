#pragma once

#include <Windows.h>
#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "LightShaderClass.h"
#include "LightClass.h"
#include "TextClass.h"

static const bool FULL_SCREEN = false;
static const bool VSYNC_ENABLED = false;
static const float SCREEN_DEPTH = 1000.0f;
static const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass(void);
	~GraphicsClass(void);

	bool Initialize(int, int, HWND);
	void Shutdown(void);
	bool Frame(int, int, float);


private:
	bool Render(void);
	bool Render(float);

	D3DClass* D3D;
	CameraClass* Camera;
	ModelClass* Model;
	ColorShaderClass* ColorShader;
	TextureShaderClass* TextureShader;
	LightShaderClass* LightShader;
	LightClass* Light;
	TextClass* Text;
};
