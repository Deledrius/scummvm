//
//  Instruction.cpp
//  Phantasma
//
//  Created by Thomas Harte on 08/12/2013.
//  Copyright (c) 2013 Thomas Harte. All rights reserved.
//

#include "freescape/language/instruction.h"
#include "freescape/language/8bitDetokeniser.h"
#include "freescape/freescape.h"

namespace Freescape {

FCLInstruction::FCLInstruction(Token::Type _type) {
	// TODO: learn modern constructor syntax
	type = _type;
	thenInstructions = nullptr;
	elseInstructions = nullptr;
}

FCLInstruction::FCLInstruction() {
	type = Token::UNKNOWN;
	thenInstructions = nullptr;
	elseInstructions = nullptr;
}

void FCLInstruction::setSource(int32 _source) {
	source = _source;
}

void FCLInstruction::setDestination(int32 _destination) {
	destination = _destination;
}

void FCLInstruction::setBranches(FCLInstructionVector *thenBranch, FCLInstructionVector *elseBranch) {
	thenInstructions = thenBranch;
	elseInstructions = elseBranch;
}

Token::Type FCLInstruction::getType() {
	return type;
}

void FreescapeEngine::executeCode(FCLInstructionVector &code, bool shot, bool collided) {
	assert(!(shot && collided));
	int ip = 0;
	int codeSize = code.size();
	while (ip <= codeSize - 1) {
		FCLInstruction &instruction = code[ip];
		debug("Executing ip: %d in code with size: %d", ip, codeSize);
		switch (instruction.getType()) {
			default:
			break;
			case Token::COLLIDEDQ:
			if (collided)
				executeCode(*instruction.thenInstructions, shot, collided);
			// else branch is always empty
			assert(instruction.elseInstructions == nullptr);
			break;
			case Token::SHOTQ:
			if (shot)
				executeCode(*instruction.thenInstructions, shot, collided);
			// else branch is always empty
			assert(instruction.elseInstructions == nullptr);
			break;
			case Token::VARNOTEQ:
			if (executeEndIfNotEqual(instruction))
				ip = codeSize;
			break;
			case Token::ADDVAR:
			executeIncrementVariable(instruction);
			break;
			case Token::SUBVAR:
			executeDecrementVariable(instruction);
			break;
			case Token::GOTO:
			executeGoto(instruction);
			break;
			case Token::TOGVIS:
			executeToggleVisibility(instruction);
			break;
			case Token::INVIS:
			executeMakeInvisible(instruction);
			break;
			case Token::VIS:
			executeMakeVisible(instruction);
			break;
			case Token::DESTROY:
			executeDestroy(instruction);
			break;
			case Token::REDRAW:
			executeRedraw(instruction);
			break;
			case Token::DELAY:
			executeDelay(instruction);
			break;
			case Token::SOUND:
			executeSound(instruction);
			break;
			case Token::SETBIT:
			executeSetBit(instruction);
			break;
			case Token::CLEARBIT:
			executeClearBit(instruction);
			break;
			case Token::BITNOTEQ:
			if (executeEndIfBitNotEqual(instruction))
				ip = codeSize;
			break;
			case Token::INVISQ:
			if (executeEndIfVisibilityIsNotEqual(instruction))
				ip = codeSize;
			break;
		}
		ip++;
	}
	return;
}


void FreescapeEngine::executeRedraw(FCLInstruction &instruction) {
	debug("Redrawing screen");
	drawFrame();
}

void FreescapeEngine::executeSound(FCLInstruction &instruction) {
	uint16 index = instruction.source;
	playSound(index);
}

void FreescapeEngine::executeDelay(FCLInstruction &instruction) {
	uint16 delay = instruction.source;
	debug("Delaying %d * 1/50 seconds", delay);
	g_system->delayMillis(20 * delay);
}

bool FreescapeEngine::executeEndIfVisibilityIsNotEqual(FCLInstruction &instruction) {
	uint16 objectID = instruction.source;
	uint16 value = instruction.destination;
	debug("End condition if visibility of obj with id %d is %d!", objectID, value);
	Object *obj = _currentArea->objectWithID(objectID);
	assert(obj);
	return (obj->isInvisible() == value);
}

bool FreescapeEngine::executeEndIfNotEqual(FCLInstruction &instruction) {
	uint16 variable = instruction.source;
	uint16 value = instruction.destination;
	debug("End condition if variable %d is not equal to %d!", variable, value);
	return (_gameStateVars[variable] != value);
}

void FreescapeEngine::executeIncrementVariable(FCLInstruction &instruction) {
	uint16 variable = instruction.source;
	uint16 increment = instruction.destination;
	_gameStateVars[variable] = _gameStateVars[variable] + increment;
	if (variable == k8bitVariableScore) {
		debug("Score incremented by %d up to %d", increment, _gameStateVars[variable]);
	} else
		debug("Variable %d by %d incremented up to %d!", variable, increment, _gameStateVars[variable]);
}

void FreescapeEngine::executeDecrementVariable(FCLInstruction &instruction) {
	uint16 variable = instruction.source;
	uint16 decrement = instruction.destination;
	_gameStateVars[variable] = _gameStateVars[variable] - decrement;
	if (variable == k8bitVariableEnergy) {
		debug("Energy decrement by %d up to %d", decrement, _gameStateVars[variable]);
	} else
		debug("Variable %d by %d incremented up to %d!", variable, decrement, _gameStateVars[variable]);
}

void FreescapeEngine::executeDestroy(FCLInstruction &instruction) {
	uint16 objectID = instruction.source;
	debug("Destroying obj %d!", objectID);
	Object *obj = _currentArea->objectWithID(objectID);
	assert(!obj->isDestroyed());
	obj->destroy();
}

void FreescapeEngine::executeMakeInvisible(FCLInstruction &instruction) {
	uint16 objectID = 0;
	uint16 areaID = _currentArea->getAreaID();

	if (instruction.destination > 0) {
		objectID = instruction.destination;
		areaID = instruction.source;
	} else {
		objectID = instruction.source;
	}

	debug("Making obj %d invisible in area %d!", objectID, areaID);
	Object *obj = (*_areasByAreaID)[areaID]->objectWithID(objectID);
	obj->makeInvisible();
}

void FreescapeEngine::executeMakeVisible(FCLInstruction &instruction) {
	uint16 objectID = 0;
	uint16 areaID = _currentArea->getAreaID();

	if (instruction.destination > 0) {
		objectID = instruction.destination;
		areaID = instruction.source;
	} else {
		objectID = instruction.source;
	}

	debug("Making obj %d visible in area %d!", objectID, areaID);
	Object *obj = (*_areasByAreaID)[areaID]->objectWithID(objectID);
	obj->makeVisible();
}

void FreescapeEngine::executeToggleVisibility(FCLInstruction &instruction) {
	uint16 objectID = 0;
	uint16 areaID = _currentArea->getAreaID();

	if (instruction.destination > 0) {
		objectID = instruction.destination;
		areaID = instruction.source;
	} else {
		objectID = instruction.source;
	}

	debug("Toggling obj %d visibility in area %d!", objectID, areaID);
	Object *obj = (*_areasByAreaID)[areaID]->objectWithID(objectID);
	obj->toggleVisibility();
}

void FreescapeEngine::executeGoto(FCLInstruction &instruction) {
	uint16 areaID = instruction.source;
	uint16 entranceID = instruction.destination;
	gotoArea(areaID, entranceID);
}

void FreescapeEngine::executeSetBit(FCLInstruction &instruction) {
	uint16 index = instruction.source - 1; // Starts in 1
	assert(index < 32);
	_gameStateBits[_currentArea->getAreaID()] |= (1 << index);
	debug("Setting bit %d", index);
	//debug("v: %d", (_gameStateBits[_currentArea->getAreaID()] & (1 << index)));
}

void FreescapeEngine::executeClearBit(FCLInstruction &instruction) {
	uint16 index = instruction.source - 1; // Starts in 1
	assert(index < 32);
	_gameStateBits[_currentArea->getAreaID()] &= ~(1 << index);
	debug("Clearing bit %d", index);
}

void FreescapeEngine::executeToggleBit(FCLInstruction &instruction) {
	uint16 index = instruction.source - 1; // Starts in 1
	_gameStateBits[_currentArea->getAreaID()] ^= (1 << index);
	debug("Toggling bit %d", index);
}

bool FreescapeEngine::executeEndIfBitNotEqual(FCLInstruction &instruction) {
	uint16 index = instruction.source - 1; // Starts in 1
	uint16 value = instruction.destination;
	assert(index < 32);
	debug("End condition if bit %d is not equal to %d!", index, value);
	return (((_gameStateBits[_currentArea->getAreaID()] >> index) & 1) != value);
}

} // End of namespace Freescape