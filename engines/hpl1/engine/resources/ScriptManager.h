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

#ifndef HPL_SCRIPT_MANAGER_H
#define HPL_SCRIPT_MANAGER_H

#include "hpl1/engine/resources/ResourceManager.h"

namespace hpl {

class cSystem;
class cResources;
class iScript;

class cScriptManager : public iResourceManager {
public:
	cScriptManager(cSystem *apSystem, cResources *apResources);
	~cScriptManager();

	iResourceBase *Create(const tString &asName);
	/**
	 * Create a new script.
	 * \param asName name of the script.
	 * \return
	 */
	iScript *CreateScript(const tString &asName);

	void Destroy(iResourceBase *apResource);
	void Unload(iResourceBase *apResource);

private:
	cSystem *mpSystem;
	cResources *mpResources;
};

};     // namespace hpl
#endif // HPL_SCRIPT_MANAGER_H
