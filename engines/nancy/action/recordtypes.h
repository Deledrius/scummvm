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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef NANCY_ACTION_RECORDTYPES_H
#define NANCY_ACTION_RECORDTYPES_H

#include "engines/nancy/action/actionrecord.h"
#include "engines/nancy/playstate.h"

#include "common/stream.h"
#include "common/array.h"

namespace Nancy {

class NancyEngine;

// Describes a hotspot
struct HotspotDesc {
    uint16 frameID = 0;
    Common::Rect coords;

    void readData(Common::SeekableReadStream &stream);
};

class SceneChange : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    uint16 sceneID = 0;
    uint16 frameID = 0;
    uint16 verticalOffset = 0;
    bool doNotStartSound = false;
};

class HotMultiframeSceneChange : public SceneChange {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    Common::Array<HotspotDesc> hotspots;
};

// The exact same logic as Hot1FrExitSceneChange
class Hot1FrSceneChange : public SceneChange {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    HotspotDesc hotspotDesc;
};

class HotMultiframeMultisceneChange : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class StartFrameNextScene : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class StartStopPlayerScrolling : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    // TODO add a Start and Stop subclass

    byte type = 0;
};

class PlayPrimaryVideoChan0 : public ActionRecord {

struct ConditionFlags {
    byte unknown[5];
};

struct ResponseStruct {
    Common::Array<ConditionFlags> conditionFlags;
    byte unknown[0x1d8]; // TODO
};

struct FlagsStruct {
    Common::Array<ConditionFlags> conditionFlags;
    uint32 unknown; // TODO
};

public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte videoData[0x69C]; // TODO this is its own class
    Common::Array<ResponseStruct> responses;
    Common::Array<FlagsStruct> flagsStructs;
};

// Base class for PlaySecondaryVideoChan0 and PlaySecondaryVideoChan1
class PlaySecondaryVideo : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class PlaySecondaryVideoChan0 : public PlaySecondaryVideo {
    // TODO
};

class PlaySecondaryVideoChan1 : public PlaySecondaryVideo {
    // TODO
};

class PlaySecondaryMovie : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class PlayStaticBitmapAnimation : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte bitmapData[0xA88];
};

// TODO should inherit from above as the only difference is one int of data
class PlayIntStaticBitmapAnimation : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte bitmapData[0xA8C];
};

class MapCall : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte mapData = 0;
};

class MapCallHot1Fr : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class MapCallHotMultiframe : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class MapLocationAccess : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class MapSound : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class MapAviOverride : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class MapAviOverrideOff : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte overrideOffData = 0;
};

class TextBoxWrite : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class TextBoxClear : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte clearData = 0;
};

class BumpPlayerClock : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class SaveContinueGame : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte saveContinueData = 0;
};

class TurnOffMainRendering : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte turnOffData = 0;
};

class TurnOnMainRendering : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte turnOnData = 0;
};

class ResetAndStartTimer : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;
};

class StopTimer : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;
};

class EventFlags : public ActionRecord {
public:
    struct FlagDesc {
        int16 label;
        PlayState::Flag flag;
    };
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    FlagDesc descs[10];
};

class EventFlagsMultiHS : public EventFlags {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    Common::Array<HotspotDesc> hotspots;
};

class OrderingPuzzle : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class LoseGame : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte loseData = 0;
};

class PushScene : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte pushData = 0;
};

class PopScene : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte popData = 0;
};

class WinGame : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;

    byte winData = 0;
};

class LeverPuzzle : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class Telephone : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class SliderPuzzle : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class PasswordPuzzle : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class AddInventoryNoHS : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class RemoveInventoryNoHS : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class DifficultyLevel : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    virtual void execute(NancyEngine *engine) override;

    uint16 difficulty = 0;
    int16 flagLabel = 0;
    uint16 flagCondition = 0;
};

class RotatingLockPuzzle : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class ShowInventoryItem : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class PlayDigiSoundAndDie : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
    // TODO subclass into Play and Stop (?)
};

class PlaySoundPanFrameAnchorAndDie : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class PlaySoundMultiHS : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

class HintSystem : public ActionRecord {
public:
    virtual uint16 readData(Common::SeekableReadStream &stream) override;
};

} // End of namespace Nancy

#endif // NANCY_ACTION_RECORDTYPES_H