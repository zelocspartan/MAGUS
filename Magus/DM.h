#ifndef SERVER_H
#define SERVER_H


#include "olcPixelGameEngine.h"
#include "ScreenManager.h"



class DungeonMaster;

template <class T>
class MagusServer : public ScreenManager <T>
{
public:
	std::shared_ptr<DungeonMaster> DM;

public:
	MagusServer() {

	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels


		return true;
	}
};



#endif	//SERVER_H



#ifndef DM_H
#define DM_H

#include "Player.h"

#include <vector>
#include <memory>


class DungeonMaster
{
public:
	std::vector<std::shared_ptr<Adventurer>> adventurers;



};


#endif	// DM_H