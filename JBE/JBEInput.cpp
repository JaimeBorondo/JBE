#include "JBEInput.h"

//Static vars
std::bitset<INPUT_MAX_CONTROLLERS> Input::controllers_active_;
char Input::kb_prev_[SDL_NUM_SCANCODES];
char Input::kb_curr_[SDL_NUM_SCANCODES];
char Input::m_prev_[Input::MOUSE_NUMBTNS];
char Input::m_curr_[Input::MOUSE_NUMBTNS];
char Input::gp_prev_[INPUT_MAX_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];
char Input::gp_curr_[INPUT_MAX_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];
Input::Gamepad_Axes Input::gp_axes_[INPUT_MAX_CONTROLLERS];

void Input::Init()
{
	std::memset(kb_curr_, 0, SDL_NUM_SCANCODES);
	std::memset(kb_prev_, 0, SDL_NUM_SCANCODES);

	std::memset(m_prev_, 0, Input::MOUSE_NUMBTNS);
	std::memset(m_curr_, 0, Input::MOUSE_NUMBTNS);

	for (unsigned c = 0; c < INPUT_MAX_CONTROLLERS; ++c)
	{
		std::memset(gp_prev_[c], 0, SDL_CONTROLLER_BUTTON_MAX);
		std::memset(gp_curr_[c], 0, SDL_CONTROLLER_BUTTON_MAX);

		gp_axes_[c].ls_x = gp_axes_[c].ls_y = gp_axes_[c].lt =
		gp_axes_[c].rs_x = gp_axes_[c].rs_y = gp_axes_[c].rt = 0.0f;

		SDL_GameController * gc = SDL_GameControllerOpen(c);
		controllers_active_.set(c, SDL_GameControllerGetAttached(gc) == SDL_TRUE);
	}
}

void Input::Update()
{
	UpdateKeyboard();
	UpdateMouse();
	UpdateControllers();
}

bool Input::HandleEvent(SDL_Event * ev)
{
	if (HandleKeyboardEvent(ev))
		return true;

	if (HandleMouseEvent(ev))
		return true;

	if (HandleGamePadEvent(ev))
		return true;

	return false;
}

bool Input::IsKeyTriggered(SDL_Scancode sc)
{
	return kb_curr_[sc] == 1;
}

bool Input::IsKeyPressed(SDL_Scancode sc)
{
	return kb_curr_[sc] == 2;
}

bool Input::IsKeyReleased(SDL_Scancode sc)
{
	return kb_curr_[sc] == 3;
}

bool Input::IsMouseButtonTriggered(MOUSE_BTN m)
{
	return m_curr_[m] == 1;
}

bool Input::IsMouseButtonPressed(MOUSE_BTN m)
{
	return m_curr_[m] == 2;
}

bool Input::IsMouseButtonReleased(MOUSE_BTN m)
{
	return m_curr_[m] == 3;
}

int Input::GetMouseWheelDelta()
{
	return 0;
}

int Input::GetMousePosX()
{
	return 0;
}

int Input::GetMousePosY()
{
	return 0;
}

bool Input::IsGamePadTriggered(unsigned which, SDL_GameControllerButton btn)
{
	return gp_curr_[which][btn] == 1;
}

bool Input::IsGamePadPressed(unsigned which, SDL_GameControllerButton btn)
{
	return gp_curr_[which][btn] == 2;
}

bool Input::IsGamePadReleased(unsigned which, SDL_GameControllerButton btn)
{
	return gp_curr_[which][btn] == 3;
}

float Input::GamePadLeftTriggerValue(unsigned which)
{
	return gp_axes_[which].lt;
}

float Input::GamePadRightTriggerValue(unsigned which)
{
	return gp_axes_[which].rt;
}

float Input::GamePadLeftStickXValue(unsigned which)
{
	return gp_axes_[which].ls_x;
}

float Input::GamePadLeftStickYValue(unsigned which)
{
	return gp_axes_[which].ls_y;
}

float Input::GamePadRightStickXValue(unsigned which)
{
	return gp_axes_[which].rs_x;
}

float Input::GamePadRightStickYValue(unsigned which)
{
	return gp_axes_[which].rs_y;
}

std::vector<unsigned> Input::GetActiveControllers()
{
	std::vector<unsigned> retval;

	for (unsigned i = 0; i < INPUT_MAX_CONTROLLERS; ++i)
		if (controllers_active_[i] == 1)
			retval.push_back(i);

	return retval;
}

bool Input::HandleKeyboardEvent(SDL_Event * ev)
{
	switch (ev->type)
	{
		case SDL_KEYDOWN:
			kb_curr_[ev->key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			kb_curr_[ev->key.keysym.scancode] = 0;
			break;
		default: //not our message
			return false;
	}

	return true;
}

bool Input::HandleMouseEvent(SDL_Event * ev)
{
	switch (ev->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			m_curr_[ev->button.button] = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			m_curr_[ev->button.button]= 0;
			break;
			//TODO add support for scrollwheel and logging mouse position
		default: //not our message
			return false;
	}

	return true;
}

bool Input::HandleGamePadEvent(SDL_Event * ev)
{
	switch (ev->type)
	{
	case SDL_CONTROLLERDEVICEADDED:
		controllers_active_.set(ev->cdevice.which, true);
		break;
	case SDL_CONTROLLERDEVICEREMOVED:
		controllers_active_.set(ev->cdevice.which, false);
		break;
	case SDL_CONTROLLERBUTTONDOWN:
		gp_curr_[ev->cbutton.which][ev->cbutton.button] = 1;
		break;
	case SDL_CONTROLLERBUTTONUP:
		gp_curr_[ev->cbutton.which][ev->cbutton.button] = 0;
		break;
	case SDL_CONTROLLERAXISMOTION:
		switch (ev->caxis.axis)
		{
			case SDL_CONTROLLER_AXIS_LEFTX:
				gp_axes_[ev->caxis.which].ls_x = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
			case SDL_CONTROLLER_AXIS_LEFTY:
				gp_axes_[ev->caxis.which].ls_y = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
			case SDL_CONTROLLER_AXIS_RIGHTX:
				gp_axes_[ev->caxis.which].rs_x = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
			case SDL_CONTROLLER_AXIS_RIGHTY:
				gp_axes_[ev->caxis.which].rs_y = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
				gp_axes_[ev->caxis.which].lt = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
			case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
				gp_axes_[ev->caxis.which].rt = static_cast<float>(ev->caxis.value) / 32768.0f;
				break;
		}
		break;

	default: //not our message
		return false;
	}

	return true;
}

void Input::UpdateControllers()
{
	for (unsigned controller = 0; controller < INPUT_MAX_CONTROLLERS; controller++)
	for (unsigned i = 0; i < SDL_CONTROLLER_BUTTON_MAX; ++i)
	{
		if (gp_prev_[controller][i] == 0 && gp_curr_[controller][i] == 1)
			gp_prev_[controller][i] = 1;
		else if (gp_prev_[controller][i] == 1 && gp_curr_[controller][i] == 1) //second frame down, set to pressed
			gp_curr_[controller][i] = 2;
		else if (gp_prev_[controller][i] != 0 && gp_curr_[controller][i] == 0) //key was released
		{
			gp_curr_[controller][i] = 3;
			gp_prev_[controller][i] = 0;
		}
		else if (gp_curr_[controller][i] == 3)
			gp_curr_[controller][i] = 0;
	}
}

void Input::UpdateMouse()
{
	for (unsigned i = 0; i < Input::MOUSE_NUMBTNS; ++i)
	{
		if (m_prev_[i] == 0 && m_curr_[i] == 1)
			m_prev_[i] = 1;
		else if (m_prev_[i] == 1 && m_curr_[i] == 1) //second frame down, set to pressed
			m_curr_[i] = 2;
		else if (m_prev_[i] != 0 && m_curr_[i] == 0) //key was released
		{
			m_curr_[i] = 3;
			m_prev_[i] = 0;
		}
		else if (m_curr_[i] == 3)
			m_curr_[i] = 0;
	}

	//Clear scroll value here when implemented
}

void Input::UpdateKeyboard()
{
	for (unsigned i = 0; i < SDL_NUM_SCANCODES; ++i)
	{
		if (kb_prev_[i] == 0 && kb_curr_[i] == 1)
			kb_prev_[i] = 1;
		else if (kb_prev_[i] == 1 && kb_curr_[i] == 1) //second frame down, set to pressed
			kb_curr_[i] = 2;
		else if (kb_prev_[i] != 0 && kb_curr_[i] == 0) //key was released
		{
			kb_curr_[i] = 3;
			kb_prev_[i] = 0;
		}
		else if (kb_curr_[i] == 3)
			kb_curr_[i] = 0;
	}
}
