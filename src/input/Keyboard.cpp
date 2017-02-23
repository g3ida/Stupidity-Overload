#include "../../include/input/Keyboard.h"

void
Keyboard::process(SDL_Event& event)
{

	for(int i=0; i < SDL_NUM_SCANCODES; i++)
    {
        m_release[i] = m_press[i] = 0;
    }
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
