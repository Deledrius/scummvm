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

//include <string.h>
#include "ags/engine/ac/textbox.h"
#include "ags/shared/ac/common.h"
#include "ags/shared/ac/gamesetupstruct.h"
#include "ags/engine/ac/string.h"

#include "ags/shared/debugging/out.h"
#include "ags/engine/script/script_api.h"
#include "ags/engine/script/script_runtime.h"
#include "ags/engine/ac/dynobj/scriptstring.h"

namespace AGS3 {

extern GameSetupStruct game;


// ** TEXT BOX FUNCTIONS

const char *TextBox_GetText_New(GUITextBox *texbox) {
	return CreateNewScriptString(texbox->Text);
}

void TextBox_GetText(GUITextBox *texbox, char *buffer) {
	strcpy(buffer, texbox->Text);
}

void TextBox_SetText(GUITextBox *texbox, const char *newtex) {
	if (strcmp(texbox->Text, newtex)) {
		texbox->Text = newtex;
		guis_need_update = 1;
	}
}

int TextBox_GetTextColor(GUITextBox *guit) {
	return guit->TextColor;
}

void TextBox_SetTextColor(GUITextBox *guit, int colr) {
	if (guit->TextColor != colr) {
		guit->TextColor = colr;
		guis_need_update = 1;
	}
}

int TextBox_GetFont(GUITextBox *guit) {
	return guit->Font;
}

void TextBox_SetFont(GUITextBox *guit, int fontnum) {
	if ((fontnum < 0) || (fontnum >= game.numfonts))
		quit("!SetTextBoxFont: invalid font number.");

	if (guit->Font != fontnum) {
		guit->Font = fontnum;
		guis_need_update = 1;
	}
}

bool TextBox_GetShowBorder(GUITextBox *guit) {
	return guit->IsBorderShown();
}

void TextBox_SetShowBorder(GUITextBox *guit, bool on) {
	if (guit->IsBorderShown() != on) {
		guit->SetShowBorder(on);
		guis_need_update = 1;
	}
}

//=============================================================================
//
// Script API Functions
//
//=============================================================================

extern ScriptString myScriptStringImpl;

// void (GUITextBox *texbox, char *buffer)
RuntimeScriptValue Sc_TextBox_GetText(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_VOID_POBJ(GUITextBox, TextBox_GetText, char);
}

// void (GUITextBox *texbox, const char *newtex)
RuntimeScriptValue Sc_TextBox_SetText(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_VOID_POBJ(GUITextBox, TextBox_SetText, const char);
}

// int (GUITextBox *guit)
RuntimeScriptValue Sc_TextBox_GetFont(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_INT(GUITextBox, TextBox_GetFont);
}

// void (GUITextBox *guit, int fontnum)
RuntimeScriptValue Sc_TextBox_SetFont(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_VOID_PINT(GUITextBox, TextBox_SetFont);
}

RuntimeScriptValue Sc_TextBox_GetShowBorder(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_BOOL(GUITextBox, TextBox_GetShowBorder);
}

// void (GUITextBox *guit, int fontnum)
RuntimeScriptValue Sc_TextBox_SetShowBorder(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_VOID_PBOOL(GUITextBox, TextBox_SetShowBorder);
}

// const char* (GUITextBox *texbox)
RuntimeScriptValue Sc_TextBox_GetText_New(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_OBJ(GUITextBox, const char *, myScriptStringImpl, TextBox_GetText_New);
}

// int (GUITextBox *guit)
RuntimeScriptValue Sc_TextBox_GetTextColor(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_INT(GUITextBox, TextBox_GetTextColor);
}

// void (GUITextBox *guit, int colr)
RuntimeScriptValue Sc_TextBox_SetTextColor(void *self, const RuntimeScriptValue *params, int32_t param_count) {
	API_OBJCALL_VOID_PINT(GUITextBox, TextBox_SetTextColor);
}


void RegisterTextBoxAPI() {
	ccAddExternalObjectFunction("TextBox::GetText^1", Sc_TextBox_GetText);
	ccAddExternalObjectFunction("TextBox::SetText^1", Sc_TextBox_SetText);
	ccAddExternalObjectFunction("TextBox::get_Font", Sc_TextBox_GetFont);
	ccAddExternalObjectFunction("TextBox::set_Font", Sc_TextBox_SetFont);
	ccAddExternalObjectFunction("TextBox::get_ShowBorder", Sc_TextBox_GetShowBorder);
	ccAddExternalObjectFunction("TextBox::set_ShowBorder", Sc_TextBox_SetShowBorder);
	ccAddExternalObjectFunction("TextBox::get_Text", Sc_TextBox_GetText_New);
	ccAddExternalObjectFunction("TextBox::set_Text", Sc_TextBox_SetText);
	ccAddExternalObjectFunction("TextBox::get_TextColor", Sc_TextBox_GetTextColor);
	ccAddExternalObjectFunction("TextBox::set_TextColor", Sc_TextBox_SetTextColor);

	/* ----------------------- Registering unsafe exports for plugins -----------------------*/

	ccAddExternalFunctionForPlugin("TextBox::GetText^1", (void *)TextBox_GetText);
	ccAddExternalFunctionForPlugin("TextBox::SetText^1", (void *)TextBox_SetText);
	ccAddExternalFunctionForPlugin("TextBox::get_Font", (void *)TextBox_GetFont);
	ccAddExternalFunctionForPlugin("TextBox::set_Font", (void *)TextBox_SetFont);
	ccAddExternalFunctionForPlugin("TextBox::get_Text", (void *)TextBox_GetText_New);
	ccAddExternalFunctionForPlugin("TextBox::set_Text", (void *)TextBox_SetText);
	ccAddExternalFunctionForPlugin("TextBox::get_TextColor", (void *)TextBox_GetTextColor);
	ccAddExternalFunctionForPlugin("TextBox::set_TextColor", (void *)TextBox_SetTextColor);
}

} // namespace AGS3
