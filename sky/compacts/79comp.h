/* ScummVM - Scumm Interpreter
 * Copyright (C) 2003 The ScummVM project
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$ 
 *
 */

#ifndef SKY79COMP_H
#define SKY79COMP_H




namespace SkyCompact {

uint16 sc791_palette[] = {
	0,
	1024,
	514,
	771,
	1540,
	514,
	772,
	1283,
	1027,
	1028,
	1030,
	1029,
	775,
	1540,
	1540,
	1286,
	2308,
	771,
	1033,
	1028,
	1542,
	1288,
	1284,
	2054,
	1034,
	2053,
	1541,
	1542,
	3078,
	1283,
	1290,
	1284,
	1799,
	1543,
	3080,
	1029,
	1800,
	2566,
	1286,
	1038,
	1540,
	2056,
	1545,
	1800,
	1799,
	1040,
	3332,
	1541,
	2056,
	1800,
	2568,
	1547,
	3591,
	1030,
	1042,
	2564,
	1800,
	2058,
	2313,
	2057,
	1295,
	3078,
	1800,
	2568,
	4361,
	1541,
	1806,
	2054,
	2826,
	1806,
	2568,
	2058,
	1808,
	3078,
	2313,
	1301,
	2565,
	2570,
	1810,
	2565,
	3082,
	2064,
	3592,
	2057,
	2825,
	3595,
	2569,
	1810,
	3079,
	2571,
	3082,
	3084,
	3083,
	2576,
	4617,
	1801,
	1560,
	5638,
	1287,
	2322,
	3593,
	2571,
	1814,
	5127,
	2313,
	3340,
	3596,
	3084,
	3340,
	6670,
	1286,
	2072,
	4102,
	2827,
	3345,
	3853,
	3342,
	3853,
	5390,
	2827,
	2331,
	6409,
	2570,
	4110,
	8208,
	1543,
	2333,
	7944,
	2056,
	2839,
	5387,
	3085,
	4112,
	7439,
	2570,
	2083,
	4614,
	4881,
	2847,
	6923,
	3342,
	3865,
	9230,
	2059,
	3106,
	7433,
	3086,
	2343,
	8455,
	2829,
	2854,
	8200,
	3856,
	3366,
	8716,
	3599,
	3368,
	11021,
	2572,
	3624,
	11531,
	2572,
	3882,
	9742,
	3858,
	4140,
	10766,
	3601,
	4656,
	11021,
	4627,
	4402,
	12045,
	4114,
	5173,
	12303,
	4886,
	5427,
	12817,
	4886,
	6702,
	8472,
	8737,
	8483,
	14625,
	4632,
	6710,
	13589,
	5915,
	9272,
	8993,
	8481,
	3086,
	4364,
	3855,
	4628,
	5906,
	5397,
	6171,
	7704,
	6939,
	7713,
	9246,
	8738,
	9512,
	11045,
	10537,
	11310,
	12844,
	12336,
	13109,
	14387,
	14135,
	15163,
	16187,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	0,
	14336,
	13364,
	11569,
	9261,
	8481,
	6687,
	6681,
	4626,
	2578,
	1803,
	770,
	519,
	13571,
	9517,
	9778,
	11805,
	5151,
	5926,
	8205,
	1808,
	2586,
	11267,
	2056,
	8210,
	7441,
	6954,
	9494,
	4119,
	3866,
	4864,
	13316,
	13364,
	11563,
	8751,
	9506,
	10024,
	8242,
	10527,
	6174,
	5927,
	7698,
	3600,
	2325,
	2308,
	11573,
	12837,
	7462,
	7982,
	9748,
	3351,
	4128,
	6663,
	778,
	9533,
	13100,
	9244,
	5162,
	8476,
	5390,
	2072,
	3855,
	2308,
	2865,
	9995,
	1285,
	285,
	4865,
	0,
	11573,
	12837,
	7462,
	0,
	16128,
	0,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	13887,
	13878,
	12077,
	8241,
	10527,
	5917,
	5925,
	7698,
	2865,
	9995,
	1285,
	285,
	16129,
	16191,
};

uint16 sc79_chip_list[] = {
	IT_SC79_LAYER_0+DISK_10,
	IT_SC79_SUPPORT+DISK_10,
	IT_SC79_CROUCH+DISK_10,
	IT_SC79_CLIMB+DISK_10,
	IT_SC79_TIE_ROPE+DISK_10,
	IT_SC79_TOSS_ROPE+DISK_10,
	IT_SC79_ROPE+DISK_10,
	IT_SC79_KNOT+DISK_10,
	0,
};

uint16 sc79_climb_up[] = {
	92*64,
	372,
	280,
	24,
	366,
	280,
	23,
	368,
	280,
	22,
	365,
	280,
	21,
	364,
	280,
	20,
	364,
	280,
	19,
	364,
	280,
	18,
	363,
	280,
	17,
	367,
	280,
	16,
	365,
	280,
	15,
	363,
	280,
	14,
	363,
	280,
	13,
	363,
	280,
	12,
	362,
	277,
	11,
	365,
	276,
	10,
	364,
	271,
	9,
	353,
	266,
	8,
	353,
	265,
	7,
	352,
	264,
	6,
	352,
	262,
	5,
	346,
	262,
	4,
	340,
	263,
	3,
	335,
	262,
	2,
	330,
	261,
	1,
	323,
	258,
	0,
	0,
	0,
};

Compact sc79_exit = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	79,	// screen
	0,	// place
	0,	// getToTable
	128,	// xcood
	210,	// ycood
	0,	// frame
	1+T7,	// cursorText
	STD_EXIT_LEFT_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	155-128,	// mouseSize_x
	280-210,	// mouseSize_y
	SC79_EXIT_ACTION,	// actionScript
};

Compact sc79_rope = {
	L_SCRIPT,	// logic
	ST_LOGIC+ST_RECREATE,	// status
	0,	// sync
	79,	// screen
	0,	// place
	0,	// getToTable
	288,	// xcood
	306,	// ycood
	98*64,	// frame
	49,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	65531,	// mouseRel_x
	0,	// mouseRel_y
	332-325,	// mouseSize_x
	327-305,	// mouseSize_y
	SC79_ROPE_ACTION,	// actionScript
	0,	// upFlag
	0,	// downFlag
	0,	// getToFlag
	0,	// flag
	0,	// mood
	0,	// grafixProg
	0,	// offset
	C_BASE_MODE,	// mode
	SC79_ROPE_LOGIC,	// baseSub
	0,	// baseSub_off
};

Compact sc79_support = {
	0,	// logic
	ST_MOUSE+ST_FOREGROUND,	// status
	0,	// sync
	79,	// screen
	0,	// place
	0,	// getToTable
	275,	// xcood
	267,	// ycood
	48*64,	// frame
	20573,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	65533,	// mouseRel_y
	296-275,	// mouseSize_x
	315-264,	// mouseSize_y
	SC79_SUPPORT_ACTION,	// actionScript
};

uint16 sc79_palette[] = {
	0,
	1024,
	514,
	771,
	1540,
	514,
	772,
	1283,
	1027,
	1028,
	1030,
	1029,
	775,
	1540,
	1540,
	1286,
	2308,
	771,
	1033,
	1028,
	1542,
	1288,
	1284,
	2054,
	1034,
	2053,
	1541,
	1542,
	3078,
	1283,
	1290,
	1284,
	1799,
	1543,
	3080,
	1029,
	1800,
	2566,
	1286,
	1038,
	1540,
	2056,
	1545,
	1800,
	1799,
	1040,
	3332,
	1541,
	2056,
	1800,
	2568,
	1547,
	3591,
	1030,
	1042,
	2564,
	1800,
	2058,
	2313,
	2057,
	1295,
	3078,
	1800,
	2568,
	4361,
	1541,
	1806,
	2054,
	2826,
	1806,
	2568,
	2058,
	1808,
	3078,
	2313,
	1301,
	2565,
	2570,
	1810,
	2565,
	3082,
	2064,
	3592,
	2057,
	2825,
	3595,
	2569,
	1810,
	3079,
	2571,
	3082,
	3084,
	3083,
	2576,
	4617,
	1801,
	1560,
	5638,
	1287,
	2322,
	3593,
	2571,
	1814,
	5127,
	2313,
	3340,
	3596,
	3084,
	3340,
	6670,
	1286,
	2072,
	4102,
	2827,
	3345,
	3853,
	3342,
	3853,
	5390,
	2827,
	2331,
	6409,
	2570,
	4110,
	8208,
	1543,
	2333,
	7944,
	2056,
	2839,
	5387,
	3085,
	4112,
	7439,
	2570,
	2083,
	4614,
	4881,
	2847,
	6923,
	3342,
	3865,
	9230,
	2059,
	3106,
	7433,
	3086,
	2343,
	8455,
	2829,
	2854,
	8200,
	3856,
	3366,
	8716,
	3599,
	3368,
	11021,
	2572,
	3624,
	11531,
	2572,
	3882,
	9742,
	3858,
	4140,
	10766,
	3601,
	4656,
	11021,
	4627,
	4402,
	12045,
	4114,
	5173,
	12303,
	4886,
	5427,
	12817,
	4886,
	6702,
	8472,
	8737,
	8483,
	14625,
	4632,
	6710,
	13589,
	5915,
	9272,
	8993,
	8481,
	3086,
	4364,
	3855,
	4628,
	5906,
	5397,
	6171,
	7704,
	6939,
	7713,
	9246,
	8738,
	9512,
	11045,
	10537,
	11310,
	12844,
	12336,
	13109,
	14387,
	14135,
	15163,
	16187,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	0,
	14336,
	13364,
	11569,
	9261,
	8481,
	6687,
	6681,
	4626,
	2578,
	1803,
	770,
	519,
	13571,
	9517,
	9778,
	11805,
	5151,
	5926,
	8205,
	1808,
	2586,
	11267,
	2056,
	8210,
	7441,
	6954,
	9494,
	4119,
	3866,
	4864,
	13316,
	13364,
	11563,
	8751,
	9506,
	10024,
	8242,
	10527,
	6174,
	5927,
	7698,
	3600,
	2325,
	2308,
	11573,
	12837,
	7462,
	7982,
	9748,
	3351,
	4128,
	6663,
	778,
	9533,
	13100,
	9244,
	5162,
	8476,
	5390,
	2072,
	3855,
	2308,
	2865,
	9995,
	1285,
	285,
	4865,
	0,
	11573,
	12837,
	7462,
	0,
	16128,
	0,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	16191,
	13887,
	13878,
	12077,
	8241,
	10527,
	5917,
	5925,
	7698,
	2865,
	9995,
	1285,
	285,
	16129,
	16191,
};

uint16 sc79_climb_down[] = {
	92*64,
	323,
	258,
	0,
	330,
	261,
	1,
	335,
	262,
	2,
	340,
	263,
	3,
	346,
	262,
	4,
	352,
	262,
	5,
	352,
	264,
	6,
	353,
	265,
	7,
	353,
	266,
	8,
	364,
	271,
	9,
	365,
	276,
	10,
	362,
	277,
	11,
	363,
	280,
	12,
	363,
	280,
	13,
	363,
	280,
	14,
	365,
	280,
	15,
	367,
	280,
	16,
	363,
	280,
	17,
	364,
	280,
	18,
	364,
	280,
	19,
	364,
	280,
	20,
	365,
	280,
	21,
	368,
	280,
	22,
	366,
	280,
	23,
	372,
	280,
	24,
	0,
	0,
};

uint16 sc79_crouch_down[] = {
	91*64,
	348,
	226,
	0,
	345,
	227,
	1,
	340,
	231,
	2,
	338,
	239,
	3,
	335,
	248,
	4,
	335,
	250,
	5,
	329,
	251,
	6,
	321,
	256,
	7,
	315,
	259,
	8,
	318,
	259,
	9,
	0,
	0,
};

uint16 sc79_pipe_table[] = {
	ID_SC79_PIPE,
	RET_OK,
	ID_SC79_EXIT,
	GT_SC79_EXIT,
	0,
	SC79_EXIT_WALK_ON,
	ID_SC79_SUPPORT,
	GT_SC79_SUPPORT,
	ID_SC79_LADDER,
	GT_SC79_LADDER,
	ID_SC79_KNOT,
	GT_SC79_KNOT,
	ID_SC79_ROPE,
	GT_SC79_ROPE,
	65535,
};

uint16 reset_78_79[] = {
	C_SCREEN,
	79,
	C_PLACE,
	ID_SC79_PIPE,
	C_XCOOD,
	OFF_LEFT,
	C_YCOOD,
	272,
	65535,
};

uint16 sc79_crouch_up[] = {
	91*64,
	318,
	259,
	9,
	315,
	259,
	8,
	321,
	256,
	7,
	329,
	251,
	6,
	335,
	250,
	5,
	335,
	248,
	4,
	338,
	239,
	3,
	340,
	231,
	2,
	345,
	227,
	1,
	348,
	226,
	0,
	0,
	0,
};

uint16 sc79_rope_anim[] = {
	98*64,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	310,
	304,
	0,
	321,
	304,
	1,
	314,
	304,
	2,
	311,
	304,
	3,
	311,
	304,
	4,
	310,
	304,
	5,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	310,
	304,
	4,
	0,
};

Compact sc79_knot = {
	L_SCRIPT,	// logic
	ST_LOGIC,	// status
	0,	// sync
	79,	// screen
	0,	// place
	0,	// getToTable
	288,	// xcood
	265,	// ycood
	101*64,	// frame
	20892,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	298-288,	// mouseSize_x
	275-265,	// mouseSize_y
	SC79_KNOT_ACTION,	// actionScript
	0,	// upFlag
	0,	// downFlag
	0,	// getToFlag
	0,	// flag
	0,	// mood
	0,	// grafixProg
	0,	// offset
	C_BASE_MODE,	// mode
	SC79_KNOT_LOGIC,	// baseSub
	0,	// baseSub_off
};

uint16 sc79_fast_list[] = {
	12+DISK_10,
	51+DISK_10,
	52+DISK_10,
	53+DISK_10,
	54+DISK_10,
	268+DISK_10,
	0,
};

uint16 reset_80_79[] = {
	C_SCREEN,
	79,
	C_PLACE,
	ID_SC79_PIPE,
	65535,
};

Compact sc79_ladder = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	79,	// screen
	0,	// place
	0,	// getToTable
	361,	// xcood
	284,	// ycood
	0,	// frame
	20828,	// cursorText
	STD_ON,	// mouseOn
	STD_OFF,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	368-361,	// mouseSize_x
	327-284,	// mouseSize_y
	SC79_LADDER_ACTION,	// actionScript
};

uint16 sc79_toss_rope[] = {
	97*64,
	284,
	236,
	0,
	285,
	231,
	1,
	285,
	231,
	1,
	285,
	226,
	2,
	285,
	226,
	3,
	285,
	226,
	3,
	285,
	226,
	4,
	285,
	226,
	5,
	285,
	226,
	6,
	285,
	226,
	7,
	285,
	226,
	8,
	285,
	226,
	9,
	285,
	224,
	10,
	285,
	223,
	11,
	285,
	226,
	12,
	285,
	226,
	13,
	285,
	226,
	14,
	285,
	226,
	15,
	285,
	226,
	16,
	285,
	226,
	17,
	285,
	226,
	18,
	285,
	226,
	19,
	285,
	226,
	20,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	285,
	226,
	21,
	0,
};

uint32 *grid79 = 0;

uint16 sc79_logic_list[] = {
	ID_FOSTER,
	ID_SC79_SUPPORT,
	ID_SC79_ROPE,
	ID_SC79_KNOT,
	ID_SC67_PULSE1,
	0XFFFF,
	ID_STD_MENU_LOGIC,
};

uint16 sc79_mouse_list[] = {
	ID_SC79_EXIT,
	ID_SC79_LADDER,
	ID_SC79_ROPE,
	ID_SC79_KNOT,
	ID_SC79_SUPPORT,
	ID_SC79_PIPE,
	0XFFFF,
	ID_TEXT_MOUSE,
};

uint16 sc79_tie_rope[] = {
	96*64,
	285,
	231,
	0,
	284,
	236,
	1,
	284,
	238,
	2,
	284,
	240,
	3,
	284,
	241,
	4,
	284,
	241,
	5,
	284,
	241,
	6,
	284,
	241,
	7,
	284,
	241,
	8,
	284,
	242,
	9,
	284,
	242,
	9,
	284,
	241,
	8,
	284,
	241,
	7,
	284,
	241,
	6,
	284,
	241,
	6,
	284,
	241,
	7,
	284,
	241,
	8,
	284,
	242,
	9,
	284,
	241,
	8,
	284,
	242,
	9,
	0,
};

Compact sc79_pipe = {
	0,	// logic
	ST_MOUSE,	// status
	0,	// sync
	79,	// screen
	0,	// place
	sc79_pipe_table,	// getToTable
	128,	// xcood
	270,	// ycood
	0,	// frame
	0,	// cursorText
	0,	// mouseOn
	0,	// mouseOff
	ADVISOR_188,	// mouseClick
	0,	// mouseRel_x
	0,	// mouseRel_y
	360-128,	// mouseSize_x
	280-270,	// mouseSize_y
	FLOOR_ACTION,	// actionScript
};

}; // namespace SkyCompact

#endif
