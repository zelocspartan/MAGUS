
#include "Scene.h"
#include "ScreenManager.h"
#include "HUD.h"

bool Scene::updateScene(olc::vd2d vMouse, ScreenManager* cScreen) {
	if (!isActive)
		return false;


	// Background
	cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager::screenLayer::background]);



	// Foreground
	cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager::screenLayer::foreground]);



	// HUD
	cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager::screenLayer::hud]);
	for (auto& hud : HUDs) {
		hud->updateHUD(vMouse, cScreen);
	}


	// Tooltip
	cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager::screenLayer::tooltip]);



	cScreen->SetDrawTarget(nullptr);

	return true;
}
