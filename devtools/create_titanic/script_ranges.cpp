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

 // Disable symbol overrides so that we can use system headers.
#define FORBIDDEN_SYMBOL_ALLOW_ALL

// HACK to allow building with the SDL backend on MinGW
// see bug #1800764 "TOOLS: MinGW tools building broken"
#ifdef main
#undef main
#endif // main

#include "file.h"
#include "script_ranges.h"

const uint BARBOT_RANGE1[] = { 250062, 250064, 250065, 250066, 250067, 250068, 250069, 250070, 250071, 250063, 0 };
const uint BARBOT_RANGE2[] = { 250200, 250201, 250202, 250203, 250204, 250205, 250206, 250207, 0 };
const uint BARBOT_RANGE3[] = { 250160, 250161, 250162, 250163, 0 };
const uint BARBOT_RANGE4[] = { 250175, 250176, 250177, 250178, 250179, 250180, 250181, 250182, 250183, 0 };
const uint BARBOT_RANGE5[] = { 250114, 250004, 0 };
const uint BARBOT_RANGE6[] = { 250042, 250009, 250010, 250011, 251692, 251693, 251694, 0 };
const uint BARBOT_RANGE7[] = { 250012, 250111, 0 };
const uint BARBOT_RANGE8[] = { 250013, 250119, 0 };
const uint BARBOT_RANGE9[] = { 250027, 250126, 250055, 0 };
const uint BARBOT_RANGE10[] = { 250032, 250130, 0 };
const uint BARBOT_RANGE11[] = { 250038, 250134, 0 };
const uint BARBOT_RANGE12[] = { 250039, 250135, 250050, 0 };
const uint BARBOT_RANGE13[] = { 250016, 250120, 250136, 250145, 250143, 0 };
const uint BARBOT_RANGE14[] = { 250040, 250138, 250139, 0 };
const uint BARBOT_RANGE15[] = { 250037, 250133, 250617, 0 };
const uint BARBOT_RANGE16[] = { 250031, 250129, 0 };
const uint BARBOT_RANGE17[] = { 250036, 250132, 0 };
const uint BARBOT_RANGE18[] = { 250035, 250137, 0 };
const uint BARBOT_RANGE19[] = { 250021, 250123, 0 };
const uint BARBOT_RANGE20[] = { 250006, 250117, 0 };
const uint BARBOT_RANGE21[] = { 250024, 250124, 0 };
const uint BARBOT_RANGE22[] = { 250002, 250113, 0 };
const uint BARBOT_RANGE23[] = { 250152, 250153, 250079, 250194, 250149, 250151, 250150,
250208, 250209, 250157, 250195, 250076, 250156, 250074,
250075, 250080, 250192, 250109, 250159, 250110, 250148,
250053, 250155, 250197, 250072, 250077, 250001, 250154,
250196, 250198, 250199, 250158, 250073, 0 };
const uint BARBOT_RANGE24[] = { 251831, 251832, 251833, 251834, 251835, 250617, 0 };
const uint BARBOT_RANGE25[] = { 250033, 251838, 0 };
const uint BARBOT_RANGE26[] = { 250014, 251827, 251781, 250617, 0 };
const uint BARBOT_RANGE27[] = { 251855, 251856, 0 };
const uint BARBOT_RANGE28[] = { 251852, 251853, 0 };
const uint BARBOT_RANGE29[] = { 251250, 251261, 251272, 251277, 251278, 251279, 251280,
251281, 251282, 251251, 251252, 251253, 251254, 251255,
251256, 251257, 251258, 251259, 251260, 251262, 251263,
251264, 251265, 251266, 251267, 251268, 251269, 251270,
251271, 251273, 251274, 251275, 251276, 0 };
const uint BARBOT_RANGE30[] = { 251283, 251284, 251285, 251286, 0 };
const uint BARBOT_RANGE31[] = { 250527, 250530, 250531, 250532, 250533, 250534, 250535,
250536, 250537, 250528, 250529, 0 };
const uint BARBOT_RANGE32[] = { 250593, 250594, 0 };
const uint BARBOT_RANGE33[] = { 250263, 250264, 250265, 250266, 0 };
const uint BARBOT_RANGE34[] = { 250227, 250228, 250229, 250230, 0 };
const uint BARBOT_RANGE35[] = { 250239, 250240, 250241, 250242, 250243, 0 };
const uint BARBOT_RANGE36[] = { 250507, 250222, 250678, 250588, 0 };
const uint BARBOT_RANGE37[] = { 250365, 250366, 250367, 250368, 0 };
const uint BARBOT_RANGE38[] = { 250936, 250937, 250938, 0 };
const uint BARBOT_RANGE39[] = { 250610, 250611, 0 };
const uint BARBOT_RANGE40[] = { 250082, 250093, 250102, 250104, 250105, 250106, 250107,
250108, 250091, 250092, 250094, 250095, 250096, 250097,
250098, 250099, 250100, 250101, 251700, 251701, 251702,
251703, 251704, 251862, 250617, 250268, 250272, 0 };
const uint BARBOT_RANGE41[] = { 250584, 250585, 0 };
const uint BARBOT_RANGE42[] = { 250579, 251142, 0 };
const uint BARBOT_RANGE43[] = { 250577, 250578, 0 };
const uint BARBOT_RANGE44[] = { 250244, 250245, 250246, 250247, 250248, 250249, 250250,
250251, 250252, 250253, 250254, 250255, 250256, 250257,
250258, 250259, 250260, 250261, 250262, 0 };
const uint BARBOT_RANGE45[] = { 250286, 250288, 250289, 250290, 250291, 250292, 250293,
250294, 250295, 250287, 0 };
const uint BARBOT_RANGE46[] = { 250296, 250299, 250300, 250301, 250302, 250303, 250304,
250305, 250306, 250297, 250298, 0 };
const uint BARBOT_RANGE47[] = { 250307, 250309, 250310, 250311, 250312, 250313, 250314,
250315, 250316, 0 };
const uint BARBOT_RANGE48[] = { 251682, 251683, 251684, 251685, 251686, 251687, 251688,
251689, 250756, 250757, 250758, 250759, 0 };
const uint BARBOT_RANGE49[] = { 250738, 250742, 250743, 250744, 250745, 250746, 250747,
250748, 250749, 250739, 250740, 250741, 0 };
const uint BARBOT_RANGE50[] = { 250659, 250660, 250661, 250379, 0 };
const uint BARBOT_RANGE51[] = { 251761, 251762, 251763, 251764, 0 };
const uint BARBOT_RANGE52[] = { 251754, 251755, 251756, 251757, 251758, 251759, 0 };
const uint BARBOT_RANGE53[] = { 250482, 250504, 250424, 250463, 250466, 250467, 250468,
250478, 250501, 250502, 250503, 250506, 250413, 251014,
250614, 250756, 250758, 250759, 250223, 250737, 250658,
251027, 250633, 250935, 250237, 251618, 0 };
const uint BARBOT_RANGE54[] = { 250504, 250434, 250436, 250466, 250467, 250468, 250469,
250470, 250472, 250501, 250502, 250503, 250505, 250413,
251681, 250756, 250758, 250759, 250223, 251027, 250633,
250935, 250237, 251618, 250371, 0 };
const uint BARBOT_RANGE55[] = { 250952, 250953, 0 };
const uint BARBOT_RANGE56[] = { 251777, 250951, 0 };
const uint BARBOT_RANGE57[] = { 251871, 251877, 251878, 251879, 251880, 251883, 251884,
251872, 251873, 0 };
const uint BARBOT_RANGE58[] = { 250228, 250236, 250258, 250259, 250378, 250465, 250536,
251016, 251048, 251068, 0 };
const uint BARBOT_RANGE59[] = { 250141, 250378, 251048, 0 };
const uint BARBOT_RANGE60[] = { 251621, 251622, 251623, 251624, 251625, 251626, 0 };
const uint BARBOT_RANGE61[] = { 251650, 251651, 0 };
const uint BARBOT_RANGE62[] = { 251305, 251306, 251307, 251308, 0 };
const uint BARBOT_RANGE63[] = { 251836, 251890, 251891, 251892, 0 };
const uint BARBOT_RANGE64[] = { 250760, 251246, 251156, 251335, 251510, 251059, 251097,
251136, 250374, 250375, 250376, 250377, 251015, 251016,
251017, 251018, 0 };
const uint BARBOT_RANGE65[] = { 250899, 250906, 250948, 250713, 250690, 0 };
const uint BARBOT_RANGE66[] = { 250906, 250948, 250713, 250899, 250690, 0 };
const uint BARBOT_RANGE67[] = { 250949, 250713, 250711, 250152, 250153, 250690, 250906, 0 };
const uint BARBOT_RANGE68[] = { 251815, 250711, 0 };
const uint BARBOT_RANGE69[] = { 251829, 250711, 0 };
const uint BARBOT_RANGE70[] = { 251779, 250712, 0 };

#define BARBOT_RANGE_COUNT 70
const ScriptRange BARBOT_RANGES[70] = {
	{ 250062, BARBOT_RANGE1, false, false },
	{ 250200, BARBOT_RANGE2, false, false },
	{ 250160, BARBOT_RANGE3, false, false },
	{ 250175, BARBOT_RANGE4, false, false },
	{ 250004, BARBOT_RANGE5, false, false },
	{ 250042, BARBOT_RANGE6, true, false },
	{ 250012, BARBOT_RANGE7, false, false },
	{ 250013, BARBOT_RANGE8, false, false },
	{ 250027, BARBOT_RANGE9, false, false },
	{ 250032, BARBOT_RANGE10, false, false },
	{ 250038, BARBOT_RANGE11, false, false },
	{ 250039, BARBOT_RANGE12, false, false },
	{ 250016, BARBOT_RANGE13, false, false },
	{ 250040, BARBOT_RANGE14, false, false },
	{ 250037, BARBOT_RANGE15, false, false },
	{ 250031, BARBOT_RANGE16, false, false },
	{ 250036, BARBOT_RANGE17, false, false },
	{ 250035, BARBOT_RANGE18, false, false },
	{ 250021, BARBOT_RANGE19, false, false },
	{ 250006, BARBOT_RANGE20, false, false },

	{ 250024, BARBOT_RANGE21, false, false },
	{ 250002, BARBOT_RANGE22, false, false },
	{ 250210, BARBOT_RANGE23, false, false },
	{ 251831, BARBOT_RANGE24, false, false },
	{ 250033, BARBOT_RANGE25, false, false },
	{ 250014, BARBOT_RANGE26, false, false },
	{ 251855, BARBOT_RANGE27, false, false },
	{ 251852, BARBOT_RANGE28, false, false },
	{ 251250, BARBOT_RANGE29, false, false },
	{ 251283, BARBOT_RANGE30, false, false },
	{ 250527, BARBOT_RANGE31, false, false },
	{ 250593, BARBOT_RANGE32, false, false },
	{ 250263, BARBOT_RANGE33, false, false },
	{ 250227, BARBOT_RANGE34, false, false },
	{ 250239, BARBOT_RANGE35, false, false },
	{ 250507, BARBOT_RANGE36, false, false },
	{ 250365, BARBOT_RANGE37, false, false },
	{ 250936, BARBOT_RANGE38, false, false },
	{ 250610, BARBOT_RANGE39, false, false },
	{ 250082, BARBOT_RANGE40, true, false },

	{ 250584, BARBOT_RANGE41, false, false },
	{ 250579, BARBOT_RANGE42, false, false },
	{ 250577, BARBOT_RANGE43, false, false },
	{ 250244, BARBOT_RANGE44, true, false },
	{ 250286, BARBOT_RANGE45, true, false },
	{ 250296, BARBOT_RANGE46, true, false },
	{ 250307, BARBOT_RANGE47, true, false },
	{ 251682, BARBOT_RANGE48, true, false },
	{ 250738, BARBOT_RANGE49, true, false },
	{ 250659, BARBOT_RANGE50, true, false },
	{ 251761, BARBOT_RANGE51, false, false },
	{ 251754, BARBOT_RANGE52, false, false },
	{ 251896, BARBOT_RANGE53, true, false },
	{ 251897, BARBOT_RANGE54, true, false },
	{ 250952, BARBOT_RANGE55, false, false },
	{ 251777, BARBOT_RANGE56, false, false },
	{ 251871, BARBOT_RANGE57, true, false },
	{ 250140, BARBOT_RANGE58, true, false },
	{ 250141, BARBOT_RANGE59, false, false },
	{ 251621, BARBOT_RANGE60, false, false },

	{ 251650, BARBOT_RANGE61, false, false },
	{ 251305, BARBOT_RANGE62, false, false },
	{ 251836, BARBOT_RANGE63, false, false },
	{ 251018, BARBOT_RANGE64, true, false },
	{ 250899, BARBOT_RANGE65, false, false },
	{ 250899, BARBOT_RANGE66, false, false },
	{ 251899, BARBOT_RANGE67, false, false },
	{ 251815, BARBOT_RANGE68, false, false },
	{ 251829, BARBOT_RANGE69, false, false },
	{ 251779, BARBOT_RANGE70, false, false }
};

const uint DESKBOT_RANGE1[] = { 240002, 240003, 240006, 240007, 0 };
const uint DESKBOT_RANGE2[] = { 240008, 240009, 240010, 240011, 240012, 240013, 240004, 240005, 0 };
const uint DESKBOT_RANGE3[] = { 240336, 240337, 240338, 240339, 240340, 240341, 240342, 240343, 240344, 0 };
const uint DESKBOT_RANGE4[] = { 240345, 240346, 240347, 0 };
const uint DESKBOT_RANGE5[] = { 240348, 240349, 240350, 0 };
const uint DESKBOT_RANGE6[] = { 240351, 240352, 240353, 0 };
const uint DESKBOT_RANGE7[] = { 240355, 240356, 240357, 0 };
const uint DESKBOT_RANGE8[] = { 240359, 240360, 240361, 0 };
const uint DESKBOT_RANGE9[] = { 240362, 240363, 240364, 240365, 240366, 240367, 0 };
const uint DESKBOT_RANGE10[] = { 240368, 240369, 240370, 240371, 0 };

const uint DESKBOT_RANGE11[] = { 240372, 240373, 240374, 0 };
const uint DESKBOT_RANGE12[] = { 240375, 240376, 240377, 0 };
const uint DESKBOT_RANGE13[] = { 240378, 240379, 240380, 0 };
const uint DESKBOT_RANGE14[] = { 240381, 240382, 240383, 240384, 0 };
const uint DESKBOT_RANGE15[] = { 240385, 240386, 240387, 0 };
const uint DESKBOT_RANGE16[] = { 240388, 240389, 240390, 0 };
const uint DESKBOT_RANGE17[] = { 240391, 240392, 240393, 0 };
const uint DESKBOT_RANGE18[] = { 240394, 240395, 240396, 240397, 0 };
const uint DESKBOT_RANGE19[] = { 240399, 0 };
const uint DESKBOT_RANGE20[] = { 240401, 240402, 240403, 0 };

const uint DESKBOT_RANGE21[] = { 240404, 240405, 240406, 0 };
const uint DESKBOT_RANGE22[] = { 240407, 240408, 240409, 240900, 240410, 240411, 240412, 240900, 241671, 241672,
241673, 241671, 241672, 241673, 241671, 241672, 241673, 0 };
const uint DESKBOT_RANGE23[] = { 240421, 240422, 0 };
const uint DESKBOT_RANGE24[] = { 240451, 240424, 240425, 240426, 240452, 240455, 240456, 240457, 240458, 240459, 240460, 0 };
const uint DESKBOT_RANGE25[] = { 240451, 240424, 240425, 240426, 240452, 240455, 240456, 240457, 240458, 0 };
const uint DESKBOT_RANGE26[] = { 240428, 240429, 240430, 0 };
const uint DESKBOT_RANGE27[] = { 240431, 240432, 0 };
const uint DESKBOT_RANGE28[] = { 240435, 240436, 240437, 240438, 240439, 0 };
const uint DESKBOT_RANGE29[] = { 240440, 240441, 240442, 240443, 240444, 0 };
const uint DESKBOT_RANGE30[] = { 240451, 240452, 0 };

const uint DESKBOT_RANGE31[] = { 240455, 240456, 240457, 240458, 240459, 240460, 0 };
const uint DESKBOT_RANGE32[] = { 240461, 240462, 240463, 240464, 240977, 240978, 240979, 240980, 240804, 240806,
	240807, 240808, 0 };
const uint DESKBOT_RANGE33[] = { 241742, 241743, 241744, 241745, 241746, 241747, 241748, 240954, 0 };
const uint DESKBOT_RANGE34[] = { 240480, 240481, 240482, 0 };
const uint DESKBOT_RANGE35[] = { 241117, 241515, 0 };
const uint DESKBOT_RANGE36[] = { 240486, 241585, 240487, 241585, 240488, 241585, 0 };
const uint DESKBOT_RANGE37[] = { 240490, 240491, 0 };
const uint DESKBOT_RANGE38[] = { 240496, 240507, 240518, 240529, 240540, 240542, 240543, 240544, 240545, 240497,
	240498, 240499, 240500, 240501, 240502, 240503, 240504, 240505, 240506, 240508,
	240509, 240510, 240511, 240512, 240513, 240514, 240515, 240516, 240517, 240519,
	240520, 240521, 240522, 240523, 240524, 240525, 240526, 240527, 240528, 240530,
	240531, 240532, 240533, 240534, 240535, 240536, 240537, 240538, 240539, 240541, 0 };
const uint DESKBOT_RANGE39[] = { 240587, 240588, 0 };
const uint DESKBOT_RANGE40[] = { 240589, 240590, 240591, 241652, 0 };

const uint DESKBOT_RANGE41[] = { 240592, 240593, 240594, 241653, 0 };
const uint DESKBOT_RANGE42[] = { 240595, 240596, 0 };
const uint DESKBOT_RANGE43[] = { 240597, 240598, 0 };
const uint DESKBOT_RANGE44[] = { 240602, 240613, 240622, 240623, 240624, 240627, 240603, 240606, 240609, 0 };
const uint DESKBOT_RANGE45[] = { 240629, 240630, 240354, 0 };
const uint DESKBOT_RANGE46[] = { 240635, 240636, 240637, 0 };
const uint DESKBOT_RANGE47[] = {
	240640, 240656, 240667, 240678, 240689, 240699, 240710, 240721, 240732, 240641,
	240647, 240648, 240649, 240650, 240651, 240652, 240653, 240654, 240655, 240657,
	240658, 240659, 240660, 240661, 240662, 240663, 240664, 240665, 240666, 240668,
	240669, 240670, 240671, 240672, 240673, 240674, 240675, 240676, 240677, 240679,
	240680, 240681, 240682, 240683, 240684, 240685, 240686, 240687, 240688, 240690,
	240691, 240692, 240693, 240694, 240695, 240696, 240697, 240698, 240700, 240701,
	240702, 240703, 240704, 240705, 240706, 240707, 240708, 240709, 240711, 240712,
	240713, 240714, 240715, 240716, 240717, 240718, 240719, 240720, 240722, 240723,
	240724, 240725, 240726, 240727, 240728, 240729, 240730, 240731, 240733, 240734,
	240735, 240736, 240737, 240738, 240739, 240740, 240741, 240742, 240642, 240643,
	240644, 240645, 240646, 0
};
const uint DESKBOT_RANGE48[] = { 240758, 240759, 240760, 0 };
const uint DESKBOT_RANGE49[] = { 240761, 240762, 240764, 240766, 0 };
const uint DESKBOT_RANGE50[] = { 240335, 240776, 240778, 240779, 240780, 240781, 0 };

const uint DESKBOT_RANGE51[] = { 240335, 240776, 240777, 240778, 240779, 240780, 240781, 0 };
const uint DESKBOT_RANGE52[] = { 240782, 240783, 240834, 240592, 240589, 240768, 240770, 240771, 240769, 240772,
240773, 240590, 240593, 240595, 240587, 240597, 240591, 240594, 240596, 240588,
240598, 241120, 240675, 241124, 0 };
const uint DESKBOT_RANGE53[] = { 240787, 240788, 240789, 240790, 240791, 241635, 0 };
const uint DESKBOT_RANGE54[] = { 240792, 240793, 240794, 240795, 240796, 240797, 241635, 0 };
const uint DESKBOT_RANGE55[] = { 240798, 240799, 240800, 241635, 0 };
const uint DESKBOT_RANGE56[] = { 240804, 240806, 240807, 240808, 0 };
const uint DESKBOT_RANGE57[] = { 240809, 240820, 240822, 240823, 240824, 240825, 240826, 240827, 240828, 240829,
240810, 240811, 240812, 240813, 240814, 240815, 240816, 240817, 240818, 240819,
240821, 0 };
const uint DESKBOT_RANGE58[] = { 240835, 240836, 240837, 240838, 240839, 240840, 0 };
const uint DESKBOT_RANGE59[] = { 240861, 240862, 240863, 0 };
const uint DESKBOT_RANGE60[] = { 240881, 240883, 240884, 240885, 240886, 240887, 240888, 240889, 240890, 240882, 0 };

const uint DESKBOT_RANGE61[] = { 240894, 240895, 240896, 240897, 240898, 240899, 240900, 240901, 240902, 0 };
const uint DESKBOT_RANGE62[] = { 240904, 240905, 240906, 240907, 240908, 241342, 0 };
const uint DESKBOT_RANGE63[] = { 240911, 240922, 240930, 240932, 240933, 240934, 240935, 240936, 240937, 240912,
	240913, 240914, 240915, 240916, 240917, 240918, 240919, 240920, 240921, 240923,
	240931, 240925, 240926, 240927, 240928, 240929, 0
};
const uint DESKBOT_RANGE64[] = { 240948, 240949, 240950, 240951, 0 };
const uint DESKBOT_RANGE65[] = { 240959, 240960, 240961, 240962, 0 };
const uint DESKBOT_RANGE66[] = { 240965, 240966, 0 };
const uint DESKBOT_RANGE67[] = { 240972, 240973, 240974, 0 };
const uint DESKBOT_RANGE68[] = { 240977, 240978, 240979, 240980, 0 };
const uint DESKBOT_RANGE69[] = { 240982, 240983, 240984, 240985, 0 };
const uint DESKBOT_RANGE70[] = { 240988, 240989, 240990, 240991, 0 };

const uint DESKBOT_RANGE71[] = { 240992, 240994, 240995, 240996, 240997, 240998, 241000, 241001, 0 };
const uint DESKBOT_RANGE72[] = { 241002, 241004, 241005, 241006, 241007, 241008, 241009, 241010, 241011, 241003, 0 };
const uint DESKBOT_RANGE73[] = {
	241012, 241023, 241034, 241045, 241050, 241051, 241052, 241053, 241054, 241013,
	241014, 241015, 241016, 241017, 241018, 241019, 241020, 241021, 241022, 241024,
	241025, 241026, 241027, 241028, 241029, 241030, 241031, 241032, 241033, 241035,
	241036, 241037, 241038, 241039, 241040, 241041, 241042, 241043, 241044, 241046,
	241047, 241048, 241049, 0
};
const uint DESKBOT_RANGE74[] = { 241055, 241057, 241058, 241059, 241060, 241061, 241062, 241063, 241064, 241056, 0 };
const uint DESKBOT_RANGE75[] = { 241078, 241079, 241080, 241081, 241082, 241083, 241084, 241085, 0 };
const uint DESKBOT_RANGE76[] = { 241091, 241092, 241093, 241094, 241095, 0 };
const uint DESKBOT_RANGE77[] = { 241103, 241104, 241105, 241106, 241107, 0 };
const uint DESKBOT_RANGE78[] = {
	241132, 241127, 241133, 241140, 241151, 241152, 241153, 241154, 241155, 241156,
	241157, 241128, 241129, 241130, 241131, 241136, 241137, 241138, 241139, 241141,
	241142, 241143, 241144, 241145, 241146, 241147, 241148, 241149, 241150, 0
};
const uint DESKBOT_RANGE79[] = { 240404, 241099, 0 };
const uint DESKBOT_RANGE80[] = { 241125, 241124, 241125, 241125, 240649, 240729, 241686, 241680, 241738, 0 };

const uint DESKBOT_RANGE81[] = { 241096, 241112, 240727, 241679, 241738, 0 };
const uint DESKBOT_RANGE82[] = { 240833, 240845, 241464, 241465, 241674, 241738, 0 };
const uint DESKBOT_RANGE83[] = { 240726, 241684, 241738, 0 };
const uint DESKBOT_RANGE84[] = { 240728, 240728, 240728, 240644, 240953, 240728, 240601, 240728, 241075, 240728,
240952, 240728, 240600, 241120, 241683, 241738, 241738, 241738, 0 };
const uint DESKBOT_RANGE85[] = { 240730, 241738, 0 };
const uint DESKBOT_RANGE86[] = { 240008, 240009, 240010, 240011, 240012, 240013, 240004, 240005, 0 };
const uint DESKBOT_RANGE87[] = { 240677, 240680, 240766, 241109, 240633, 240747, 240940, 241187, 241120, 240665,
240669, 240620, 0 };
const uint DESKBOT_RANGE88[] = {
	240948, 240602, 240613, 240622, 240624, 240625, 240626, 240627, 240603, 240605,
	240607, 240609, 240610, 241150, 240925, 240882, 240864, 241072, 240942, 240867,
	241096, 240971, 240785, 240868, 240833, 240955, 241077, 240877, 240754, 241163,
	241071, 241161, 240871, 241114, 240963, 240956, 240750, 240958, 240851, 240866,
	241100, 240941, 241115, 241088, 240628, 240846, 240857, 241164, 241165, 240954,
	241087, 240869, 240784, 240637, 240700, 240701, 240704, 240929, 240716, 240717,
	240720, 240689, 240732, 240648, 240653, 240664, 240676, 0
};
const uint DESKBOT_RANGE89[] = { 241012, 0 };
const uint DESKBOT_RANGE90[] = { 240775, 240419, 240701, 240642, 240802, 240891, 241110, 241568, 241569, 241570, 241571, 0 };

const uint DESKBOT_RANGE91[] = { 241338, 240831, 0 };
const uint DESKBOT_RANGE92[] = { 240416, 241343, 0 };
const uint DESKBOT_RANGE93[] = { 241577, 241578, 241579, 241580, 241581, 241582, 0 };
const uint DESKBOT_RANGE94[] = { 241383, 241586, 0 };
const uint DESKBOT_RANGE95[] = { 241446, 241447, 241448, 0 };
const uint DESKBOT_RANGE96[] = { 241443, 241444, 241445, 0 };
const uint DESKBOT_RANGE97[] = { 241116, 241365, 0 };
const uint DESKBOT_RANGE98[] = {
	241522, 241523, 241524, 241525, 241526, 241527, 241528, 241529, 241530, 241531,
	241532, 241533, 241534, 241535, 241536, 241537, 241538, 241539, 241540, 241541,
	241542, 241543, 241544, 241545, 241546, 241547, 241548, 241549, 241550, 241551,
	241552, 241553, 241554, 0
};
const uint DESKBOT_RANGE99[] = { 241341, 241634, 0 };
const uint DESKBOT_RANGE100[] = { 241449, 241635, 241450, 241635, 0 };

const uint DESKBOT_RANGE101[] = { 241638, 241639, 241640, 241654, 241655, 241643, 0 };
const uint DESKBOT_RANGE102[] = { 241702, 241703, 241704, 0 };
const uint DESKBOT_RANGE103[] = { 240465, 241641, 0 };
const uint DESKBOT_RANGE104[] = { 241371, 241111, 0 };

#define DESKBOT_RANGE_COUNT 146
const ScriptRange DESKBOT_RANGES[146] = {
	{ 240546, DESKBOT_RANGE1, false, false },
	{ 240547, DESKBOT_RANGE2, false, false },
	{ 240548, DESKBOT_RANGE3, false, false },
	{ 240549, DESKBOT_RANGE4, false, false },
	{ 240550, DESKBOT_RANGE5, false, false },
	{ 240551, DESKBOT_RANGE6, false, false },
	{ 240552, DESKBOT_RANGE7, false, false },
	{ 240553, DESKBOT_RANGE8, false, false },
	{ 240554, DESKBOT_RANGE9, false, false },
	{ 240555, DESKBOT_RANGE10, false, false },

	{ 240556, DESKBOT_RANGE11, false, false },
	{ 240557, DESKBOT_RANGE12, false, false },
	{ 240558, DESKBOT_RANGE13, false, false },
	{ 240559, DESKBOT_RANGE14, false, false },
	{ 240560, DESKBOT_RANGE15, false, false },
	{ 240561, DESKBOT_RANGE16, false, false },
	{ 240562, DESKBOT_RANGE17, false, false },
	{ 240563, DESKBOT_RANGE18, false, false },
	{ 240564, DESKBOT_RANGE19, false, false },
	{ 240565, DESKBOT_RANGE20, false, false },

	{ 240566, DESKBOT_RANGE21, false, false },
	{ 240567, DESKBOT_RANGE22, false, false },
	{ 240568, DESKBOT_RANGE23, false, false },
	{ 240569, DESKBOT_RANGE24, false, false },
	{ 240570, DESKBOT_RANGE25, false, false },
	{ 240571, DESKBOT_RANGE26, false, false },
	{ 240572, DESKBOT_RANGE27, false, false },
	{ 240573, DESKBOT_RANGE28, false, false },
	{ 240574, DESKBOT_RANGE29, false, false },
	{ 240575, DESKBOT_RANGE30, false, false },

	{ 240576, DESKBOT_RANGE31, false, false },
	{ 240577, DESKBOT_RANGE32, false, false },
	{ 240578, DESKBOT_RANGE33, false, false },
	{ 240579, DESKBOT_RANGE34, false, false },
	{ 240580, DESKBOT_RANGE35, false, false },
	{ 240581, DESKBOT_RANGE36, false, false },
	{ 240582, DESKBOT_RANGE37, false, false },
	{ 240583, DESKBOT_RANGE38, false, false },
	{ 241167, DESKBOT_RANGE39, false, false },
	{ 241168, DESKBOT_RANGE40, false, false },

	{ 241169, DESKBOT_RANGE41, false, false },
	{ 241170, DESKBOT_RANGE42, false, false },
	{ 241171, DESKBOT_RANGE43, false, false },
	{ 241172, DESKBOT_RANGE44, false, false },
	{ 241173, DESKBOT_RANGE45, false, false },
	{ 241174, DESKBOT_RANGE46, false, false },
	{ 241175, DESKBOT_RANGE47, false, false },
	{ 241176, DESKBOT_RANGE48, false, false },
	{ 241177, DESKBOT_RANGE49, false, false },
	{ 241178, DESKBOT_RANGE50, false, false },

	{ 241179, DESKBOT_RANGE51, false, false },
	{ 241180, DESKBOT_RANGE52, false, false },
	{ 241181, DESKBOT_RANGE53, false, false },
	{ 241182, DESKBOT_RANGE54, false, false },
	{ 241183, DESKBOT_RANGE55, false, false },
	{ 241184, DESKBOT_RANGE56, false, false },
	{ 241185, DESKBOT_RANGE57, false, false },
	{ 241186, DESKBOT_RANGE58, false, false },
	{ 241187, DESKBOT_RANGE59, false, false },
	{ 241188, DESKBOT_RANGE60, false, false },

	{ 241189, DESKBOT_RANGE61, false, false },
	{ 241190, DESKBOT_RANGE62, false, false },
	{ 241191, DESKBOT_RANGE63, false, false },
	{ 241192, DESKBOT_RANGE64, false, false },
	{ 241193, DESKBOT_RANGE65, false, false },
	{ 241194, DESKBOT_RANGE66, false, false },
	{ 241195, DESKBOT_RANGE67, false, false },
	{ 241196, DESKBOT_RANGE68, false, false },
	{ 241197, DESKBOT_RANGE69, false, false },
	{ 241198, DESKBOT_RANGE70, false, false },

	{ 241199, DESKBOT_RANGE71, false, false },
	{ 241200, DESKBOT_RANGE72, false, false },
	{ 241201, DESKBOT_RANGE73, false, false },
	{ 241202, DESKBOT_RANGE74, false, false },
	{ 241203, DESKBOT_RANGE75, false, false },
	{ 241204, DESKBOT_RANGE76, false, false },
	{ 241205, DESKBOT_RANGE77, false, false },
	{ 241166, DESKBOT_RANGE78, false, false },
	{ 241206, DESKBOT_RANGE79, false, false },
	{ 241207, DESKBOT_RANGE80, false, false },

	{ 241208, DESKBOT_RANGE81, false, false },
	{ 241209, DESKBOT_RANGE82, false, false },
	{ 241210, DESKBOT_RANGE83, false, false },
	{ 241211, DESKBOT_RANGE84, false, false },
	{ 241212, DESKBOT_RANGE85, false, false },
	{ 241213, DESKBOT_RANGE86, false, false },
	{ 241214, DESKBOT_RANGE87, false, false },
	{ 241215, DESKBOT_RANGE88, false, false },

	{ 241217, DESKBOT_RANGE89, false, false },
	{ 241218, DESKBOT_RANGE89, false, false },
	{ 241219, DESKBOT_RANGE89, false, false },
	{ 241220, DESKBOT_RANGE89, false, false },
	{ 241221, DESKBOT_RANGE89, false, false },
	{ 241222, DESKBOT_RANGE89, false, false },
	{ 241223, DESKBOT_RANGE89, false, false },
	{ 241224, DESKBOT_RANGE89, false, false },
	{ 241225, DESKBOT_RANGE89, false, false },
	{ 241226, DESKBOT_RANGE89, false, false },
	{ 241227, DESKBOT_RANGE89, false, false },
	{ 241228, DESKBOT_RANGE89, false, false },
	{ 241229, DESKBOT_RANGE89, false, false },
	{ 241230, DESKBOT_RANGE89, false, false },
	{ 241231, DESKBOT_RANGE89, false, false },
	{ 241232, DESKBOT_RANGE89, false, false },
	{ 241233, DESKBOT_RANGE89, false, false },
	{ 241234, DESKBOT_RANGE89, false, false },
	{ 241235, DESKBOT_RANGE89, false, false },
	{ 241236, DESKBOT_RANGE89, false, false },
	{ 241237, DESKBOT_RANGE89, false, false },
	{ 241238, DESKBOT_RANGE89, false, false },
	{ 241239, DESKBOT_RANGE89, false, false },
	{ 241240, DESKBOT_RANGE89, false, false },
	{ 241241, DESKBOT_RANGE89, false, false },
	{ 241242, DESKBOT_RANGE89, false, false },
	{ 241243, DESKBOT_RANGE89, false, false },
	{ 241244, DESKBOT_RANGE89, false, false },
	{ 241245, DESKBOT_RANGE89, false, false },
	{ 241246, DESKBOT_RANGE89, false, false },
	{ 241247, DESKBOT_RANGE89, false, false },
	{ 241248, DESKBOT_RANGE89, false, false },
	{ 241249, DESKBOT_RANGE89, false, false },
	{ 241250, DESKBOT_RANGE89, false, false },
	{ 241251, DESKBOT_RANGE89, false, false },
	{ 241252, DESKBOT_RANGE89, false, false },
	{ 241253, DESKBOT_RANGE89, false, false },
	{ 241254, DESKBOT_RANGE89, false, false },
	{ 241255, DESKBOT_RANGE89, false, false },
	{ 241256, DESKBOT_RANGE89, false, false },
	{ 241257, DESKBOT_RANGE89, false, false },
	{ 241258, DESKBOT_RANGE89, false, false },
	{ 241259, DESKBOT_RANGE89, false, false },

	{ 241216, DESKBOT_RANGE90, false, false },
	{ 241625, DESKBOT_RANGE91, false, false },
	{ 241626, DESKBOT_RANGE92, false, false },
	{ 241627, DESKBOT_RANGE93, false, false },
	{ 241628, DESKBOT_RANGE94, false, false },
	{ 241629, DESKBOT_RANGE95, false, false },
	{ 241630, DESKBOT_RANGE96, false, false },
	{ 241631, DESKBOT_RANGE97, false, false },
	{ 241632, DESKBOT_RANGE98, false, false },
	{ 241633, DESKBOT_RANGE99, false, false },
	{ 241634, DESKBOT_RANGE100, false, false },

	{ 241738, DESKBOT_RANGE101, false, false },
	{ 241739, DESKBOT_RANGE102, false, false },
	{ 241740, DESKBOT_RANGE103, false, false },
	{ 241741, DESKBOT_RANGE104, false, false }
};

void writeScriptRange(const char *name, const ScriptRange *ranges, int count) {
	outputFile.seek(dataOffset);

	for (int idx = 0; idx < count; ++idx) {
		outputFile.writeLong(ranges[idx]._id);
		outputFile.writeByte(ranges[idx]._isRandom);
		outputFile.writeByte(ranges[idx]._isSequential);

		const uint *v = ranges[idx]._array;
		do {
			outputFile.writeLong(*v);
		} while (*v++ != 0);
	}

	uint size = outputFile.size() - dataOffset;
	writeEntryHeader(name, dataOffset, size);
	dataOffset += size;
}

void writeAllScriptRanges() {
	writeScriptRange("Ranges/Barbot", BARBOT_RANGES, BARBOT_RANGE_COUNT);
	writeScriptRange("Ranges/Deskbot", DESKBOT_RANGES, DESKBOT_RANGE_COUNT);
}