#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "Resources.h"

#include <string>
#include <vector>

class Attributes
{
public:
	// Variables
	std::string name;
	std::vector<std::string> description;

	uint8_t level;

	uint16_t healthPoint;
	uint16_t painPoint;
	uint32_t manaPoint;

	// Primary attributes, only destibuted points, or possibly modifiers if not player
	uint8_t strength;
	uint8_t dexterity;
	uint8_t constitution;
	uint8_t intelligence;
	uint8_t willPower;
	uint8_t charisma;
	// End of destributed points

	// Secondary attributes
	uint8_t toughness;
	uint8_t quickness;
	uint8_t consciousness;

	// Defenses
	uint8_t physicalDefense;
	uint8_t astralDefense;
	uint8_t mentalDefense;

	// Other
	uint16_t size;
	uint16_t age;
	uint16_t speed;

	// Methods
	Attributes() {};	//delete later
	Attributes(std::string n, 
		uint8_t STR, uint8_t DEX, uint8_t CON, uint8_t INT, uint8_t WIL, uint8_t CHA,
		uint16_t psize = 0, uint16_t pspeed = 0, uint16_t page = 0, uint8_t l = 0,
		uint8_t overridePhysical = 0, uint8_t overrideMental = 0, uint8_t overrideAstral = 0,
		uint16_t hp = 0, uint16_t pp = 0, uint32_t mp = 0
	) {
		strength = STR;
		dexterity = DEX;
		constitution = CON;
		intelligence = INT;
		willPower = WIL;
		charisma = CHA;

		name = n;
		level = l;

		size = psize;
		age = page;
		speed = pspeed;

		healthPoint = hp;
		painPoint = pp;
		manaPoint = mp;

		calcDefenses(overridePhysical, overrideMental, overrideAstral);
	}

	void calcDefenses(uint8_t overridePhysical = 0, uint8_t overrideMental = 0, uint8_t overrideAstral = 0, int8_t extWillPow = 0, int8_t extChar = 0) {
		// Calculate Physical defense
		if (overridePhysical != 0)
			physicalDefense = healthPoint;
		else
			physicalDefense = overridePhysical;

		// Calculate Mental defense
		if (overrideMental != 0)
			mentalDefense = DefaultDefense + calcModifier(willPower, extWillPow) + consciousness;
		else
			mentalDefense = overrideMental;

		// Calculate Astral defense
		if (overrideAstral != 0)
			astralDefense = DefaultDefense + calcModifier(charisma, extChar) + consciousness;
		else
			astralDefense = overrideAstral;
	}


	static int8_t calcModifier(uint8_t destributed, int8_t external = 0) {
		return floor((DefaultAttributeValue + destributed + external - ModifierOffset) / 2);
	}

	
	
	
	

};

class Skill
{
public:
	bool flatValue;
	Attributes modifier;
};

class Species : public Skill
{

};

class AdventurerClass : public Skill
{

};







#endif	//ATTRIBUTES_H
