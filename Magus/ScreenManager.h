
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "olcPixelGameEngine.h"

#include <vector>
#include <list>
#include <memory>

class Scene;
class BaseClass;
class HUD;


class ScreenManager : public olc::PixelGameEngine
{
public:
	std::vector<std::shared_ptr<Scene>> scenes;
	std::vector<std::shared_ptr<BaseClass>> StringHudButtons;
	uint8_t activeScene;


	olc::Sprite* Hudtextures;
	olc::Sprite* Buttontextures;
	olc::Sprite* Cursor;

	olc::Decal* HudtexturesDecal;
	olc::Decal* ButtontexturesDecal;
	olc::Decal* CursorDecal;

	olc::Sprite* Background;
	olc::Sprite* Foreground;
	olc::Sprite* Hud;
	olc::Sprite* Tooltip;

	olc::Decal* BackgroundDecal;
	olc::Decal* ForegroundDecal;
	olc::Decal* HudDecal;
	olc::Decal* TooltipDecal;

public:

	ScreenManager();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	virtual void ScreenSetup() = 0;
	virtual void AttachDatabase() = 0;
	virtual bool SubLoop(float fElapsedTime) = 0;
	void Attach(std::weak_ptr<HUD> targetHud, std::shared_ptr<BaseClass> tabItem);
	void Attach(std::weak_ptr<HUD> targetHud, std::vector<std::shared_ptr<BaseClass>> table, int tabNumber);







};


#endif	// SCREENMANAGER_H
