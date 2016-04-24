#include "JBEInput.h"
#include <SDL.h>

void Input::Init() 
{
	//Init sdl input stuff
	//memset all arrays to 0
}

bool Input::IsTriggered(SDL_Scancode sc)
{


	return false;
}

bool Input::IsPressed(SDL_Scancode sc)
{
	return false;
}

char Input::GetNumControllers(SDL_Scancode sc)
{
	return 0;
}
