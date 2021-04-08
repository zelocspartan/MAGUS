
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
	void DrawSelf(olc::PixelGameEngine* cScreen, olc::vu2d pos, olc::vu2d size, olc::Pixel color);
	void leftClickAction(ScreenManager* cScreen) {}
	void rightClickAction(ScreenManager* cScreen) {}
	void hoverAction(ScreenManager* cScreen) {}
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

	virtual void leftClickAction(ScreenManager* cScreen) { Item.lock()->leftClickAction(cScreen); };
	virtual void rightClickAction(ScreenManager* cScreen) { Item.lock()->rightClickAction(cScreen); };
	virtual void hoverAction(ScreenManager* cScreen) { Item.lock()->hoverAction(cScreen); };

};


class HUD
{
public:
	std::vector<std::string> hudTabs;
	std::vector<std::vector<HUDItem>> hudItems;
	std::map<uint8_t, std::weak_ptr<std::vector<std::shared_ptr<BaseClass>>>> dataBase;
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
	void updateHUDdatabase(ScreenManager* cScreen);
	//void attachDatabase(std::shared_ptr<std::vector<std::shared_ptr<BaseClass>>> data, uint8_t page);


};



#endif	// HUD_H
