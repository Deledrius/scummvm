/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 *
 * HPL1 Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HPL1 Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HPL1 Engine.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef HPL_ACTION_HAPTIC_H
#define HPL_ACTION_HAPTIC_H


#include "hpl1/engine/input/InputTypes.h"
#include "hpl1/engine/input/Action.h"
#include "hpl1/engine/haptic/Haptic.h"

namespace hpl {

	class cHaptic;

	class cActionHaptic : public iAction
	{
	public:
		cActionHaptic(tString asName,cHaptic *apHaptic, int mlButton);

		bool IsTriggerd();
		float GetValue();

		tString GetInputName();

		tString GetInputType(){return "HapticDeviceButton";}

		int GetButton(){ return mlButton;}
	private:
		int mlButton;
		cHaptic *mpHaptic;
	};

};
#endif // HPL_ACTIONMOUSEBUTTON_H
