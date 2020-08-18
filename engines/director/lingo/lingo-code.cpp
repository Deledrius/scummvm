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

// Heavily inspired by hoc
// Copyright (C) AT&T 1995
// All Rights Reserved
//
// Permission to use, copy, modify, and distribute this software and
// its documentation for any purpose and without fee is hereby
// granted, provided that the above copyright notice appear in all
// copies and that both that the copyright notice and this
// permission notice and warranty disclaimer appear in supporting
// documentation, and that the name of AT&T or any of its entities
// not be used in advertising or publicity pertaining to
// distribution of the software without specific, written prior
// permission.
//
// AT&T DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
// INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
// IN NO EVENT SHALL AT&T OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
// SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
// IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
// ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
// THIS SOFTWARE.

#include "director/director.h"
#include "director/movie.h"
#include "director/score.h"
#include "director/sprite.h"
#include "director/window.h"
#include "director/cursor.h"
#include "director/channel.h"
#include "director/util.h"
#include "director/lingo/lingo.h"
#include "director/lingo/lingo-builtins.h"
#include "director/lingo/lingo-code.h"
#include "director/lingo/lingo-object.h"
#include "director/lingo/lingo-the.h"
#include "director/lingo/lingo-gr.h"

namespace Director {

static struct FuncDescr {
	const inst func;
	const char *name;
	const char *args;
} funcDescr[] = {
	{ 0,					"STOP",				""  },
	{ LC::c_add,			"c_add",			"" },
	{ LC::c_putafter,		"c_putafter",		"" },	// D3
	{ LC::c_ampersand,		"c_ampersand",		"" },
	{ LC::c_and,			"c_and",			"" },
	{ LC::c_argcnoretpush,	"c_argcnoretpush",	"i" },
	{ LC::c_argcpush,		"c_argcpush",		"i" },
	{ LC::c_arraypush,		"c_arraypush",		"i" },
	{ LC::c_assign,			"c_assign",			""  },
	{ LC::c_putbefore,		"c_putbefore",		"" },	// D3
	{ LC::c_callcmd,		"c_callcmd",		"si" },
	{ LC::c_callfunc,		"c_callfunc",		"si" },
	{ LC::c_charOf,			"c_charOf",			"" },	// D3
	{ LC::c_charToOf,		"c_charToOf",		"" },	// D3
	{ LC::c_concat,			"c_concat",			"" },
	{ LC::c_constpush,		"c_constpush",		"s" },
	{ LC::c_contains,		"c_contains",		"" },
	{ LC::c_div,			"c_div",			"" },
	{ LC::c_eq,				"c_eq",				"" },
	{ LC::c_eval,			"c_eval",			"s" },
	{ LC::c_floatpush,		"c_floatpush",		"f" },
	{ LC::c_ge,				"c_ge",				"" },
	{ LC::c_goto,			"c_goto",			"" },
	{ LC::c_gotoloop,		"c_gotoloop",		"" },
	{ LC::c_gotonext,		"c_gotonext",		"" },
	{ LC::c_gotoprevious,	"c_gotoprevious",	"" },
	{ LC::c_gt,				"c_gt",				"" },
	{ LC::c_hilite,			"c_hilite",			"" },
	{ LC::c_intersects,		"c_intersects",		"" },
	{ LC::c_intpush,		"c_intpush",		"i" },
	{ LC::c_itemOf,			"c_itemOf",			"" },	// D3
	{ LC::c_itemToOf,		"c_itemToOf",		"" },	// D3
	{ LC::c_jump,			"c_jump",			"o" },
	{ LC::c_jumpifz,		"c_jumpifz",		"o" },
	{ LC::c_lazyeval,		"c_lazyeval",			"s" },
	{ LC::c_le,				"c_le",				"" },
	{ LC::c_lineOf,			"c_lineOf",			"" },	// D3
	{ LC::c_lineToOf,		"c_lineToOf",		"" },	// D3
	{ LC::c_lt,				"c_lt",				"" },
	{ LC::c_mod,			"c_mod",			"" },
	{ LC::c_mul,			"c_mul",			"" },
	{ LC::c_namepush,		"c_namepush",		"N" },
	{ LC::c_negate,			"c_negate",			"" },
	{ LC::c_neq,			"c_neq",			"" },
	{ LC::c_not,			"c_not",			"" },
	{ LC::c_objectpropassign,"c_objectpropassign","ss" }, // object, prop
	{ LC::c_objectproppush,	"c_objectproppush","ss" }, // object, prop
	{ LC::c_of,				"c_of",				"" },
	{ LC::c_or,				"c_or",				"" },
	{ LC::c_play,			"c_play",			"" },
	{ LC::c_procret,		"c_procret",		"" },
	{ LC::c_proparraypush,	"c_proparraypush",	"i" },
	{ LC::c_setImmediate,	"c_setImmediate",	"i" },
	{ LC::c_starts,			"c_starts",			"" },
	{ LC::c_stringpush,		"c_stringpush",		"s" },
	{ LC::c_sub,			"c_sub",			"" },
	{ LC::c_swap,			"c_swap",			"" },
	{ LC::c_symbolpush,		"c_symbolpush",		"s" },	// D3
	{ LC::c_tell,			"c_tell",			"" },
	{ LC::c_telldone,		"c_telldone",		"" },
	{ LC::c_theentityassign,"c_theentityassign","EF" },
	{ LC::c_theentitypush,	"c_theentitypush",	"EF" }, // entity, field
	{ LC::c_themenuentitypush,"c_themenuentitypush","EF" },
	{ LC::c_themenuitementityassign,"c_themenuitementityassign","EF" },
	{ LC::c_varpush,		"c_varpush",		"s" },
	{ LC::c_voidpush,		"c_voidpush",		""  },
	{ LC::c_whencode,		"c_whencode",		"s" },
	{ LC::c_within,			"c_within",			"" },
	{ LC::c_wordOf,			"c_wordOf",			"" },	// D3
	{ LC::c_wordToOf,		"c_wordToOf",		"" },	// D3
	{ LC::c_xpop,			"c_xpop",			""  },
	{ LC::cb_call,			"cb_call",			"N" },
	{ LC::cb_delete,		"cb_delete",		"i" },
	{ LC::cb_field,			"cb_field",			"" },
	{ LC::cb_globalassign,	"cb_globalassign",	"N" },
	{ LC::cb_globalpush,	"cb_globalpush",	"N" },
	{ LC::cb_list,			"cb_list",			"" },
	{ LC::cb_proplist,		"cb_proplist",		"" },
	{ LC::cb_localcall,		"cb_localcall",		"i" },
	{ LC::cb_objectcall,	"cb_objectcall",	"i" },
	{ LC::cb_objectfieldassign, "cb_objectfieldassign", "N" },
	{ LC::cb_objectfieldpush, "cb_objectfieldpush", "N" },
	{ LC::cb_objectpush,	"cb_objectpush",	"N" },
	{ LC::cb_theassign,		"cb_theassign",		"N" },
	{ LC::cb_theassign2,	"cb_theassign2",	"N" },
	{ LC::cb_thepush,		"cb_thepush",		"N" },
	{ LC::cb_thepush2,		"cb_thepush2",		"N" },
	{ LC::cb_unk,			"cb_unk",			"i" },
	{ LC::cb_unk1,			"cb_unk1",			"ii" },
	{ LC::cb_unk2,			"cb_unk2",			"iii" },
	{ LC::cb_varassign,		"cb_varassign",		"N" },
	{ LC::cb_varpush,		"cb_varpush",		"N" },
	{ LC::cb_v4assign,		"cb_v4assign",		"i" },
	{ LC::cb_v4assign2,		"cb_v4assign2",		"i" },
	{ LC::cb_v4theentitypush,"cb_v4theentitypush","i" },
	{ LC::cb_v4theentitynamepush,"cb_v4theentitynamepush","N" },
	{ LC::cb_v4theentityassign,"cb_v4theentityassign","i" },
	{ LC::cb_zeropush,		"cb_zeropush",		"" },
	{ LC::c_stackpeek,		"c_stackpeek",		"i" },
	{ LC::c_stackdrop,		"c_stackdrop",		"i" },
	{ 0, 0, 0 }
};

void Lingo::initFuncs() {
	Symbol sym;
	for (FuncDescr *fnc = funcDescr; fnc->name; fnc++) {
		sym.u.func = fnc->func;
		_functions[(void *)sym.u.s] = new FuncDesc(fnc->name, fnc->args);
	}
}

void Lingo::cleanupFuncs() {
	for (FuncHash::iterator it = _functions.begin(); it != _functions.end(); ++it)
		delete it->_value;
}

void Lingo::push(Datum d) {
	_stack.push_back(d);
}

void Lingo::pushVoid() {
	Datum d;
	d.u.s = NULL;
	d.type = VOID;
	push(d);
}

Datum Lingo::pop(void) {
	assert (_stack.size() != 0);

	Datum ret = _stack.back();
	_stack.pop_back();
	if (ret.lazy) {
		ret = ret.eval();
	}

	return ret;
}

Datum Lingo::peek(uint offset) {
	assert (_stack.size() > offset);

	Datum ret = _stack[_stack.size() - 1 - offset];
	if (ret.lazy) {
		ret = ret.eval();
	}
	return ret;
}

void LC::c_xpop() {
	g_lingo->pop();
}

void Lingo::pushContext(const Symbol funcSym, bool allowRetVal, Datum defaultRetVal) {
	debugC(5, kDebugLingoExec, "Pushing frame %d", g_lingo->_callstack.size() + 1);
	CFrame *fp = new CFrame;

	fp->retpc = g_lingo->_pc;
	fp->retscript = g_lingo->_currentScript;
	fp->retctx = g_lingo->_currentScriptContext;
	fp->retarchive = g_lingo->_currentArchive;
	fp->localvars = g_lingo->_localvars;
	fp->retMe = g_lingo->_currentMe;
	fp->sp = funcSym;
	fp->allowRetVal = allowRetVal;
	fp->defaultRetVal = defaultRetVal;

	g_lingo->_currentScript = funcSym.u.defn;

	if (funcSym.target)
		g_lingo->_currentMe = funcSym.target;

	if (funcSym.ctx)
		g_lingo->_currentScriptContext = funcSym.ctx;

	g_lingo->_currentArchive = funcSym.archive;

	DatumHash *localvars = g_lingo->_localvars;
	if (!funcSym.anonymous) {
		// Execute anonymous functions within the current var frame.
		localvars = new DatumHash;
	}

	if (funcSym.argNames) {
		int symNArgs = funcSym.nargs;
		if ((int)funcSym.argNames->size() < symNArgs) {
			int dropSize = symNArgs - funcSym.argNames->size();
			warning("%d arg names defined for %d args! Dropping the last %d values", funcSym.argNames->size(), symNArgs, dropSize);
			for (int i = 0; i < dropSize; i++) {
				g_lingo->pop();
				symNArgs -= 1;
			}
		} else if ((int)funcSym.argNames->size() > symNArgs) {
			warning("%d arg names defined for %d args! Ignoring the last %d names", funcSym.argNames->size(), symNArgs, funcSym.argNames->size() - symNArgs);
		}
		for (int i = symNArgs - 1; i >= 0; i--) {
			Common::String name = (*funcSym.argNames)[i];
			if (!localvars->contains(name)) {
				g_lingo->varCreate(name, false, localvars);
				Datum arg(name);
				arg.type = VAR;
				Datum value = g_lingo->pop();
				g_lingo->varAssign(arg, value, false, localvars);
			} else {
				warning("Argument %s already defined", name.c_str());
				g_lingo->pop();
			}
		}
	}
	if (funcSym.varNames) {
		for (Common::Array<Common::String>::iterator it = funcSym.varNames->begin(); it != funcSym.varNames->end(); ++it) {
			Common::String name = *it;
			if (!localvars->contains(name)) {
				(*localvars)[name] = Datum();
			} else {
				warning("Variable %s already defined", name.c_str());
			}
		}
	}
	g_lingo->_localvars = localvars;

	fp->stackSizeBefore = _stack.size();

	g_lingo->_callstack.push_back(fp);

	if (debugChannelSet(5, kDebugLingoExec)) {
		g_lingo->printCallStack(0);
	}
}

void Lingo::popContext() {
	debugC(5, kDebugLingoExec, "Popping frame %d", g_lingo->_callstack.size());
	CFrame *fp = g_lingo->_callstack.back();
	g_lingo->_callstack.pop_back();

	if (_stack.size() == fp->stackSizeBefore + 1) {
		if (!fp->allowRetVal) {
			warning("dropping return value");
			g_lingo->pop();
		}
	} else if (_stack.size() == fp->stackSizeBefore) {
		if (fp->allowRetVal) {
			warning("handler %s did not return value", fp->sp.name->c_str());
			g_lingo->push(fp->defaultRetVal);
		}
	} else if (_stack.size() > fp->stackSizeBefore) {
		error("handler %s returned extra %d values", fp->sp.name->c_str(), _stack.size() - fp->stackSizeBefore);
	} else {
		error("handler %s popped extra %d values", fp->sp.name->c_str(), fp->stackSizeBefore - _stack.size());
	}

	// Destroy anonymous function context
	if (fp->sp.anonymous) {
		delete g_lingo->_currentScriptContext;
	}

	g_lingo->_currentScript = fp->retscript;
	g_lingo->_currentScriptContext = fp->retctx;
	g_lingo->_currentArchive = fp->retarchive;
	g_lingo->_pc = fp->retpc;
	g_lingo->_currentMe = fp->retMe;

	// Restore local variables
	if (!fp->sp.anonymous) {
		g_lingo->cleanLocalVars();
		g_lingo->_localvars = fp->localvars;
	}

	if (debugChannelSet(5, kDebugLingoExec)) {
		g_lingo->printCallStack(g_lingo->_pc);
	}

	delete fp;
}

void LC::c_constpush() {
	Common::String name(g_lingo->readString());

	Symbol funcSym;
	if (g_lingo->_builtinConsts.contains(name)) {
		funcSym = g_lingo->_builtinConsts[name];
	}

	LC::call(funcSym, 0, true);
}

void LC::c_intpush() {
	int value = g_lingo->readInt();
	g_lingo->push(Datum(value));
}

void LC::c_voidpush() {
	Datum d;
	d.u.s = NULL;
	d.type = VOID;
	g_lingo->push(d);
}

void LC::c_floatpush() {
	double value = g_lingo->readFloat();
	g_lingo->push(Datum(value));
}

void LC::c_stringpush() {
	char *s = g_lingo->readString();
	g_lingo->push(Datum(Common::String(s)));
}

void LC::c_symbolpush() {
	char *s = g_lingo->readString();

	// TODO: FIXME: Currently we push string
	// If you change it, you must also fix func_play for "play done"
	// command
	Datum d = Datum(Common::String(s));
	d.type = SYMBOL;

	g_lingo->push(d);
}

void LC::c_namepush() {
	Datum d;
	int i = g_lingo->readInt();
	d.type = SYMBOL;
	d.u.s = new Common::String(g_lingo->_currentArchive->getName(i));
	g_lingo->push(d);
}

void LC::c_argcpush() {
	Datum d;
	int argsSize = g_lingo->readInt();

	d.u.i = argsSize;
	d.type = ARGC;
	g_lingo->push(d);
}

void LC::c_argcnoretpush() {
	Datum d;
	int argsSize = g_lingo->readInt();

	d.u.i = argsSize;
	d.type = ARGCNORET;
	g_lingo->push(d);
}

void LC::c_arraypush() {
	Datum d;
	int arraySize = g_lingo->readInt();

	d.type = ARRAY;
	d.u.farr = new DatumArray;

	for (int i = 0; i < arraySize; i++)
		d.u.farr->insert_at(0, g_lingo->pop());

	g_lingo->push(d);
}

void LC::c_proparraypush() {
	Datum d;
	int arraySize = g_lingo->readInt();

	d.type = PARRAY;
	d.u.parr = new PropertyArray;

	for (int i = 0; i < arraySize; i++) {
		Datum p = g_lingo->pop();
		Datum v = g_lingo->pop();

		PCell cell = PCell(p, v);
		d.u.parr->insert_at(0, cell);
	}

	g_lingo->push(d);
}

void LC::c_varpush() {
	Common::String name(g_lingo->readString());
	Datum d;

	// In immediate mode we will push variables as strings
	// This is used for playAccel
	if (g_lingo->_immediateMode) {
		g_lingo->push(Datum(Common::String(name)));

		return;
	}

	// Looking for the cast member constants
	if (g_director->getVersion() < 400 || g_director->getCurrentMovie()->_allowOutdatedLingo) {
		int val = castNumToNum(name.c_str());

		if (val != -1) {
			d.type = INT;
			d.u.i = val;
			g_lingo->push(d);
			return;
		}
	}

	d.type = VAR;
	d.u.s = new Common::String(name);
	g_lingo->push(d);
}

void LC::c_stackpeek() {
	int peekOffset = g_lingo->readInt();
	g_lingo->push(g_lingo->peek(peekOffset));
}

void LC::c_stackdrop() {
	int dropCount = g_lingo->readInt();
	for (int i = 0; i < dropCount; i++) {
		g_lingo->pop();
	}
}

void LC::c_setImmediate() {
	g_lingo->_immediateMode = g_lingo->readInt();
}

void LC::c_assign() {
	Datum d1, d2;
	d1 = g_lingo->pop();
	d2 = g_lingo->pop();

	g_lingo->varAssign(d1, d2);
}

void LC::c_eval() {
	LC::c_varpush();

	Datum d;
	d = g_lingo->pop();

	if (d.type != VAR) { // It could be cast ref
		g_lingo->push(d);
		return;
	}

	d = g_lingo->varFetch(d);

	g_lingo->push(d);
}

void LC::c_lazyeval() {
	LC::c_varpush();

	Datum d;
	d = g_lingo->pop();
	d.lazy = true;
	g_lingo->push(d);
}

void LC::c_theentitypush() {
	Datum id = g_lingo->pop();

	int entity = g_lingo->readInt();
	int field  = g_lingo->readInt();

	Datum d = g_lingo->getTheEntity(entity, id, field);
	g_lingo->push(d);
}

void LC::c_themenuentitypush() {
	int entity = g_lingo->readInt();
	int field  = g_lingo->readInt();

	Datum menuId = g_lingo->pop();
	Datum menuItemId;

	if (entity != kTheMenuItems) { // "<entity> of menuitems" has 1 parameter
		menuItemId = g_lingo->pop();
	}

	Datum d = g_lingo->getTheMenuItemEntity(entity, menuId, field, menuItemId);
	g_lingo->push(d);
}

void LC::c_theentityassign() {
	Datum id = g_lingo->pop();

	int entity = g_lingo->readInt();
	int field  = g_lingo->readInt();

	Datum d = g_lingo->pop();
	g_lingo->setTheEntity(entity, id, field, d);
}

void LC::c_themenuitementityassign() {
	int entity = g_lingo->readInt();
	int field  = g_lingo->readInt();

	Datum d = g_lingo->pop();
	Datum menuId = g_lingo->pop();
	Datum menuItemId;

	if (entity != kTheMenuItems) { // "<entity> of menuitems" has 2 parameters
		menuItemId = g_lingo->pop();
	}

	g_lingo->setTheMenuItemEntity(entity, menuId, field, menuItemId, d);
}

void LC::c_objectproppush() {
	Datum objName(g_lingo->readString());
	objName.type = VAR;
	Datum obj = g_lingo->varFetch(objName);
	Common::String propName = g_lingo->readString();

	g_lingo->push(g_lingo->getObjectProp(obj, propName));
}

void LC::c_objectpropassign() {
	Datum objName(g_lingo->readString());
	objName.type = VAR;
	Datum obj = g_lingo->varFetch(objName);
	Common::String propName = g_lingo->readString();

	Datum d = g_lingo->pop();

	g_lingo->setObjectProp(obj, propName, d);
}

void LC::c_swap() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(d2);
	g_lingo->push(d1);
}

Datum LC::mapBinaryOp(Datum (*mapFunc)(Datum &, Datum &), Datum &d1, Datum &d2) {
	// At least one of d1 and d2 must be an array
	uint arraySize;
	if (d1.type == ARRAY && d2.type == ARRAY) {
		arraySize = MIN(d1.u.farr->size(), d2.u.farr->size());
	} else if (d1.type == ARRAY) {
		arraySize = d1.u.farr->size();
	} else {
		arraySize = d2.u.farr->size();
	}
	Datum res;
	res.type = ARRAY;
	res.u.farr = new DatumArray(arraySize);
	Datum a = d1;
	Datum b = d2;
	for (uint i = 0; i < arraySize; i++) {
		if (d1.type == ARRAY) {
			a = d1.u.farr->operator[](i);
		}
		if (d2.type == ARRAY) {
			b = d2.u.farr->operator[](i);
		}
		res.u.farr->operator[](i) = mapFunc(a, b);
	}
	return res;
}

Datum LC::addData(Datum &d1, Datum &d2) {
	if (d1.type == ARRAY || d2.type == ARRAY) {
		return LC::mapBinaryOp(LC::addData, d1, d2);
	}

	int alignedType = g_lingo->getAlignedType(d1, d2, true);

	Datum res;
	if (alignedType == FLOAT) {
		res = Datum(d1.asFloat() + d2.asFloat());
	} else if (alignedType == INT) {
		res = Datum(d1.asInt() + d2.asInt());
	} else {
		warning("LC::addData(): not supported between types %s and %s", d1.type2str(), d2.type2str());
	}
	return res;
}

void LC::c_add() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::addData(d1, d2));
}

Datum LC::subData(Datum &d1, Datum &d2) {
	if (d1.type == ARRAY || d2.type == ARRAY) {
		return LC::mapBinaryOp(LC::subData, d1, d2);
	}

	int alignedType = g_lingo->getAlignedType(d1, d2, true);

	Datum res;
	if (alignedType == FLOAT) {
		res = Datum(d1.asFloat() - d2.asFloat());
	} else if (alignedType == INT) {
		res = Datum(d1.asInt() - d2.asInt());
	} else {
		warning("LC::subData(): not supported between types %s and %s", d1.type2str(), d2.type2str());
	}
	return res;
}

void LC::c_sub() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::subData(d1, d2));
}

Datum LC::mulData(Datum &d1, Datum &d2) {
	if (d1.type == ARRAY || d2.type == ARRAY) {
		return LC::mapBinaryOp(LC::mulData, d1, d2);
	}

	int alignedType = g_lingo->getAlignedType(d1, d2, true);

	Datum res;
	if (alignedType == FLOAT) {
		res = Datum(d1.asFloat() * d2.asFloat());
	} else if (alignedType == INT) {
		res = Datum(d1.asInt() * d2.asInt());
	} else {
		warning("LC::mulData(): not supported between types %s and %s", d1.type2str(), d2.type2str());
	}
	return res;
}

void LC::c_mul() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::mulData(d1, d2));
}

Datum LC::divData(Datum &d1, Datum &d2) {
	if (d1.type == ARRAY || d2.type == ARRAY) {
		return LC::mapBinaryOp(LC::divData, d1, d2);
	}

	if ((d2.type == INT && d2.u.i == 0) ||
			(d2.type == FLOAT && d2.u.f == 0.0)) {
		warning("LC::divData(): division by zero");
		d2 = Datum(1);
	}

	int alignedType = g_lingo->getAlignedType(d1, d2, true);

	if (g_director->getVersion() < 400)	// pre-D4 is INT-only
		alignedType = INT;

	Datum res;
	if (alignedType == FLOAT) {
		res = Datum(d1.asFloat() / d2.asFloat());
	} else if (alignedType == INT) {
		res = Datum(d1.asInt() / d2.asInt());
	} else {
		warning("LC::divData(): not supported between types %s and %s", d1.type2str(), d2.type2str());
	}

	return res;
}

void LC::c_div() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(divData(d1, d2));
}

Datum LC::modData(Datum &d1, Datum &d2) {
	if (d1.type == ARRAY || d2.type == ARRAY) {
		return LC::mapBinaryOp(LC::modData, d1, d2);
	}

	int i1 = d1.asInt();
	int i2 = d2.asInt();
	if (i2 == 0) {
		warning("LC::modData(): division by zero");
		i2 = 1;
	}

	Datum res(i1 % i2);
	return res;
}

void LC::c_mod() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::modData(d1, d2));
}

Datum LC::negateData(Datum &d) {
	if (d.type == ARRAY) {
		uint arraySize = d.u.farr->size();
		Datum res;
		res.type = ARRAY;
		res.u.farr = new DatumArray(arraySize);
		for (uint i = 0; i < arraySize; i++) {
			res.u.farr->operator[](i) = LC::negateData(d.u.farr->operator[](i));
		}
		return res;
	}

	Datum res = d;
	if (res.type == INT) {
		res.u.i = -res.u.i;
	} else if (res.type == FLOAT) {
		res.u.f = -res.u.f;
	} else {
		warning("LC::negateData(): not supported for type %s", res.type2str());
	}

	return res;
}

void LC::c_negate() {
	Datum d = g_lingo->pop();
	g_lingo->push(negateData(d));
}

void LC::c_ampersand() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Datum res(d1.asString() + d2.asString());
	g_lingo->push(res);
}

void LC::c_putbefore() {
	Datum var = g_lingo->pop();
	Datum a = g_lingo->pop();
	Datum b = g_lingo->varFetch(var);

	Datum res(a.asString() + b.asString());
	g_lingo->varAssign(var, res);
}

void LC::c_putafter() {
	Datum var = g_lingo->pop();
	Datum a = g_lingo->pop();
	Datum b = g_lingo->varFetch(var);

	Datum res(b.asString() + a.asString());
	g_lingo->varAssign(var, res);
}

void LC::c_concat() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Datum res(d1.asString() + " " + d2.asString());
	g_lingo->push(res);
}

void LC::c_contains() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Common::String s1 = toLowercaseMac(d1.asString());
	Common::String s2 = toLowercaseMac(d2.asString());

	int res = s1.contains(s2) ? 1 : 0;

	g_lingo->push(Datum(res));
}

void LC::c_starts() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Common::String s1 = toLowercaseMac(d1.asString());
	Common::String s2 = toLowercaseMac(d2.asString());

	int res = s1.hasPrefix(s2) ? 1 : 0;

	d1.type = INT;
	d1.u.i = res;

	g_lingo->push(d1);
}

void LC::c_intersects() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Score *score = g_director->getCurrentMovie()->getScore();
	Channel *sprite1 = score->getChannelById(d1.asInt());
	Channel *sprite2 = score->getChannelById(d2.asInt());

	if (!sprite1 || !sprite2) {
		g_lingo->push(Datum(0));
		return;
	}

	if (sprite1->_sprite->_ink == kInkTypeMatte && sprite2->_sprite->_ink == kInkTypeMatte) {
		g_lingo->push(Datum(sprite2->isMatteIntersect(sprite1)));
	} else {
		g_lingo->push(Datum(sprite2->getBbox().intersects(sprite1->getBbox())));
	}
}

void LC::c_within() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Score *score = g_director->getCurrentMovie()->getScore();
	Channel *sprite1 = score->getChannelById(d1.asInt());
	Channel *sprite2 = score->getChannelById(d2.asInt());

	if (!sprite1 || !sprite2) {
		g_lingo->push(Datum(0));
		return;
	}

	if (sprite1->_sprite->_ink == kInkTypeMatte && sprite2->_sprite->_ink == kInkTypeMatte) {
		g_lingo->push(Datum(sprite2->isMatteWithin(sprite1)));
	} else {
		g_lingo->push(Datum(sprite1->getBbox().contains(sprite2->getBbox())));
	}
}

void LC::c_of() {
	// put char 5 of word 1 of line 2 into field "thing"
	Datum target = g_lingo->pop();
	Datum last_line = g_lingo->pop();
	Datum first_line = g_lingo->pop();
	Datum last_item = g_lingo->pop();
	Datum first_item = g_lingo->pop();
	Datum last_word = g_lingo->pop();
	Datum first_word = g_lingo->pop();
	Datum last_char = g_lingo->pop();
	Datum first_char = g_lingo->pop();

	Common::String result = target.asString();

	if (first_line.u.i > 0) {
		Common::String newline("\r");
		int first = first_line.u.i;
		int last = first;
		if (last_line.u.i > 0) {
			if ((first_item.u.i > 0) || (first_word.u.i > 0) || (first_char.u.i > 0)) {
				warning("LC::c_of(): last_line defined but unused");
			} else if (last_line.u.i < first_line.u.i) {
				warning("LC::c_of(): last_line before first_line, ignoring");
			} else {
				last = last_line.u.i;
			}
		}
		uint32 pointer = 0;
		int curLine = 0;
		int firstIndex = -1;
		int lastIndex = -1;
		while (pointer < result.size()) {
			curLine += 1;
			if (curLine == first) {
				firstIndex = pointer;
			}
			pointer = result.find(newline, pointer);
			if (curLine == last) {
				lastIndex = pointer;
				break;
			}
		}
		if (firstIndex < 0 || lastIndex < 0) {
			warning("LC::c_of(): first_line or last_line out of range");
			result = "";
		} else {
			result = result.substr(firstIndex, lastIndex);
		}
	}

	if (first_item.u.i > 0 || last_item.u.i > 0) {
		warning("STUB: LC::c_of() item indexing");
	}

	if (first_word.u.i > 0) {
		int first = first_word.u.i;
		int last = first;
		if (last_word.u.i > 0) {
			if (first_char.u.i > 0) {
				warning("LC::c_of(): last_word defined but unused");
			} else if (last_word.u.i < first_word.u.i) {
				warning("LC::c_of(): last_word before first_word, ignoring");
			} else {
				last = last_word.u.i;
			}
		}
		uint32 pointer = 0;
		int curWord = 0;
		int firstIndex = -1;
		int lastIndex = -1;
		bool inWord = false;
		while (pointer < result.size()) {
			if ((result[pointer] == '\r') || (result[pointer] == '\t') ||
				(result[pointer] == '\n') || (result[pointer] == ' ')) {
				if (inWord) {
					inWord = false;
					if (last == curWord) {
						break;
					}
				}
			} else {
				if (!inWord) {
					inWord = true;
					curWord += 1;
					if (first == curWord) {
						firstIndex = pointer;
					}
				}
			}
			pointer += 1;
		}
		lastIndex = pointer;
		if (firstIndex < 0) {
			warning("LC::c_of(): first_word out of range");
			result = "";
		} else {
			result = result.substr(firstIndex, lastIndex - firstIndex);
		}
	}

	if (first_char.u.i > 0) {
		int first = first_char.u.i;
		int last = first;
		if (last_char.u.i > 0) {
			if (last_char.u.i < first_char.u.i) {
				warning("LC::c_of(): last_char before first_char, ignoring");
			} else {
				last = last_char.u.i;
			}
		}
		result = result.substr(first - 1, last - first);
	}

	target = Datum(result);

	g_lingo->push(target);
}

void LC::c_charOf() {
	Datum d2 = g_lingo->pop(); // string
	Datum d1 = g_lingo->pop(); // index

    if ((d1.type != INT && d1.type != FLOAT) || d2.type != STRING) {
		warning("LC::c_charOf(): Called with wrong data types: %s and %s", d1.type2str(), d2.type2str());
		g_lingo->push(Datum(""));
		return;
	}

	Datum res;
	int index = d1.asInt();
	Common::String chunkExpr = *d2.u.s;

	if (index < 1)
		res = Datum(chunkExpr);
	else if (uint(index) > chunkExpr.size())
		res = Datum("");
	else
		res = Datum(Common::String(chunkExpr[index - 1]));
	g_lingo->push(res);
}

void LC::c_charToOf() {
	Datum d3 = g_lingo->pop(); // string
	Datum d2 = g_lingo->pop(); // indexFrom
	Datum d1 = g_lingo->pop(); // indexTo

	if ((d1.type != INT && d1.type != FLOAT) || (d2.type != INT && d2.type != FLOAT) || d3.type != STRING) {
		warning("LC::c_charToOf(): Called with wrong data types: %s, %s and %s", d1.type2str(), d2.type2str(), d3.type2str());
		g_lingo->push(Datum(""));
		return;
	}

	int indexFrom = d1.asInt();
	int indexTo = d2.asInt();
	Common::String chunkExpr = *d3.u.s;

	Datum res;
	// The if order is important. It mimicks the checks, i.e. bugs, of Director 4.
	if (indexFrom < 0)
		res = Datum(chunkExpr);
	else if (indexTo < 0)
		res = Datum(Common::String(chunkExpr[indexTo - 1])); // treat as charOf
	else if (indexFrom > indexTo)
		res = Datum("");
	else if (uint(indexFrom) > chunkExpr.size())
		res = Datum("");
	else
		res = Datum(chunkExpr.substr(indexFrom - 1, indexTo - indexFrom + 1));
	g_lingo->push(res);
}

void LC::c_itemOf() {

	Datum d2 = g_lingo->pop(); // chunkExpression
	Datum d1 = g_lingo->pop(); // index

	char delimiter = g_lingo->_itemDelimiter;

	if ((d1.type != INT && d1.type != FLOAT) ||  d2.type != STRING) {
		warning("LC::c_itemOf(): Called with wrong data types: %s and %s", d1.type2str(), d2.type2str());
		g_lingo->push(Datum(""));
		return;
	}

	int index = d1.asInt();

	if (index < 1) {
		// returns the input string
		g_lingo->push(d2);
		return;
	}
	Common::String chunkExpr = *d2.u.s;
	uint startPos = 0;

	while (index-- > 1) {
		startPos = chunkExpr.find(delimiter, startPos);
		if (startPos == Common::String::npos)
			break;
		startPos++;  // skipping comma
	}

	Datum res;
	if (startPos == Common::String::npos) {
		res = Datum("");
	} else {
		uint endPos = chunkExpr.find(delimiter, startPos);
		if (endPos == Common::String::npos)
			endPos = chunkExpr.size();
		res = Datum(chunkExpr.substr(startPos, endPos - startPos));
	}

	g_lingo->push(res);
}

void LC::c_itemToOf() {
	Datum d3 = g_lingo->pop();
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	warning("STUB: LC::c_itemToOf(): %d %d %d", d1.u.i, d2.u.i, d3.u.i);

	g_lingo->push(d1);
}

void LC::c_lineOf() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	warning("STUB: LC::c_lineOf(): %d %d", d1.u.i, d2.u.i);

	g_lingo->push(d1);
}

void LC::c_lineToOf() {
	Datum d3 = g_lingo->pop();
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	warning("STUB: LC::c_lineToOf(): %d %d %d", d1.u.i, d2.u.i, d3.u.i);

	g_lingo->push(d1);
}

void LC::c_wordOf() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	warning("STUB: LC::c_wordOf(): %d %d", d1.u.i, d2.u.i);

	g_lingo->push(d1);
}

void LC::c_wordToOf() {
	Datum d3 = g_lingo->pop();
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	warning("STUB: LC::c_wordToOf(): %d %d %d", d1.u.i, d2.u.i, d3.u.i);

	g_lingo->push(d1);
}

void LC::c_and() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Datum res((d1.asInt() && d2.asInt()) ? 1 : 0);

	g_lingo->push(res);
}

void LC::c_or() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();

	Datum res((d1.asInt() || d2.asInt()) ? 1 : 0);

	g_lingo->push(res);
}

void LC::c_not() {
	Datum d = g_lingo->pop();

	Datum res(d.asInt() == 0 ? 1 : 0);

	g_lingo->push(res);
}

Datum LC::compareArrays(Datum (*compareFunc)(Datum, Datum), Datum d1, Datum d2, bool location, bool value) {
	// At least one of d1 and d2 must be an array
	uint arraySize;
	if (d1.type == ARRAY && d2.type == ARRAY) {
		arraySize = MIN(d1.u.farr->size(), d2.u.farr->size());
	} else if (d1.type == PARRAY && d2.type == PARRAY) {
		arraySize = MIN(d1.u.parr->size(), d2.u.parr->size());
	} else if (d1.type == ARRAY) {
		arraySize = d1.u.farr->size();
	} else if (d1.type == PARRAY) {
		arraySize = d1.u.parr->size();
	} else if (d2.type == ARRAY) {
		arraySize = d2.u.farr->size();
	} else if (d2.type == PARRAY) {
		arraySize = d2.u.parr->size();
	} else {
		warning("LC::compareArrays(): Called with wrong data types: %s and %s", d1.type2str(), d2.type2str());
		return Datum(0);
	}

	Datum res;
	res.type = INT;
	res.u.i = location ? -1 : 1;
	Datum a = d1;
	Datum b = d2;
	for (uint i = 0; i < arraySize; i++) {
		if (d1.type == ARRAY) {
			a = d1.u.farr->operator[](i);
		} else if (d1.type == PARRAY) {
			PCell t = d1.u.parr->operator[](i);
			a = value ? t.v : t.p;
		}

		if (d2.type == ARRAY) {
			b = d2.u.farr->operator[](i);
		} else if (d2.type == PARRAY) {
			PCell t = d2.u.parr->operator[](i);
			b = value ? t.v : t.p;
		}

		res = compareFunc(a, b);
		if (!location) {
			if (res.u.i == 0) {
				break;
			}
		} else {
			if (res.u.i == 1) {
				// Lingo indexing starts at 1
				res.u.i = (int)i + 1;
				break;
			}
		}
	}
	return res;
}

Datum LC::eqData(Datum d1, Datum d2) {
	// Lingo doesn't bother checking list equality if the left is longer
	if (d1.type == ARRAY && d2.type == ARRAY &&
			d1.u.farr->size() > d2.u.farr->size()) {
		return Datum(0);
	}
	if (d1.type == PARRAY && d2.type == PARRAY &&
			d1.u.parr->size() > d2.u.parr->size()) {
		return Datum(0);
	}
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::eqData, d1, d2, false, true);
	}
	d1.u.i = d1.equalTo(d2, true);
	d1.type = INT;
	return d1;
}

void LC::c_eq() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::eqData(d1, d2));
}

Datum LC::neqData(Datum d1, Datum d2) {
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::neqData, d1, d2, false, true);
	}
	d1.u.i = !d1.equalTo(d2, true);
	d1.type = INT;
	return d1;
}

void LC::c_neq() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::neqData(d1, d2));
}

Datum LC::gtData(Datum d1, Datum d2) {
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::gtData, d1, d2, false, true);
	}
	d1.u.i = (d1.compareTo(d2) > 0) ? 1 : 0;
	d1.type = INT;
	return d1;
}

void LC::c_gt() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::gtData(d1, d2));
}

Datum LC::ltData(Datum d1, Datum d2) {
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::ltData, d1, d2, false, true);
	}
	d1.u.i = (d1.compareTo(d2) < 0) ? 1 : 0;
	d1.type = INT;
	return d1;
}

void LC::c_lt() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::ltData(d1, d2));
}

Datum LC::geData(Datum d1, Datum d2) {
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::geData, d1, d2, false, true);
	}
	d1.u.i = (d1.compareTo(d2) >= 0) ? 1 : 0;
	d1.type = INT;
	return d1;
}

void LC::c_ge() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::geData(d1, d2));
}

Datum LC::leData(Datum d1, Datum d2) {
	if (d1.type == ARRAY || d2.type == ARRAY ||
			d1.type == PARRAY || d2.type == PARRAY) {
		return LC::compareArrays(LC::leData, d1, d2, false, true);
	}
	d1.u.i = (d1.compareTo(d2) <= 0) ? 1 : 0;
	d1.type = INT;
	return d1;
}

void LC::c_le() {
	Datum d2 = g_lingo->pop();
	Datum d1 = g_lingo->pop();
	g_lingo->push(LC::leData(d1, d2));
}

void LC::c_jump() {
	int jump = g_lingo->readInt();
	g_lingo->_pc = g_lingo->_pc + jump - 2;
}

void LC::c_jumpifz() {
	int jump = g_lingo->readInt();
	int test = g_lingo->pop().asInt();
	if (test == 0) {
		g_lingo->_pc = g_lingo->_pc + jump - 2;
	}
}

void LC::c_whencode() {
	Common::String eventname(g_lingo->readString());
	Datum code = g_lingo->pop();
	Datum nullId;

	// the following when events are supported by D3
	if (eventname.equalsIgnoreCase("keyDown")) {
		g_lingo->setTheEntity(kTheKeyDownScript, nullId, kTheNOField, code);
	} else if (eventname.equalsIgnoreCase("keyUp")) {
		g_lingo->setTheEntity(kTheKeyUpScript, nullId, kTheNOField, code);
	} else if (eventname.equalsIgnoreCase("mouseDown")) {
		g_lingo->setTheEntity(kTheMouseDownScript, nullId, kTheNOField, code);
	} else if (eventname.equalsIgnoreCase("mouseUp")) {
		g_lingo->setTheEntity(kTheMouseUpScript, nullId, kTheNOField, code);
	} else if (eventname.equalsIgnoreCase("timeOut")) {
		g_lingo->setTheEntity(kTheTimeoutScript, nullId, kTheNOField, code);
	} else {
		warning("LC::c_whencode(): unsupported event handler %s", eventname.c_str());
	}
}

void LC::c_tell() {
	// swap out current window
	Datum window = g_lingo->pop();
	g_lingo->push(g_director->getCurrentWindow());
	if (window.type != OBJECT || window.u.obj->getObjType() != kWindowObj) {
		warning("LC::c_tell(): wrong argument type: %s", window.type2str());
		return;
	}
	if (static_cast<Window *>(window.u.obj)->getCurrentMovie() == nullptr) {
		warning("LC::c_tell(): window has no movie");
		return;
	}
	g_director->setCurrentWindow(static_cast<Window *>(window.u.obj));

}

void LC::c_telldone() {
	Datum returnWindow = g_lingo->pop();
	if (returnWindow.type != OBJECT || returnWindow.u.obj->getObjType() != kWindowObj) {
		warning("LC::c_telldone(): wrong return window type: %s", returnWindow.type2str());
		return;
	}
	g_director->setCurrentWindow(static_cast<Window *>(returnWindow.u.obj));
}


//************************
// Built-in functions
//************************
void LC::c_goto() {
	Datum mode = g_lingo->pop();
	Datum frame, movie;

	if (mode.u.i == 2 || mode.u.i == 3)
		movie = g_lingo->pop();

	if (mode.u.i == 1 || mode.u.i == 3)
		frame = g_lingo->pop();

	g_lingo->func_goto(frame, movie);
}

void LC::c_gotoloop() {
	g_lingo->func_gotoloop();
}

void LC::c_gotonext() {
	g_lingo->func_gotonext();
}

void LC::c_gotoprevious() {
	g_lingo->func_gotoprevious();
}

void LC::c_play() {
	Datum mode = g_lingo->pop();
	Datum frame, movie;

	if (mode.u.i == 2 || mode.u.i == 3)
		movie = g_lingo->pop();

	if (mode.u.i == 1 || mode.u.i == 3)
		frame = g_lingo->pop();

	g_lingo->func_play(frame, movie);
}

void LC::c_callcmd() {
	Common::String name(g_lingo->readString());

	int nargs = g_lingo->readInt();

	LC::call(name, nargs, false);
}

void LC::c_callfunc() {
	Common::String name(g_lingo->readString());

	int nargs = g_lingo->readInt();

	LC::call(name, nargs, true);
}

void LC::call(const Common::String &name, int nargs, bool allowRetVal) {
	if (debugChannelSet(5, kDebugLingoExec))
		g_lingo->printSTUBWithArglist(name.c_str(), nargs, "call:");

	Symbol funcSym;

	if (nargs > 0) {
		Datum firstArg = g_lingo->_stack[g_lingo->_stack.size() - nargs];

		// Factory/XObject method call
		if (firstArg.lazy) { // first arg could be method name
			Datum objName(name);
			objName.type = VAR;
			Datum obj = g_lingo->varFetch(objName, false, nullptr, true);
			if (obj.type == OBJECT && (obj.u.obj->getObjType() & (kFactoryObj | kXObj))) {
				debugC(3, kDebugLingoExec, "Method called on object: <%s>", obj.asString(true).c_str());
				AbstractObject *target = obj.u.obj;
				if (firstArg.u.s->equalsIgnoreCase("mNew")) {
					target = target->clone();
				}
				funcSym = target->getMethod(*firstArg.u.s);
				if (funcSym.type != VOIDSYM) {
					g_lingo->_stack[g_lingo->_stack.size() - nargs] = funcSym.target; // Set first arg to target
					call(funcSym, nargs, allowRetVal);
					return;
				}
			}
			firstArg = firstArg.eval();
		}

		// Script/Xtra method call
		if (firstArg.type == OBJECT && !(firstArg.u.obj->getObjType() & (kFactoryObj | kXObj))) {
			debugC(3, kDebugLingoExec, "Method called on object: <%s>", firstArg.asString(true).c_str());
			AbstractObject *target = firstArg.u.obj;
			if (name.equalsIgnoreCase("birth") || name.equalsIgnoreCase("new")) {
				target = target->clone();
			}
			funcSym = target->getMethod(name);
			if (funcSym.type != VOIDSYM) {
				g_lingo->_stack[g_lingo->_stack.size() - nargs] = funcSym.target; // Set first arg to target
				call(funcSym, nargs, allowRetVal);
				return;
			}
		}
	}

	// Handler
	funcSym = g_lingo->getHandler(name);

	// Builtin
	if (allowRetVal) {
		if (g_lingo->_builtinFuncs.contains(name)) {
			funcSym = g_lingo->_builtinFuncs[name];
		}
	} else {
		if (g_lingo->_builtinCmds.contains(name)) {
			funcSym = g_lingo->_builtinCmds[name];
		}
	}

	call(funcSym, nargs, allowRetVal);
}

void LC::call(const Symbol &funcSym, int nargs, bool allowRetVal) {
	Datum target = funcSym.target;

	if (funcSym.type == VOIDSYM) {
		warning("Call to undefined handler. Dropping %d stack items", nargs);

		for (int i = 0; i < nargs; i++)
			g_lingo->pop();

		// Push dummy value
		if (allowRetVal)
			g_lingo->pushVoid();

		return;
	}

	if (funcSym.type != HANDLER && target.type != VOID) {
		// Drop the target argument (only needed for user-defined methods)
		g_lingo->_stack.remove_at(g_lingo->_stack.size() - nargs);
		nargs--;
	}

	if (funcSym.nargs != -1) {
		if (funcSym.type == HANDLER || funcSym.type == HBLTIN) {
			if (funcSym.maxArgs < nargs) {
				warning("Incorrect number of arguments for handler %s (%d, expected %d to %d). Dropping extra %d",
							funcSym.name->c_str(), nargs, funcSym.nargs, funcSym.maxArgs, nargs - funcSym.maxArgs);
				while (nargs > funcSym.maxArgs) {
					g_lingo->pop();
					nargs--;
				}
			}
			if (funcSym.nargs > nargs) {
				warning("Incorrect number of arguments for handler %s (%d, expected %d to %d). Adding extra %d voids",
							funcSym.name->c_str(), nargs, funcSym.nargs, funcSym.maxArgs, funcSym.nargs - nargs);
				while (nargs < funcSym.nargs) {
					Datum d;
					d.u.s = NULL;
					d.type = VOID;
					g_lingo->push(d);
					nargs++;
				}
			}
		} else if (funcSym.nargs > nargs || funcSym.maxArgs < nargs) {
			warning("Incorrect number of arguments for builtin %s (%d, expected %d to %d). Dropping %d stack items.",
						funcSym.name->c_str(), nargs, funcSym.nargs, funcSym.maxArgs, nargs);

			for (int i = 0; i < nargs; i++)
				g_lingo->pop();

			// Push dummy value
			if (allowRetVal)
				g_lingo->pushVoid();

			return;
		}
	}

	if (funcSym.type != HANDLER) {
		uint stackSizeBefore = g_lingo->_stack.size() - nargs;

		if (target.type != VOID) {
			// Only need to update the me obj
			// Pushing an entire stack frame is not necessary
			Datum retMe = g_lingo->_currentMe;
			g_lingo->_currentMe = target;
			(*funcSym.u.bltin)(nargs);
			g_lingo->_currentMe = retMe;
		} else {
			(*funcSym.u.bltin)(nargs);
		}

		uint stackSize = g_lingo->_stack.size();

		if (funcSym.u.bltin != LB::b_return && funcSym.u.bltin != LB::b_returnNumber && funcSym.u.bltin != LB::b_value) {
			if (stackSize == stackSizeBefore + 1) {
				if (!allowRetVal) {
					warning("dropping return value");
					g_lingo->pop();
				}
			} else if (stackSize == stackSizeBefore) {
				if (allowRetVal)
					error("builtin function %s did not return value", funcSym.name->c_str());
			} else if (stackSize > stackSizeBefore) {
				error("builtin %s returned extra %d values", funcSym.name->c_str(), stackSize - stackSizeBefore);
			} else {
				error("builtin %s popped extra %d values", funcSym.name->c_str(), stackSizeBefore - stackSize);
			}
		}
		return;
	}

	Datum defaultRetVal;
	if (funcSym.target && funcSym.target->getObjType() == kFactoryObj && funcSym.name->equalsIgnoreCase("mNew")) {
		defaultRetVal = funcSym.target; // return me
	}

	g_lingo->pushContext(funcSym, allowRetVal, defaultRetVal);

	g_lingo->_pc = 0;
}

void LC::c_procret() {
	if (g_lingo->_callstack.size() == 0) {
		warning("LC::c_procret(): Call stack underflow");
		g_lingo->_abort = true;
		return;
	}

	g_lingo->popContext();

	if (g_lingo->_callstack.size() == 0) {
		debugC(5, kDebugLingoExec, "Call stack empty, returning");
		g_lingo->_abort = true;
		return;
	}
}

void LC::c_hilite() {
	Datum first_char = g_lingo->pop();
	Datum last_char = g_lingo->pop();
	Datum first_word = g_lingo->pop();
	Datum last_word = g_lingo->pop();
	Datum first_item = g_lingo->pop();
	Datum last_item = g_lingo->pop();
	Datum first_line = g_lingo->pop();
	Datum last_line = g_lingo->pop();
	Datum cast_id = g_lingo->pop();

	warning("STUB: LC::c_hilite(): %d %d %d %d %d %d %d %d %d",
		first_char.u.i, last_char.u.i, first_word.u.i, last_word.u.i,
		first_item.u.i, last_item.u.i, first_line.u.i, last_line.u.i,
		cast_id.u.i);
}

}
