
#include "Player.h"
#include "DM.h"
#include "Resources.h"
#include "Scene.h"
#include "HUD.h"


void MagusClient::ScreenSetup() {
	SetPixelMode(olc::Pixel::ALPHA);
	//only test!!!
	enum PlayerScenes {
		main,
		inventory,
		map
	};
	enum PlayerHuds {
		one,
		two
	};


	adventurer = std::make_shared<Adventurer>(Adventurer());
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("1")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("2")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("3")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("4")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("5")));



	scenes.push_back(std::make_shared<Scene>(Scene()));	//main
	scenes.push_back(std::make_shared<Scene>(Scene()));	//inventory
	scenes.push_back(std::make_shared<Scene>(Scene()));	//map


	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD()));	//one
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD()));	//two
	int i = 0;
	for (auto& hud : scenes[main]->HUDs) {
		hud->bracketHeight = 20;
		hud->location.x = i * 200;
		hud->location.y = i++ * 200 +60;
		hud->size = { 0, 80 };
	}

	scenes[main]->HUDs[one]->hudTabs.push_back("tab one");	//one
	scenes[main]->HUDs[one]->hudTabs.push_back("tab two");	//two
	scenes[main]->HUDs[one]->hudTabs.push_back("tab three");	//two
	scenes[main]->HUDs[one]->hudTabs.push_back("tab four");	//two

	scenes[main]->HUDs[one]->addItem(adventurer->test[0]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[1]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[2]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[3]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[4]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[3], 1);
	scenes[main]->HUDs[one]->addItem(adventurer->test[4], 1);
	//scenes[main]->HUDs[one]->attachDatabase(adventurer->test);
	scenes[main]->isActive = true;
	scenes[inventory]->isActive = false;
	scenes[map]->isActive = false;

	for (auto& hud : scenes[main]->HUDs) {
		hud->updateHUDdatabase(this);
	}


	
	scenes[inventory]->HUDs.push_back(std::make_shared<HUD>(HUD()));	//one
	scenes[inventory]->HUDs.push_back(std::make_shared<HUD>(HUD()));	//two
}


void MagusServer::ScreenSetup() {

	SetPixelMode(olc::Pixel::ALPHA);




}
