#ifndef _DEF_GAME_H_
#define _DEF_GAME_H_

#include <SDL2/SDL.h>
#include <stack>
#include "../include/AbstractGameState.h"

class Game
{
public:
    Game();
    virtual ~Game();
    int exec();

private:
    void init();
    void handleEvents();
    void update(Uint32 ms);
    void render();
    void cleanUp() noexcept;

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_Event m_event;
    bool m_end = false;
	std::stack<AbstractGameState*> m_states;
};

#endif //_DEF_GAME_H_
