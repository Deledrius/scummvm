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

#ifndef M4_RIDDLE_ROOMS_SECTION3_ROOM352_H
#define M4_RIDDLE_ROOMS_SECTION3_ROOM352_H

#include "m4/riddle/rooms/room.h"

namespace M4 {
namespace Riddle {
namespace Rooms {

class Room352 : public Room {
private:
	int _val1 = 0;
	int _val2 = 0;
	int _cabStop = 0;
	machine *_cabStopMach = nullptr;
	machine *_machine1 = nullptr;
	machine *_meiChecksShoe = nullptr;
	int _playerX = 0, _playerY = 0;
	int _playerScale = 0;
	machine *_ripsh1 = nullptr;
	machine *_ripDoor = nullptr;

	bool _buttonFlag = false;

	static void escapeKeyPressed(void *, void *);

public:
	Room352() : Room() {}
	~Room352() override {}

	void preload() override;
	void init() override;
	void daemon() override;
};

} // namespace Rooms
} // namespace Riddle
} // namespace M4

#endif
