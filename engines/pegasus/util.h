/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
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
 */

#ifndef PEGASUS_MMSHELL_MMIDOBJECT_H
#define PEGASUS_MMSHELL_MMIDOBJECT_H

#include "pegasus/types.h"

namespace Common {
	class RandomSource;
}

namespace Pegasus {

class IDObject {
public:
	IDObject(const tMM32BitID id);
	~IDObject();
	
	tMM32BitID getObjectID() const;

private:
	tMM32BitID _objectID;
};

class FunctionPtr;

typedef void (*tFunctionPtr)(FunctionPtr *theFunction, void *functionArg);

class FunctionPtr {
public:
	FunctionPtr();
	virtual ~FunctionPtr();
	
	void setFunctionPtr(tFunctionPtr function, void *functionArg);

protected:
	void callFunction();
	
	tFunctionPtr _function;
	void *_functionArg;
};

int32 linearInterp(const int32 start1, const int32 stop1, const int32 current1, const int32 start2, const int32 stop2);

void shuffleArray(int32 *arr, int32 count, Common::RandomSource &random);

int32 pegasusRound(const int32 a, const int32 b);

} // End of namespace Pegasus

#endif
