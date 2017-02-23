#ifndef _DEF_ABSTRACT_GAME_STATE_H_
#define _DEF_ABSTRACT_GAME_STATE_H_

#include <SDL2/SDL.h>

class AbstractGameState
{
public :
	virtual void onEnter(SDL_Renderer* renderer) = 0;
	virtual AbstractGameState* handleEvent(SDL_Event& event) = 0;
	virtual AbstractGameState* update(Uint32 ms) = 0;
	virtual AbstractGameState* render(SDL_Renderer* m_renderer) = 0;
	virtual void onExit() = 0;
	virtual ~AbstractGameState() {};
};

#endif //_DEF_ABSTRACT_GAME_STATE_H_
