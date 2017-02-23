#ifndef _DEF_GAME_SETTINGS_H_
#define _DEF_GAME_SETTINGS_H_

#include <string>

class GameSettings
{
public :
	//avoid instantiation and copying
	GameSettings() = delete;
	GameSettings(const GameSettings&) = delete;
	GameSettings&& operator=(const GameSettings&) = delete;

	//loading and saving sttings
	static void load(const std::string& filename);
	static void save(const std::string& filename);
	static void reset(void);

public :
	static unsigned int screenWidth;
	static unsigned int screenHeight;
	static bool isFullscreen;
	static unsigned int numFPS;
	static const std::string GameName;
	static const std::string GameVersion;
	static unsigned int MusicVolume;
	static unsigned int SoundVolume;
};

#endif //_DEF_GAME_SETTINGS_H_
