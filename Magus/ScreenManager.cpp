
#include "ScreenManager.h"
#include "Scene.h"
#include "HUD.h"

ScreenManager::ScreenManager()
{
	// Name your application
	sAppName = "M.A.G.U.S. client";

	screenLayers.push_back(new olc::Sprite(ScreenWidth(), ScreenHeight()));	// Background
	screenLayers.push_back(new olc::Sprite(ScreenWidth(), ScreenHeight()));	// Foreground
	screenLayers.push_back(new olc::Sprite(ScreenWidth(), ScreenHeight()));	// HUD
	screenLayers.push_back(new olc::Sprite(ScreenWidth(), ScreenHeight()));	// Tooltip
}

// Shall be generic, only the setup and states differenciate the sub classes
bool ScreenManager::OnUserUpdate(float fElapsedTime) 
{
	// Called once per frame
	olc::vd2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
	SubLoop(fElapsedTime);

	for (auto& scene : scenes)
	{
		scene->updateScene(vMouse, this);
	}

	return true;
}



