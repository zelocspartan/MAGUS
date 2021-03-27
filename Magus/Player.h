#ifndef CLIENT_H
#define CLIENT_H


#include "olcPixelGameEngine.h"
#include "ScreenManager.h"



class Adventurer;


class MagusClient : public ScreenManager
{
	enum ClientState {

	};

public:
	std::shared_ptr<Adventurer> adventurer;

public:
	MagusClient() {

	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		return true;
	}

	virtual bool SubLoop(float fElapsedTime) override {
		// Called once per frame, shall contain only Client specific operations


		return true;
	}


};




#endif	//CLIENT_H



#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Spell.h"
#include "Attributes.h"

//#include "olcPGEX_Network.h"


#include <vector>
#include <string>


class Adventurer
{
public:
	// Variables
	Species species;
	AdventurerClass advClass;
	Attributes attributes;

	std::vector<Skill> skills;
	std::vector<Item> items;
	std::vector<Spell> spells;

	// Current state
	uint16_t currentHealthPoints;
	uint16_t currentPainPoints;	
	uint32_t currentManaPoints;

	// Override variables
	uint8_t overridePhysical = 0;
	uint8_t overrideMental = 0;
	uint8_t overrideAstral = 0;

	// Methods
	void levelUp(uint8_t thrownValue) {
		int8_t extConst = 0;
		//ToDo calculate external constitution
		levelUpPainPoint(thrownValue, extConst);
		levelUpManaPoint();
		updateAttributes();
	}
	
	void levelUpManaPoint() {
		//ToDo
	}

	void levelUpPainPoint(uint8_t thrownValue, int8_t extConst = 0) {
		attributes.painPoint += thrownValue + Attributes::calcModifier(attributes.constitution, extConst);
	}

	void updateAttributes() {
		int8_t extToughMod = 0;
		int8_t extQuickMod = 0;
		int8_t extConscMod = 0;
		int8_t extWillPow = 0;
		int8_t extChar = 0;
		int8_t extConst = 0;
		// ToDo
	
		calcSecondaryAttributes(extToughMod, extQuickMod, extConscMod);
		calcHP(extConst);
		attributes.calcDefenses(overridePhysical, overrideMental, overrideAstral, extWillPow, extChar);
	}

	void calcSecondaryAttributes(int8_t extToughMod = 0, int8_t extQuickMod = 0, int8_t extConscMod = 0) {
		attributes.toughness = extToughMod;
		attributes.quickness = extQuickMod;
		attributes.consciousness = extConscMod;
	}

	void calcHP(int8_t extConst = 0) {
		attributes.healthPoint = DefaultHealthPoint + attributes.toughness + Attributes::calcModifier(attributes.constitution, extConst);
	}

};



#endif	// PLAYER_H