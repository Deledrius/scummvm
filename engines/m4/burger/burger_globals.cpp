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

#include "common/debug.h"
#include "m4/burger/burger_globals.h"
#include "m4/gui/gui_vmng.h"
#include "m4/mem/mem.h"
#include "m4/detection.h"

namespace M4 {
namespace Burger {

const char *GAME_MODES[4] = { "WHOLE_GAME", "INTERACTIVE_DEMO", "MAGAZINE_DEMO", "WHOLE_GAME" };

/**
 * Structure for accented character replacement
 */
struct ConverterEntry {
	const char *_find;
	byte _replace;
};
static const ConverterEntry ASCII_CONVERTERS[] = {
	{ "\xc4", 1 },
	{ "\xc9", 2 },
	{ "\xd6", 3 },
	{ "\xdc", 4 },
	{ "\xe1", 5 },
	{ "\xe4", 6 },
	{ "\xe9", 0x0B },
	{ "\xf6", 0x0C },
	{ "\xfc", 0x0E },
	{ "\xdf", 0x0F },
	{ "\xe2", 0x10 },
	{ "\xe0", 0x11 },
	{ "\xef", 0x12 },
	{ "\xee", 0x13 },
	{ "\xea", 0x14 },
	{ "\xe8", 0x15 },
	{ "\xeb", 0x16 },
	{ "\xf9", 0x17 },
	{ "\xfb", 0x18 },
	{ "\xe7", 0x19 },
	{ "\xc7", 0x1C },
	{ "\xf4", 0x1D },
	{ nullptr, 0 }
};


void BurgerGlobals::main_cold_data_init() {
	// TODO
	initMouseSeries("cursor", nullptr);

	_kernel.first_fade = 32;
	debugC(1, kDebugCore, "executing - %s", GAME_MODES[_gameMode]);



	// TODO
}

void BurgerGlobals::initMouseSeries(const Common::String &assetName, RGB8 *myPalette) {
	int32 maxW, maxH;

	_mouseSeriesHandle = nullptr;
	_mouseSeriesOffset = 0;
	_mouseSeriesPalOffset = 0;

	if (_mouseSprite)
		_mouseSprite->data = nullptr;
	if (_mouseBuffer.data)
		mem_free(_mouseBuffer.data);

	if (LoadSpriteSeries(assetName.c_str(), &_mouseSeriesHandle, &_mouseSeriesOffset, &_mouseSeriesPalOffset, myPalette) > 0) {
		_mouseSeriesResource = assetName;

		if (ws_GetSSMaxWH(_mouseSeriesHandle, _mouseSeriesOffset, &maxW, &maxH)) {
			if (maxW && maxH) {
				_mouseBuffer.data = (byte *)mem_alloc(maxW * maxH, "mouse graphic");
				_mouseBuffer.W = maxW;
				_mouseBuffer.h = maxH;
				_mouseBuffer.stride = maxW;

				vmng_screen_show(_mouseScreenSource);
				ResizeScreen(_mouseScreenSource, maxW, maxH);

				_currMouseNum = -1;
				_mouseIsLocked = false;
				mouse_set_sprite(kArrowCursor);
			}
		}
	}
}

void BurgerGlobals::custom_ascii_converter_proc(char *string) {
	char *str;

	for (const auto &entry : ASCII_CONVERTERS) {
		while ((str = strstr(string, entry._find)) != nullptr)
			*str = entry._replace;
	}
}

} // namespace Burger
} // namespace M4
