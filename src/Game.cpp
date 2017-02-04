/*
Stupidity Overload
Copyright (C) 2017 Gaïda Mohamed Alaa Eddine <med.gaida@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>

#include "../include/Game.h"
#include "../include/GameSettings.h"
#include "../include/GameException.h"


Game::Game()
{

}

void
Game::init()
{
   	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        throw GameInitExeception(std::string("FATAL ERROR : cannot initialize SDL ! ") + SDL_GetError());


	m_window = SDL_CreateWindow(GameSettings::GameName.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              GameSettings::screenWidth,
                              GameSettings::screenHeight,
                              SDL_WINDOW_SHOWN);
    if(!m_window)
    {
        throw GameInitExeception(std::string("FATAL ERROR : cannot create SDL_Window ! ") + SDL_GetError());
    }


    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if(!m_renderer)
    {
		throw GameInitExeception(std::string("FATAL ERROR : cannot create SDL renderer ! ") + SDL_GetError());
        //return -1; throw sth
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

	SDL_WaitEvent(&m_event);

    if(m_event.window.event == SDL_WINDOWEVENT_CLOSE)
        m_end = true;

}

void
Game::update()
{

}


void
Game::render()
{
    // Drawing

    SDL_SetRenderDrawColor(m_renderer, 0x00, 0xAA, 0xAA, 0xFF);
    SDL_RenderClear(m_renderer);

    SDL_RenderPresent(m_renderer);
}

void
Game::cleanUp() noexcept
{
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
        SDL_Quit();
}


int
Game::exec()
{
    init();
    try
    {
        while(!m_end)
        {
            handleEvents();
            update();
            render();
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
