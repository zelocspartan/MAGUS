
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "olcPixelGameEngine.h"

#include <vector>
#include <memory>

template <class T> class HUD;

template <class T>
class ScreenManager : public olc::PixelGameEngine
{
public:
	enum screenLayer {
		background,
		foreground,
		hud
	};

	std::vector<std::shared_ptr<olc::Sprite>> screenLayers;

	std::vector<std::shared_ptr<HUD<T>>> HUDs;


public:
	ScreenManager()
	{
		// Name your application
		sAppName = "M.A.G.U.S. client";
	}

};



#endif	// SCREENMANAGER_H


#ifndef HUD_H
#define HUD_H


#include "olcPixelGameEngine.h"
#include "Resources.h"

#include <vector>
#include <memory>




template <class T>
class HUDItem {

public:
	std::weak_ptr<T> Item;
	std::string name;
	int verticalPos;
	Type type;

	HUDItem(int pos, Type t, std::shared_ptr<T> item = nullptr) {
		Item = item;
		type = t;
		verticalPos = pos;
	}
	~HUDItem() {}

	bool hover(olc::vd2d vMouse, ScreenManager<T>* cScreen, int offset, int width, int bracketHeight, olc::vu2d HUDlocation) {
		int x = vMouse.x;
		int y = vMouse.y;
		if (x >= HUDlocation.x && x <= (HUDlocation.x + width))
			if (y >= ((verticalPos - cScreen->verticalOffset + offset) * bracketHeight) && y <= ((verticalPos - cScreen->verticalOffset + offset + 1) * bracketHeight) - 1) {
				DrawBracket(cScreen, offset, olc::RED, olc::BLACK);
				return true;
			}
		return false;
	}

	void DrawBracket(ScreenManager<T>* cScreen, int width, int bracketHeight, int offset, olc::Pixel border = olc::BLACK, olc::Pixel backround = olc::BLACK) {
		cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager<T>::screenLayer::hud]);
		//cScreen->FillRect({ 1,(verticalPos - cScreen->verticalOffset + offset) * HUDBRACKETHEIGHT +1}, { HUDWIDTH - 3, HUDBRACKETHEIGHT - 2 }, backround);
		cScreen->DrawRect({ 1,(verticalPos - cScreen->verticalOffset + offset) * bracketHeight + 1 }, { cScreen->width - 3, bracketHeight - 2 }, border);
		cScreen->DrawString({ 15, (verticalPos - cScreen->verticalOffset + offset) * bracketHeight + 5 }, name, olc::CYAN);
		cScreen->SetDrawTarget(nullptr);
	}

	virtual void leftClickAction(ScreenManager<T>* cScreen) {
		
	};
	virtual void rightClickAction(ScreenManager<T>* cScreen) {

	}

};


template <class T>
class HUD
{
public:
	std::vector<std::shared_ptr<HUDItem<T>>> hudItems;
	olc::vu2d location;
	olc::vu2d size;
	int bracketHight;


	void drawHUD(ScreenManager<T>* cScreen) {
		cScreen->SetDrawTarget(cScreen->screenLayers[ScreenManager<T>::screenLayer::hud]);
		for (int i = 0; i < hudItems.size(); i++) {
			
		}
		cScreen->SetDrawTarget(nullptr);
	}

	bool HUDhover(olc::vd2d vMouse, ScreenManager<T>* cScreen) {
		int x = vMouse.x;
		int y = vMouse.y;
		if (x >= location.x && x <= (location.x + size.x))
			if (y >= location.y && y <= (location.y + size.y)) {
				// ToDo check huditem hover, and action
				return true;
			}
		return false;
	}


};



#endif	// HUD_H
