
#include "Scene.h"
#include "ScreenManager.h"
#include "HUD.h"

bool Scene::updateScene(olc::vd2d vMouse, ScreenManager* cScreen) {

	// Background
	cScreen->DrawDecal({ 0,0 }, cScreen->BackgroundDecal);



	// Foreground


	// HUD

	for (auto& hud : HUDs) {
		hud->updateHUD(vMouse, cScreen);
	}


	// Tooltip





	return true;
}
