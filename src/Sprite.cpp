#include "../include/Sprite.h"
#include "../include/Logger.h"

Sprite::Sprite()
{

}

Sprite::~Sprite()
{

}

void
Sprite::setNumRows(int numRows)
{
	if(m_numRows == 0)
		return;
	m_numRows = numRows;
	m_numFrames = m_numRows * m_numCols;
	m_startFrame = 1;
	m_endFrame = m_numFrames - 1;

	restart();
}

void
Sprite::setNumCols(int numCols)
{
	if(m_numCols == 0)
		return;
	m_numCols = numCols;
	m_numFrames = m_numRows * m_numCols;
	m_startFrame = 1;
	m_endFrame = m_numFrames - 1;

	restart();

}

void
Sprite::setStartFrame(int startFrame)
{
	if(startFrame > m_numFrames)
		return;
	
	m_startFrame = startFrame;

	if(m_endFrame < m_startFrame)
		m_endFrame = m_startFrame;
	
	if(m_currentFrame < m_startFrame)
		m_currentFrame = m_startFrame;

	m_numFrames = m_endFrame - m_startFrame + 1;

	restart();
}

void
Sprite::setEndFrame(int endFrame)
{
	if(endFrame > m_numFrames || endFrame < m_startFrame)
		return;
	
	m_endFrame = endFrame;
	
	if(m_currentFrame > m_endFrame)
		m_currentFrame = m_endFrame;

	m_numFrames = m_endFrame - m_startFrame + 1;

	restart();
}

void
Sprite::restart()
{
	if(m_reverse)
	{
		m_currentFrame = m_endFrame;
	}
	else
	{
		m_currentFrame = m_startFrame;

	}
	m_frameTime = 0;
}

void
Sprite::update(Uint32 ms)
{
	if(m_paused)
		return;
	
	if(m_loop)
	{
		if(m_reverse)
		{
			int tmp = ((ms + m_frameTime) * m_fps) / 1000;
			if(tmp > m_currentFrame - m_startFrame)
				m_currentFrame = m_endFrame + 1 - tmp % m_numFrames; // I don't know why it works when i added +1
			else
				m_currentFrame -= tmp;
			
			m_frameTime = ((ms + m_frameTime) % (1000 / m_fps));
		}
		else
		{
			m_currentFrame = ((m_currentFrame - m_startFrame + (((ms + m_frameTime) * m_fps) / 1000)) % m_numFrames) + m_startFrame;
			m_frameTime = ((ms + m_frameTime) % (1000 / m_fps));
		}
	}
	else
	{
		if(m_reverse)
		{
			m_currentFrame = ((m_currentFrame - (((ms + m_frameTime) * m_fps) / 1000)));
			m_frameTime = ((ms + m_frameTime) % (1000 / m_fps));

			if(m_currentFrame < m_startFrame)
			{
				m_currentFrame = m_startFrame;
				m_frameTime = 0;
			}
		}
		else
		{
			m_currentFrame = ((m_currentFrame + (((ms + m_frameTime) * m_fps) / 1000)));
			m_frameTime = ((ms + m_frameTime) % (1000 / m_fps));

			if(m_currentFrame > m_endFrame)
			{
				m_currentFrame = m_endFrame;
				m_frameTime = 0;
			}
		}
	}
	LOG << "frame number : " << m_currentFrame << "\n";
}

void
drawSprite(int x, int y, const Sprite& a, const Texture& t)
{
	int frameWidth = t.getWidth() / a.m_numCols;
	int frameHeight = t.getHeight() / a.m_numRows;

	int px = (a.m_currentFrame %  a.m_numCols) * frameWidth;
	int py = (a.m_currentFrame /  a.m_numCols) * frameHeight;
	t.draw(px, py, frameWidth, frameHeight, x, y);
}
