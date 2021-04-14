
#include "ScreenManager.h"
#include "Scene.h"
#include "HUD.h"

ScreenManager::ScreenManager()
{
	// Name your application
	sAppName = "M.A.G.U.S. client";

	// Texture Setup

	Hudtextures = new olc::Sprite(HUDTEXTURES);
	Buttontextures = new olc::Sprite(BUTTONTEXTURES);
	BGtextures = new olc::Sprite(BGTEXTURES);

	Screen = new olc::Sprite(SCREENWIDTH, SCREENHIGHT);
	Screendecal = new olc::Decal(BGtextures);

	SetPixelMode(olc::Pixel::ALPHA);
}

// Shall be generic, only the setup and states differenciate the sub classes
bool ScreenManager::OnUserUpdate(float fElapsedTime)
{
	// Called once per frame
	olc::vd2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
	SubLoop(fElapsedTime);

	scenes[activeScene]->updateScene(vMouse, this);

	Screendecal->Update();
	//DrawDecal({ 0,0 }, Screendecal);

	return true;
}



