
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
		fight,
	};
	enum PlayerHuds {
		qualification,
		Strength,
		Dexterity,
		Constitution,
		Inteligence,
		Willpower,
		Charisma,
	};


	adventurer = std::make_shared<Adventurer>(Adventurer());
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("eszleles     +7")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("meregkeveres +5")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("rejtozes     +4")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("gyogyitas    +2")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("futas        +7")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("13/+2")));

	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Kepzettség")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Str")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Dex")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Con")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Int")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Wil")));
	adventurer->random.push_back(std::make_shared<BaseClass>(BaseClass("Cha")));


	scenes.push_back(std::make_shared<Scene>(Scene()));	//main
	scenes.push_back(std::make_shared<Scene>(Scene()));	//inventory
	scenes.push_back(std::make_shared<Scene>(Scene()));	//map


	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({30, 70},30/*képzetségek száma*/,160)));	//qualification
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({30, 0},1)));//strength
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({95, 0},1)));//dex
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({160, 0},1)));//con
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({230, 0},1)));//int
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({295, 0},1)));//wil
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({360, 0},1)));//cha
	
#pragma region 
	scenes[main]->HUDs[qualification]->addTab(adventurer->random[0]);

	scenes[main]->HUDs[qualification]->addItem(adventurer->test[0]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[1]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[2]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[3]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[4]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[3]);
	scenes[main]->HUDs[qualification]->addItem(adventurer->test[4]);
#pragma endregion képzetségek
#pragma region 
	scenes[main]->HUDs[Strength]->addTab(adventurer->random[1]);
	scenes[main]->HUDs[Dexterity]->addTab(adventurer->random[2]);
	scenes[main]->HUDs[Constitution]->addTab(adventurer->random[3]);
	scenes[main]->HUDs[Inteligence]->addTab(adventurer->random[4]);
	scenes[main]->HUDs[Willpower]->addTab(adventurer->random[5]);
	scenes[main]->HUDs[Charisma]->addTab(adventurer->random[6]);

	scenes[main]->HUDs[Strength]->addItem(adventurer->test[5]);
	scenes[main]->HUDs[Dexterity]->addItem(adventurer->test[5]);
	scenes[main]->HUDs[Constitution]->addItem(adventurer->test[5]);
	scenes[main]->HUDs[Inteligence]->addItem(adventurer->test[5]);
	scenes[main]->HUDs[Willpower]->addItem(adventurer->test[5]);
	scenes[main]->HUDs[Charisma]->addItem(adventurer->test[5]);
#pragma endregion Main Stat
	/*
	scenes[main]->HUDs[inventory]->addTab(adventurer->random[1]);	//one
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

	*/
	//scenes[main]->HUDs[one]->attachDatabase(adventurer->test);

	for (auto& hud : scenes[main]->HUDs) {
		hud->updateHUDdatabase(this);
	}
}


void MagusServer::ScreenSetup() {

	SetPixelMode(olc::Pixel::ALPHA);




}
