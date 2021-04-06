
#ifndef HUD_H
#define HUD_H



#include "Resources.h"

#include <vector>
#include <memory>
#include <string>


class ScreenManager;
class BaseClass {
	std::string name;


public:
	BaseClass(std::string n) { name = n; }
	void DrawSelf(olc::PixelGameEngine* cScreen, olc::vu2d pos, olc::vu2d size, olc::Pixel color);
};


class HUDItem {

public:
	std::weak_ptr<BaseClass> Item;
	int verticalPos;
	HUDType type;
	std::string name;

	HUDItem(int pos, HUDType t = header, std::shared_ptr<BaseClass> item = nullptr);
	~HUDItem() {};

	bool hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, olc::vu2d size, int bracketHeight, olc::vu2d HUDlocation);
	void DrawBracket(ScreenManager* cScreen, olc::vu2d HUDlocation, olc::vu2d size, int bracketHeight, int verticalOffset, olc::Pixel border = olc::BLACK, olc::Pixel backround = olc::BLACK);
	bool updateBracket(ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation,
		int verticalOffset, olc::vu2d size, int bracketHeight);

	virtual void leftClickAction(ScreenManager* cScreen) {};
	virtual void rightClickAction(ScreenManager* cScreen) {};

};


class HUD
{
public:
	std::vector<std::string> hudTabs;
	std::vector<std::vector<HUDItem>> hudItems;
	uint8_t activeTab;
	olc::vu2d location;
	olc::vu2d size;
	olc::Pixel borderColor;
	olc::Pixel bracketBackgroundColor;
	int bracketHeight;
	int verticalOffset;	// for scroller


	void drawHUD(ScreenManager* cScreen);
	bool hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen);
	bool updateHUD(olc::vd2d vMouse, ScreenManager* cScreen);
	void addItem(std::shared_ptr<BaseClass> newItem, int tab = 0);


};



#endif	// HUD_H
