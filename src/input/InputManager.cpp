#include "../../include/input/InputManager.h"


InputManager::InputManager() : m_ActionKeyMap(), m_StatesKeyMap(),
							m_ActionButtonMap(), m_StatesButtonMap()
{
	// setup default m_ActionKeyMap values
	bind(Action::Jump, SDL_SCANCODE_UP);

	// setup default m_StatesKeyMap values
	bind(State::MoveLeft, SDL_SCANCODE_LEFT);
	bind(State::MoveRight, SDL_SCANCODE_LEFT);

	// setup default m_ActionButtonMap values

	// setup default m_StatesButtonMap values

}


void
InputManager::process(SDL_Event& ev)
{

		switch(ev.type)
		{
		case SDL_KEYDOWN :
		case SDL_KEYUP :
			keyboard.process(ev);
			break;
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEBUTTONUP :
			mouse.process(ev);
			break;
		}

	// process actions
	for(auto x : m_ActionKeyMap)
	{
		if(keyboard.keyPressed(x.first))
		{
			if(m_ActionCallbackMap.find(x.second)!= m_ActionCallbackMap.end())
			{
				m_ActionCallbackMap[x.second]();
			}
		}
	}

	for(auto x : m_ActionButtonMap)
	{
		if(mouse.buttonPressed(x.first))
		{
			if(m_ActionCallbackMap.find(x.second) != m_ActionCallbackMap.end())
				m_ActionCallbackMap[x.second]();
		}
	}

	// process states
	for(auto x : m_StatesKeyMap)
	{
		if(keyboard.keyDown(x.first))
		{
			if(m_StatesCallbackMap.find(x.second)!= m_StatesCallbackMap.end())
				m_StatesCallbackMap[x.second]();
		}
	}

	for(auto x : m_StatesButtonMap)
	{
		if(mouse.buttonDown(x.first))
		{
			if(m_StatesCallbackMap.find(x.second)!= m_StatesCallbackMap.end())
				m_StatesCallbackMap[x.second]();
		}
	}

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
			keyboard.process(m_event);
			break;
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEBUTTONUP :
			mouse.process(m_event);
			break;
		}
	}

	// process actions
	for(auto x : m_ActionKeyMap)
	{
		if(keyboard.keyPressed(x.first))
		{
			if(m_ActionCallbackMap.find(x.second)!= m_ActionCallbackMap.end())
				m_ActionCallbackMap[x.second]();
		}
	}

	for(auto x : m_ActionButtonMap)
	{
		if(keyboard.keyPressed(x.first))
		{
			if(m_ActionCallbackMap.find(x.second) != m_ActionCallbackMap.end())
				m_ActionCallbackMap[x.second]();
		}
	}


	// process states
	for(auto x : m_StatesKeyMap)
	{
		if(keyboard.keyDown(x.first))
		{
			if(m_StatesCallbackMap.find(x.second)!= m_StatesCallbackMap.end())
				m_StatesCallbackMap[x.second]();
		}
	}

	for(auto x : m_StatesButtonMap)
	{
		if(keyboard.keyDown(x.first))
		{
			if(m_StatesCallbackMap.find(x.second)!= m_StatesCallbackMap.end())
				m_StatesCallbackMap[x.second]();
		}
	}
}

void
InputManager::registerCommand(Action action, commandCallback callback)
{
	auto i = m_ActionCallbackMap.find(action);
	if (i != m_ActionCallbackMap.end())
		m_ActionCallbackMap.erase(i);

	// add new mapping
	m_ActionCallbackMap[action] = std::move(callback);
}

void
InputManager::registerCommand(State state, commandCallback callback)
{

	auto i = m_StatesCallbackMap.find(state);
	if (i != m_StatesCallbackMap.end())
		m_StatesCallbackMap.erase(i);

	// add new mapping
	m_StatesCallbackMap[state] = std::move(callback);
}

void
InputManager::bind(Action action, SDL_Scancode code)
{
	for(auto i = m_ActionKeyMap.begin(); i != m_ActionKeyMap.end(); /* no ++i */)
	{
		if (i->second == action)
		{
			auto e = i;
			++i;
			m_ActionKeyMap.erase(e);
		}
		else
		{
			++i;
		}
	}
	auto i = m_ActionKeyMap.find(code);
	if (i != m_ActionKeyMap.end())
		m_ActionKeyMap.erase(i);

	// add new mapping
	m_ActionKeyMap[code] = action;
}

void
InputManager::bind(State state, SDL_Scancode code)
{
	for(auto i = m_StatesKeyMap.begin(); i != m_StatesKeyMap.end(); /* no ++i */)
	{
		if (i->second == state)
		{
			auto e = i;
			++i;
			m_StatesKeyMap.erase(e);
		}
		else
		{
			++i;
		}
	}
	auto i = m_StatesKeyMap.find(code);
	if (i != m_StatesKeyMap.end())
		m_StatesKeyMap.erase(i);

	// add new mapping
	m_StatesKeyMap[code] = state;
}

void
InputManager::bind(Action action, Uint8 button)
{
	for(auto i = m_ActionButtonMap.begin(); i != m_ActionButtonMap.end(); /* no ++i */)
	{
		if (i->second == action)
		{
			auto e = i;
			++i;
			m_ActionButtonMap.erase(e);
		}
		else
		{
			++i;
		}
	}
	auto i = m_ActionButtonMap.find(button);
	if (i != m_ActionButtonMap.end())
		m_ActionButtonMap.erase(i);

	// add new mapping
	m_ActionButtonMap[button] = action;
}

void
InputManager::bind(State state, Uint8 button)
{
	for(auto i = m_StatesButtonMap.begin(); i != m_StatesButtonMap.end(); /* no ++i */)
	{
		if (i->second == state)
		{
			auto e = i;
			++i;
			m_StatesButtonMap.erase(e);
		}
		else
		{
			++i;
		}
	}
	auto i = m_StatesButtonMap.find(button);
	if (i != m_StatesButtonMap.end())
		m_StatesButtonMap.erase(i);

	// add new mapping
	m_StatesButtonMap[button] = state;
}

SDL_Scancode
InputManager::getScancodeAction(Action a) const
{
	for(const auto& i : m_ActionKeyMap)
	{
		if (i.second == a)
		{
			return i.first;
		}
	}
	return SDL_SCANCODE_UNKNOWN;
}

SDL_Scancode
InputManager::getScancodeState(State s) const
{
	for(const auto& i : m_StatesKeyMap)
	{
		if (i.second == s)
		{
			return i.first;
		}
	}
	return SDL_SCANCODE_UNKNOWN;
}
