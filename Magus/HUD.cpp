
#include "ScreenManager.h"
#include "HUD.h"

void BaseClass::DrawSelf(olc::PixelGameEngine* cScreen, olc::vu2d position, olc::vu2d size, olc::Pixel color) {
	position.y += 5;
	position.x += 15;
	cScreen->DrawString(position, name, color);
}

#pragma region HUDItem

HUDItem::HUDItem(int pos, HUDType t, std::shared_ptr<BaseClass> item) {
	Item = item;
	type = t;
	verticalPos = pos;
}

bool HUDItem::hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, olc::vu2d size, int bracketHeight, olc::vu2d HUDlocation) {
	int x = vMouse.x;
	int y = vMouse.y;
	uint32_t width = size.x;
	if (x >= HUDlocation.x && x <= (HUDlocation.x + width))
		if (y >= (HUDlocation.y + (verticalPos + 1 - verticalOffset) * bracketHeight + 6 + HUDBORDER_WIDTH) && y <= (HUDlocation.y + (verticalPos + 1 - verticalOffset + 1) * bracketHeight) - 1 + 6 + HUDBORDER_WIDTH) {
			DrawBracket(cScreen, HUDlocation, size, bracketHeight, verticalOffset, olc::RED, olc::BLACK);
			hoverAction(cScreen);
			return true;
		}
	return false;
}

void HUDItem::DrawBracket(ScreenManager* cScreen, olc::vu2d HUDlocation, olc::vu2d size, int bracketHeight, int verticalOffset, olc::Pixel border, olc::Pixel backround) {
	// Dont care about offscreen stuff
	int width = size.x;
	int x = HUDlocation.x;
	int y = HUDlocation.y;
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight - 1
		&& (verticalPos - verticalOffset) >= 0) {
		olc::vu2d loc = { (uint32_t)(x + HUDBORDER_WIDTH), (uint32_t)(y + (verticalPos + 1 - verticalOffset) * bracketHeight + HUDBORDER_WIDTH + 6) };
		cScreen->DrawRect(loc, { width - 2*HUDBORDER_WIDTH, bracketHeight - 2 }, border);
		if (!Item.expired()) {
			Item.lock()->DrawSelf(cScreen, loc, { 0,0 }, olc::CYAN);
		}
	}
}

bool HUDItem::updateBracket(
	ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation, 
	int verticalOffset, olc::vu2d size, int bracketHeight
) {
	// Dont care about offscreen stuff
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight - 1
		&& (verticalPos - verticalOffset) >= 0) {
		if (hover(vMouse, cScreen, verticalOffset, size, bracketHeight, HUDlocation)) {
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
	int tempxoffset;
	int tempyoffset;

#pragma region HUD background draw
	// Draw first row of background
	tempyoffset = location.y;
	cScreen->DrawPartialSprite(location, cScreen->Hudtextures, HUDBRACKET_UL_LOC, HUDBRACKET_UL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		tempxoffset = location.x + hucSize.x * t + hulSize.x;
		cScreen->DrawPartialSprite({ tempxoffset,tempyoffset}, cScreen->Hudtextures, HUDBRACKET_UC_LOC, HUDBRACKET_UC_SIZE);
	}
	tempxoffset = location.x + hucSize.x * horizontalparts + hulSize.x;
	cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset}, cScreen->Hudtextures, HUDBRACKET_UR_LOC, HUDBRACKET_UR_SIZE);

	// Draw middle rows
	for (int y = 0; y < verticalparts; y++) {
		tempyoffset = location.y + hmlSize.y * y + hulSize.y;
		tempxoffset = location.x;
		cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_ML_LOC, HUDBRACKET_ML_SIZE);
		for (int x = 0; x < horizontalparts; x++) {
			tempxoffset = location.x + hucSize.x * x + hmlSize.x;
			cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_MC_LOC, HUDBRACKET_MC_SIZE);
		}
		tempxoffset = location.x + hucSize.x * horizontalparts + hmlSize.x;
		cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_MR_LOC, HUDBRACKET_MR_SIZE);
	}

	// Draw bottom rows
	tempyoffset = location.y + hmlSize.y * verticalparts + hulSize.y;
	tempxoffset = location.x;
	cScreen->DrawPartialSprite({ tempxoffset, tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BL_LOC, HUDBRACKET_BL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		tempxoffset = location.x + hucSize.x * t + hulSize.x;
		cScreen->DrawPartialSprite({ tempxoffset,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BC_LOC, HUDBRACKET_BC_SIZE);
	}
	tempxoffset = location.x + hucSize.x * horizontalparts + hulSize.x;
	cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BR_LOC, HUDBRACKET_BR_SIZE);

#pragma endregion

#pragma region HUD tab draw
	// Draw tabs on the hud
	int i = 0;
	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;
	int horizontalPos = location.x + HUDBORDER_WIDTH;
	int verticalPos = location.y + HUDBORDER_WIDTH;

	for (auto& tab : hudTabs) {
		// Calculate button size
		olc::vi2d s = cScreen->GetTextSize(tab);
		int textWidth = s.x + 4 + 2 * BUTTONBORDER_WIDTH;
		float temp = (float)(textWidth - blSize.x - brSize.x) / (float)(bcSize.x);
		int centerParts = temp;
		if (temp > centerParts) centerParts++;
		if (0 > centerParts) centerParts = 0;

		int stringOffset = centerParts * bcSize.x + blSize.x + brSize.x;
		stringOffset -= s.x;
		stringOffset /= 2;

		// Draw button
		cScreen->DrawPartialSprite({ horizontalPos, verticalPos }, cScreen->Buttontextures, BUTTON_LEFT_LOC, BUTTON_LEFT_SIZE);
		for (int t = 0; t < centerParts; t++)
		{
			tempxoffset = horizontalPos + t * bcSize.x + blSize.x;
			cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_CENTER_LOC, BUTTON_CENTER_SIZE);
		}
		tempxoffset = horizontalPos + centerParts * bcSize.x + blSize.x;
		cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_RIGHT_LOC, BUTTON_RIGHT_SIZE);
		
		// Draw tab text
		cScreen->DrawString({ horizontalPos + stringOffset,verticalPos + 3 + BUTTONBORDER_WIDTH }, tab, olc::RED);

		// Draw active border
		if (i++ == activeTab) {
			cScreen->DrawPartialSprite({ horizontalPos, verticalPos }, cScreen->Buttontextures, BUTTON_ACTIVE_LEFT_LOC, BUTTON_ACTIVE_LEFT_SIZE);
			for (int t = 0; t < centerParts; t++)
			{
				tempxoffset = horizontalPos + t * bcSize.x + blSize.x;
				cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_ACTIVE_CENTER_LOC, BUTTON_ACTIVE_CENTER_SIZE);
			}
			tempxoffset = horizontalPos + centerParts * bcSize.x + blSize.x;
			cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_ACTIVE_RIGHT_LOC, BUTTON_ACTIVE_RIGHT_SIZE);
		}
		horizontalPos += centerParts * bcSize.x + blSize.x + brSize.x;
	}

#pragma endregion

	if(hudItems.size() > 0 && hudItems[activeTab].size() > 0) {
		for (auto& item : hudItems[activeTab]) {
			item.DrawBracket(cScreen, location, size, bcSize.y, verticalOffset);
		}
	}
}

bool HUD::hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	int x = vMouse.x;
	int y = vMouse.y;
	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;

	if (x >= location.x && x <= (location.x + size.x))
		if (y >= location.y && y <= (location.y + size.y)) {

			if (hudItems.size() > 0) {
				int i = 0;

				// Draw active tab items in hud body
				if (hudItems[activeTab].size() > 0) {
					for (auto& item : hudItems[activeTab]) {
						item.updateBracket(cScreen, vMouse, location, verticalOffset, size, bcSize.y);
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
				int horizontalPos = location.x + HUDBORDER_WIDTH;
				int verticalPos = location.y + HUDBORDER_WIDTH;
				for (auto& tab : hudTabs) {
					// Calculate button size
					olc::vi2d s = cScreen->GetTextSize(tab);
					int textWidth = s.x + 4 + 2 * BUTTONBORDER_WIDTH;
					float temp = (float)(textWidth - blSize.x - brSize.x) / (float)(bcSize.x);
					int centerParts = temp;
					if (temp > centerParts) centerParts++;
					if (0 > centerParts) centerParts = 0;

					if (vMouse.x <= location.x + HUDBORDER_WIDTH + horizontalPos + centerParts * bcSize.x + blSize.x + brSize.x) {

						cScreen->DrawPartialSprite({ horizontalPos, verticalPos }, cScreen->Buttontextures, BUTTON_HOVER_LEFT_LOC, BUTTON_HOVER_LEFT_SIZE);
						for (int z = 0; z < centerParts; z++)
						{
							int tempxoffset = horizontalPos + z * bcSize.x + blSize.x;
							cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_HOVER_CENTER_LOC, BUTTON_HOVER_CENTER_SIZE);
						}
						int tempxoffset = horizontalPos + centerParts * bcSize.x + blSize.x;
						cScreen->DrawPartialSprite({ tempxoffset, verticalPos }, cScreen->Buttontextures, BUTTON_HOVER_RIGHT_LOC, BUTTON_HOVER_RIGHT_SIZE);

						if (t != activeTab) {	// If the active tab is being hovered, there is no action required
							if (cScreen->GetMouse(0).bPressed) {
								activeTab = t;
								verticalOffset = 0;
							}
						}
						break;
					}
					t++;
					horizontalPos += centerParts * bcSize.x + blSize.x + brSize.x;
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
	olc::vu2d blSize = BUTTON_LEFT_SIZE;
	olc::vu2d bcSize = BUTTON_CENTER_SIZE;
	olc::vu2d brSize = BUTTON_RIGHT_SIZE;
	olc::vu2d hulSize = HUDBRACKET_UL_SIZE;
	olc::vu2d hmlSize = HUDBRACKET_ML_SIZE;
	olc::vu2d hblSize = HUDBRACKET_BL_SIZE;
	olc::vu2d hurSize = HUDBRACKET_UR_SIZE;
	olc::vu2d hucSize = HUDBRACKET_UC_SIZE;
	float ftemp;
	uint16_t utemp;

	// Horizontal size
	size.x = 2 * HUDBORDER_WIDTH;
	for (auto& tab : hudTabs) {
		olc::vi2d s = cScreen->GetTextSize(tab);
		s.x += 4 + 2 * BUTTONBORDER_WIDTH;
		float temp = (float)(s.x - blSize.x - brSize.x) / (float)(bcSize.x);
		uint16_t buttonSize = temp;	// Inner size
		if (temp > buttonSize)
			buttonSize++;
		else if (buttonSize < 0)
			buttonSize = 0;
		size.x += buttonSize * bcSize.x + blSize.x + brSize.x;
	}
	ftemp = (float)(size.x - hulSize.x - hurSize.x) / (float)(hucSize.x);
	utemp = ftemp;
	if (utemp < ftemp)
		utemp++;
	size.x = hulSize.x + hurSize.x + utemp * hucSize.x;

	// Vertical Size
	size.y = 2 * HUDBORDER_WIDTH + bcSize.y + numberOfBrackets * bcSize.y;
	ftemp = (float)(size.y - hulSize.y - hblSize.y) / (float)(hmlSize.y);
	utemp = ftemp;
	if (ftemp > utemp)
		utemp++;
	size.y = hulSize.y + hmlSize.y * utemp + hblSize.y;

	// Resetup database
	//hudItems.clear();
	hudItems.resize(hudTabs.size());	
	/*
	for (auto& data : dataBase) {
		auto it = data.second.lock()->begin();
		for (it; it < data.second.lock()->end(); ++it) {
			addItem((*it), data.first);
		}
	}*/
}
/*
void HUD::attachDatabase(std::vector<std::shared_ptr<BaseClass>> data, uint8_t page) {
	dataBase.insert(std::pair<uint8_t, std::vector<std::shared_ptr<BaseClass>>> (page,data));
}*/


#pragma endregion