#include "SystemClass.h"


SystemClass::SystemClass(void)
{
	Input = nullptr;
	Graphics = nullptr;
}

SystemClass::SystemClass(const SystemClass& other)
{
	Input = other.Input;
	Graphics = other.Graphics;
}

SystemClass::~SystemClass(void)
{
}

bool SystemClass::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;
	bool result;

	InitializeWindows(screenWidth, screenHeight);

	Input = new InputClass();

	if(!Input)
	{
		return false;
	}

	Input->Initialize();

	Graphics = new GraphicsClass();
	if(!Graphics)
	{
		return false;
	}

	result = Graphics->Initialize(screenWidth, screenHeight, Hwnd);

	return result;
}

void SystemClass::Shutdown()
{
	if(Graphics)
	{
		Graphics->Shutdown();
		delete Graphics;
		Graphics = nullptr;
	}

	if(Input)
	{
		delete Input;
		Input = nullptr;
	}

	ShutdownWindows();
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false;
	bool result;

	ZeroMemory(&msg, sizeof(MSG));

	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}
	}
}

bool SystemClass::Frame()
{
	bool result;

	if(Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	result = Graphics->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
		case WM_KEYDOWN:
			{
				Input->KeyDown((unsigned int)wparam);
				return 0;
			}
		case WM_KEYUP:
			{
				Input->KeyUp((unsigned int)wparam);
				return 0;
			}
		default:
			{
				return DefWindowProc(hwnd, msg, wparam, lparam);
			}
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX;
	int posY;

	ApplicationHandle = this;

	HInstance = GetModuleHandle(NULL);

	ApplicationName = L"DirectX11Demo";

	wc.style =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = HInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ApplicationName;
	wc. cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	if(FULL_SCREEN == true)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long) screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long) screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = 0;
		posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	Hwnd = CreateWindowEx(WS_EX_APPWINDOW, ApplicationName, ApplicationName, 
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP, posX, posY, 
		screenWidth, screenHeight, NULL, NULL, HInstance, NULL);

	ShowWindow(Hwnd, SW_SHOW);
	SetForegroundWindow(Hwnd);
	SetFocus(Hwnd);

	ShowCursor(false);
}

void SystemClass::ShutdownWindows()
{
	ShowCursor(true);

	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(Hwnd);
	Hwnd = NULL;
	
	UnregisterClass(ApplicationName, HInstance);
	HInstance = NULL;

	ApplicationHandle = nullptr;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch(message)
	{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}
		default:
			{
				return ApplicationHandle->MessageHandler(hwnd, message, wparam, lparam);
			}
	}
}