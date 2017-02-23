#ifndef _DEF_MOUSE_H_
#define _DEF_MOUSE_H_

#include <SDL2/SDL.h>

class Mouse
{
public :
	inline int getX()
	{
		return m_x;
	}

	inline int getY()
	{
		return m_y;
	}
	// button down
	inline bool leftButtonDown() const
	{
		return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_LEFT));
	}

	inline bool rightButtonDown() const
	{
		return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_RIGHT));
	}

	inline bool middleButtonDown() const
	{
		return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	// button pressed
	inline bool leftButtonPressed() const
	{
		return m_isLeftPressed;
	}

	inline bool rightButtonPressed() const
	{
		return m_isRightPressed;
	}

	inline bool middleButtonPressed() const
	{
		return m_isMiddlePressed;
	}

	// button released
	inline bool leftButtonReleased() const
	{
		return m_isLeftReleased;
	}

	inline bool rightButtonReleased() const
	{
		return m_isRightReleased;
	}

	inline bool middleButtonReleased() const
	{
		return m_isMiddleReleased;
	}

	// other useful functions
	inline bool buttonPressed(Uint8 button) const
	{
		if(button == SDL_BUTTON_LEFT) return leftButtonPressed();
		if(button == SDL_BUTTON_RIGHT) return rightButtonPressed();
		if(button == SDL_BUTTON_MIDDLE) return middleButtonPressed();
		return false;
	}

	inline bool buttonDown(Uint8 button) const
	{
		return (button && m_buttonFlags);
	}

	void process(SDL_Event& event);

private :
		int m_buttonFlags = 0;

		int m_x = 0;
		int m_y = 0;

		bool m_isLeftPressed = false;
		bool m_isLeftReleased = false;

		bool m_isRightPressed = false;
		bool m_isRightReleased = false;

		bool m_isMiddlePressed = false;
		bool m_isMiddleReleased = false;
};

#endif //_DEF_MOUSE_H_
