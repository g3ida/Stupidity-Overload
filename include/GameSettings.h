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
