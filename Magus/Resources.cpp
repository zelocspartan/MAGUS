
#include "Player.h"
#include "DM.h"
#include "Resources.h"
#include "Scene.h"
#include "HUD.h"


void MagusClient::ScreenSetup() {
	//only test!!!
	enum PlayerScenes {
		main
	};



	scenes.push_back(std::make_shared<Scene>(new Scene()));	//main
	scenes.push_back(std::make_shared<Scene>(new Scene()));	//inventory
	scenes.push_back(std::make_shared<Scene>(new Scene()));	//map


	scenes[main]->HUDs.push_back(std::make_shared<HUD>(new HUD()));
	

}


void MagusServer::ScreenSetup() {





}
