/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 */

#ifndef HPL_LOWLEVELINPUT_SDL_H
#define HPL_LOWLEVELINPUT_SDL_H

#include "hpl1/engine/input/LowLevelInput.h"
#include <list>

//#include "SDL/SDL.h"
#include "temp-types.h"

namespace hpl {

class iLowLevelGraphics;

class cLowLevelInputSDL : public iLowLevelInput {
public:
	cLowLevelInputSDL(iLowLevelGraphics *apLowLevelGraphics);
	~cLowLevelInputSDL();

	void LockInput(bool abX);

	void BeginInputUpdate();
	void EndInputUpdate();

	iMouse *CreateMouse();
	iKeyboard *CreateKeyboard();

public:
	std::list<SDL_Event> mlstEvents;

private:
	iLowLevelGraphics *mpLowLevelGraphics;
};
};     // namespace hpl
#endif // HPL_LOWLEVELINPUT_SDL_H
