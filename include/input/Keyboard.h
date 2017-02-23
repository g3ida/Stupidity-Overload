#ifndef _DEF_KEYBOARD_H_
#define _DEF_KEYBOARD_H_

#include <SDL2/SDL.h>

class Keyboard
{
public :
	inline bool keyPressed(const SDL_Scancode& k) const
	{
		return m_press[k];
	}

	inline bool keyReleased(const SDL_Scancode& k) const
	{
		return m_release[k];
	}

	inline bool keyDown(const SDL_Scancode& k) const
	{
		if(m_keystates == nullptr) return false;
		return m_keystates[k];
	}

	inline bool keyUp(const SDL_Scancode& k) const
	{
		if(m_keystates == nullptr) return false;
		return !m_keystates[k];
	}

	inline bool keyPressed(const SDL_Keycode& k) const
	{
		return m_press[SDL_GetScancodeFromKey(k)];
	}

	inline bool keyReleased(const SDL_Keycode& k) const
	{
		return m_release[SDL_GetScancodeFromKey(k)];
	}

	inline bool keyDown(const SDL_Keycode& k) const
	{
		if(m_keystates == nullptr) return false;
		return m_keystates[SDL_GetScancodeFromKey(k)];
	}

	inline bool keyUp(const SDL_Keycode& k) const
	{
		if(m_keystates == nullptr) return false;
		return !m_keystates[SDL_GetScancodeFromKey(k)];
	}

	void process(SDL_Event& event);

private :
	Uint8 m_press[SDL_NUM_SCANCODES];
	Uint8 m_release[SDL_NUM_SCANCODES];
	const Uint8 *m_keystates = nullptr;
};

#endif //_DEF_KEYBOARD_H_
