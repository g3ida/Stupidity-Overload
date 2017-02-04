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

#ifndef _DEF_TEXTURE_H_
#define _DEF_TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>

class Texture
{
public :
	Texture(SDL_Renderer* renderer, const std::string& filename);

	Texture(Texture* texture);
	Texture&& operator=(const Texture& texture);

	void load(SDL_Renderer* renderer,  const std::string& filename);
	void free();

	void draw(int x, int y);
	void draw(int x, int y, int w, int h);

	~Texture();
private :
	std::string m_filename;
	int m_width = 0;
	int m_height = 0;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};

#endif //_DEF_TEXTURE_H_
