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

#ifndef _DEF_GAME_H_
#define _DEF_GAME_H_

#include <SDL2/SDL.h>
#include <memory>

class Game
{
public:
    Game();
    virtual ~Game();
    int exec();

private:
    void init();
    void handleEvents();
    void update();
    void render();
    void cleanUp() noexcept;

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_Event m_event;
    bool m_end = false;
};

#endif //_DEF_GAME_H_
