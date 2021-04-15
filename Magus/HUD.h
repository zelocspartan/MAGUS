
#ifndef HUD_H
#define HUD_H



#include "Resources.h"

#include <vector>
#include <memory>
#include <string>
#include <math.h>
#include <map>


class ScreenManager;
class BaseClass {
	std::string name;


public:
	BaseClass(std::string n) { name = n; }
	virtual void DrawSelf(ScreenManager* cScreen, olc::vu2d pos, olc::vu2d size, olc::Pixel color);
	virtual void leftClickAction(ScreenManager* cScreen) {}
	virtual void rightClickAction(ScreenManager* cScreen) {}
	virtual void hoverAction(ScreenManager* cScreen) {}
	virtual int getTextLength(ScreenManager* cScreen) { return cScreen->GetTextSize(name).x; }
};


class HUDTab {
	olc::vu2d location;
	olc::vu2d size;
	uint8_t stringOffset;
	std::weak_ptr<BaseClass> Item;

public:

	HUDTab(std::shared_ptr<BaseClass> item);
	uint8_t calcSize(ScreenManager* cScreen, olc::vu2d pos);
	bool TabHover(ScreenManager* cScreen, olc::vd2d vMouse);
	void DrawSelf(ScreenManager* cScreen, bool activeTab, olc::Pixel color = olc::RED);
	void offsetButton(int os);
};


class HUDItem {

	std::weak_ptr<BaseClass> Item;
	int verticalPos;
	HUDType type;

	virtual void leftClickAction(ScreenManager* cScreen) { Item.lock()->leftClickAction(cScreen); };
	virtual void rightClickAction(ScreenManager* cScreen) { Item.lock()->rightClickAction(cScreen); };
	virtual void hoverAction(ScreenManager* cScreen) { Item.lock()->hoverAction(cScreen); };

public:

	HUDItem(int pos, HUDType t = header, std::shared_ptr<BaseClass> item = nullptr);
	~HUDItem() {};

	bool hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, int horizontalOffset, olc::vu2d size, int bracketHeight, olc::vu2d HUDlocation);
	void DrawBracket(ScreenManager* cScreen, olc::vu2d HUDlocation, olc::vu2d size, int bracketHeight, int verticalOffset, int horizontalOffset);
	bool updateBracket(ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation,
		int verticalOffset, int horizontalOffset, olc::vu2d size, int bracketHeight);

};


class HUD
{
	std::vector<HUDTab> hudTabs;
	std::vector<std::vector<HUDItem>> hudItems;
	std::map<uint8_t, std::weak_ptr<std::vector<std::shared_ptr<BaseClass>>>> dataBase;
	olc::vu2d location;
	uint8_t numberOfBrackets;
	int minimalWidth;

	// Automatic variables
	olc::vu2d size;
	uint8_t activeTab;
	int verticalOffset;
	int buttonOffset;
	int lineOffset;

	// internal methods
	void drawHUD(ScreenManager* cScreen);
	bool hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen);

public:
	HUD(olc::vu2d loc, uint8_t numOfBrack = 5, int minimalW = 0);
	bool updateHUD(olc::vd2d vMouse, ScreenManager* cScreen);
	void addItem(std::shared_ptr<BaseClass> newItem, int tab = 0);
	void addTab(std::shared_ptr<BaseClass> newTab);
	void updateHUDdatabase(ScreenManager* cScreen);
	void clearHUDDatabase();
	void resizeHUDDatabase();

};



#endif	// HUD_H
