#pragma once
#define INPUT_MAX_CONTROLLERS 8


//Can I forward declare enums and use them as such (no pointer) ?
enum SDL_Scancode;
union SDL_EVENT;

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
	*	\brief	Updates the current buffer depending on last frame and 
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
	*/
	static bool HandleEvent(SDL_EVENT *ev);

	static bool IsTriggered(SDL_Scancode sc);
	static bool IsPressed(SDL_Scancode sc);
	static char GetNumControllers(SDL_Scancode sc);

private:
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
	*	\brief	Handler for Keyboard specific events.
	*
	*	\retval	true	The event was a keyboard event.
	*	\retval false	The event was not a keyboard event.
	*/
	static bool HandleKeyboardEvent(SDL_EVENT *ev);
	
	/*
	*	\brief	Handler for Mouse specific events.
	*
	*	\retval	true	The event was a mouse event.
	*	\retval false	The event was not a mouse event.
	*/
	static bool HandleMouseEvent(SDL_EVENT *ev);
	
	/*
	*	\brief	Handler for Gamepad specific events.
	*
	*	\retval	true	The event was a gamepad event.
	*	\retval false	The event was not a gamepad event.
	*/
	static bool HandleGamePadEvent(SDL_EVENT *ev);

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
	*	\brief	State of the keyboard last frame
	*/
	static char kb_prev_[SDL_NUM_SCANCODES];
	/*
	*	\brief	State of the keyboard this frame
	*/
	static char kb_curr_[SDL_NUM_SCANCODES];
	
	/*
	*	\brief	State of the GamePads last frame
	*
	*	\detail	For 8 controllers, this is already 4kb(4096b) of data.
	*			Think twice before adding support for more controllers
	*/
	static char gp_prev_[INPUT_MAX_CONTROLLERS][SDL_NUM_SCANCODES];
	
	/*
	*	\brief	State of the GamePads this frame
	*
	*	\detail	For 8 controllers, this is already 4kb(4096b) of data.
	*			Think twice before adding support for more controllers
	*/
	static char gp_curr_[INPUT_MAX_CONTROLLERS][SDL_NUM_SCANCODES];
};