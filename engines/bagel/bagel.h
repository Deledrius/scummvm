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

#ifndef BAGEL_H
#define BAGEL_H

#include "common/scummsys.h"
#include "common/system.h"
#include "common/error.h"
#include "common/fs.h"
#include "common/hash-str.h"
#include "common/random.h"
#include "common/serializer.h"
#include "common/util.h"
#include "engines/engine.h"
#include "engines/savestate.h"
#include "graphics/screen.h"

#include "bagel/detection.h"
#include "bagel/music.h"
#include "bagel/baglib/master_win.h"
#include "bagel/boflib/stdinc.h"
#include "bagel/boflib/bit_buf.h"
#include "bagel/boflib/string.h"

namespace Bagel {

struct BagelGameDescription;

class BagelEngine : public Engine {
	struct Timer {
		uint32 _interval = 0;
		uint32 _lastExpiryTime = 0;
		CBofWindow *_window = nullptr;
		UINT _id = 0;
		BOFCALLBACK _callback = nullptr;

		Timer() {}
		Timer(uint32 interval, CBofWindow *window, UINT id, BOFCALLBACK callback) :
			_interval(interval), _window(window), _id(id), _callback(callback),
			_lastExpiryTime(0) {
		}
	};

private:
	const ADGameDescription *_gameDescription;
	Common::RandomSource _randomSource;
	ST_BAGEL_SAVE _saveData;
	Common::List<Timer> _timers;

	bool canSaveLoadFromWindow() const;

protected:
	CBagMasterWin *_masterWin = nullptr;

public:
	Graphics::Screen *_screen = nullptr;
	MusicPlayer *_midi = nullptr;
	bool _useOriginalSaveLoad = false;
	ZIPGLOBAL _zg;

public:
	BagelEngine(OSystem *syst, const ADGameDescription *gameDesc);
	~BagelEngine() override;

	uint32 getFeatures() const;

	/**
	 * Returns the game Id
	 */
	Common::String getGameId() const;

	/**
	 * Gets a random number
	 */
	uint32 getRandomNumber(uint maxNum = 0x7fffffff) {
		return _randomSource.getRandomNumber(maxNum);
	}

	bool hasFeature(EngineFeature f) const override {
		return
		    (f == kSupportsLoadingDuringRuntime) ||
		    (f == kSupportsSavingDuringRuntime) ||
		    (f == kSupportsReturnToLauncher);
	};

	bool canLoadGameStateCurrently(Common::U32String *msg = nullptr) override;
	bool canSaveGameStateCurrently(Common::U32String *msg = nullptr) override;

	/**
	 * Save a game state
	 */
	Common::Error saveGameState(int slot, const Common::String &desc, bool isAutosave = false) override;
	Common::Error saveGameState(int slot, const Common::String &desc, bool isAutosave,
		ST_BAGEL_SAVE &saveData);

	/**
	 * Load a game state
	 */
	Common::Error loadGameState(int slot) override;

	/**
	 * Handles saving the game
	 */
	Common::Error saveGameStream(Common::WriteStream *stream, bool isAutosave = false) override;

	/**
	 * Hnadles loading a savegame
	 */
	Common::Error loadGameStream(Common::SeekableReadStream *stream) override;

	/**
	 * Returns a list of savegames
	 */
	SaveStateList listSaves() const;

	/**
	 * Returns true if any savegames exist
	 */
	bool savesExist() const;

	VOID AddTimer(uint32 interval, CBofWindow *win, UINT nID, BOFCALLBACK pCallBack) {
		_timers.push_back(Timer(interval, win, nID, pCallBack));
	}
	VOID RemoveTimer(UINT nID);
	VOID CheckTimers();
};

extern BagelEngine *g_engine;
#define SHOULD_QUIT ::Bagel::g_engine->shouldQuit()

} // End of namespace Bagel

#endif // BAGEL_H
