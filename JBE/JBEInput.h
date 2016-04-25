#pragma once
#define INPUT_MAX_CONTROLLERS 8

#include <SDL.h>
#include <bitset>
#include <vector>

class Input 
{
public:
	enum class INPUT_SOURCE : int
	{
		ERR = -1,

		CONTROLLER,
		KEYBOARD,
		MOUSE,

		NUM_INPUT_SRCS
	};

	//not an enum class, will only use for indexing, dont need the strong typing
	enum MOUSE_BTN
	{
		INVALID,
		MOUSE_LEFT,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
		MOUSE_X1,
		MOUSE_X2,

		MOUSE_NUMBTNS = MOUSE_X2
	};


	/*
	*	\name	Init
	*
	*	\brief	Initializes the memory and buffers needed for storing 
	*			keys or buttons pressed.
	*
	*	\detail	Sets up the storage buffers for last state and 
	*			current state for keyboard, mouse and controller (s).
	*			Will set up enough space for 8 controllers.
	*			Will use flags to determine how many are actually active
	*			at any time.
	*/
	static void Init();

	/*
	*	\name	Update
	*
	*	\brief	Updates the current buffers depending on last frame and 
	*			current frame input.
	*
	*	\detail	Will call the update handlers of all input subtyped
	*			which will set the current input state to one of the 
	*			following
	*			<li>
	*			0 = not pressed (up this frame, down the previous)
	*			1 = triggered (first frame down, not persistent)
	*			2 = pressed (down for more than one frame, persistent)
	*			3 = released this frame (first frame up, not persistent)
	*			</li>
	*/
	static void Update();

	/*
	*	\name	HandleEvent
	*
	*	\brief	Interprets the given event and sets the current keyboard
	*	\returns	true if this event was input related, false otherwise	
	*/
	static bool HandleEvent(SDL_Event *ev);

	/*
	*	\brief	Returns whether the keyboard key 'sc' was pressed this frame
	*			for the first time
	*/
	static bool IsKeyTriggered(SDL_Scancode sc);

	/*
	*	\brief	Returns whether the keyboard key 'sc' has been pressed for 
	*			longer that the current frame
	*/
	static bool IsKeyPressed(SDL_Scancode sc);

	/*
	*	\brief	Returns whether the keyboard key 'sc' was pressed last frame
	*			and no longer is
	*/
	static bool IsKeyReleased(SDL_Scancode sc);

	/*
	*	\brief	Returns whether the mouse button 'm' was pressed this frame
	*			for the first time
	*/
	static bool IsMouseButtonTriggered(MOUSE_BTN m);

	/*
	*	\brief	Returns whether the mouse button 'm' has been pressed for
	*			longer that the current frame
	*/
	static bool IsMouseButtonPressed(MOUSE_BTN m);

	/*
	*	\brief	Returns whether the mouse button 'm' was pressed last frame
	*			and no longer is
	*/
	static bool IsMouseButtonReleased(MOUSE_BTN m);
	
	/*
	*	\brief	Returns how much the mouse wheel scrolled up (positive) 
	*			or down (negative) this frame.
	*/
	static int GetMouseWheelDelta();

	/*
	*	\brief	Returns the X coordinate for the mouse's position this frame
	*/
	static int GetMousePosX();
	

	/*
	*	\brief	Returns the Y coordinate for the mouse's position this frame
	*/
	static int GetMousePosY();


	/*
	*	\brief	Returns whether the game pad button 'btn' was pressed for the
	*			first time this frame on the controller 'which'
	*/
	static bool IsGamePadTriggered(unsigned which, SDL_GameControllerButton btn);

	/*
	*	\brief	Returns whether the game pad button 'btn' has been pressed for 
	*			longer than this frame on the controller 'which'
	*/
	static bool IsGamePadPressed(unsigned which, SDL_GameControllerButton btn);

	/*
	*	\brief	Returns whether the game pad button 'btn' was pressed last frame
	*			and no longer is on the controller 'which'
	*/
	static bool IsGamePadReleased(unsigned which, SDL_GameControllerButton btn);

	/*
	*	\brief	Returns how pressed the left trigger button is on the controller
	*			'which'
	*/
	static float GamePadLeftTriggerValue(unsigned which);
	
	/*
	*	\brief	Returns how pressed the right trigger button is on the controller
	*			'which'
	*/
	static float GamePadRightTriggerValue(unsigned which);

	/*
	*	\brief	Returns the X-axis status of the left stick on the controller
	*			'which'
	*/
	static float GamePadLeftStickXValue(unsigned which);
	
	/*
	*	\brief	Returns the Y-axis status of the left stick on the controller
	*			'which'
	*/
	static float GamePadLeftStickYValue(unsigned which);
	
	/*
	*	\brief	Returns the X-axis status of the right stick on the controller
	*			'which'
	*/
	static float GamePadRightStickXValue(unsigned which);
	
	/*
	*	\brief	Returns the Y-axis status of the right stick on the controller
	*			'which'
	*/
	static float GamePadRightStickYValue(unsigned which);

	/*
	*	\brief	Returns a vector containing the ID's of the active (plugged in)
	*			controllers this frame
	*/
	static std::vector<unsigned> GetActiveControllers();

private:

	/*
	*	\brief	Handler for Keyboard specific events.
	*
	*	\retval	true	The event was a keyboard event.
	*	\retval false	The event was not a keyboard event.
	*/
	static bool HandleKeyboardEvent(SDL_Event *ev);
	
	/*
	*	\brief	Handler for Mouse specific events.
	*
	*	\retval	true	The event was a mouse event.
	*	\retval false	The event was not a mouse event.
	*/
	static bool HandleMouseEvent(SDL_Event *ev);
	
	/*
	*	\brief	Handler for Gamepad specific events.
	*
	*	\retval	true	The event was a gamepad event.
	*	\retval false	The event was not a gamepad event.
	*/
	static bool HandleGamePadEvent(SDL_Event *ev);

	/*
	*	\brief	Handler for Keyboard specific events.
	*
	*	\retval	true	The event was a keyboard event.
	*	\retval false	The event was not a keyboard event.
	*/
	static void UpdateControllers();
	
	/*
	*	\brief	Handler for Keyboard specific events.
	*
	*	\retval	true	The event was a keyboard event.
	*	\retval false	The event was not a keyboard event.
	*/
	static void UpdateMouse();
	
	/*
	*	\brief	Handler for Keyboard specific events.
	*
	*	\retval	true	The event was a keyboard event.
	*	\retval false	The event was not a keyboard event.
	*/
	static void UpdateKeyboard();
	
	/*
	*	\brief	Bitfield for controllers active
	*/
	static std::bitset<INPUT_MAX_CONTROLLERS> controllers_active_;

	/*
	*	\brief	State of the keyboard last frame
	*/
	static char kb_prev_[SDL_NUM_SCANCODES];

	/*
	*	\brief	State of the keyboard this frame
	*/
	static char kb_curr_[SDL_NUM_SCANCODES];

	/*
	*	\brief	State of the mouse the previous frame
	*/
	static char m_prev_[MOUSE_NUMBTNS];

	/*
	*	\brief	State of the mouse this frame
	*/
	static char m_curr_[MOUSE_NUMBTNS];
	
	/*
	*	\brief	State of the GamePads last frame
	*/
	static char gp_prev_[INPUT_MAX_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];
	
	/*
	*	\brief	State of the GamePads this frame
	*/
	static char gp_curr_[INPUT_MAX_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];
};