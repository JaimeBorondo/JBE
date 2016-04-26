#pragma once

#include <SDL.h>
#include <string>

class WindowManager
{
public:
	/*************************************************************************************/
	/*!
	\brief
	Creates a Window given title and dimensions

	\param wname	Title of the created window.
	\param width	Window width.
	\param height	Window Height.
	\param flags	Window Creation flags

	\retval true	Initialization successful.
	\retval false	Initialization failed.
	*/
	/*************************************************************************************/
	static bool Initialize(std::string wname, int width, int height, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	/*************************************************************************************/
	/*!
	\brief
		Polls and forwards window messages
	*/
	/*************************************************************************************/
	static void Update();

	/*************************************************************************************/
	/*!
	\brief
		Cleans up
	*/
	/*************************************************************************************/
	static void CleanUp();

	/*************************************************************************************/
	/*
	\brief
		Sets the window to fullscreen or regular mode	
	*/
	/*************************************************************************************/
	static void SetFullscreen(bool fs);

	/*************************************************************************************/
	/*!
	\brief
		Gets a pointer to the SDL window structure
	*/
	/*************************************************************************************/
	static SDL_Window * GetWindowHandle(void);

private:
	/*************************************************************************************/
	/*!
	\brief
		SDL Window structure
	*/
	/*************************************************************************************/
	static SDL_Window * window_;
};