
#include "Scene.h"
#include "ScreenManager.h"
#include "HUD.h"

bool Scene::updateScene(olc::vd2d vMouse, ScreenManager* cScreen) {
	if (!isActive)
		return false;

	//cScreen->SetDrawTarget(cScreen->Screen);

	// Background
	//cScreen->Clear(olc::BLUE);

	cScreen->DrawSprite({ 0,0 }, cScreen->BGtextures);


	// Foreground



	// HUD


	for (auto& hud : HUDs) {
		hud->updateHUD(vMouse, cScreen);
	}


	// Tooltip





	cScreen->SetDrawTarget(nullptr);

	return true;
}
