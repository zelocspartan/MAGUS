
#ifndef HUD_H
#define HUD_H



#include "Resources.h"

#include <vector>
#include <memory>
#include <string>


class ScreenManager;
class BaseClass;


class HUDItem {

public:
	std::weak_ptr<BaseClass> Item;
	int verticalPos;
	HUDType type;
	std::string name;

	HUDItem(int pos, HUDType t = header, std::shared_ptr<BaseClass> item = nullptr);
	~HUDItem() {};

	bool hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, int width, int bracketHeight, olc::vu2d HUDlocation);
	void DrawBracket(ScreenManager* cScreen, int width, int bracketHeight, int verticalOffset, olc::Pixel border = olc::BLACK, olc::Pixel backround = olc::BLACK);
	bool updateBracket(ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation,
		int verticalOffset, int width, int bracketHeight);

	virtual void leftClickAction(ScreenManager* cScreen) {};
	virtual void rightClickAction(ScreenManager* cScreen) {};

};


class HUD
{
public:
	std::vector<std::shared_ptr<HUDItem>> hudItems;
	olc::vu2d location;
	olc::vu2d size;
	olc::Pixel borderColor;
	olc::Pixel bracketBackgroundColor;
	int bracketHeight;
	int verticalOffset;	// for scroller


	void drawHUD(ScreenManager* cScreen);
	bool hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen);
	bool updateHUD(olc::vd2d vMouse, ScreenManager* cScreen);


};



#endif	// HUD_H
