#include "GraphicsClass.h"


GraphicsClass::GraphicsClass(void)
{
	D3D = nullptr;
	Camera = nullptr;
	Model = nullptr;
	ColorShader = nullptr;
	TextureShader = nullptr;
	LightShader = nullptr;
	Light = nullptr;
}


GraphicsClass::~GraphicsClass(void)
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	D3D = new D3DClass();
	if(!D3D)
	{
		return false;
	}

	result = D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	Camera = new CameraClass();
	if(!Camera)
	{
		return false;
	}
	Camera->SetPosition(0.0f, -2.0f, -10.0f);
	Camera->Render();
	Camera->GetViewMatrix(baseViewMatrix);

	Model = new ModelClass();
	if(!Model)
	{
		return false;
	}
	result = Model->Initialize(D3D->GetDevice(), "../basemodel.obj", L"../basemodelTexture.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could now initialize model object", L"Error", MB_OK);
		return false;
	}

	LightShader = new LightShaderClass();
	if(!LightShader)
	{
		return false;
	}
	result = LightShader->Initialize(D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader.", L"Error", MB_OK);
		return false;
	}

	Light = new LightClass();
	if(!Light)
	{
		return false;
	}
	Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	Light->SetDirection(0.0f, 0.0f, 1.0f);

	Text = new TextClass();
	if(!Text)
	{
		return false;
	}
	result = Text->Initialize(D3D->GetDevice(), D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	if(Text)
	{
		Text->Shutdown();
		delete Text;
		Text = nullptr;
	}
	if(Light)
	{
		delete Light;
		Light = nullptr;
	}
	if(LightShader)
	{
		LightShader->Shutdown();
		delete LightShader;
		LightShader = 0;
	}
	if(TextureShader)
	{
		TextureShader->Shutdown();
		delete TextureShader;
		TextureShader = nullptr;
	}
	if(ColorShader)
	{
		ColorShader->Shutdown();
		delete ColorShader;
		ColorShader = nullptr;
	}

	if(Model)
	{
		Model->Shutdown();
		delete Model;
		Model = nullptr;
	}

	if(Camera)
	{
		delete Camera;
		Camera = nullptr;
	}

	if(D3D)
	{
		D3D->Shutdown();
		delete D3D;
		D3D = nullptr;
	}
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	result = Text->SetFps(fps, D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	result = Text->SetCpu(cpu, D3D->GetDeviceContext());
	if(!result)
	{
		return false;
	}

	static float rotation = 0.0f;

	rotation += (float)D3DX_PI * 0.01f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	result = Render(rotation);
	if(!result)
	{
		return false;
	}
	Sleep(50);
	return true;
}

bool GraphicsClass::Render()
{
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX orthoMatrix;
	bool result;

	D3D->BeginScene(0.4f, 0.611f, 0.94f, 1.0f);

	Camera->Render();

	Camera->GetViewMatrix(viewMatrix);
	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);
	D3D->GetOrthoMatrix(orthoMatrix);

	D3D->TurnZBufferOff();
	D3D->TurnOnAlphaBlending();
	result = Text->Render(D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	D3D->TurnOffAlphaBlending();
	
	D3D->TurnZBufferOn();
	Model->Render(D3D->GetDeviceContext());

	result = LightShader->Render(D3D->GetDeviceContext(),
		Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		Model->GetTexture(), Light->GetDirection(), Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	D3D->EndScene();
	return true;
}

bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXMATRIX worldMatrix;
	D3DXMATRIX orthoMatrix;
	bool result;

	D3D->BeginScene(0.4f, 0.611f, 0.94f, 1.0f);

	Camera->Render();

	Camera->GetViewMatrix(viewMatrix);
	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);
	D3D->GetOrthoMatrix(orthoMatrix);

	D3D->TurnZBufferOff();
	D3D->TurnOnAlphaBlending();
	result = Text->Render(D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	D3D->TurnOffAlphaBlending();
	
	D3D->TurnZBufferOn();

	D3DXMatrixRotationY(&worldMatrix, rotation);

	Model->Render(D3D->GetDeviceContext());

	result = LightShader->Render(D3D->GetDeviceContext(),
		Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		Model->GetTexture(), Light->GetDirection(), Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	if(!result)
	{
		return false;
	}

	D3D->EndScene();
	return true;
}
