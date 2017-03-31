#include "../include/InputManager.h"

/*
The keyboard class
*/

Uint8 InputManager::Keyboard::m_press[SDL_NUM_SCANCODES] = {0};
Uint8 InputManager::Keyboard::m_release[SDL_NUM_SCANCODES] = {0};
const Uint8 *InputManager::Keyboard::m_keystates = nullptr;

void
InputManager::Keyboard::process(SDL_Event& event)
{

	//for(int i=0; i < SDL_NUM_SCANCODES; i++)
    //{
    //    m_release[i] = m_press[i] = 0;
    //}
	if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
			m_press[event.key.keysym.scancode] = 1;
	}
	else if(event.type == SDL_KEYUP)
	{
		m_release[event.key.keysym.scancode] = 1;
	}

	m_keystates = SDL_GetKeyboardState(nullptr);
}

void
InputManager::Keyboard::clear()
{
	for(int i=0; i < SDL_NUM_SCANCODES; i++)
    {
        m_release[i] = m_press[i] = 0;
    }
}

/*
 The Mouse class
*/

int InputManager::Mouse::m_buttonFlags = 0;

int InputManager::Mouse::m_x = 0;
int InputManager::Mouse::m_y = 0;

bool InputManager::Mouse::m_isLeftPressed = false;
bool InputManager::Mouse::m_isLeftReleased = false;

bool InputManager::Mouse::m_isRightPressed = false;
bool InputManager::Mouse::m_isRightReleased = false;

bool InputManager::Mouse::m_isMiddlePressed = false;
bool InputManager::Mouse::m_isMiddleReleased = false;

bool InputManager::Mouse::m_mouseMoved = false;
int InputManager::Mouse::m_dx = 0;
int InputManager::Mouse::m_dy = 0;

bool InputManager::Mouse::m_mouseWheel = false;
int InputManager::Mouse::m_xwheel = 0;
int InputManager::Mouse::m_ywheel = 0;

void
InputManager::Mouse::process(SDL_Event& event)
{


	if(event.type == SDL_MOUSEBUTTONDOWN)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			m_isLeftPressed = true;
		}
		else if(event.button.button == SDL_BUTTON_RIGHT)
		{
			m_isRightPressed = true;
		}
		else if(event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_isMiddlePressed = false;
		}
	}
	else if(event.type == SDL_MOUSEBUTTONUP)
	{
		if(event.button.button == SDL_BUTTON_LEFT)
		{
			m_isLeftReleased = true;
		}
		else if(event.button.button == SDL_BUTTON_RIGHT)
		{
			m_isRightReleased = true;
		}
		else if(event.button.button == SDL_BUTTON_MIDDLE)
		{
			m_isMiddleReleased = false;
		}
	}
	else if(event.type == SDL_MOUSEMOTION)
	{
		m_mouseMoved = true;
		m_dx = event.motion.xrel;
		m_dy = event.motion.yrel;
	}
	else if(event.type == SDL_MOUSEWHEEL)
	{
		m_mouseWheel = true;
		m_xwheel = event.wheel.x;
		m_ywheel = event.wheel.x;
	}

	m_buttonFlags = SDL_GetMouseState(&m_x, &m_y);
}

void
InputManager::Mouse::clear()
{
	m_isLeftPressed = false;
	m_isLeftReleased = false;
	m_isRightPressed = false;
	m_isRightReleased = false;
	m_isMiddlePressed = false;
	m_isMiddleReleased = false;
	m_mouseMoved = false;
	m_mouseWheel = false;
}

/*
 The Window class
*/


std::vector<InputManager::Window::WindowEvent> InputManager::Window::m_eventList;

void
InputManager::Window::process(SDL_Event& event)
{
    //m_eventList.clear();
    if(event.type == SDL_WINDOWEVENT)
    {
        m_eventList.push_back(SDLWindowEventID2Event(event.window.event));
    }
}

void
InputManager::Window::clear()
{
    m_eventList.clear();
}

/*
 The InputManager class
*/

InputManager::InputManager() : m_keyboardKeyMap(), m_mouseButtonMap(),
							m_mouseRangeMap(), m_windowEventMap(),
							m_eventCallbackMap()
{
	// setup default mapping values
}

void
InputManager::process()
{
	while(SDL_PollEvent(&m_event))
	{
		switch(m_event.type)
		{
		case SDL_KEYDOWN :
		case SDL_KEYUP :
			Keyboard::process(m_event);
			break;
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEBUTTONUP :
		case SDL_MOUSEMOTION :
		case SDL_MOUSEWHEEL :
			Mouse::process(m_event);
			break;
		case SDL_WINDOWEVENT :
			Window::process(m_event);
			break;
		}
	}
}

void
InputManager::clear()
{
	Keyboard::clear();
	Mouse::clear();
	Window::clear();
}

void
InputManager::registerCommand(const std::string& actionName, CommandCallback callback)
{
	auto i = m_callbackMap.find(actionName);
	if (i != m_callbackMap.end())
		m_callbackMap.erase(i);
	m_callbackMap[actionName] = std::move(callback);
}

void
InputManager::registerCommand(std::string&& actionName, CommandCallback callback)
{
	auto i = m_callbackMap.find(actionName);
	if (i != m_callbackMap.end())
		m_callbackMap.erase(i);
	m_callbackMap[std::move(actionName)] = std::move(callback);
}

void
InputManager::bind(const std::string& actionName, Keyboard::KeyEvent kev)
{
	for(auto i = m_keyboardKeyMap.begin(); i != m_keyboardKeyMap.end(); /* no ++i */)
	{
		if (i->second == kev)
		{
			auto e = i;
			++i;
			m_keyboardKeyMap.erase(e);
		}
		else
		{
			++i;
		}
	}

	auto i = m_keyboardKeyMap.find(actionName);
	if (i != m_keyboardKeyMap.end())
		m_keyboardKeyMap.erase(i);

	// add new mapping
	m_keyboardKeyMap[actionName] = kev;
}

void
InputManager::bind(const std::string& actionName, Mouse::MouseEvent mev)
{
	for(auto i = m_mouseButtonMap.begin(); i != m_mouseButtonMap.end(); /* no ++i */)
	{
		if (i->second == mev)
		{
			auto e = i;
			++i;
			m_mouseButtonMap.erase(e);
		}
		else
		{
			++i;
		}
	}

	auto i = m_mouseButtonMap.find(actionName);
	if (i != m_mouseButtonMap.end())
		m_mouseButtonMap.erase(i);

	// add new mapping
	m_mouseButtonMap[actionName] = mev;
}

void
InputManager::bind(const std::string& actionName, Mouse::RangeEvent rev)
{
	for(auto i = m_mouseRangeMap.begin(); i != m_mouseRangeMap.end(); /* no ++i */)
	{
		if (i->second == rev)
		{
			auto e = i;
			++i;
			m_mouseRangeMap.erase(e);
		}
		else
		{
			++i;
		}
	}

	auto i = m_mouseRangeMap.find(actionName);
	if (i != m_mouseRangeMap.end())
		m_mouseRangeMap.erase(i);

	// add new mapping
	m_mouseRangeMap[actionName] = rev;
}

void
InputManager::bind(const std::string& actionName, Window::WindowEvent wev)
{
	for(auto i = m_windowEventMap.begin(); i != m_windowEventMap.end(); /* no ++i */)
	{
		if (i->second == wev)
		{
			auto e = i;
			++i;
			m_windowEventMap.erase(e);
		}
		else
		{
			++i;
		}
	}

	auto i = m_windowEventMap.find(actionName);
	if (i != m_windowEventMap.end())
		m_windowEventMap.erase(i);

	// add new mapping
	m_windowEventMap[actionName] = wev;
}

void
InputManager::bind(const std::string& actionName, EventCallback callback)
{
	auto i = m_eventCallbackMap.find(actionName);
	if (i != m_eventCallbackMap.end())
		m_eventCallbackMap.erase(i);

	// add new mapping
	m_eventCallbackMap[actionName] = callback;
}

void
InputManager::fire()
{
	for(auto x : m_keyboardKeyMap)
	{
		if(Keyboard::checkEvent(x.second))
		{
			if(m_callbackMap.find(x.first)!= m_callbackMap.end())
			{
				(m_callbackMap[x.first])(nullptr, nullptr);
			}
		}
	}

	for(auto x : m_mouseButtonMap)
	{
		if(Mouse::checkEvent(x.second))
		{
			if(m_callbackMap.find(x.first)!= m_callbackMap.end())
			{
				m_callbackMap[x.first](nullptr, nullptr);
			}
		}
	}

	for(auto x : m_windowEventMap)
	{
		if(Window::checkEvent(x.second))
		{
			if(m_callbackMap.find(x.first)!= m_callbackMap.end())
			{
				m_callbackMap[x.first](nullptr, nullptr);
			}
		}
	}

	for(auto x : m_eventCallbackMap)
	{
		if((x.second)())
		{
			if(m_callbackMap.find(x.first)!= m_callbackMap.end())
			{
				m_callbackMap[x.first](nullptr, nullptr);
			}
		}
	}

	//process ranges
	for(auto x : m_mouseRangeMap)
	{
		int i, j;
		switch(x.second)
		{
		case Mouse::RangeEvent::MouseWheel :
			if(Mouse::mouseWheelMoved(&i, &j))
			{
				if(m_callbackMap.find(x.first) != m_callbackMap.end())
					m_callbackMap[x.first](static_cast<void*>(&i), static_cast<void*>(&j));
			}
			break;
		case Mouse::RangeEvent::MouseMotion :
			if(Mouse::mouseMoved(&i, &j))
			{
				if(m_callbackMap.find(x.first) != m_callbackMap.end())
					m_callbackMap[x.first](static_cast<void*>(&i), static_cast<void*>(&j));
			}
			break;
		}
	}
}
