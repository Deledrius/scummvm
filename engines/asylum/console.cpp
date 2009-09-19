/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

// Console module

#include "asylum/asylum.h"
#include "asylum/console.h"
#include "asylum/shared.h"

namespace Asylum {

extern int g_debugPolygons;
extern int g_debugBarriers;

Console::Console(AsylumEngine *vm) : GUI::Debugger() {
	_vm = vm;

	DCmd_Register("video",			WRAP_METHOD(Console, cmdPlayVideo));
	DCmd_Register("script",			WRAP_METHOD(Console, cmdRunScript));
	DCmd_Register("scene",			WRAP_METHOD(Console, cmdChangeScene));
	DCmd_Register("flags",			WRAP_METHOD(Console, cmdShowFlags));
	DCmd_Register("toggle_flag",	WRAP_METHOD(Console, cmdToggleFlag));
	DCmd_Register("dump_action",	WRAP_METHOD(Console, cmdDumpActionArea));

	DVar_Register("showpolygons",  &g_debugPolygons, DVAR_INT, 0);
	DVar_Register("showbarriers",  &g_debugBarriers, DVAR_INT, 0);
}

Console::~Console() {
}

bool Console::cmdDumpActionArea(int argc, const char **argv) {

	if (argc == 2) {
		// TODO Get an action area by index/id
	} else {
		for (uint32 i = 0; i < Shared.getScene()->worldstats()->numActions; i++) {
			ActionArea *a = &Shared.getScene()->worldstats()->actions[i];
			printActionAreaStats(a);
		}
	}

	return true;
}

void Console::printActionAreaStats(ActionArea *a) {
	DebugPrintf("id[%d] name[%s] field01[%d] field02[%d] field40[%d] field44[%d] flags[%d] \n"
				"actionListIdx1[%d] actionListIdx2[%d] actionType[%d] field_7C[%d] polyIdx[%d]\n"
				"field_84[%d] field_88[%d] soundResId[%d] field_90[%d] palette[%d] volume[%d]\n\n",
			a->id,
			a->name,
			a->field01,
			a->field02,
			a->field_40,
			a->field_44,
			a->flags,
			a->actionListIdx1,
			a->actionListIdx2,
			a->actionType,
			//a->flagNums[10],
			a->field_7C,
			a->polyIdx,
			a->field_84,
			a->field_88,
			a->soundResId,
			a->field_90,
			a->paletteValue,
			//a->array[5],
			a->volume);
}

bool Console::cmdShowFlags(int argc, const char **argv) {
	for (int i = 0; i < 1512; i++) {
		if (Shared.isGameFlagSet(i)) {
			DebugPrintf("Game Flag %d is Active\n", i);
		}
	}

	return true;
}

bool Console::cmdToggleFlag(int argc, const char **argv) {
	if (argc != 2 || atoi(argv[1]) > 1512 || atoi(argv[1]) < 0) {
		DebugPrintf("Enter a value between 0 and 1512\n");
		return true;
	}
	Shared.toggleGameFlag(atoi(argv[1]));
	DebugPrintf("Flag %d == %d\n", atoi(argv[1]), Shared.isGameFlagSet(atoi(argv[1])));

	return true;
}

bool Console::cmdPlayVideo(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Usage %s <video number>\n", argv[0]);
		return true;
	}
	
	ScriptMan.delayedVideoIndex = atoi(argv[1]);

	return false;
}

bool Console::cmdRunScript(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Usage %s <script number>\n", argv[0]);
		return true;
	}

	ScriptMan.setScriptIndex(atoi(argv[1]));

	return false;
}

bool Console::cmdChangeScene(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Usage %s <scene number>\n", argv[0]);
		return true;
	}
	
	if (atoi(argv[1]) - 4 < 1 || atoi(argv[1]) - 4 >= 15) {
		DebugPrintf("Attempt to SetupStartingInfo(%d); Invalid world\n", atoi(argv[1]));
		return true;
	}

	ScriptMan.delayedSceneIndex = atoi(argv[1]);
	ScriptMan.setScript(0);

	return false;
}


} // End of namespace Asulym
