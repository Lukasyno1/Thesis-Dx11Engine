#include "Game.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <iostream>
#pragma comment(lib,"PhysX3DEBUG_x64.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")		//PhysX extended library 
#pragma comment(lib, "PhysXProfileSDKDEBUG.lib") 
#pragma comment(lib, "PhysX3CharacterKinematicDEBUG_x64.lib") //Only for character controller
#pragma comment(lib, "PhysXVisualDebuggerSDKDEBUG.lib") //For PVD only 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Game game;
	Timer timer, gameTimer;
	float delta=0.0f;
	if (game.Initialize(hInstance, "Title", "MyWindowClass", 800, 600))
	{
		game.InitGame();
		timer.Start();	
		gameTimer.Start();
		while (game.ProcessMessages())
		{
			game.Render();
			delta += timer.GetMilisecondsElapsed();
			while (delta > 16.6) //1/60 sekundy
			{	
				game.ProcessInput();
				game.Update();
				game.SimulatePhysics();				
				delta -= 16.6;
			}
			timer.Restart();
		}		
	}
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	std::cout << "Twoj czas: " << gameTimer.GetMilisecondsElapsed() / 1000 << std::endl;
	std::cout << "Nacisnij enter, aby wyjsc..." << std::endl;
	std::cin.get();
	return 0;
}