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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "ultima/detection.h"
#include "ultima/ultima8/ultima8.h"
#include "base/plugins.h"
#include "common/savefile.h"
#include "common/str-array.h"
#include "common/memstream.h"
#include "common/system.h"
#include "common/translation.h"

static const PlainGameDescriptor ULTIMA_GAMES[] = {
#ifdef ENABLE_ULTIMA8
	{ "ultima8", "Ultima 8 - Pagan" },
#endif
	{ 0, 0 }
};

#include "ultima/detection_tables.h"

UltimaMetaEngine::UltimaMetaEngine() : AdvancedMetaEngine(Ultima::GAME_DESCRIPTIONS,
	        sizeof(Ultima::UltimaGameDescription), ULTIMA_GAMES) {
#ifdef ENABLE_ULTIMA8
	static const char *const DIRECTORY_GLOBS[2] = { "usecode", 0 };
	_maxScanDepth = 2;
	_directoryGlobs = DIRECTORY_GLOBS;
#endif
}

bool UltimaMetaEngine::hasFeature(MetaEngineFeature f) const {
	return
		(f == kSupportsListSaves) ||
		(f == kSupportsDeleteSave) ||
		(f == kSavesSupportMetaInfo) ||
		(f == kSavesSupportThumbnail) ||
		(f == kSavesSupportCreationDate) ||
		(f == kSavesSupportPlayTime) ||
		(f == kSupportsLoadingDuringStartup) ||
		(f == kSavesUseExtendedFormat);
}

bool UltimaMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Ultima::UltimaGameDescription *gd = (const Ultima::UltimaGameDescription *)desc;
	if (gd) {
		switch (gd->gameId) {
		case Ultima::GAME_ULTIMA8:
			*engine = new Ultima8::Ultima8Engine(syst, gd);
			break;
		default:
			error("Unsupported game specified");
		}
	}
	return gd != 0;
}

int UltimaMetaEngine::getMaximumSaveSlot() const {
	return MAX_SAVES;
}

const char *UltimaMetaEngine::getSavegamePattern(const char *target) const {
	static char buffer[100];
	snprintf(buffer, 200, "%s.###", target == nullptr ? getEngineId() : target);

	return buffer;
}

#if PLUGIN_ENABLED_DYNAMIC(ULTIMA)
REGISTER_PLUGIN_DYNAMIC(ULTIMA, PLUGIN_TYPE_ENGINE, UltimaMetaEngine);
#else
REGISTER_PLUGIN_STATIC(ULTIMA, PLUGIN_TYPE_ENGINE, UltimaMetaEngine);
#endif
