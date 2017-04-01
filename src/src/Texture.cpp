#include "../include/Texture.h"
#include "../include/GameException.h"
#include <string>

Texture::Texture() : m_filename()
{
	// do nothing
}

Texture::Texture(SDL_Renderer* renderer, const std::string& filename) : m_filename(filename)
{
	m_renderer = renderer;
	if(m_renderer == nullptr)
		throw GameGraphicsException(std::string("GRAPHICS ERROR : bad renderer passed to the texture : ") + filename);

	try
	{
		Texture::load(renderer,  filename);
	} catch (GameGraphicsException& e)
	{
		throw;
	}
}

void
Texture::load(SDL_Renderer* renderer,  const std::string& filename)
{
	if(m_texture != nullptr)
		Texture::free();

	m_renderer = renderer;

	m_filename = filename;
	if((m_texture = IMG_LoadTexture(renderer, filename.c_str())) == nullptr)
	{
		m_filename = "";
		throw GameGraphicsException(std::string("GRAPHICS ERROR : unable to load texture : ") + filename + IMG_GetError());
	}
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

	LOG ("loaded texture ", filename , " : " , m_width , "--" , m_height , '\n');
}

void
Texture::free()
{
	if(m_texture != nullptr)
	{
		LOG("deleted texture ", m_filename, '\n');
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
	m_filename = "";
}

void
Texture::draw(int x, int y) const
{
	SDL_Rect dest = {x, y, int(m_width * m_scaleX), int(m_height * m_scaleY)};
	SDL_RenderCopy(m_renderer, m_texture, nullptr, &dest);
}

void
Texture::draw(int x, int y, int w, int h) const
{
	if(m_texture != nullptr && m_renderer != nullptr)
	{
		SDL_Rect dest = {x, y, w, h};
		SDL_RenderCopy(m_renderer, m_texture, nullptr, &dest);
	}
}

void
Texture::draw(int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW, int destH) const
{
	if(m_texture != nullptr)
	{
		if(destW == -1)
			destW = int(srcW * m_scaleX);

		if(destH == -1)
			destH = int(srcH * m_scaleY);

		SDL_Rect dest = {destX, destY, destW, destH};
		SDL_Rect src = {srcX, srcY, srcW, srcH};

		SDL_RenderCopy(m_renderer, m_texture, &src, &dest);
	}
}


Texture::~Texture()
{
	Texture::free();
}

