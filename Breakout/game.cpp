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

// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "utils.h"

// This Include
#include "Game.h"

// Static Variables
Game* Game::game = 0;

// Static Function Prototypes

// Implementation

Game::Game()
	: level(0)
	, clock(0)
	, applicationInstance(0)
	, mainWindow(0)
	, backBuffer(0)
{

}

Game::~Game()
{
	delete level;
	level = 0;

	delete backBuffer;
	backBuffer = 0;

	delete clock;
	clock = 0;
}

bool
Game::Initialise(HINSTANCE hInstance, HWND hwnd, int width, int height)
{
	applicationInstance = hInstance;
	mainWindow = hwnd;

	clock = new CClock();
	VALIDATE(clock->Initialise());
	clock->Process();

	backBuffer = new CBackBuffer();
	VALIDATE(backBuffer->Initialise(hwnd, width, height));

	level = new Level();
	VALIDATE(level->Initialise(width, height));

	ShowCursor(false);

	return (true);
}

void
Game::Draw()
{
	backBuffer->Clear();

	level->Draw();

	backBuffer->Present();
}

void
Game::Process(float deltaTick)
{
	level->Process(deltaTick);
}

void
Game::ExecuteOneFrame()
{
	float dataTick = clock->GetDeltaTick();

	Process(dataTick);
	Draw();

	clock->Process();

	Sleep(1);
}

Game&
Game::GetInstance()
{
	if (game == 0)
	{
		game = new Game();
	}

	return (*game);
}

void
Game::GameOverWon()
{
	MessageBox(mainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
Game::GameOverLost()
{
	MessageBox(mainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
Game::DestroyInstance()
{
	delete game;
	game = 0;
}

CBackBuffer*
Game::GetBackBuffer()
{
	return (backBuffer);
}

Level*
Game::GetLevel()
{
	return (level);
}

HINSTANCE
Game::GetAppInstance()
{
	return (applicationInstance);
}

HWND
Game::GetWindow()
{
	return (mainWindow);
}

