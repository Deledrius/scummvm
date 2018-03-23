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

#ifndef BLADERUNNER_POLICE_MAZE_H
#define BLADERUNNER_POLICE_MAZE_H

#include "bladerunner/vector.h"

namespace BladeRunner {

enum {
	kNumMazeTracks = 64,
	kNumTrackPoints = 100
};

class BladeRunnerEngine;

class PoliceMazeTargetTrack {
	int _time;
	bool _isPresent;
	int _itemId;
	int _count;
	Vector3 _points[kNumTrackPoints];
	int *_data;
	int _dataIndex;
	int _pmt_var1;
	int _pmt_var2;
	int _pmt_var3;
	int _pmt_var4;
	int _pointIndex;
	int _pmt_var5;
	int _rotating;
	int _maxAngle;
	int _angleChange;
	bool _visible;

public:
	PoliceMazeTargetTrack();
	~PoliceMazeTargetTrack();

	void reset();
};

class PoliceMaze {
	BladeRunnerEngine *_vm;

	PoliceMazeTargetTrack *_tracks[kNumMazeTracks];
	bool _isActive;
	bool _needAnnouncement;
	bool _announcementRead;
	int _pm_var1;
	int _pm_var2;

public:
	PoliceMaze(BladeRunnerEngine *vm);
	~PoliceMaze();

	void tick();
	void reset();
};

} // End of namespace BladeRunner

#endif
