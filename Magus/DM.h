#ifndef SERVER_H
#define SERVER_H


#include "olcPixelGameEngine.h"



class DungeonMaster;

class MagusServer : public olc::PixelGameEngine
{
public:
	std::shared_ptr<DungeonMaster> DM;

	MagusServer()
	{
		// Name your application
		sAppName = "M.A.G.U.S. client";
	}

public:
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