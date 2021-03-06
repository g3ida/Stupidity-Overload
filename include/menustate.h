#ifndef _DEF_MENU_STATE_
#define _DEF_MENU_STATE_

#include "AbstractGameState.h"
#include "Sprite.h"

class MenuState : public AbstractGameState
{
public :
  MenuState(){};
	virtual void onEnter(SDL_Renderer* renderer);
	virtual AbstractGameState* handleEvent();
	virtual AbstractGameState* update(Uint32 ms);
	virtual AbstractGameState* render(SDL_Renderer* m_renderer);
	virtual void onExit();

private :
    bool isleft = false;
	Sprite s, l, r;
	int x = 300;
	Texture t;
};

#endif //_DEF_MENU_STATE_
