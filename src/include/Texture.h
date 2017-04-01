#ifndef _DEF_TEXTURE_H_
#define _DEF_TEXTURE_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/logging/Log.h"

class Texture
{
public :
	Texture();
	Texture(SDL_Renderer* renderer, const std::string& filename);

	// prevent copying and assignment operations
	Texture(Texture* texture) = delete;
	Texture&& operator=(const Texture& texture) = delete;

	void load(SDL_Renderer* renderer,  const std::string& filename);
	void free();

	inline void setScale(float scaleX, float scaleY= -1)
	{
		if(scaleY == -1) scaleY = scaleX;
		if(scaleX < 0 || scaleY < 0) return;
		m_scaleX = scaleX;
		m_scaleY = scaleY;
	}

	inline float getScaleX() const {return m_scaleX;}
	inline float getScaleY() const {return m_scaleY;}

	void draw(int x, int y) const;
	void draw(int x, int y, int w, int h) const;
	void draw(int srcX, int srcY, int srcW, int srcH, int destX, int destY, int destW=-1, int destH=-1) const;

	inline int getWidth() const {return m_width;}
	inline int getHeight() const {return m_height;}
	inline const std::string& getFilename() const {return m_filename;}


	~Texture();
private :
	std::string m_filename;

	int m_width = 0;
	int m_height = 0;
	float m_scaleX = 1.0;
	float m_scaleY = 1.0;

	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;
};

#endif //_DEF_TEXTURE_H_
