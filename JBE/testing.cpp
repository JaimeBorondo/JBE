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

	bool quit = false;

	while (!quit) 
	{
		WindowManager::Update();
		Input::Update();

		if (Input::IsKeyTriggered(SDL_SCANCODE_F))
			std::cout << "T\n";
		if (Input::IsKeyPressed(SDL_SCANCODE_F))
			std::cout << "P";
		if (Input::IsKeyReleased(SDL_SCANCODE_F))
			std::cout << "\nR";

		if (Input::IsKeyTriggered(SDL_SCANCODE_Q))
			quit = true;
	}

	WindowManager::CleanUp();

	return 0;
}