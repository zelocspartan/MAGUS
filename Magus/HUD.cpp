
#include "ScreenManager.h"
#include "HUD.h"

void BaseClass::DrawSelf(ScreenManager* cScreen, olc::vu2d position, olc::vu2d size, olc::Pixel color) {
	position.y += 5;
	cScreen->DrawStringDecal(position, name, color);
}

#pragma region HUDTab
uint8_t HUDTab::calcSize(ScreenManager* cScreen, olc::vu2d pos) {
	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;

	if (Item.expired())
		return 0;

	location = pos;

	// Calculate button size
	int s = Item.lock()->getTextLength(cScreen);
	int textWidth = s + 4 + 2 * BUTTONBORDER_WIDTH;
	int reqCentPixel = textWidth - blSize.x - brSize.x;
	double temp = (float)(reqCentPixel) / (float)(bcSize.x);
	int centerParts = temp;
	if (temp > centerParts) centerParts++;
	if (0 > centerParts || reqCentPixel < 0) centerParts = 0;

	size.x = blSize.x + centerParts * bcSize.x + brSize.x;
	size.y = bcSize.y;

	stringOffset = (size.x - s) / 2;

	return size.x;
}
bool HUDTab::TabHover(ScreenManager* cScreen, olc::vd2d vMouse) {
	if (Item.expired())
		return false;

	if (location.x < vMouse.x && location.x + size.x > vMouse.x) {
		if (location.y < vMouse.y && location.y + size.y > vMouse.y) {
			olc::vu2d blSize = BUTTON_LEFT_SIZE;
			olc::vu2d bcSize = BUTTON_CENTER_SIZE;
			olc::vu2d brSize = BUTTON_RIGHT_SIZE;
			int centerParts = (size.x - blSize.x - brSize.x) / (bcSize.x);
			olc::vf2d templocation;

			templocation.x = location.x;
			templocation.y = location.y;
			// Draw button
			cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_LEFT_LOC, BUTTON_HOVER_LEFT_SIZE);
			for (int t = 0; t < centerParts; t++)
			{
				templocation.x = location.x + t * bcSize.x + blSize.x;
				cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_CENTER_LOC, BUTTON_HOVER_CENTER_SIZE);
			}
			templocation.x = location.x + centerParts * bcSize.x + blSize.x;
			cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_RIGHT_LOC, BUTTON_HOVER_RIGHT_SIZE);

			Item.lock()->hoverAction(cScreen);

			return true;
		}
	}
	return false;
}
void HUDTab::DrawSelf(ScreenManager* cScreen, bool activeTab, olc::Pixel color) {
	if (Item.expired())
		return;

	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;
	int centerParts = (size.x - blSize.x - brSize.x) / (bcSize.x);
	olc::vf2d templocation;
	int i = 0;
	templocation.x = location.x;
	templocation.y = location.y;
	

	// Draw button
	cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_LEFT_LOC, BUTTON_LEFT_SIZE);
	for (int t = 0; t < centerParts; t++)
	{
		templocation.x = location.x + t * bcSize.x + blSize.x;
		cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_CENTER_LOC, BUTTON_CENTER_SIZE);

	}
	templocation.x = location.x + centerParts * bcSize.x + blSize.x;
	cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_RIGHT_LOC, BUTTON_RIGHT_SIZE);

	// Draw string
	olc::vu2d pos = { location.x + stringOffset, location.y };
	Item.lock()->DrawSelf(cScreen, pos, { 0,0 }, color);

	// Draw active border
	if (activeTab) {
		templocation = location;
		cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_ACTIVE_LEFT_LOC, BUTTON_ACTIVE_LEFT_SIZE);
		for (int t = 0; t < centerParts; t++)
		{
			templocation.x = location.x + t * bcSize.x + blSize.x;
			cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_ACTIVE_CENTER_LOC, BUTTON_ACTIVE_CENTER_SIZE);
		}
		templocation.x = location.x + centerParts * bcSize.x + blSize.x;
		cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_ACTIVE_RIGHT_LOC, BUTTON_ACTIVE_RIGHT_SIZE);
	}

}
HUDTab::HUDTab(std::shared_ptr<BaseClass> item) { Item = item; }
void HUDTab::offsetButton(int os) { location.x += os; }

#pragma endregion

#pragma region HUDItem

HUDItem::HUDItem(int pos, HUDType t, std::shared_ptr<BaseClass> item) {
	Item = item;
	type = t;
	verticalPos = pos;
}
bool HUDItem::hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, int horizontalOffset, olc::vu2d size, int bracketHeight, olc::vu2d HUDlocation) {
	int x = vMouse.x;
	int y = vMouse.y;
	uint32_t width = size.x;
	if (x >= HUDlocation.x && x <= (HUDlocation.x + width))
		if (y >= (HUDlocation.y + (verticalPos + 1 - verticalOffset) * bracketHeight + 6 + HUDBORDER_WIDTH) && y <= (HUDlocation.y + (verticalPos + 1 - verticalOffset + 1) * bracketHeight) - 1 + 6 + HUDBORDER_WIDTH) {
			olc::vu2d location = { (uint32_t)(HUDlocation.x + HUDBORDER_WIDTH), (uint32_t)(HUDlocation.y + (verticalPos + 1 - verticalOffset) * bracketHeight + HUDBORDER_WIDTH + 6) };

			olc::vu2d blSize = BUTTON_LEFT_SIZE;
			olc::vu2d bcSize = BUTTON_CENTER_SIZE;
			olc::vu2d brSize = BUTTON_RIGHT_SIZE;
			int centerParts = (size.x - blSize.x - brSize.x - 2 * HUDBORDER_WIDTH) / (bcSize.x);
			olc::vf2d templocation;

			templocation.x = location.x + horizontalOffset;
			templocation.y = location.y;

			// Draw button
			cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_LEFT_LOC, BUTTON_HOVER_LEFT_SIZE);
			for (int t = 0; t < centerParts; t++)
			{
				templocation.x = location.x + t * bcSize.x + blSize.x + horizontalOffset;
				cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_CENTER_LOC, BUTTON_HOVER_CENTER_SIZE);
			}
			templocation.x = location.x + centerParts * bcSize.x + blSize.x + horizontalOffset;
			cScreen->DrawPartialDecal(templocation, cScreen->ButtontexturesDecal, BUTTON_HOVER_RIGHT_LOC, BUTTON_HOVER_RIGHT_SIZE);

			hoverAction(cScreen);
			return true;
		}
	return false;
}
void HUDItem::DrawBracket(ScreenManager* cScreen, olc::vu2d HUDlocation, olc::vu2d size, int bracketHeight, int verticalOffset, int horizontalOffset) {
	// Dont care about offscreen stuff
	int width = size.x;
	int x = HUDlocation.x;
	int y = HUDlocation.y;
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight - 1
		&& (verticalPos - verticalOffset) >= 0) {
		olc::vu2d loc = { (uint32_t)(x + horizontalOffset + 15), (uint32_t)(y + (verticalPos + 1 - verticalOffset) * bracketHeight + HUDBORDER_WIDTH + 6) };
		//cScreen->DrawRect(loc, { width - 2*HUDBORDER_WIDTH, bracketHeight - 2 }, border);
		if (!Item.expired()) {
			Item.lock()->DrawSelf(cScreen, loc, { 0,0 }, olc::CYAN);
		}
	}
}
bool HUDItem::updateBracket(
	ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation, 
	int verticalOffset, int horizontalOffset, olc::vu2d size, int bracketHeight
) {
	// Dont care about offscreen stuff
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight - 1
		&& (verticalPos - verticalOffset) >= 0) {
		if (hover(vMouse, cScreen, verticalOffset, horizontalOffset, size, bracketHeight, HUDlocation)) {
			if (cScreen->GetMouse(0).bPressed)
				leftClickAction(cScreen);
			if (cScreen->GetMouse(1).bPressed)
				rightClickAction(cScreen);
			return true;
		}
	}
	return false;
}

#pragma endregion

#pragma region HUD

HUD::HUD(olc::vu2d loc, uint8_t numOfBrack, int minimalW) {
	location = loc;
	numberOfBrackets = numOfBrack;
	minimalWidth = minimalW;

	// Automatic variables
	lineOffset = 0;
	buttonOffset = 0;
	verticalOffset = 0;
	size = { 0,0 };
	activeTab = 0;
}
void HUD::drawHUD(ScreenManager* cScreen) {
	// If there is nothing to draw
	if (size.x == 0 || size.y == 0)
		return;

	// Get the actual size for the hud 
	olc::vu2d hulSize = HUDBRACKET_UL_SIZE;
	olc::vu2d hurSize = HUDBRACKET_UR_SIZE;
	olc::vu2d hucSize = HUDBRACKET_UC_SIZE;
	olc::vu2d hmlSize = HUDBRACKET_UC_SIZE;
	olc::vu2d hblSize = HUDBRACKET_UC_SIZE;
	int horizontalparts = (size.x - hulSize.x - hurSize.x) / (hucSize.x);
	int verticalparts = (size.y - hulSize.y - hurSize.y) / (hucSize.y);
	olc::vf2d templocation;

	templocation.x = location.x;
	templocation.y = location.y;

#pragma region HUD background draw
	// Draw first row of background
	cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_UL_LOC, HUDBRACKET_UL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		templocation.x = location.x + hucSize.x * t + hulSize.x;
		cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_UC_LOC, HUDBRACKET_UC_SIZE);
	}
	templocation.x = location.x + hucSize.x * horizontalparts + hulSize.x;
	cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_UR_LOC, HUDBRACKET_UR_SIZE);

	// Draw middle rows
	for (int y = 0; y < verticalparts; y++) {
		templocation.y = location.y + hmlSize.y * y + hulSize.y;
		templocation.x = location.x;
		cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_ML_LOC, HUDBRACKET_ML_SIZE);
		for (int x = 0; x < horizontalparts; x++) {
			templocation.x = location.x + hucSize.x * x + hmlSize.x;
			cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_MC_LOC, HUDBRACKET_MC_SIZE);
		}
		templocation.x = location.x + hucSize.x * horizontalparts + hmlSize.x;
		cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_MR_LOC, HUDBRACKET_MR_SIZE);
	}

	// Draw bottom rows
	templocation.y = location.y + hmlSize.y * verticalparts + hulSize.y;
	templocation.x = location.x;
	cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_BL_LOC, HUDBRACKET_BL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		templocation.x = location.x + hucSize.x * t + hulSize.x;
		cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_BC_LOC, HUDBRACKET_BC_SIZE);
	}
	templocation.x = location.x + hucSize.x * horizontalparts + hulSize.x;
	cScreen->DrawPartialDecal(templocation, cScreen->HudtexturesDecal, HUDBRACKET_BR_LOC, HUDBRACKET_BR_SIZE);

#pragma endregion

#pragma region HUD tab draw
	// Draw tabs on the hud
	int i = 0;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;

	for (auto& tab : hudTabs) {
		bool active = false;
		if (i++ == activeTab)
			active = true;
		tab.DrawSelf(cScreen, active);
	}

#pragma endregion

	if(hudItems.size() > 0 && hudItems[activeTab].size() > 0) {
		for (auto& item : hudItems[activeTab]) {
			item.DrawBracket(cScreen, location, size, bcSize.y, verticalOffset, lineOffset);
		}
	}
}
bool HUD::hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	int x = vMouse.x;
	int y = vMouse.y;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;

	if (x >= location.x && x <= (location.x + size.x))
		if (y >= location.y && y <= (location.y + size.y)) {

			if (hudItems.size() > 0) {
				int i = 0;

				// Draw active tab items in hud body
				if (hudItems[activeTab].size() > 0) {
					for (auto& item : hudItems[activeTab]) {
						item.updateBracket(cScreen, vMouse, location, verticalOffset, lineOffset, size, bcSize.y);
						i++;
					}
				}

				// Handle HUD input
				if (i > numberOfBrackets) {
					if (cScreen->GetMouseWheel() < 0)
						if (verticalOffset < i - numberOfBrackets) verticalOffset++;
						else verticalOffset = i - numberOfBrackets;

					if (cScreen->GetMouseWheel() > 0)
						if (verticalOffset > 0) verticalOffset--;
						else verticalOffset = 0;
				}
			}

			if (vMouse.y <= location.y + HUDBORDER_WIDTH + bcSize.y
				&& vMouse.y >= location.y + HUDBORDER_WIDTH) {	// If in the first bracket (hud tabs line)
				int t = 0;
				for (auto& tab : hudTabs) {
					if (tab.TabHover(cScreen, vMouse)) {
						if (t != activeTab) {	// If the active tab is being hovered, there is no action required
							if (cScreen->GetMouse(0).bPressed) {
								activeTab = t;
								verticalOffset = 0;
							}
						}
						break;
					}
					t++;
				}
			}

			return true;
		}
	return false;
}
bool HUD::updateHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	// Other updates
	drawHUD(cScreen);
	return hoverHUD(vMouse, cScreen);
}
void HUD::addItem(std::shared_ptr<BaseClass> newItem, int tab) {
	if (tab >= hudItems.size()) {
		hudItems.resize(tab + 1);
	}
	hudItems[tab].push_back(HUDItem(hudItems[tab].size(), header, newItem));
}
void HUD::updateHUDdatabase(ScreenManager* cScreen) {
	if (numberOfBrackets == 0 || hudTabs.size() == 0)
		return;

	// Effectively autosize
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;
	olc::vu2d hulSize = HUDBRACKET_UL_SIZE;
	olc::vu2d hmlSize = HUDBRACKET_ML_SIZE;
	olc::vu2d hblSize = HUDBRACKET_BL_SIZE;
	olc::vu2d hurSize = HUDBRACKET_UR_SIZE;
	olc::vu2d hucSize = HUDBRACKET_UC_SIZE;
	float ftemp;
	uint16_t utemp;
	int buttonwidth = 0;

	// Horizontal size
	size.x = HUDBORDER_WIDTH;
	olc::vu2d tempPos = { 0 ,location.y + HUDBORDER_WIDTH };
	for (auto& tab : hudTabs) {
		tempPos.x = location.x + size.x;
		size.x += tab.calcSize(cScreen, tempPos);	// Calculate and set position, size, and string offset for tabs
	}
	buttonwidth = size.x - HUDBORDER_WIDTH;			// Sub calculation for button offset
	size.x += HUDBORDER_WIDTH;

	// Check for minimal width
	if (minimalWidth > size.x) size.x = minimalWidth;

	ftemp = (float)(size.x - hulSize.x - hurSize.x) / (float)(hucSize.x);
	utemp = ftemp;
	if (utemp < ftemp)
		utemp++;
	size.x = hulSize.x + hurSize.x + utemp * hucSize.x;		// Get the actual required width of the hud block
	
	// Center buttons
	buttonOffset = (size.x - buttonwidth) / 2 - HUDBORDER_WIDTH;
	for (auto& tab : hudTabs) {
		tab.offsetButton(buttonOffset);
	}

	// Center lines
	int centerParts = (size.x - blSize.x - brSize.x - 2 * HUDBORDER_WIDTH) / (bcSize.x);	// For getting the maximum centerparts that fit inbetween the hud borders
	lineOffset = (size.x - (blSize.x + brSize.x + centerParts * bcSize.x)) / 2 - HUDBORDER_WIDTH;


	// Vertical Size
	size.y = 2 * HUDBORDER_WIDTH + bcSize.y + numberOfBrackets * bcSize.y;
	ftemp = (float)(size.y - hulSize.y - hblSize.y) / (float)(hmlSize.y);
	utemp = ftemp;
	if (ftemp > utemp)
		utemp++;
	size.y = hulSize.y + hmlSize.y * utemp + hblSize.y;		// Get the actual required height of the hud block
}
void HUD::addTab(std::shared_ptr<BaseClass> newTab) {
	hudTabs.push_back(HUDTab(newTab));
}
void HUD::clearHUDDatabase() {
	hudTabs.clear();
	hudItems.clear();
}
void HUD::resizeHUDDatabase() { hudItems.resize(hudTabs.size()); }


#pragma endregion