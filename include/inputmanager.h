#ifndef _DEF_INPUT_MANAGER_H_
#define _DEF_INPUT_MANAGER_H_

#include <SDL2/SDL.h>

#include <map>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class InputManager
{
public :
	/*
	 The keyboard class
	*/
	class Keyboard
	{
	public :
		//type declatations
        enum class KeyStatus
		{
			KeyPress,
			KeyRelease,
			KeyDown,
			KeyUp
		};
		using KeyEvent = std::pair<KeyStatus, SDL_Scancode>;

		// this class is to simplify your life :p
		class Event
		{
		public :
			inline static KeyEvent keyPress(SDL_Scancode code)
			{
				return std::make_pair(KeyStatus::KeyPress, code);
			}

			inline static KeyEvent keyRelease(SDL_Scancode code)
			{
				return std::make_pair(KeyStatus::KeyRelease, code);
			}

			inline static KeyEvent keyDown(SDL_Scancode code)
			{
				return std::make_pair(KeyStatus::KeyDown, code);
			}

			inline static KeyEvent keyUp(SDL_Scancode code)
			{
				return std::make_pair(KeyStatus::KeyUp, code);
			}
		};

		// static functions
		static inline bool checkEvent(const KeyEvent& kev)
		{
			switch (kev.first)
			{
				case KeyStatus::KeyPress :
					return keyPressed(kev.second); break;
				case KeyStatus::KeyRelease :
					return keyReleased(kev.second); break;
				case KeyStatus::KeyDown :
					return keyDown(kev.second); break;
				case KeyStatus::KeyUp :
					return keyUp(kev.second); break;
			}
		}

		static inline bool keyPressed(const SDL_Scancode& k)
		{
			return m_press[k];
		}

		static inline bool keyReleased(const SDL_Scancode& k)
		{
			return m_release[k];
		}

		static inline bool keyDown(const SDL_Scancode& k)
		{
			if(m_keystates == nullptr) return false;
			return m_keystates[k];
		}

		static inline bool keyUp(const SDL_Scancode& k)
		{
			if(m_keystates == nullptr) return false;
			return !m_keystates[k];
		}

		static inline bool keyPressed(const SDL_Keycode& k)
		{
			return m_press[SDL_GetScancodeFromKey(k)];
		}

		static inline bool keyReleased(const SDL_Keycode& k)
		{
			return m_release[SDL_GetScancodeFromKey(k)];
		}

		static inline bool keyDown(const SDL_Keycode& k)
		{
			if(m_keystates == nullptr) return false;
			return m_keystates[SDL_GetScancodeFromKey(k)];
		}

		static inline bool keyUp(const SDL_Keycode& k)
		{
			if(m_keystates == nullptr) return false;
			return !m_keystates[SDL_GetScancodeFromKey(k)];
		}

		static void process(SDL_Event& event);
		static void clear();

	private :
		static Uint8 m_press[SDL_NUM_SCANCODES];
		static Uint8 m_release[SDL_NUM_SCANCODES];
		static const Uint8 *m_keystates;
	};

	/*
	 The Mouse class
	*/
	class Mouse
	{
	public :
		// type declarations
		enum class ButtonStatus
		{
			ButtonPress,
			ButtonRelease,
			ButtonDown,
			ButtonUp
		};
		using MouseEvent = std::pair<ButtonStatus, Uint8>;

		// this class is to simplify your life :p
		class Event
		{
		public :
			inline static MouseEvent buttonPress(Uint8 button)
			{
				return std::make_pair(ButtonStatus::ButtonPress, button);
			}

			inline static MouseEvent buttonRelease(Uint8 button)
			{
				return std::make_pair(ButtonStatus::ButtonRelease, button);
			}

			inline static MouseEvent buttonDown(Uint8 button)
			{
				return std::make_pair(ButtonStatus::ButtonDown, button);
			}

			inline static MouseEvent buttonUp(Uint8 button)
			{
				return std::make_pair(ButtonStatus::ButtonUp, button);
			}
		};

		enum class RangeEvent
		{
			MouseMotion,
			MouseWheel
		};

		// static functions
		static inline bool checkEvent(const MouseEvent& mev)
		{
			switch (mev.first)
			{
				case ButtonStatus::ButtonPress :
					return buttonPressed(mev.second); break;
				case ButtonStatus::ButtonRelease :
					return buttonReleased(mev.second); break;
				case ButtonStatus::ButtonDown :
					return buttonDown(mev.second); break;
				case ButtonStatus::ButtonUp :
					return buttonUp(mev.second); break;
			}
		}

		static inline int getX()
		{
			return m_x;
		}

		static inline int getY()
		{
			return m_y;
		}
		// button down
		static inline bool leftButtonDown()
		{
			return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_LEFT));
		}

		static inline bool rightButtonDown()
		{
			return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_RIGHT));
		}

		static inline bool middleButtonDown()
		{
			return (m_buttonFlags && SDL_BUTTON(SDL_BUTTON_MIDDLE));
		}

		// button pressed
		static inline bool leftButtonPressed()
		{
			return m_isLeftPressed;
		}

		static inline bool rightButtonPressed()
		{
			return m_isRightPressed;
		}

		static inline bool middleButtonPressed()
		{
			return m_isMiddlePressed;
		}

		// button released
		static inline bool leftButtonReleased()
		{
			return m_isLeftReleased;
		}

		static inline bool rightButtonReleased()
		{
			return m_isRightReleased;
		}

		static inline bool middleButtonReleased()
		{
			return m_isMiddleReleased;
		}

		// other useful functions
		static inline bool buttonPressed(Uint8 button)
		{
			if(button == SDL_BUTTON_LEFT) return leftButtonPressed();
			if(button == SDL_BUTTON_RIGHT) return rightButtonPressed();
			if(button == SDL_BUTTON_MIDDLE) return middleButtonPressed();
			return false;
		}

		static inline bool buttonReleased(Uint8 button)
		{
			if(button == SDL_BUTTON_LEFT) return leftButtonReleased();
			if(button == SDL_BUTTON_RIGHT) return rightButtonReleased();
			if(button == SDL_BUTTON_MIDDLE) return middleButtonReleased();
			return false;
		}

		static inline bool buttonDown(Uint8 button)
		{
			return (button && m_buttonFlags);
		}

		static inline bool buttonUp(Uint8 button)
		{
			return (!buttonDown(button));
		}

		static inline bool mouseMoved(int *dx, int *dy)
		{
			if(m_mouseMoved)
			{
				if(dx) *dx = m_dx;
				if(dy) *dy = m_dy;
				return true;
			}
			return false;
		}

		static inline bool mouseWheelMoved(int *xwheel, int *ywheel)
		{
			if(m_mouseWheel)
			{
				if(xwheel) *xwheel = m_xwheel;
				if(ywheel) *ywheel = m_ywheel;
				return true;
			}
			return false;
		}

		static void process(SDL_Event& event);
		static void clear();

	private :
			static int m_buttonFlags;

			static int m_x;
			static int m_y;

			static bool m_isLeftPressed;
			static bool m_isLeftReleased;

			static bool m_isRightPressed;
			static bool m_isRightReleased;

			static bool m_isMiddlePressed;
			static bool m_isMiddleReleased;

			static bool m_mouseMoved;
			static int m_dx;
			static int m_dy;

			static bool m_mouseWheel;
			static int m_xwheel;
			static int m_ywheel;
	};

	/*
	 The Window class
	*/
	class Window
	{
	public :
		//type declarations
		enum class WindowEvent
		{
			QuitRequest,
			Shown,
			Hidden,
			Minimized,
			Maximized,
			Exposed,
			Moved,
			Resized,
			SizeChanged,
			Restored,
			GainMouseFocus,
			LostMouseFocus,
			GainKeyboardFocus,
			LostKeyboardFocus,
			TakeFocus,
			None,
			//other events will be added later, at least I wish...
		};

	    //convert Input::Window::WindowEvent into SDL_WindowEventID
		static constexpr SDL_WindowEventID Event2SDLWindowEventID(WindowEvent event)
		{
			switch(event)
			{
			case WindowEvent::QuitRequest :
				return SDL_WINDOWEVENT_CLOSE; break;
			case WindowEvent::Shown :
				return SDL_WINDOWEVENT_SHOWN; break;
			case WindowEvent::Hidden :
				return SDL_WINDOWEVENT_HIDDEN; break;
			case WindowEvent::Maximized :
				return SDL_WINDOWEVENT_MAXIMIZED; break;
			case WindowEvent::Minimized :
				return SDL_WINDOWEVENT_MINIMIZED; break;
			case WindowEvent::Exposed :
				return SDL_WINDOWEVENT_EXPOSED; break;
			case WindowEvent::Moved :
				return SDL_WINDOWEVENT_MOVED; break;
			case WindowEvent::Resized :
				return SDL_WINDOWEVENT_RESIZED; break;
			case WindowEvent::SizeChanged :
				return SDL_WINDOWEVENT_SIZE_CHANGED; break;
			case WindowEvent::Restored :
				return SDL_WINDOWEVENT_RESTORED; break;
			case WindowEvent::GainMouseFocus :
				return SDL_WINDOWEVENT_ENTER; break;
			case WindowEvent::LostMouseFocus :
				return SDL_WINDOWEVENT_LEAVE; break;
			case WindowEvent::GainKeyboardFocus :
				return SDL_WINDOWEVENT_FOCUS_GAINED; break;
			case WindowEvent::LostKeyboardFocus :
				return SDL_WINDOWEVENT_FOCUS_LOST; break;
			case WindowEvent::TakeFocus :
				return SDL_WINDOWEVENT_TAKE_FOCUS; break;
			default :
			    return SDL_WINDOWEVENT_NONE;
			}
			return SDL_WINDOWEVENT_NONE;
		}

		static constexpr WindowEvent SDLWindowEventID2Event(Uint8 event)
		{
			switch(event)
			{
			case SDL_WINDOWEVENT_CLOSE :
				return WindowEvent::QuitRequest; break;
			case SDL_WINDOWEVENT_SHOWN :
				return WindowEvent::Shown; break;
			case SDL_WINDOWEVENT_HIDDEN :
				return WindowEvent::Hidden; break;
			case SDL_WINDOWEVENT_MAXIMIZED :
				return WindowEvent::Maximized; break;
			case SDL_WINDOWEVENT_MINIMIZED :
				return WindowEvent::Minimized; break;
			case SDL_WINDOWEVENT_EXPOSED :
				return WindowEvent::Exposed; break;
			case SDL_WINDOWEVENT_MOVED :
				return WindowEvent::Moved; break;
			case SDL_WINDOWEVENT_RESIZED :
				return WindowEvent::Resized; break;
			case SDL_WINDOWEVENT_SIZE_CHANGED :
				return WindowEvent::SizeChanged; break;
			case SDL_WINDOWEVENT_RESTORED :
				return WindowEvent::Restored; break;
			case SDL_WINDOWEVENT_ENTER :
				return WindowEvent::GainMouseFocus; break;
			case SDL_WINDOWEVENT_LEAVE :
				return WindowEvent::LostMouseFocus; break;
			case SDL_WINDOWEVENT_FOCUS_GAINED :
				return WindowEvent::GainKeyboardFocus; break;
			case SDL_WINDOWEVENT_FOCUS_LOST :
				return WindowEvent::LostKeyboardFocus; break;
			case SDL_WINDOWEVENT_TAKE_FOCUS :
				return WindowEvent::TakeFocus; break;
			default :
				return WindowEvent::None;
			}
			return WindowEvent::None;
		}

		static inline bool checkEvent(WindowEvent wevent)
		{
			return (std::find(m_eventList.begin(), m_eventList.end(), wevent) != m_eventList.end());
		}

		static void process(SDL_Event& event);
		static void clear();

	private :
		static std::vector<WindowEvent> m_eventList;
	};

	/*
	 The InputManager class
	*/
	//function callback
	typedef std::function<void(void*, void*)> CommandCallback;
	//used for user defined events
	typedef std::function<bool(void)> EventCallback;

	void process();
	void clear();

	// make class singleton
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	inline static InputManager& getInstance()
	{
		static InputManager manager;
		return manager;
	}

	// register events
	void registerCommand(const std::string& actionName, CommandCallback callback);
	// and a move version for more speed
	void registerCommand(std::string&& actionName, CommandCallback callback);


	// binding functions
	void bind(const std::string& actionName, Keyboard::KeyEvent kev);
	void bind(const std::string& actionName, Mouse::MouseEvent mev);
	void bind(const std::string& actionName, Mouse::RangeEvent rev);
	void bind(const std::string& actionName, Window::WindowEvent wev);
	void bind(const std::string& actionName, EventCallback callback);

	void fire();

private :
	// private constructor to make class singleton
	InputManager();

private :
	// callbacks containers
	std::map<std::string, CommandCallback> m_callbackMap;

	// key mapping
	std::map<std::string, Keyboard::KeyEvent> m_keyboardKeyMap;
	// mouse button mapping
	std::map<std::string, Mouse::MouseEvent> m_mouseButtonMap;
	// mouse ranges mapping
	std::map<std::string, Mouse::RangeEvent> m_mouseRangeMap;
	// window events mapping
	std::map<std::string, Window::WindowEvent> m_windowEventMap;
	// user callback events mapping
	std::map<std::string, EventCallback> m_eventCallbackMap;
	//std::list<std::pair<EventCallback, std::string>> m_eventCallbackMap;

	// the event variable
	SDL_Event m_event;
};

#endif //_DEF_INPUT_MANAGER_H_
