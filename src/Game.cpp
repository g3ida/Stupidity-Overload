#include <iostream>
#include <new>

#include "../include/Game.h"
#include "../include/GameSettings.h"
#include "../include/GameException.h"
#include "../include/MenuState.h"

// for logging
#include "../include/logging/Log.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game()
{

}

void
Game::init()
{

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        throw GameInitExeception(std::string("INIT ERROR : cannot initialize SDL ! ") + SDL_GetError());

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw GameInitExeception(std::string("INIT ERROR : IMG_Init: Failed to init required png support ! ") + IMG_GetError());
	}

	m_window = SDL_CreateWindow(GameSettings::GameName.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              GameSettings::screenWidth,
                              GameSettings::screenHeight,
                              SDL_WINDOW_SHOWN | (GameSettings::isFullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if(!m_window)
    {
        throw GameInitExeception(std::string("INIT ERROR : cannot create SDL_Window ! ") + SDL_GetError());
    }


    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(!m_renderer)
    {
		throw GameInitExeception(std::string("FATAL ERROR : cannot create SDL renderer ! ") + SDL_GetError());
    }

	try
	{
		// creating start menu
		m_states.push(new MenuState());
		m_states.top()->onEnter(m_renderer);
	}
	catch(std::bad_alloc& e)
	{
		throw;
	}
}
void
Game::handleEvents()
{
    /*
	while(SDL_PollEvent(&m_event))
	{
		if(m_event.window.event == SDL_WINDOWEVENT_CLOSE)
			m_end = true;
	}
	*/

	//SDL_WaitEvent(&m_event);

    if(m_event.window.event == SDL_WINDOWEVENT_CLOSE)
    {
        m_end = true;
    }
	m_states.top()->handleEvent(m_event);

}

void
Game::update(Uint32 ms)
{
	m_states.top()->update(ms);
}


void
Game::render()
{

	// Clear the renderer with white
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xAA, 0xAA, 0xFF);
    SDL_RenderClear(m_renderer);

	m_states.top()->render(m_renderer);

	// Update renderer
    SDL_RenderPresent(m_renderer);
}

void
Game::cleanUp() noexcept
{

	while(!m_states.empty())
	{
		m_states.top()->onExit();
		delete m_states.top();
		m_states.pop();
	}

   if(m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if(m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    if(SDL_WasInit(0))
	{
		// I have put the IMG_Quit here because the SDL_image won't get
		// initialized unless SDL was initialized; i might have come up
		// with a better solution but this will work fine in almost all
		// cases.
		IMG_Quit();
        SDL_Quit();
	}
}


int
Game::exec()
{
    init();
	Uint32 currentTime = SDL_GetTicks();
	Uint32 lastTime = 0;

	Uint32 delayTime = (1000 / GameSettings::numFPS);

    try
    {
        while(!m_end)
        {
			while(SDL_PollEvent(&m_event))
			{
	            handleEvents();
			}

			currentTime = SDL_GetTicks();
			Uint32 deltaTime = currentTime - lastTime;
			if (deltaTime >= delayTime)
			{
				update(deltaTime);
				render();
				lastTime = currentTime;
			}
			else
			{
				SDL_Delay(delayTime - deltaTime);
			}
        }

    } catch(const std::exception& e)
    {
		std::cerr << e.what();
		cleanUp();
		return -1;
    }
    cleanUp();

    return 0;
}

Game::~Game()
{

}
