#ifndef _DEF_SPRITE_H_
#define _DEF_SPRITE_H_

#include "Texture.h"
#include <SDL2/SDL.h>

class Sprite;
void drawSprite(int x, int y, const Sprite& a, const Texture& t);

class Sprite final
{
public :
	friend void drawSprite(int x, int y, const Sprite& a, const Texture& t);

	Sprite();
	~Sprite();

	void setNumRows(int numRows);
	void setNumCols(int numCols);
	// note that frame numbers vary from to m_numFrames-1
	void setStartFrame(int startFrame);
	void setEndFrame(int endFrame);
	inline void setFps(int fps);
	inline void setCurrentFrame(int currentFrame);

	inline int getCurrentFrame() const;
	inline int getFps() const;

	inline void pause();
	inline void resume();
	void restart();
	inline bool isPaused() const;

	inline void loop(bool doLoop);
	inline void reverse(bool doBackward);

	void update(Uint32 ms);

private :
	int m_numRows = 1;
	int m_numCols = 1;

	int m_numFrames = 1;
	int m_startFrame = 0;
	int m_endFrame = 0;

	bool m_loop = true;
	bool m_paused = false;
	bool m_reverse = false;

	int m_fps = 20; //the current m_fps can be -fps if animation reversed.

	int m_currentFrame = 0;
	unsigned int m_frameTime = 0;
};

inline void
Sprite::setFps(int fps)
{
	m_fps = fps;
}

inline void
Sprite::setCurrentFrame(int currentFrame)
{
	if((currentFrame < m_startFrame) || (currentFrame > m_endFrame))
		return;
	m_currentFrame = currentFrame;
	m_frameTime = 0;
}

inline int
Sprite::getFps() const
{
	return m_fps;
}

inline int
Sprite::getCurrentFrame() const
{
	return m_currentFrame;
}

inline void
Sprite::pause()
{
	m_paused = true;
}

inline void
Sprite::resume()
{
	m_paused = false;
}

inline bool
Sprite::isPaused() const
{
	return m_paused;
}

inline void
Sprite::loop(bool doLoop)
{
	m_loop = doLoop;
}

inline void
Sprite::reverse(bool doReverse)
{
	m_reverse = doReverse;
}

#endif //_DEF_SPRITE_H_