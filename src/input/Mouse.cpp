#include "../../include/input/Mouse.h"

void
Mouse::process(SDL_Event& event)
{

	m_isLeftPressed = false;
	m_isLeftReleased = false;
	m_isRightPressed = false;
	m_isRightReleased = false;
	m_isMiddlePressed = false;
	m_isMiddleReleased = false;

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

	m_buttonFlags = SDL_GetMouseState(&m_x, &m_y);
}
