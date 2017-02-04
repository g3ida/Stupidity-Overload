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

#ifndef _DEF_UTILITY_H_
#define _DEF_UTILITY_H_

namespace sdl2 {
struct SDL_Deleter {
  void operator()(SDL_Surface*  ptr) { if (ptr) SDL_FreeSurface(ptr); }
  void operator()(SDL_Texture*  ptr) { if (ptr) SDL_DestroyTexture(ptr); }
  void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
  void operator()(SDL_Window*   ptr) { if (ptr) SDL_DestroyWindow(ptr); }
  void operator()(SDL_RWops*    ptr) { if (ptr) SDL_RWclose(ptr); }
};

// Unique Pointers
using SurfacePtr  = std::unique_ptr<SDL_Surface,  SDL_Deleter>;
using TexturePtr  = std::unique_ptr<SDL_Texture,  SDL_Deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, SDL_Deleter>;
using WindowPtr   = std::unique_ptr<SDL_Window,   SDL_Deleter>;
using RWopsPtr    = std::unique_ptr<SDL_RWops,    SDL_Deleter>;
}


#endif // _DEF_UTILITY_H_
