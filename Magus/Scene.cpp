
#include "Scene.h"
#include "ScreenManager.h"
#include "HUD.h"

bool Scene::updateScene(olc::vd2d vMouse, ScreenManager* cScreen) {
	if (!isActive)
		return false;


	// Background
	cScreen->Clear(olc::BLUE);


	// Foreground



	// HUD


	for (auto& hud : HUDs) {
		hud->updateHUD(vMouse, cScreen);
	}


	// Tooltip





	

	return true;
}
