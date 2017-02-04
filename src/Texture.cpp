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

#include "../include/Texture.h"

Texture::Texture(SDL_Renderer* renderer, const std::string& filename) : m_filename(filename)
{
	m_renderer = renderer;
}

Texture::Texture(Texture* texture)
{

}

Texture&&
Texture::operator=(const Texture& texture)
{

}

void
Texture::load(SDL_Renderer* renderer,  const std::string& filename)
{
	if(m_texture != nullptr)
		Texture::free();
	 m_filename = filename;
}

void
Texture::free()
{
	if(m_texture)
		SDL_DestroyTexture(m_texture);
}

void
Texture::draw(int x, int y)
{

}
void
Texture::draw(int x, int y, int w, int h)
{

}

Texture::~Texture()
{
	Texture::free();
}
