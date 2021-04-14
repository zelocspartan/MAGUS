
#include "ScreenManager.h"
#include "Scene.h"
#include "HUD.h"

ScreenManager::ScreenManager()
{
	// Name your application
	sAppName = "M.A.G.U.S. client";	

	SetPixelMode(olc::Pixel::ALPHA);
}

bool ScreenManager::OnUserCreate()
{
	// Called once at the start, so create things here
	ScreenSetup();

	// Texture Setup

	Hudtextures = new olc::Sprite(HUDTEXTURES);
	Buttontextures = new olc::Sprite(BUTTONTEXTURES);
	Cursor = new olc::Sprite(CURSORTEXTURE);

	HudtexturesDecal = new olc::Decal(Hudtextures);
	ButtontexturesDecal = new olc::Decal(Buttontextures);
	CursorDecal = new olc::Decal(Cursor);

	Background = new olc::Sprite(BGTEXTURES);		

	BackgroundDecal = new olc::Decal(Background);
	
	return true;
}

// Shall be generic, only the setup and states differenciate the sub classes
bool ScreenManager::OnUserUpdate(float fElapsedTime)
{
	// Called once per frame
	olc::vd2d vMouse = { (float)GetMouseX(), (float)GetMouseY() };
	SubLoop(fElapsedTime);

	scenes[activeScene]->updateScene(vMouse, this);

	//olc::vf2d cent = { (float)(Cursor->width / 2), (float)(Cursor->height / 2) };
	//DrawRotatedDecal(vMouse, CursorDecal, 3.14, cent , { 0.1,0.1 });
	return true;
}



