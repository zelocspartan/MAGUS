
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
	Cursor = new olc::Sprite(CURSORTEXTURE);

	
	

	SetPixelMode(olc::Pixel::ALPHA);
}

// Shall be generic, only the setup and states differenciate the sub classes
bool ScreenManager::OnUserUpdate(float fElapsedTime)
{
	// Called once per frame
	olc::vd2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
	olc::vf2d cent = { (float)(Cursor->width / 2), (float)(Cursor->height / 2) };
	SubLoop(fElapsedTime);

	scenes[activeScene]->updateScene(vMouse, this);

	

	Screendecal->Update();
	DrawDecal({ 0,0 }, BackgroundDecal);
	DrawDecal({ 0,0 }, Screendecal);
	DrawRotatedDecal(vMouse, CursorDecal, 3.14, cent , { 0.1,0.1 });
	return true;
}



