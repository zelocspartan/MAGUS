
#include "Player.h"
#include "DM.h"
#include "Resources.h"
#include "Scene.h"
#include "HUD.h"

#pragma region Player Screen Setup

void MagusClient::ScreenSetup() {
	// Enums moved to player.h

	// this part is only for testing
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("eszleles     +7")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("meregkeveres +5")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("rejtozes     +4")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("gyogyitas    +2")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("futas        +7")));
	adventurer->test.push_back(std::make_shared<BaseClass>(BaseClass("13/+2")));
	// end of test part

	// Adding header texts
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Kepzettség")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Str")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Dex")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Con")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Int")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Wil")));
	StringHudButtons.push_back(std::make_shared<BaseClass>(BaseClass("Cha")));
	// End of header texts

	// Adding Scenes
	scenes.push_back(std::make_shared<Scene>(Scene()));	//main
	scenes.push_back(std::make_shared<Scene>(Scene()));	//inventory
	scenes.push_back(std::make_shared<Scene>(Scene()));	//map
	// End of Scenes

	// Adding HUDs
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({30, 70},30/*képzetségek száma*/,160)));	//qualification
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({30, 0},1)));//strength
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({95, 0},1)));//dex
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({160, 0},1)));//con
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({230, 0},1)));//int
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({295, 0},1)));//wil
	scenes[main]->HUDs.push_back(std::make_shared<HUD>(HUD({360, 0},1)));//cha
	// End of HUDs

	// This function is attaching tabs and items to HUDs
	AttachDatabase();
}

void MagusClient::AttachDatabase() {
	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->clearHUDDatabase();
		}
	}

	// Put tab attaches here

	Attach(scenes[main]->HUDs[qualification], StringHudButtons[0]);
	Attach(scenes[main]->HUDs[Strength], StringHudButtons[1]);
	Attach(scenes[main]->HUDs[Dexterity], StringHudButtons[2]);
	Attach(scenes[main]->HUDs[Constitution], StringHudButtons[3]);
	Attach(scenes[main]->HUDs[Inteligence], StringHudButtons[4]);
	Attach(scenes[main]->HUDs[Willpower], StringHudButtons[5]);
	Attach(scenes[main]->HUDs[Charisma], StringHudButtons[6]);



	// End of tab attaches

	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->resizeHUDDatabase();
		}
	}

	// Put item attaches here

	Attach(scenes[0]->HUDs[0], adventurer->test, 0);



	// End of item attaches

	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->updateHUDdatabase(this);
		}
	}
}

#pragma endregion

#pragma region DM Screen Setup

void MagusServer::ScreenSetup() {




	AttachDatabase();
}

void MagusServer::AttachDatabase() {
	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->clearHUDDatabase();
		}
	}

	// Put tab attaches here




	// End of tab attaches

	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->resizeHUDDatabase();
		}
	}

	// Put item attaches here




	// End of item attaches

	for (auto& scene : scenes) {
		for (auto& hud : scene->HUDs) {
			hud->updateHUDdatabase(this);
		}
	}
}

#pragma endregion
