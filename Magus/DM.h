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

	virtual bool SubLoop(float fElapsedTime) override {
		// Called once per frame, shall contain only Server specific operations

		return true;
	}

	void ScreenSetup() override;
	void AttachDatabase() override;

};



#endif	//SERVER_H



