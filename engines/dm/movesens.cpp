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

/*
* Based on the Reverse Engineering work of Christophe Fontanel,
* maintainer of the Dungeon Master Encyclopaedia (http://dmweb.free.fr/)
*/


#include "dm/movesens.h"
#include "dm/champion.h"
#include "dm/inventory.h"
#include "dm/dungeonman.h"
#include "dm/objectman.h"
#include "dm/timeline.h"
#include "dm/group.h"
#include "dm/projexpl.h"
#include "dm/text.h"
#include "dm/sounds.h"


namespace DM {

MovesensMan::MovesensMan(DMEngine *vm) : _vm(vm) {
	_moveResultMapX = 0;
	_moveResultMapY = 0;
	_moveResultMapIndex = 0;
	_moveResultDir = 0;
	_moveResultCell = 0;
	_useRopeToClimbDownPit = false;
	_sensorRotationEffect = 0;
	_sensorRotationEffMapX = 0;
	_sensorRotationEffMapY = 0;
	_sensorRotationEffCell = 0;
}

bool MovesensMan::sensorIsTriggeredByClickOnWall(int16 mapX, int16 mapY, uint16 cellParam) {
	bool atLeastOneSensorWasTriggered = false;
	Thing leaderHandObject = _vm->_championMan->_leaderHandObject;
	int16 sensorCountToProcessPerCell[4];
	for (int16 i = k0_CellNorthWest; i < k3_CellSouthWest + 1; i++)
		sensorCountToProcessPerCell[i] = 0;

	Thing squareFirstThing = _vm->_dungeonMan->getSquareFirstThing(mapX, mapY);
	Thing thingBeingProcessed = squareFirstThing;
	while (thingBeingProcessed != Thing::_endOfList) {
		ThingType thingType = thingBeingProcessed.getType();
		if (thingType == k3_SensorThingType)
			sensorCountToProcessPerCell[(thingBeingProcessed).getCell()]++;
		else if (thingType >= k4_GroupThingType)
			break;

		thingBeingProcessed = _vm->_dungeonMan->getNextThing(thingBeingProcessed);
	}
	Thing lastProcessedThing = thingBeingProcessed = squareFirstThing;
	while (thingBeingProcessed != Thing::_endOfList) {
		bool skipToNextThing = false;
		uint16 ProcessedThingType = (thingBeingProcessed).getType();
		if (ProcessedThingType == k3_SensorThingType) {
			int16 cellIdx = thingBeingProcessed.getCell();
			sensorCountToProcessPerCell[cellIdx]--;
			Sensor *currentSensor = (Sensor *)_vm->_dungeonMan->getThingData(thingBeingProcessed);
			SensorType processedSensorType = currentSensor->getType();
			if (processedSensorType == k0_SensorDisabled)
				skipToNextThing = true;
			else if ((_vm->_championMan->_leaderIndex == kM1_ChampionNone) && (processedSensorType != k127_SensorWallChampionPortrait))
				skipToNextThing = true;
			else if (cellIdx != cellParam)
				skipToNextThing = true;

			bool doNotTriggerSensor;
			int16 sensorData = 0;
			int16 sensorEffect = 0;
			if (!skipToNextThing) {
				sensorData = currentSensor->getData();
				sensorEffect = currentSensor->getAttrEffectA();

				switch (processedSensorType) {
				case k1_SensorWallOrnClick:
					doNotTriggerSensor = false;
					if (currentSensor->getAttrEffectA() == k3_SensorEffHold)
						skipToNextThing = true;
					break;
				case k2_SensorWallOrnClickWithAnyObj:
					doNotTriggerSensor = (_vm->_championMan->_leaderEmptyHanded != currentSensor->getAttrRevertEffectA());
					break;
				case k17_SensorWallOrnClickWithSpecObjRemovedSensor:
				case k11_SensorWallOrnClickWithSpecObjRemovedRotateSensors:
					if (sensorCountToProcessPerCell[cellIdx]) { /* If the sensor is not the last one of its type on the cell */
						skipToNextThing = true;
						break;
					}
					// No break on purpose
				case k3_SensorWallOrnClickWithSpecObj:
				case k4_SensorWallOrnClickWithSpecObjRemoved:
					doNotTriggerSensor = ((sensorData == _vm->_objectMan->getObjectType(leaderHandObject)) == currentSensor->getAttrRevertEffectA());
					if (!doNotTriggerSensor && (processedSensorType == k17_SensorWallOrnClickWithSpecObjRemovedSensor)) {
						if (lastProcessedThing == thingBeingProcessed) /* If the sensor is the only one of its type on the cell */
							break;
						Sensor *lastSensor = (Sensor *)_vm->_dungeonMan->getThingData(lastProcessedThing);
						lastSensor->setNextThing(currentSensor->getNextThing());
						currentSensor->setNextThing(Thing::_none);
						thingBeingProcessed = lastProcessedThing;
					}
					if (!doNotTriggerSensor && (processedSensorType == k11_SensorWallOrnClickWithSpecObjRemovedRotateSensors)) {
						triggerLocalEffect(k2_SensorEffToggle, mapX, mapY, cellIdx); /* This will cause a rotation of the sensors at the specified cell on the specified square after all sensors have been processed */
					}
					break;
				case k12_SensorWallObjGeneratorRotateSensors:
					if (sensorCountToProcessPerCell[cellIdx]) { /* If the sensor is not the last one of its type on the cell */
						skipToNextThing = true;
						break;
					}
					doNotTriggerSensor = !_vm->_championMan->_leaderEmptyHanded;
					if (!doNotTriggerSensor)
						triggerLocalEffect(k2_SensorEffToggle, mapX, mapY, cellIdx); /* This will cause a rotation of the sensors at the specified cell on the specified square after all sensors have been processed */
					break;
				case k13_SensorWallSingleObjStorageRotateSensors:
					if (_vm->_championMan->_leaderEmptyHanded) {
						leaderHandObject = getObjectOfTypeInCell(mapX, mapY, cellIdx, sensorData);
						if (leaderHandObject == Thing::_none) {
							skipToNextThing = true;
							break;
						}
						_vm->_dungeonMan->unlinkThingFromList(leaderHandObject, Thing(0), mapX, mapY);
						_vm->_championMan->putObjectInLeaderHand(leaderHandObject, true);
					} else {
						if ((_vm->_objectMan->getObjectType(leaderHandObject) != sensorData) || (getObjectOfTypeInCell(mapX, mapY, cellIdx, sensorData) != Thing::_none)) {
							skipToNextThing = true;
							break;
						}
						_vm->_championMan->getObjectRemovedFromLeaderHand();
						_vm->_dungeonMan->linkThingToList(thingWithNewCell(leaderHandObject, cellIdx), Thing(0), mapX, mapY);
						leaderHandObject = Thing::_none;
					}
					triggerLocalEffect(k2_SensorEffToggle, mapX, mapY, cellIdx); /* This will cause a rotation of the sensors at the specified cell on the specified square after all sensors have been processed */
					if ((sensorEffect == k3_SensorEffHold) && !_vm->_championMan->_leaderEmptyHanded)
						doNotTriggerSensor = true;
					else
						doNotTriggerSensor = false;
	
					break;
				case k16_SensorWallObjExchanger: {
					if (sensorCountToProcessPerCell[cellIdx]) { /* If the sensor is not the last one of its type on the cell */
						skipToNextThing = true;
						break;
					}
					Thing thingOnSquare = _vm->_dungeonMan->getSquareFirstObject(mapX, mapY);
					if ((_vm->_objectMan->getObjectType(leaderHandObject) != sensorData) || (thingOnSquare == Thing::_none)) {
						skipToNextThing = true;
						break;
					}
					_vm->_dungeonMan->unlinkThingFromList(thingOnSquare, Thing(0), mapX, mapY);
					_vm->_championMan->getObjectRemovedFromLeaderHand();
					_vm->_dungeonMan->linkThingToList(thingWithNewCell(leaderHandObject, cellIdx), Thing(0), mapX, mapY);
					_vm->_championMan->putObjectInLeaderHand(thingOnSquare, true);
					doNotTriggerSensor = false;
					}
					break;
				case k127_SensorWallChampionPortrait:
					_vm->_championMan->addCandidateChampionToParty(sensorData);
					skipToNextThing = true;
					break;
				default:
					skipToNextThing = true;
					break;
				}
			}

			if (!skipToNextThing) {
				if (sensorEffect == k3_SensorEffHold) {
					sensorEffect = doNotTriggerSensor ? k1_SensorEffClear : k0_SensorEffSet;
					doNotTriggerSensor = false;
				}
				if (!doNotTriggerSensor) {
					atLeastOneSensorWasTriggered = true;
					if (currentSensor->getAttrAudibleA())
						_vm->_sound->requestPlay(k01_soundSWITCH, _vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY, k1_soundModePlayIfPrioritized);
	
					if (!_vm->_championMan->_leaderEmptyHanded && ((processedSensorType == k4_SensorWallOrnClickWithSpecObjRemoved) || (processedSensorType == k11_SensorWallOrnClickWithSpecObjRemovedRotateSensors) || (processedSensorType == k17_SensorWallOrnClickWithSpecObjRemovedSensor))) {
						Thing *leaderThing = (Thing *)_vm->_dungeonMan->getThingData(leaderHandObject);
						*leaderThing = Thing::_none;
						_vm->_championMan->getObjectRemovedFromLeaderHand();
						leaderHandObject = Thing::_none;
					} else if (_vm->_championMan->_leaderEmptyHanded
						&& (processedSensorType == k12_SensorWallObjGeneratorRotateSensors)) {
						leaderHandObject = _vm->_dungeonMan->getObjForProjectileLaucherOrObjGen(sensorData);
						if (leaderHandObject != Thing::_none)
							_vm->_championMan->putObjectInLeaderHand(leaderHandObject, true);
					}
					triggerEffect(currentSensor, sensorEffect, mapX, mapY, cellIdx);
				}
				skipToNextThing = true;
			}
		}
		if (!skipToNextThing && (ProcessedThingType >= k4_GroupThingType))
			break;

		lastProcessedThing = thingBeingProcessed;
		thingBeingProcessed = _vm->_dungeonMan->getNextThing(thingBeingProcessed);
	}
	processRotationEffect();
	return atLeastOneSensorWasTriggered;
}

bool MovesensMan::getMoveResult(Thing thing, int16 mapX, int16 mapY, int16 destMapX, int16 destMapY) {
	ThingType thingType = kM1_PartyThingType;
	int16 traversedPitCount = 0;
	uint16 moveGroupResult = 0;
	uint16 thingCell = 0;
	bool thingLevitates = false;

	if (thing != Thing::_party) {
		thingType = thing.getType();
		thingCell = thing.getCell();
		thingLevitates = isLevitating(thing);
	}
	/* If moving the party or a creature on the party map from a dungeon square then check for a projectile impact */
	if ((mapX >= 0) && ((thing == Thing::_party) || ((thingType == k4_GroupThingType) && (_vm->_dungeonMan->_currMapIndex == _vm->_dungeonMan->_partyMapIndex)))) {
		if (moveIsKilledByProjectileImpact(mapX, mapY, destMapX, destMapY, thing))
			return true; /* The specified group thing cannot be moved because it was killed by a projectile impact */
	}

	uint16 mapIndexSource = 0;
	uint16 mapIndexDestination = 0;
	bool groupOnPartyMap = false;
	bool partySquare = false;
	bool audibleTeleporter = false;

	if (destMapX >= 0) {
		mapIndexSource = mapIndexDestination = _vm->_dungeonMan->_currMapIndex;
		groupOnPartyMap = (mapIndexSource == _vm->_dungeonMan->_partyMapIndex) && (mapX >= 0);
		uint16 direction = 0;
		bool fallKilledGroup = false;
		bool drawDungeonViewWhileFalling = false;
		bool destinationIsTeleporterTarget = false;
		int16 requiredTeleporterScope;
		if (thing == Thing::_party) {
			_vm->_dungeonMan->_partyMapX = destMapX;
			_vm->_dungeonMan->_partyMapY = destMapY;
			requiredTeleporterScope = k0x0002_TelepScopeObjOrParty;
			drawDungeonViewWhileFalling = !_vm->_inventoryMan->_inventoryChampionOrdinal && !_vm->_championMan->_partyIsSleeping;
			direction = _vm->_dungeonMan->_partyDir;
		} else if (thingType == k4_GroupThingType)
			requiredTeleporterScope = k0x0001_TelepScopeCreatures;
		else
			requiredTeleporterScope = (k0x0001_TelepScopeCreatures | k0x0002_TelepScopeObjOrParty);

		if (thingType == k14_ProjectileThingType) {
			Teleporter *L0712_ps_Teleporter = (Teleporter *)_vm->_dungeonMan->getThingData(thing);
			_moveResultDir = (_vm->_timeline->_events[((Projectile *)L0712_ps_Teleporter)->_eventIndex])._C._projectile.getDir();
		}

		int16 destinationSquareData = 0;
		/* No more than 1000 chained moves at once (in a chain of teleporters and pits for example) */
		for (int16 chainedMoveCount = 1000; --chainedMoveCount; ) {
			destinationSquareData = _vm->_dungeonMan->_currMapData[destMapX][destMapY];
			SquareType destinationSquareType = Square(destinationSquareData).getType();
			if (destinationSquareType == k5_ElementTypeTeleporter) {
				if (!getFlag(destinationSquareData, k0x0008_TeleporterOpen))
					break;

				Teleporter *teleporter = (Teleporter *)_vm->_dungeonMan->getSquareFirstThingData(destMapX, destMapY);
				if ((teleporter->getScope() == k0x0001_TelepScopeCreatures) && (thingType != k4_GroupThingType))
					break;

				if ((requiredTeleporterScope != (k0x0001_TelepScopeCreatures | k0x0002_TelepScopeObjOrParty)) && !getFlag(teleporter->getScope(), requiredTeleporterScope))
					break;

				destinationIsTeleporterTarget = (destMapX == teleporter->getTargetMapX()) && (destMapY == teleporter->getTargetMapY()) && (mapIndexDestination == teleporter->getTargetMapIndex());
				destMapX = teleporter->getTargetMapX();
				destMapY = teleporter->getTargetMapY();
				audibleTeleporter = teleporter->isAudible();
				_vm->_dungeonMan->setCurrentMap(mapIndexDestination = teleporter->getTargetMapIndex());
				if (thing == Thing::_party) {
					_vm->_dungeonMan->_partyMapX = destMapX;
					_vm->_dungeonMan->_partyMapY = destMapY;
					if (teleporter->isAudible())
						_vm->_sound->requestPlay(k17_soundBUZZ, _vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY, k0_soundModePlayImmediately);

					drawDungeonViewWhileFalling = true;
					if (teleporter->getAbsoluteRotation())
						_vm->_championMan->setPartyDirection(teleporter->getRotation());
					else
						_vm->_championMan->setPartyDirection(normalizeModulo4(_vm->_dungeonMan->_partyDir + teleporter->getRotation()));
				} else {
					if (thingType == k4_GroupThingType) {
						if (teleporter->isAudible())
							_vm->_sound->requestPlay(k17_soundBUZZ, destMapX, destMapY, k1_soundModePlayIfPrioritized);

						moveGroupResult = getTeleporterRotatedGroupResult(teleporter, thing, mapIndexSource);
					} else {
						if (thingType == k14_ProjectileThingType)
							thing = getTeleporterRotatedProjectileThing(teleporter, thing);
						else if (!(teleporter->getAbsoluteRotation()) && (mapX != -2))
							thing = thingWithNewCell(thing, normalizeModulo4(thing.getCell() + teleporter->getRotation()));
					}
				}
				if (destinationIsTeleporterTarget)
					break;
			} else {
				if ((destinationSquareType == k2_ElementTypePit) && !thingLevitates && getFlag(destinationSquareData, k0x0008_PitOpen) && !getFlag(destinationSquareData, k0x0001_PitImaginary)) {
					if (drawDungeonViewWhileFalling && !_useRopeToClimbDownPit) {
						drawDungeonViewWhileFalling = true;
						if (traversedPitCount) {
							_vm->_dungeonMan->setCurrentMapAndPartyMap(mapIndexDestination);
							_vm->_displayMan->loadCurrentMapGraphics();
						}
						traversedPitCount++;
						_vm->_displayMan->drawDungeon(_vm->_dungeonMan->_partyDir, destMapX, destMapY); /* BUG0_28 When falling through multiple pits the dungeon view is updated to show each traversed map but the graphics used for creatures, wall and floor ornaments may not be correct. The dungeon view is drawn for each map by using the graphics loaded for the source map. Therefore the graphics for creatures, wall and floor ornaments may not look like what they should */
																												  /* BUG0_71 Some timings are too short on fast computers. When the party falls in a series of pits, the dungeon view is refreshed too quickly because the execution speed is not limited */
																												  /* BUG0_01 While drawing creatures the engine will read invalid ACTIVE_GROUP data in _vm->_groupMan->_g375_activeGroups because the data is for the creatures on the source map and not the map being drawn. The only consequence is that creatures may be drawn with incorrect bitmaps and/or directions */
					}
					mapIndexDestination = _vm->_dungeonMan->getLocationAfterLevelChange(mapIndexDestination, 1, &destMapX, &destMapY);
					_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
					if (thing == Thing::_party) {
						_vm->_dungeonMan->_partyMapX = destMapX;
						_vm->_dungeonMan->_partyMapY = destMapY;
						if (_vm->_championMan->_partyChampionCount > 0) {
							if (_useRopeToClimbDownPit) {
								Champion *curChampion = _vm->_championMan->_champions;
								for (int16 championIdx = k0_ChampionFirst; championIdx < _vm->_championMan->_partyChampionCount; championIdx++, curChampion++) {
									if (curChampion->_currHealth)
										_vm->_championMan->decrementStamina(championIdx, ((curChampion->_load * 25) / _vm->_championMan->getMaximumLoad(curChampion)) + 1);
								}
							} else if (_vm->_championMan->getDamagedChampionCount(20, k0x0010_ChampionWoundLegs | k0x0020_ChampionWoundFeet, k2_attackType_SELF))
								_vm->_sound->requestPlay(k06_soundSCREAM, _vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY, k0_soundModePlayImmediately);
						}
						_useRopeToClimbDownPit = false;
					} else if (thingType == k4_GroupThingType) {
						_vm->_dungeonMan->setCurrentMap(mapIndexSource);
						uint16 outcome = _vm->_groupMan->getDamageAllCreaturesOutcome((Group *)_vm->_dungeonMan->getThingData(thing), mapX, mapY, 20, false);
						_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
						fallKilledGroup = (outcome == k2_outcomeKilledAllCreaturesInGroup);
						if (fallKilledGroup)
							break;

						if (outcome == k1_outcomeKilledSomeCreaturesInGroup)
							_vm->_groupMan->dropMovingCreatureFixedPossession(thing, destMapX, destMapY);
					}
				} else if ((destinationSquareType == k3_ElementTypeStairs) && (thing != Thing::_party) && (thingType != k14_ProjectileThingType)) {
					if (!getFlag(destinationSquareData, k0x0004_StairsUp)) {
						mapIndexDestination = _vm->_dungeonMan->getLocationAfterLevelChange(mapIndexDestination, 1, &destMapX, &destMapY);
						_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
					}
					direction = _vm->_dungeonMan->getStairsExitDirection(destMapX, destMapY);
					destMapX += _vm->_dirIntoStepCountEast[direction], destMapY += _vm->_dirIntoStepCountNorth[direction];
					direction = returnOppositeDir((Direction)direction);
					uint16 thingCell = thing.getCell();
					thingCell = normalizeModulo4((((thingCell - direction + 1) & 0x0002) >> 1) + direction);
					thing = thingWithNewCell(thing, thingCell);
				} else
					break;
			}
		}
		if ((thingType == k4_GroupThingType) && (fallKilledGroup || !_vm->_dungeonMan->isCreatureAllowedOnMap(thing, mapIndexDestination))) {
			_vm->_groupMan->dropMovingCreatureFixedPossession(thing, destMapX, destMapY);
			_vm->_groupMan->dropGroupPossessions(destMapX, destMapY, thing, k2_soundModePlayOneTickLater);
			_vm->_dungeonMan->setCurrentMap(mapIndexSource);
			if (mapX >= 0)
				_vm->_groupMan->groupDelete(mapX, mapY);

			return true; /* The specified group thing cannot be moved because it was killed by a fall or because it is not allowed on the destination map */
		}
		_moveResultMapX = destMapX;
		_moveResultMapY = destMapY;
		_moveResultMapIndex = mapIndexDestination;
		_moveResultCell = thing.getCell();
		partySquare = (mapIndexDestination == mapIndexSource) && (destMapX == mapX) && (destMapY == mapY);
		if (partySquare) {
			if (thing == Thing::_party) {
				if (_vm->_dungeonMan->_partyDir == direction)
					return false;
			} else if ((_moveResultCell == thingCell) && (thingType != k14_ProjectileThingType))
				return false;
		} else {
			if ((thing == Thing::_party) && _vm->_championMan->_partyChampionCount) {
				uint16 oldDestinationSquare = destinationSquareData;
				int16 scentIndex = _vm->_championMan->_party._scentCount;
				while (scentIndex >= 24) {
					_vm->_championMan->deleteScent(0);
					scentIndex--;
				}

				if (scentIndex)
					_vm->_championMan->addScentStrength(mapX, mapY, (int)(_vm->_gameTime - _vm->_projexpl->_lastPartyMovementTime));

				_vm->_projexpl->_lastPartyMovementTime = _vm->_gameTime;
				_vm->_championMan->_party._scentCount++;
				if (_vm->_championMan->_party._event79Count_Footprints)
					_vm->_championMan->_party._lastScentIndex = _vm->_championMan->_party._scentCount;

				_vm->_championMan->_party._scents[scentIndex].setMapX(destMapX);
				_vm->_championMan->_party._scents[scentIndex].setMapY(destMapY);
				_vm->_championMan->_party._scents[scentIndex].setMapIndex(mapIndexDestination);
				_vm->_championMan->_party._scentStrengths[scentIndex] = 0;
				_vm->_championMan->addScentStrength(destMapX, destMapY, k0x8000_mergeCycles | 24);
				destinationSquareData = oldDestinationSquare;
			}
			if (mapIndexDestination != mapIndexSource)
				_vm->_dungeonMan->setCurrentMap(mapIndexSource);
		}
	}
	if (mapX >= 0) {
		if (thing == Thing::_party)
			processThingAdditionOrRemoval(mapX, mapY, Thing::_party, partySquare, false);
		else if (thingLevitates)
			_vm->_dungeonMan->unlinkThingFromList(thing, Thing::_none, mapX, mapY);
		else
			processThingAdditionOrRemoval(mapX, mapY, thing, (_vm->_dungeonMan->_currMapIndex == _vm->_dungeonMan->_partyMapIndex) && (mapX == _vm->_dungeonMan->_partyMapX) && (mapY == _vm->_dungeonMan->_partyMapY), false);
	}
	if (destMapX >= 0) {
		if (thing == Thing::_party) {
			_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
			if ((thing = _vm->_groupMan->groupGetThing(_vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY)) != Thing::_endOfList) { /* Delete group if party moves onto its square */
				_vm->_groupMan->dropGroupPossessions(_vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY, thing, k1_soundModePlayIfPrioritized);
				_vm->_groupMan->groupDelete(_vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY);
			}

			if (mapIndexDestination == mapIndexSource)
				processThingAdditionOrRemoval(_vm->_dungeonMan->_partyMapX, _vm->_dungeonMan->_partyMapY, Thing::_party, partySquare, true);
			else {
				_vm->_dungeonMan->setCurrentMap(mapIndexSource);
				_vm->_newPartyMapIndex = mapIndexDestination;
			}
		} else {
			if (thingType == k4_GroupThingType) {
				_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
				Teleporter *L0712_ps_Teleporter = (Teleporter *)_vm->_dungeonMan->getThingData(thing);
				int16 activeGroupIndex = ((Group *)L0712_ps_Teleporter)->getActiveGroupIndex();
				if (((mapIndexDestination == _vm->_dungeonMan->_partyMapIndex) && (destMapX == _vm->_dungeonMan->_partyMapX) && (destMapY == _vm->_dungeonMan->_partyMapY)) || (_vm->_groupMan->groupGetThing(destMapX, destMapY) != Thing::_endOfList)) { /* If a group tries to move to the party square or over another group then create an event to move the group later */
					_vm->_dungeonMan->setCurrentMap(mapIndexSource);
					if (mapX >= 0)
						_vm->_groupMan->groupDeleteEvents(mapX, mapY);

					if (groupOnPartyMap)
						_vm->_groupMan->removeActiveGroup(activeGroupIndex);

					createEventMoveGroup(thing, destMapX, destMapY, mapIndexDestination, audibleTeleporter);
					return true; /* The specified group thing cannot be moved because the party or another group is on the destination square */
				}
				uint16 movementSoundIndex = getSound(((Group *)_vm->_dungeonMan->_thingData[k4_GroupThingType])[thing.getIndex()]._type);
				if (movementSoundIndex < k34_D13_soundCount)
					_vm->_sound->requestPlay(movementSoundIndex, destMapX, destMapY, k1_soundModePlayIfPrioritized);

				if (groupOnPartyMap && (mapIndexDestination != _vm->_dungeonMan->_partyMapIndex)) { /* If the group leaves the party map */
					_vm->_groupMan->removeActiveGroup(activeGroupIndex);
					moveGroupResult = true;
				} else if ((mapIndexDestination == _vm->_dungeonMan->_partyMapIndex) && (!groupOnPartyMap)) { /* If the group arrives on the party map */
					_vm->_groupMan->addActiveGroup(thing, destMapX, destMapY);
					moveGroupResult = true;
				}
				if (thingLevitates)
					_vm->_dungeonMan->linkThingToList(thing, Thing(0), destMapX, destMapY);
				else
					processThingAdditionOrRemoval(destMapX, destMapY, thing, false, true);

				if (moveGroupResult || (mapX < 0)) /* If group moved from one map to another or if it was just placed on a square */
					_vm->_groupMan->startWandering(destMapX, destMapY);

				_vm->_dungeonMan->setCurrentMap(mapIndexSource);
				if (mapX >= 0) {
					if (moveGroupResult > 1) /* If the group behavior was C6_BEHAVIOR_ATTACK before being teleported from and to the party map */
						_vm->_groupMan->stopAttacking(&_vm->_groupMan->_activeGroups[moveGroupResult - 2], mapX, mapY);
					else if (moveGroupResult) /* If the group was teleported or leaved the party map or entered the party map */
						_vm->_groupMan->groupDeleteEvents(mapX, mapY);
				}
				return moveGroupResult;
			}
			_vm->_dungeonMan->setCurrentMap(mapIndexDestination);
			if (thingType == k14_ProjectileThingType) /* BUG0_29 An explosion can trigger a floor sensor. Explosions do not trigger floor sensors on the square where they are created. However, if an explosion is moved by a teleporter (or by falling into a pit, see BUG0_26) after it was created, it can trigger floor sensors on the destination square. This is because explosions are not considered as levitating in the code, while projectiles are. The condition here should be (L0713_B_ThingLevitates) so that explosions would not start sensor processing on their destination square as they should be Levitating. This would work if F0264_MOVE_IsLevitating returned true for explosions (see BUG0_26) */
				_vm->_dungeonMan->linkThingToList(thing, Thing(0), destMapX, destMapY);
			else
				processThingAdditionOrRemoval(destMapX, destMapY, thing, (_vm->_dungeonMan->_currMapIndex == _vm->_dungeonMan->_partyMapIndex) && (destMapX == _vm->_dungeonMan->_partyMapX) && (destMapY == _vm->_dungeonMan->_partyMapY), true);

			_vm->_dungeonMan->setCurrentMap(mapIndexSource);
		}
	}
	return false;
}

bool MovesensMan::isLevitating(Thing thing) {
	ThingType thingType = thing.getType();
	bool retVal = false;
	if (thingType == k4_GroupThingType)
		retVal = getFlag(_vm->_dungeonMan->getCreatureAttributes(thing), k0x0020_MaskCreatureInfo_levitation);
	else if (thingType == k14_ProjectileThingType)
		/* BUG0_26 An explosion may fall in a pit. If a pit is opened while there is an explosion above then the explosion
		falls into the pit in getMoveResult(). Explosions are not considered as levitating so they are moved when the pit
		is opened. This function should return true for explosions */
		retVal = true;

	return retVal;
}

bool MovesensMan::moveIsKilledByProjectileImpact(int16 srcMapX, int16 srcMapY, int16 destMapX, int16 destMapY, Thing thing) {
	Thing L0697_T_Thing;
	uint16 L0699_ui_Multiple;
#define AL0699_ui_Cell                      L0699_ui_Multiple
#define AL0699_ui_PrimaryDirection          L0699_ui_Multiple
#define AL0699_ui_ChampionOrCreatureOrdinal L0699_ui_Multiple
	int16 L0700_i_Multiple;
#define AL0700_B_CreatureAlive      L0700_i_Multiple
#define AL0700_i_Distance           L0700_i_Multiple
#define AL0700_i_SecondaryDirection L0700_i_Multiple
	Group *L0701_ps_Group;
	int16 L0702_i_ImpactType;
	bool L0703_B_CheckDestinationSquareProjectileImpacts;
	uint16 L0704_ui_ProjectileMapX;
	uint16 L0705_ui_ProjectileMapY;
	byte L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[4]; /* This array is used only when moving between two adjacent squares and is used to test projectile impacts when the party or group is in the 'intermediary' step between the two squares. Without this test, in the example below no impact would be detected. In this example, the party moves from the source square on the left (which contains a single champion at cell 2) to the destination square on the right (which contains a single projectile at cell 3).
																			Party:      Projectiles on target square:   Incorrect result without the test for the intermediary step (the champion would have passed through the projectile without impact):
																			00    ->    00                         00
																			01          P0                         P1 */
	byte L0707_auc_ChampionOrCreatureOrdinalInCell[4]; /* This array has an entry for each cell on the source square, containing the ordinal of the champion or creature (0 if there is no champion or creature at this cell) */


	L0703_B_CheckDestinationSquareProjectileImpacts = false;
	for (int16 i = 0; i < 4; ++i)
		L0707_auc_ChampionOrCreatureOrdinalInCell[i] = 0;
	if (thing == Thing::_party) {
		L0702_i_ImpactType = kM2_ChampionElemType;
		for (AL0699_ui_Cell = k0_CellNorthWest; AL0699_ui_Cell < k3_CellSouthWest + 1; AL0699_ui_Cell++) {
			if (_vm->_championMan->getIndexInCell((ViewCell)AL0699_ui_Cell) >= 0) {
				L0707_auc_ChampionOrCreatureOrdinalInCell[AL0699_ui_Cell] = _vm->indexToOrdinal(AL0699_ui_Cell);
			}
		}
	} else {
		L0702_i_ImpactType = kM1_CreatureElemType;
		L0701_ps_Group = (Group *)_vm->_dungeonMan->getThingData(thing);
		for (AL0699_ui_Cell = k0_CellNorthWest, AL0700_B_CreatureAlive = false; AL0699_ui_Cell < k3_CellSouthWest + 1; AL0699_ui_Cell++) {
			AL0700_B_CreatureAlive |= L0701_ps_Group->_health[AL0699_ui_Cell];
			if (_vm->_groupMan->getCreatureOrdinalInCell(L0701_ps_Group, AL0699_ui_Cell)) {
				L0707_auc_ChampionOrCreatureOrdinalInCell[AL0699_ui_Cell] = _vm->indexToOrdinal(AL0699_ui_Cell);
			}
		}
		if (!AL0700_B_CreatureAlive) {
			return false;
		}
	}
	if ((destMapX >= 0) && ((abs(srcMapX - destMapX) + abs(srcMapY - destMapY)) == 1)) { /* If source and destination squares are adjacent (if party or group is not being teleported) */
		AL0699_ui_PrimaryDirection = _vm->_groupMan->getDirsWhereDestIsVisibleFromSource(srcMapX, srcMapY, destMapX, destMapY);
		AL0700_i_SecondaryDirection = returnNextVal(AL0699_ui_PrimaryDirection);
		for (int16 i = 0; i < 4; ++i)
			L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[i] = 0;

		L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[returnPrevVal(AL0699_ui_PrimaryDirection)] = L0707_auc_ChampionOrCreatureOrdinalInCell[AL0699_ui_PrimaryDirection];
		if (L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[returnPrevVal(AL0699_ui_PrimaryDirection)]) {
			L0703_B_CheckDestinationSquareProjectileImpacts = true;
		}

		L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[returnNextVal(AL0700_i_SecondaryDirection)] = L0707_auc_ChampionOrCreatureOrdinalInCell[AL0700_i_SecondaryDirection];
		if (L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[returnNextVal(AL0700_i_SecondaryDirection)]) {
			L0703_B_CheckDestinationSquareProjectileImpacts = true;
		}
		if (!L0707_auc_ChampionOrCreatureOrdinalInCell[AL0699_ui_PrimaryDirection]) {
			L0707_auc_ChampionOrCreatureOrdinalInCell[AL0699_ui_PrimaryDirection] = L0707_auc_ChampionOrCreatureOrdinalInCell[returnPrevVal(AL0699_ui_PrimaryDirection)];
		}
		if (!L0707_auc_ChampionOrCreatureOrdinalInCell[AL0700_i_SecondaryDirection]) {
			L0707_auc_ChampionOrCreatureOrdinalInCell[AL0700_i_SecondaryDirection] = L0707_auc_ChampionOrCreatureOrdinalInCell[returnNextVal(AL0700_i_SecondaryDirection)];
		}
	}
	L0704_ui_ProjectileMapX = srcMapX; /* Check impacts with projectiles on the source square */
	L0705_ui_ProjectileMapY = srcMapY;
T0266017_CheckProjectileImpacts:
	L0697_T_Thing = _vm->_dungeonMan->getSquareFirstThing(L0704_ui_ProjectileMapX, L0705_ui_ProjectileMapY);
	while (L0697_T_Thing != Thing::_endOfList) {
		if (((L0697_T_Thing).getType() == k14_ProjectileThingType) &&
			(_vm->_timeline->_events[(((Projectile *)_vm->_dungeonMan->_thingData[k14_ProjectileThingType])[(L0697_T_Thing).getIndex()])._eventIndex]._type != k48_TMEventTypeMoveProjectileIgnoreImpacts) && (AL0699_ui_ChampionOrCreatureOrdinal = L0707_auc_ChampionOrCreatureOrdinalInCell[(L0697_T_Thing).getCell()]) &&
			_vm->_projexpl->hasProjectileImpactOccurred(L0702_i_ImpactType, srcMapX, srcMapY, _vm->ordinalToIndex(AL0699_ui_ChampionOrCreatureOrdinal), L0697_T_Thing)) {
			_vm->_projexpl->projectileDeleteEvent(L0697_T_Thing);
			if (_vm->_projexpl->_creatureDamageOutcome == k2_outcomeKilledAllCreaturesInGroup) {
				return true;
			}
			goto T0266017_CheckProjectileImpacts;
		}
		L0697_T_Thing = _vm->_dungeonMan->getNextThing(L0697_T_Thing);
	}
	if (L0703_B_CheckDestinationSquareProjectileImpacts) {
		srcMapX |= ((L0704_ui_ProjectileMapX = destMapX) + 1) << 8; /* Check impacts with projectiles on the destination square */
		srcMapY |= (L0705_ui_ProjectileMapY = destMapY) << 8;
		for (uint16 i = 0; i < 4; ++i)
			L0707_auc_ChampionOrCreatureOrdinalInCell[i] = L0706_auc_IntermediaryChampionOrCreatureOrdinalInCell[i];
		L0703_B_CheckDestinationSquareProjectileImpacts = false;
		goto T0266017_CheckProjectileImpacts;
	}
	return false;
}

void MovesensMan::addEvent(byte type, byte mapX, byte mapY, byte cell, byte effect, int32 time) {
	TimelineEvent L0729_s_Event;

	setMapAndTime(L0729_s_Event._mapTime, _vm->_dungeonMan->_currMapIndex, time);
	L0729_s_Event._type = type;
	L0729_s_Event._priority = 0;
	L0729_s_Event._B._location._mapX = mapX;
	L0729_s_Event._B._location._mapY = mapY;
	L0729_s_Event._C.A._cell = cell;
	L0729_s_Event._C.A._effect = effect;
	_vm->_timeline->addEventGetEventIndex(&L0729_s_Event);
}

int16 MovesensMan::getSound(byte creatureType) {
	if (_vm->_championMan->_partyIsSleeping) {
		return 35;
	}

	switch (creatureType) {
	case k3_CreatureTypeWizardEyeFlyingEye:
	case k8_CreatureTypeGhostRive:
	case k11_CreatureTypeBlackFlame:
	case k19_CreatureTypeMaterializerZytaz:
	case k23_CreatureTypeLordChaos:
	case k25_CreatureTypeLordOrder:
	case k26_CreatureTypeGreyLord:
		return 35;
	case k2_CreatureTypeGiggler:
	case k9_CreatureTypeStoneGolem:
	case k10_CreatureTypeMummy:
	case k14_CreatureTypeVexirk:
	case k16_CreatureTypeTrolinAntman:
	case k22_CreatureTypeDemon:
		return k24_soundMOVE_MUMMY_TROLIN_ANTMAN_STONE_GOLEM_GIGGLER_VEXIRK_DEMON;
	case k0_CreatureTypeGiantScorpionScorpion:
	case k4_CreatureTypePainRatHellHound:
	case k5_CreatureTypeRuster:
	case k6_CreatureTypeScreamer:
	case k7_CreatureTypeRockpile:
	case k15_CreatureTypeMagnetaWormWorm:
	case k21_CreatureTypeOitu:
		return k26_soundMOVE_SCREAMER_ROCK_ROCKPILE_MAGENTA_WORM_WORM_PAIN_RAT_HELLHOUND_RUSTER_GIANT_SCORPION_SCORPION_OITU;
	case k24_CreatureTypeRedDragon:
		return k32_soundMOVE_RED_DRAGON;
	case k12_CreatureTypeSkeleton:
		return k33_soundMOVE_SKELETON;
	case k18_CreatureTypeAnimatedArmourDethKnight:
		return k22_soundMOVE_ANIMATED_ARMOUR_DETH_KNIGHT;
	case k1_CreatureTypeSwampSlimeSlime:
	case k20_CreatureTypeWaterElemental:
		return k27_soundMOVE_SWAMP_SLIME_SLIME_DEVIL_WATER_ELEMENTAL;
	case k13_CreatureTypeCouatl:
	case k17_CreatureTypeGiantWaspMuncher:
		return k23_soundMOVE_COUATL_GIANT_WASP_MUNCHER;
	}
	return -1000; // if this is returned, it's an error, this should break it good
}

int16 MovesensMan::getTeleporterRotatedGroupResult(Teleporter *teleporter, Thing thing, uint16 mapIndex) {
	int16 L0683_i_Rotation;
	uint16 L0684_ui_GroupDirections;
	uint16 L0685_ui_UpdatedGroupDirections;
	Group *L0686_ps_Group;
	uint16 L0687_ui_UpdatedGroupCells;
	int16 L0688_i_CreatureIndex;
	bool L0689_B_AbsoluteRotation;
	uint16 L0690_ui_GroupCells;
	int16 L0691_i_CreatureSize;
	int16 L0692_i_RelativeRotation;

	L0686_ps_Group = (Group *)_vm->_dungeonMan->getThingData(thing);
	L0683_i_Rotation = teleporter->getRotation();
	L0684_ui_GroupDirections = _vm->_groupMan->getGroupDirections(L0686_ps_Group, mapIndex);

	L0689_B_AbsoluteRotation = teleporter->getAbsoluteRotation();
	if (L0689_B_AbsoluteRotation) {
		L0685_ui_UpdatedGroupDirections = L0683_i_Rotation;
	} else {
		L0685_ui_UpdatedGroupDirections = normalizeModulo4(L0684_ui_GroupDirections + L0683_i_Rotation);
	}

	L0687_ui_UpdatedGroupCells = _vm->_groupMan->getGroupCells(L0686_ps_Group, mapIndex);
	if (L0687_ui_UpdatedGroupCells != k255_CreatureTypeSingleCenteredCreature) {
		L0690_ui_GroupCells = L0687_ui_UpdatedGroupCells;
		L0691_i_CreatureSize = getFlag(_vm->_dungeonMan->_creatureInfos[L0686_ps_Group->_type]._attributes, k0x0003_MaskCreatureInfo_size);
		L0692_i_RelativeRotation = normalizeModulo4(4 + L0685_ui_UpdatedGroupDirections - L0684_ui_GroupDirections);
		for (L0688_i_CreatureIndex = 0; L0688_i_CreatureIndex <= L0686_ps_Group->getCount(); L0688_i_CreatureIndex++) {
			L0685_ui_UpdatedGroupDirections = _vm->_groupMan->getGroupValueUpdatedWithCreatureValue(L0685_ui_UpdatedGroupDirections, L0688_i_CreatureIndex, L0689_B_AbsoluteRotation ? L0683_i_Rotation : normalizeModulo4(L0684_ui_GroupDirections + L0683_i_Rotation));
			if (L0691_i_CreatureSize == k0_MaskCreatureSizeQuarter) {
				L0692_i_RelativeRotation = !L0689_B_AbsoluteRotation;
				if (L0692_i_RelativeRotation) 
					L0692_i_RelativeRotation = L0683_i_Rotation;
			}
			if (L0692_i_RelativeRotation) {
				L0687_ui_UpdatedGroupCells = _vm->_groupMan->getGroupValueUpdatedWithCreatureValue(L0687_ui_UpdatedGroupCells, L0688_i_CreatureIndex, normalizeModulo4(L0690_ui_GroupCells + L0692_i_RelativeRotation));
			}
			L0684_ui_GroupDirections >>= 2;
			L0690_ui_GroupCells >>= 2;
		}
	}
	_vm->_dungeonMan->setGroupDirections(L0686_ps_Group, L0685_ui_UpdatedGroupDirections, mapIndex);
	_vm->_dungeonMan->setGroupCells(L0686_ps_Group, L0687_ui_UpdatedGroupCells, mapIndex);
	if ((mapIndex == _vm->_dungeonMan->_partyMapIndex) && (L0686_ps_Group->setBehaviour(k6_behavior_ATTACK))) {
		return L0686_ps_Group->getActiveGroupIndex() + 2;
	}
	return 1;
}

Thing MovesensMan::getTeleporterRotatedProjectileThing(Teleporter *teleporter, Thing projectileThing) {
	int16 L0693_i_UpdatedDirection;
	int16 L0694_i_Rotation;

	L0693_i_UpdatedDirection = _moveResultDir;
	L0694_i_Rotation = teleporter->getRotation();
	if (teleporter->getAbsoluteRotation()) {
		L0693_i_UpdatedDirection = L0694_i_Rotation;
	} else {
		L0693_i_UpdatedDirection = normalizeModulo4(L0693_i_UpdatedDirection + L0694_i_Rotation);
		projectileThing = thingWithNewCell(projectileThing, normalizeModulo4((projectileThing).getCell() + L0694_i_Rotation));
	}
	_moveResultDir = L0693_i_UpdatedDirection;
	return projectileThing;
}

void MovesensMan::processThingAdditionOrRemoval(uint16 mapX, uint16 mapY, Thing thing, bool partySquare, bool addThing) {
	Thing L0766_T_Thing;
	int16 L0767_i_ThingType;
	bool L0768_B_TriggerSensor;
	Sensor *L0769_ps_Sensor;
	int16 L0770_ui_SensorTriggeredCell;
	uint16 L0771_ui_ThingType;
	bool L0772_B_SquareContainsObject;
	bool L0773_B_SquareContainsGroup;
	int16 L0774_i_ObjectType;
	bool L0775_B_SquareContainsThingOfSameType;
	bool L0776_B_SquareContainsThingOfDifferentType;
	uint16 L0777_ui_Square;
	int16 L0778_i_Effect;
	int16 L0779_i_SensorData;


	if (thing != Thing::_party) {
		L0767_i_ThingType = thing.getType();
		L0774_i_ObjectType = _vm->_objectMan->getObjectType(thing);
	} else {
		L0767_i_ThingType = kM1_PartyThingType;
		L0774_i_ObjectType = kM1_IconIndiceNone;
	}
	if ((!addThing) && (L0767_i_ThingType != kM1_PartyThingType)) {
		_vm->_dungeonMan->unlinkThingFromList(thing, Thing(0), mapX, mapY);
	}

	L0777_ui_Square = _vm->_dungeonMan->_currMapData[mapX][mapY];
	if (Square(L0777_ui_Square).getType() == k0_WallElemType) {
		L0770_ui_SensorTriggeredCell = thing.getCell();
	} else {
		L0770_ui_SensorTriggeredCell = kM1_CellAny; // this will wrap around
	}
	L0772_B_SquareContainsObject = L0773_B_SquareContainsGroup = L0775_B_SquareContainsThingOfSameType = L0776_B_SquareContainsThingOfDifferentType = false;
	L0766_T_Thing = _vm->_dungeonMan->getSquareFirstThing(mapX, mapY);
	if (L0770_ui_SensorTriggeredCell == kM1_CellAny) {
		while (L0766_T_Thing != Thing::_endOfList) {
			if ((L0771_ui_ThingType = (L0766_T_Thing).getType()) == k4_GroupThingType) {
				L0773_B_SquareContainsGroup = true;
			} else {
				if ((L0771_ui_ThingType == k2_TextstringType) && (L0767_i_ThingType == kM1_PartyThingType) && addThing && !partySquare) {
					_vm->_dungeonMan->decodeText(_vm->_stringBuildBuffer, L0766_T_Thing, k1_TextTypeMessage);
					_vm->_textMan->printMessage(k15_ColorWhite, _vm->_stringBuildBuffer);
				} else {
					if ((L0771_ui_ThingType > k4_GroupThingType) && (L0771_ui_ThingType < k14_ProjectileThingType)) {
						L0772_B_SquareContainsObject = true;
						L0775_B_SquareContainsThingOfSameType |= (_vm->_objectMan->getObjectType(L0766_T_Thing) == L0774_i_ObjectType);
						L0776_B_SquareContainsThingOfDifferentType |= (_vm->_objectMan->getObjectType(L0766_T_Thing) != L0774_i_ObjectType);
					}
				}
			}
			L0766_T_Thing = _vm->_dungeonMan->getNextThing(L0766_T_Thing);
		}
	} else {
		while (L0766_T_Thing != Thing::_endOfList) {
			if ((L0770_ui_SensorTriggeredCell == (L0766_T_Thing).getCell()) && ((L0766_T_Thing).getType() > k4_GroupThingType)) {
				L0772_B_SquareContainsObject = true;
				L0775_B_SquareContainsThingOfSameType |= (_vm->_objectMan->getObjectType(L0766_T_Thing) == L0774_i_ObjectType);
				L0776_B_SquareContainsThingOfDifferentType |= (_vm->_objectMan->getObjectType(L0766_T_Thing) != L0774_i_ObjectType);
			}
			L0766_T_Thing = _vm->_dungeonMan->getNextThing(L0766_T_Thing);
		}
	}
	if (addThing && (L0767_i_ThingType != kM1_PartyThingType)) {
		_vm->_dungeonMan->linkThingToList(thing, Thing(0), mapX, mapY);
	}
	L0766_T_Thing = _vm->_dungeonMan->getSquareFirstThing(mapX, mapY);
	while (L0766_T_Thing != Thing::_endOfList) {
		L0771_ui_ThingType = (L0766_T_Thing).getType();
		if (L0771_ui_ThingType == k3_SensorThingType) {
			L0769_ps_Sensor = (Sensor *)_vm->_dungeonMan->getThingData(L0766_T_Thing);
			if ((L0769_ps_Sensor)->getType() == k0_SensorDisabled)
				goto T0276079;
			L0779_i_SensorData = L0769_ps_Sensor->getData();
			L0768_B_TriggerSensor = addThing;
			if (L0770_ui_SensorTriggeredCell == kM1_CellAny) {
				switch (L0769_ps_Sensor->getType()) {
				case k1_SensorFloorTheronPartyCreatureObj:
					if (partySquare || L0772_B_SquareContainsObject || L0773_B_SquareContainsGroup) /* BUG0_30 A floor sensor is not triggered when you put an object on the floor if a levitating creature is present on the same square. The condition to determine if the sensor should be triggered checks if there is a creature on the square but does not check whether the creature is levitating. While it is normal not to trigger the sensor if there is a non levitating creature on the square (because it was already triggered by the creature itself), a levitating creature should not prevent triggering the sensor with an object. */
						goto T0276079;
					break;
				case k2_SensorFloorTheronPartyCreature:
					if ((L0767_i_ThingType > k4_GroupThingType) || partySquare || L0773_B_SquareContainsGroup)
						goto T0276079;
					break;
				case k3_SensorFloorParty:
					if ((L0767_i_ThingType != kM1_PartyThingType) || (_vm->_championMan->_partyChampionCount == 0))
						goto T0276079;
					if (L0779_i_SensorData == 0) {
						if (partySquare)
							goto T0276079;
					} else {
						if (!addThing) {
							L0768_B_TriggerSensor = false;
						} else {
							L0768_B_TriggerSensor = (L0779_i_SensorData == _vm->indexToOrdinal(_vm->_dungeonMan->_partyDir));
						}
					}
					break;
				case k4_SensorFloorObj:
					if ((L0779_i_SensorData != _vm->_objectMan->getObjectType(thing)) || L0775_B_SquareContainsThingOfSameType)
						goto T0276079;
					break;
				case k5_SensorFloorPartyOnStairs:
					if ((L0767_i_ThingType != kM1_PartyThingType) || (Square(L0777_ui_Square).getType() != k3_StairsElemType))
						goto T0276079;
					break;
				case k6_SensorFloorGroupGenerator:
					goto T0276079;
				case k7_SensorFloorCreature:
					if ((L0767_i_ThingType > k4_GroupThingType) || (L0767_i_ThingType == kM1_PartyThingType) || L0773_B_SquareContainsGroup)
						goto T0276079;
					break;
				case k8_SensorFloorPartyPossession:
					if (L0767_i_ThingType != kM1_PartyThingType)
						goto T0276079;
					L0768_B_TriggerSensor = isObjcetInPartyPossession(L0779_i_SensorData);
					break;
				case k9_SensorFloorVersionChecker:
					if ((L0767_i_ThingType != kM1_PartyThingType) || !addThing || partySquare)
						goto T0276079;
					// Strangerke: 20 is a hardcoded version of the game. later version uses 21. Not present in the original dungeons anyway.
					L0768_B_TriggerSensor = (L0779_i_SensorData <= 20);
					break;
				default:
					goto T0276079;
				}
			} else {
				if (L0770_ui_SensorTriggeredCell != (L0766_T_Thing).getCell())
					goto T0276079;
				switch (L0769_ps_Sensor->getType()) {
				case k1_SensorWallOrnClick:
					if (L0772_B_SquareContainsObject)
						goto T0276079;
					break;
				case k2_SensorWallOrnClickWithAnyObj:
					if (L0775_B_SquareContainsThingOfSameType || (L0769_ps_Sensor->getData() != _vm->_objectMan->getObjectType(thing)))
						goto T0276079;
					break;
				case k3_SensorWallOrnClickWithSpecObj:
					if (L0776_B_SquareContainsThingOfDifferentType || (L0769_ps_Sensor->getData() == _vm->_objectMan->getObjectType(thing)))
						goto T0276079;
					break;
				default:
					goto T0276079;
				}
			}
			L0768_B_TriggerSensor ^= L0769_ps_Sensor->getAttrRevertEffectA();
			L0778_i_Effect = L0769_ps_Sensor->getAttrEffectA();
			if (L0778_i_Effect == k3_SensorEffHold) {
				L0778_i_Effect = L0768_B_TriggerSensor ? k0_SensorEffSet : k1_SensorEffClear;
			} else if (!L0768_B_TriggerSensor)
				goto T0276079;

			if (L0769_ps_Sensor->getAttrAudibleA())
				_vm->_sound->requestPlay(k01_soundSWITCH, mapX, mapY, k1_soundModePlayIfPrioritized);

			triggerEffect(L0769_ps_Sensor, L0778_i_Effect, mapX, mapY, (uint16)kM1_CellAny); // this will wrap around
			goto T0276079;
		}
		if (L0771_ui_ThingType >= k4_GroupThingType)
			break;
T0276079:
		L0766_T_Thing = _vm->_dungeonMan->getNextThing(L0766_T_Thing);
	}
	processRotationEffect();
}

bool MovesensMan::isObjcetInPartyPossession(int16 objectType) {
	int16 L0742_i_ChampionIndex;
	uint16 L0743_ui_SlotIndex = 0;
	Thing L0744_T_Thing = Thing::_none;
	Champion *L0745_ps_Champion;
	Thing *L0746_pT_Thing = nullptr;
	int16 L0747_i_ObjectType;
	bool L0748_B_LeaderHandObjectProcessed;
	Container *L0749_ps_Container;


	L0748_B_LeaderHandObjectProcessed = false;
	for (L0742_i_ChampionIndex = k0_ChampionFirst, L0745_ps_Champion = _vm->_championMan->_champions; L0742_i_ChampionIndex < _vm->_championMan->_partyChampionCount; L0742_i_ChampionIndex++, L0745_ps_Champion++) {
		if (L0745_ps_Champion->_currHealth) {
			L0746_pT_Thing = L0745_ps_Champion->_slots;
			for (L0743_ui_SlotIndex = k0_ChampionSlotReadyHand; (L0743_ui_SlotIndex < k30_ChampionSlotChest_1) && !L0748_B_LeaderHandObjectProcessed; L0743_ui_SlotIndex++) {
				L0744_T_Thing = *L0746_pT_Thing++;
T0274003:
				L0747_i_ObjectType = _vm->_objectMan->getObjectType(L0744_T_Thing);
				if (L0747_i_ObjectType == objectType) {
					return true;
				}
				if (L0747_i_ObjectType == k144_IconIndiceContainerChestClosed) {
					L0749_ps_Container = (Container *)_vm->_dungeonMan->getThingData(L0744_T_Thing);
					L0744_T_Thing = L0749_ps_Container->getSlot();
					while (L0744_T_Thing != Thing::_endOfList) {
						if (_vm->_objectMan->getObjectType(L0744_T_Thing) == objectType) {
							return true;
						}
						L0744_T_Thing = _vm->_dungeonMan->getNextThing(L0744_T_Thing);
					}
				}
			}
		}
	}
	if (!L0748_B_LeaderHandObjectProcessed) {
		L0748_B_LeaderHandObjectProcessed = true;
		L0744_T_Thing = _vm->_championMan->_leaderHandObject;
		goto T0274003;
	}
	return false;
}

void MovesensMan::triggerEffect(Sensor *sensor, int16 effect, int16 mapX, int16 mapY, uint16 cell) {
	byte g59_squareTypeToEventType[7] = { // @ G0059_auc_Graphic562_SquareTypeToEventType
		k6_TMEventTypeWall,
		k5_TMEventTypeCorridor,
		k9_TMEventTypePit,
		k0_TMEventTypeNone,
		k10_TMEventTypeDoor,
		k8_TMEventTypeTeleporter,
		k7_TMEventTypeFakeWall}; /* 1 byte of padding inserted by compiler */

	int16 L0736_i_TargetMapX;
	int16 L0737_i_TargetMapY;
	int32 L0738_l_Time;
	uint16 L0739_ui_SquareType;
	uint16 L0740_ui_TargetCell;


	if (sensor->getAttrOnlyOnce()) {
		sensor->setTypeDisabled();
	}
	L0738_l_Time = _vm->_gameTime + sensor->getAttrValue();
	if (sensor->getAttrLocalEffect()) {
		triggerLocalEffect(sensor->getActionLocalEffect(), mapX, mapY, cell);
	} else {
		L0736_i_TargetMapX = sensor->getActionTargetMapX();
		L0737_i_TargetMapY = sensor->getActionTargetMapY();
		L0739_ui_SquareType = Square(_vm->_dungeonMan->_currMapData[L0736_i_TargetMapX][L0737_i_TargetMapY]).getType();
		if (L0739_ui_SquareType == k0_ElementTypeWall) {
			L0740_ui_TargetCell = sensor->getActionTargetCell();
		} else {
			L0740_ui_TargetCell = k0_CellNorthWest;
		}
		addEvent(g59_squareTypeToEventType[L0739_ui_SquareType], L0736_i_TargetMapX, L0737_i_TargetMapY, L0740_ui_TargetCell, effect, L0738_l_Time);
	}
}

void MovesensMan::triggerLocalEffect(int16 localEffect, int16 effX, int16 effY, int16 effCell) {
	if (localEffect == k10_SensorEffAddExp) {
		addSkillExperience(k8_ChampionSkillSteal, 300, localEffect != kM1_CellAny);
		return;
	}
	_sensorRotationEffect = localEffect;
	_sensorRotationEffMapX = effX;
	_sensorRotationEffMapY = effY;
	_sensorRotationEffCell = effCell;
}

void MovesensMan::addSkillExperience(int16 skillIndex, uint16 exp, bool leaderOnly) {

	if (leaderOnly) {
		if (_vm->_championMan->_leaderIndex != kM1_ChampionNone) {
			_vm->_championMan->addSkillExperience(_vm->_championMan->_leaderIndex, skillIndex, exp);
		}
	} else {
		exp /= _vm->_championMan->_partyChampionCount;
		Champion *L0731_ps_Champion = _vm->_championMan->_champions;
		for (int16 L0730_i_ChampionIndex = k0_ChampionFirst; L0730_i_ChampionIndex < _vm->_championMan->_partyChampionCount; L0730_i_ChampionIndex++, L0731_ps_Champion++) {
			if (L0731_ps_Champion->_currHealth) {
				_vm->_championMan->addSkillExperience(L0730_i_ChampionIndex, skillIndex, exp);
			}
		}
	}
}

void MovesensMan::processRotationEffect() {
	Thing L0732_T_FirstSensorThing;
	Thing L0733_T_LastSensorThing;
	Sensor *L0734_ps_FirstSensor;
	Sensor *L0735_ps_LastSensor;


	if (_sensorRotationEffect == kM1_SensorEffNone) {
		return;
	}
	switch (_sensorRotationEffect) {
	case k1_SensorEffClear:
	case k2_SensorEffToggle:
		L0732_T_FirstSensorThing = _vm->_dungeonMan->getSquareFirstThing(_sensorRotationEffMapX, _sensorRotationEffMapY);
		while (((L0732_T_FirstSensorThing).getType() != k3_SensorThingType) || ((_sensorRotationEffCell != kM1_CellAny) && ((L0732_T_FirstSensorThing).getCell() != _sensorRotationEffCell))) {
			L0732_T_FirstSensorThing = _vm->_dungeonMan->getNextThing(L0732_T_FirstSensorThing);
		}
		L0734_ps_FirstSensor = (Sensor *)_vm->_dungeonMan->getThingData(L0732_T_FirstSensorThing);
		L0733_T_LastSensorThing = L0734_ps_FirstSensor->getNextThing();
		while ((L0733_T_LastSensorThing != Thing::_endOfList) && (((L0733_T_LastSensorThing).getType() != k3_SensorThingType) || ((_sensorRotationEffCell != kM1_CellAny) && ((L0733_T_LastSensorThing).getCell() != _sensorRotationEffCell)))) {
			L0733_T_LastSensorThing = _vm->_dungeonMan->getNextThing(L0733_T_LastSensorThing);
		}
		if (L0733_T_LastSensorThing == Thing::_endOfList)
			break;
		_vm->_dungeonMan->unlinkThingFromList(L0732_T_FirstSensorThing, Thing(0), _sensorRotationEffMapX, _sensorRotationEffMapY);
		L0735_ps_LastSensor = (Sensor *)_vm->_dungeonMan->getThingData(L0733_T_LastSensorThing);
		L0733_T_LastSensorThing = _vm->_dungeonMan->getNextThing(L0733_T_LastSensorThing);
		while (((L0733_T_LastSensorThing != Thing::_endOfList) && ((L0733_T_LastSensorThing).getType() == k3_SensorThingType))) {
			if ((_sensorRotationEffCell == kM1_CellAny) || ((L0733_T_LastSensorThing).getCell() == _sensorRotationEffCell)) {
				L0735_ps_LastSensor = (Sensor *)_vm->_dungeonMan->getThingData(L0733_T_LastSensorThing);
			}
			L0733_T_LastSensorThing = _vm->_dungeonMan->getNextThing(L0733_T_LastSensorThing);
		}
		L0734_ps_FirstSensor->setNextThing(L0735_ps_LastSensor->getNextThing());
		L0735_ps_LastSensor->setNextThing(L0732_T_FirstSensorThing);
	}
	_sensorRotationEffect = kM1_SensorEffNone;
}

void MovesensMan::createEventMoveGroup(Thing groupThing, int16 mapX, int16 mapY, int16 mapIndex, bool audible) {
	TimelineEvent L0696_s_Event;

	setMapAndTime(L0696_s_Event._mapTime, mapIndex, _vm->_gameTime + 5);
	L0696_s_Event._type = audible ? k61_TMEventTypeMoveGroupAudible : k60_TMEventTypeMoveGroupSilent;
	L0696_s_Event._priority = 0;
	L0696_s_Event._B._location._mapX = mapX;
	L0696_s_Event._B._location._mapY = mapY;
	L0696_s_Event._C._slot = groupThing.toUint16();
	_vm->_timeline->addEventGetEventIndex(&L0696_s_Event);
}

Thing MovesensMan::getObjectOfTypeInCell(int16 mapX, int16 mapY, int16 cell, int16 objectType) {
	Thing L0741_T_Thing;


	L0741_T_Thing = _vm->_dungeonMan->getSquareFirstObject(mapX, mapY);
	while (L0741_T_Thing != Thing::_endOfList) {
		if (_vm->_objectMan->getObjectType(L0741_T_Thing) == objectType) {
			if ((cell == kM1_CellAny) || ((L0741_T_Thing.getCell()) == cell)) {
				return L0741_T_Thing;
			}
		}
		L0741_T_Thing = _vm->_dungeonMan->getNextThing(L0741_T_Thing);
	}
	return Thing::_none;
}
}
