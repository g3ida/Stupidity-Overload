#ifndef _DEF_INPUT_MANAGER_H_
#define _DEF_INPUT_MANAGER_H_

#include <SDL2/SDL.h>

#include <map>
#include <functional>

#include "Action.h"
#include "State.h"
#include "Keyboard.h"
#include "Mouse.h"

class InputManager
{
public :
	// function callback
	typedef std::function<void(void)> commandCallback;


	void process();
	void process(SDL_Event& ev);
	// make class singleton
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	inline static InputManager& getInstance()
	{
		static InputManager manager;
		return manager;
	}

	void registerCommand(Action action, commandCallback callback);
	void registerCommand(State state, commandCallback callback);

	void bind(Action action, SDL_Scancode code);
	void bind(State state, SDL_Scancode code);

	void bind(Action action, Uint8 button);
	void bind(State state, Uint8 button);

	SDL_Scancode getScancodeAction(Action a) const;
	SDL_Scancode getScancodeState(State s) const;

	Keyboard keyboard;
	Mouse mouse;

private :

	InputManager();

	//void fire(Action action);
	//void fire(State state);

private :
	std::map<Action, commandCallback> m_ActionCallbackMap;
	std::map<State, commandCallback> m_StatesCallbackMap;

	std::map<SDL_Scancode, Action> m_ActionKeyMap;
	std::map<SDL_Scancode, State> m_StatesKeyMap;

	std::map<Uint8, Action> m_ActionButtonMap;
	std::map<Uint8, State> m_StatesButtonMap;

	SDL_Event m_event;
};

#endif //_DEF_INPUT_MANAGER_H_
