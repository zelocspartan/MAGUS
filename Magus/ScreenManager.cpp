
#include "ScreenManager.h"
#include "Scene.h"
#include "HUD.h"

ScreenManager::ScreenManager()
{
	// Name your application
	sAppName = "M.A.G.U.S. client";

}

// Shall be generic, only the setup and states differenciate the sub classes
bool ScreenManager::OnUserUpdate(float fElapsedTime) 
{
	// Called once per frame
	olc::vd2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
	SubLoop(fElapsedTime);

	scenes[activeScene]->updateScene(vMouse, this);


	return true;
}



