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

	std::vector<unsigned> controllers = Input::GetActiveControllers();

	bool quit = false;

	while (!quit) 
	{
		WindowManager::Update();
		Input::Update();
		
		std::vector<unsigned> controllers_t = Input::GetActiveControllers();
		
		if (controllers_t.size() != controllers.size()) 
		{
			std::cout << "A controller was ";
			if (controllers_t.size() > controllers.size())
				std::cout << "connected." << std::endl;
			else
				std::cout << "disconnected." << std::endl;

			controllers = controllers_t;
		}


		if (Input::IsKeyTriggered(SDL_SCANCODE_Q))
			quit = true;
	}

	WindowManager::CleanUp();

	return 0;
}