#ifndef SERVER_H
#define SERVER_H


#include "olcPixelGameEngine.h"
#include "ScreenManager.h"



class DungeonMaster;


class MagusServer : public ScreenManager
{
	enum ServerState {

	};

public:
	std::shared_ptr<DungeonMaster> DM;

public:
	MagusServer() {

	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		ScreenSetup();


		return true;
	}

	virtual bool SubLoop(float fElapsedTime) override {
		// Called once per frame, shall contain only Server specific operations

		return true;
	}

	void ScreenSetup();

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