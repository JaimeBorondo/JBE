#include "JBEWindow.h"
#include "JBEInput.h"

#include <iostream>

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

int main(int argc, char* args[])
{
	WindowManager::Initialize("Engine test", 1280, 720);
	Input::Init();

	bool quit = false;
	bool fs = false;

	while (!quit)
	{
		WindowManager::Update();
		Input::Update();

		if (Input::IsKeyTriggered(SDL_SCANCODE_F) || Input::IsGamePadTriggered(0, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X))
		{
			fs = !fs;
			WindowManager::SetFullscreen(fs);
		}


		if (Input::IsKeyTriggered(SDL_SCANCODE_Q) || Input::IsGamePadTriggered(0, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y))
			quit = true;
	}

	WindowManager::CleanUp();

	return 0;
}
