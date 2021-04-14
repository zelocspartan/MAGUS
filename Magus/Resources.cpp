
#include "Player.h"
#include "DM.h"
#include "Resources.h"
#include "Scene.h"
#include "HUD.h"


void MagusClient::ScreenSetup() {
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

	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("tab one")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("tab two")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("tab three")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("tab four")));


	scenes.push_back(std::make_shared<Scene>(Scene()));	//main
	scenes.push_back(std::make_shared<Scene>(Scene()));	//inventory
	scenes.push_back(std::make_shared<Scene>(Scene()));	//map


	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({200, 60})));	//one
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({800, 120})));	//two

	scenes[main]->HUDs[one]->addTab(adventurer->random[0]);	//one
	scenes[main]->HUDs[one]->addTab(adventurer->random[1]);	//two
	scenes[main]->HUDs[one]->addTab(adventurer->random[2]);	//three
	scenes[main]->HUDs[one]->addTab(adventurer->random[3]);	//four

	scenes[main]->HUDs[one]->addItem(adventurer->test[0]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[1]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[2]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[3]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[4]);
	scenes[main]->HUDs[one]->addItem(adventurer->test[3], 1);
	scenes[main]->HUDs[one]->addItem(adventurer->test[4], 1);
	
	scenes[main]->HUDs[inventory]->addTab(adventurer->random[0]);	//one
	scenes[main]->HUDs[inventory]->addTab(adventurer->random[1]);	//two
	scenes[main]->HUDs[inventory]->addTab(adventurer->random[2]);	//three
	scenes[main]->HUDs[inventory]->addTab(adventurer->random[3]);	//four
					   
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[0]);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[1]);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[2]);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[3]);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[4]);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[3], 1);
	scenes[main]->HUDs[inventory]->addItem(adventurer->test[4], 1);

	
	//scenes[main]->HUDs[one]->attachDatabase(adventurer->test);
	scenes[main]->isActive = true;
	scenes[inventory]->isActive = false;
	scenes[map]->isActive = false;

	for (auto& hud : scenes[main]->HUDs) {
		hud->updateHUDdatabase(this);
	}
}


void MagusServer::ScreenSetup() {

	SetPixelMode(olc::Pixel::ALPHA);




}
