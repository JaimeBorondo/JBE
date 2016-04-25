#include "JBEWindow.h"
#include "JBEInput.h"

SDL_Window *WindowManager::window_;

bool WindowManager::Initialize(std::string wname, int w, int h, Uint32 f)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

	//Create the window
	int c = SDL_WINDOWPOS_CENTERED;
	window_ = SDL_CreateWindow(wname.c_str(), c, c, w, h, f);		  
													  
	if (window_ == 0)
	{
		SDL_Quit();
		return false;
	}

	return true;
}

void WindowManager::Update()
{
	SDL_Event evt;
	SDL_PollEvent(&evt);

	if (evt.type == SDL_QUIT)
		CleanUp();

	Input::HandleEvent(&evt);
}

void WindowManager::CleanUp()
{
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

SDL_Window * WindowManager::GetWindowHandle(void)
{
	return window_;
}
