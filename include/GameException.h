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

#ifndef _DEF_GAME_EXCEPTION_H_
#define _DEF_GAME_EXCEPTION_H_

#include <exception>
#include <string>

class GameException : public std::exception
{
public :
	GameException(const std::string& s) : m_msg(s) {}
    const char* what() const noexcept {return m_msg.c_str();}
private :
	std::string m_msg;
};

class GameInitExeception : public GameException
{
public :
    using GameException::GameException;
    //GameInitExeception(const std::string& s) : GameException(s) {}
};

#endif // _DEF_GAME_EXCEPTION_H_
