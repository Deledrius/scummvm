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

#include <vector>
#include <vector>
#include <filesystem>
#include <fstream>
#include "twp/twp.h"
#include "twp/detection.h"
#include "twp/console.h"
#include "twp/vm.h"
#include "twp/ggpack.h"
#include "common/scummsys.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/events.h"
#include "common/system.h"
#include "common/file.h"
#include "image/png.h"
#include "engines/util.h"
#include "graphics/palette.h"

namespace Twp {

TwpEngine *g_engine;

TwpEngine::TwpEngine(OSystem *syst, const ADGameDescription *gameDesc)
	: Engine(syst),
	  _gameDescription(gameDesc),
	  _randomSource("Twp") {
	g_engine = this;
}

TwpEngine::~TwpEngine() {
	delete _screen;
}

uint32 TwpEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String TwpEngine::getGameId() const {
	return _gameDescription->gameId;
}

Common::Error TwpEngine::run() {
	Graphics::PixelFormat fmt(4, 8, 8, 8, 8, 0, 8, 16, 24);
	initGraphics(1280, 720, &fmt);
	_screen = new Graphics::Screen(1280, 720, fmt);

	XorKey key{{0x4F, 0xD0, 0xA0, 0xAC, 0x4A, 0x56, 0xB9, 0xE5, 0x93, 0x79, 0x45, 0xA5, 0xC1, 0xCB, 0x31, 0x93}, 0xAD};
	// XorKey key{{0x4F, 0xD0, 0xA0, 0xAC, 0x4A, 0x56, 0xB9, 0xE5, 0x93, 0x79, 0x45, 0xA5, 0xC1, 0xCB, 0x31, 0x93}, 0x6D};
	// XorKey key{{0x4F, 0xD0, 0xA0, 0xAC, 0x4A, 0x5B, 0xB9, 0xE5, 0x93, 0x79, 0x45, 0xA5, 0xC1, 0xCB, 0x31, 0x93}, 0x6D};
	// XorKey key{{0x4F, 0xD0, 0xA0, 0xAC, 0x4A, 0x5B, 0xB9, 0xE5, 0x93, 0x79, 0x45, 0xA5, 0xC1, 0xCB, 0x31, 0x93}, 0xAD};

	Common::File f;
	f.open("ThimbleweedPark.ggpack1");

	Scene scene;
	scene.pack.open(&f, key);

	const SQChar *code = R"(
	function bounceImage() {
		local image = createObject("RaySheet", ["fstand_head1"]);
		local x = random(100, 1180);
		local y = random(100, 620);

		do {
			local steps = random(100, 150);
			local end_x = random(0, 1180);
			local end_y = random(0, 620);

			local dx = (end_x - x) / steps;
			local dy = (end_y - y) / steps;

			for (local i = 0; i < steps; i++) {
				x += dx;
				y += dy;
				objectAt(image, x, y);
				breaktime(0.01);
			}
		} while (1);
	}

	for (local i = 1; i <= 100; i++) {
		startthread(bounceImage);
	})";

	Vm v;
	v.setScene(&scene);
	v.exec(code);

	// Set the engine's debugger console
	setDebugger(new Console());

	// If a savegame was selected from the launcher, load it
	int saveSlot = ConfMan.getInt("save_slot");
	if (saveSlot != -1)
		(void)loadGameState(saveSlot);

	// Simple event handling loop
	Common::Event e;
	while (!shouldQuit()) {
		const uint deltaTimeMs = 10;
		while (g_system->getEventManager()->pollEvent(e)) {
		}

		// update threads
		for (int i = 0; i < scene.threads.size(); i++) {
			Thread *thread = scene.threads[i];
			if (thread->update(deltaTimeMs)) {
				// TODO: delete it
			}
		}

		// update screen
		_screen->clear(0xFF808080);
		for (int i = 0; i < scene.entities.size(); i++) {
			Entity &ett = scene.entities[i];
			_screen->transBlitFrom(ett.surface, ett.rect, Common::Point(ett.x, ett.y));
		}
		_screen->update();

		// Delay for a bit. All events loops should have a delay
		// to prevent the system being unduly loaded
		g_system->delayMillis(deltaTimeMs);
	}

	return Common::kNoError;
}

Common::Error TwpEngine::syncGame(Common::Serializer &s) {
	// The Serializer has methods isLoading() and isSaving()
	// if you need to specific steps; for example setting
	// an array size after reading it's length, whereas
	// for saving it would write the existing array's length
	int dummy = 0;
	s.syncAsUint32LE(dummy);

	return Common::kNoError;
}

} // End of namespace Twp
