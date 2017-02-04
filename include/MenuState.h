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

#ifndef _DEF_MENU_STATE_
#define _DEF_MENU_STATE_

#include "AbstractGameState.h"

class MenuState : public AbstractGameState
{
public :
	virtual void onEnter();
	virtual AbstractGameState* handleEvent();
	virtual AbstractGameState* update();
	virtual AbstractGameState* render();
	virtual void onExit();
};

#endif //_DEF_MENU_STATE_
