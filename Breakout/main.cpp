//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

//Library Includes
#include <windows.h>
#include <windowsx.h>

//Local Includes
#include "Game.h"
#include "Clock.h"
#include "utils.h"
#include "level.h"
#include "paddle.h"

const int width = 400;
const int height = 400;


#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

LRESULT CALLBACK
WindowProc(HWND hwnd, UINT message, WPARAM widthParam, LPARAM lengthParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
	{
		int mouseX = LOWORD(lengthParam);
		//CGame::GetInstance().GetLevel()->GetPaddle()->SetX(static_cast<float>(iMouseX));
		return (0);
	}
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return(0);
	}
		break;

	default:break;
	}

	return (DefWindowProc(hwnd, message, widthParam, lengthParam));
}

HWND
CreateAndRegisterWindow(HINSTANCE hInstance, int width, int height, const wchar_t* title)
{
	WNDCLASSEX winclass;

	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(NULL_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&winclass))
	{
		// Failed to register.
		return (0);
	}

	HWND hwnd;
	hwnd = CreateWindowEx(NULL,
		WINDOW_CLASS_NAME,
		title,
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
	{
		// Failed to create.
		return (0);
	}

	return (hwnd);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE previousInstance, LPSTR commandLine, int commandShow)
{
	MSG message;
	RECT rectangle;
	ZeroMemory(&message, sizeof(MSG));


	HWND hwnd = CreateAndRegisterWindow(hInstance, width, height, L"Breakout");

	Game& game = Game::GetInstance();
	
	GetClientRect(hwnd, &rectangle);

	//if (!rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
	if (!game.Initialise(hInstance, hwnd, rectangle.right, rectangle.bottom))
	{
		// Failed
		return (0);
	}

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			game.ExecuteOneFrame();
		}
	}

	Game::DestroyInstance();

	return (static_cast<int>(message.wParam));
}
