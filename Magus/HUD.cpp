
#include "ScreenManager.h"
#include "HUD.h"

void BaseClass::DrawSelf(olc::PixelGameEngine* cScreen, olc::vu2d position, olc::vu2d size, olc::Pixel color) {
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
		if (y >= (HUDlocation.y + (verticalPos + 1 - verticalOffset) * bracketHeight) && y <= (HUDlocation.y + (verticalPos + 1 - verticalOffset + 1) * bracketHeight) - 1) {
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
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight
		&& (verticalPos - verticalOffset) >= 0) {
		//cScreen->FillRect({ 1,(verticalPos - cScreen->verticalOffset + offset) * HUDBRACKETHEIGHT +1}, { HUDWIDTH - 3, HUDBRACKETHEIGHT - 2 }, backround);
		//cScreen->DrawRect({ x + 1, y + (verticalPos + 1 - verticalOffset) * bracketHeight + 1 }, { width - 3, bracketHeight - 2 }, border);
		olc::vu2d loc = { (uint32_t)(x + 15), (uint32_t)(y + (verticalPos + 1 - verticalOffset) * bracketHeight + 5) };
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
	if ((verticalPos + 1 - verticalOffset) < size.y / bracketHeight
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

#pragma region HUD background draw
	//cScreen->FillRect(location, size, bracketBackgroundColor);
	//cScreen->DrawRect(location, size, borderColor);

	// Get the actual size for the hud 
	olc::vu2d ulSize = HUDBRACKET_UL_SIZE;
	olc::vu2d urSize = HUDBRACKET_UR_SIZE;
	olc::vu2d ucSize = HUDBRACKET_UC_SIZE;
	olc::vu2d mlSize = HUDBRACKET_UC_SIZE;
	olc::vu2d blSize = HUDBRACKET_UC_SIZE;
	float temp = (float)(size.x - ulSize.x - urSize.x) / (float)(ucSize.x);
	int horizontalparts = temp;
	if (temp > horizontalparts)
		horizontalparts++;
	size.x = ulSize.x + urSize.x + horizontalparts * ucSize.x;

	temp = (float)(size.y - ulSize.y - urSize.y) / (float)(ucSize.y);
	int verticalparts = temp;
	if (temp > verticalparts)
		verticalparts++;

	// Draw first row of background
	int tempxoffset;
	int tempyoffset = location.y;
	cScreen->DrawPartialSprite(location, cScreen->Hudtextures, HUDBRACKET_UL_LOC, HUDBRACKET_UL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		tempxoffset = location.x + ucSize.x * t + ulSize.x;
		cScreen->DrawPartialSprite({ tempxoffset,tempyoffset}, cScreen->Hudtextures, HUDBRACKET_UC_LOC, HUDBRACKET_UC_SIZE);
	}
	tempxoffset = location.x + ucSize.x * horizontalparts + ulSize.x;
	cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset}, cScreen->Hudtextures, HUDBRACKET_UR_LOC, HUDBRACKET_UR_SIZE);

	// Draw middle rows
	for (int y = 0; y < verticalparts; y++) {
		tempyoffset = location.y + mlSize.y * y + ulSize.y;
		tempxoffset = location.x;
		cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_ML_LOC, HUDBRACKET_ML_SIZE);
		for (int x = 0; x < horizontalparts; x++) {
			tempxoffset = location.x + ucSize.x * x + mlSize.x;
			cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_MC_LOC, HUDBRACKET_MC_SIZE);
		}
		tempxoffset = location.x + ucSize.x * horizontalparts + mlSize.x;
		cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_MR_LOC, HUDBRACKET_MR_SIZE);
	}

	// Draw bottom rows
	tempyoffset = location.y + mlSize.y * verticalparts + ulSize.y;
	tempxoffset = location.x;
	cScreen->DrawPartialSprite({ tempxoffset, tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BL_LOC, HUDBRACKET_BL_SIZE);
	for (int t = 0; t < horizontalparts; t++)
	{
		tempxoffset = location.x + ucSize.x * t + ulSize.x;
		cScreen->DrawPartialSprite({ tempxoffset,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BC_LOC, HUDBRACKET_BC_SIZE);
	}
	tempxoffset = location.x + ucSize.x * horizontalparts + ulSize.x;
	cScreen->DrawPartialSprite({ tempxoffset ,tempyoffset }, cScreen->Hudtextures, HUDBRACKET_BR_LOC, HUDBRACKET_BR_SIZE);

#pragma endregion

	// Draw tabs on the hud
	int i = 0;
	int horizontalPos = 0;
	int verticalPos = location.y + 1;
	for (auto& tab : hudTabs) {
		olc::vi2d s = cScreen->GetTextSize(tab);
		cScreen->DrawString({ horizontalPos + 2,verticalPos + 8 }, tab, olc::RED);
		if (i++ == activeTab) {
			cScreen->DrawRect({ horizontalPos + 1,verticalPos }, { s.x + 2, bracketHeight - 2 }, olc::BLUE);
		}
		horizontalPos += s.x + 4;
	}

	if(hudItems.size() > 0 && hudItems[activeTab].size() > 0) {
		for (auto& item : hudItems[activeTab]) {
			item.DrawBracket(cScreen, location, size, bracketHeight, verticalOffset);
		}
	}
}

bool HUD::hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	int x = vMouse.x;
	int y = vMouse.y;
	if (x >= location.x && x <= (location.x + size.x))
		if (y >= location.y && y <= (location.y + size.y)) {

			if (hudItems.size() > 0) {
				int i = 0;

				if (hudItems[activeTab].size() > 0) {
					for (auto& item : hudItems[activeTab]) {
						item.updateBracket(cScreen, vMouse, location, verticalOffset, size, bracketHeight);
						i++;
					}
				}


				// Handle HUD input
				if (i > size.y / bracketHeight) {
					if (cScreen->GetMouseWheel() < 0)
						if (verticalOffset < i - size.y / bracketHeight + 1) verticalOffset++;
						else verticalOffset = i - size.y / bracketHeight + 1;

					if (cScreen->GetMouseWheel() > 0)
						if (verticalOffset > 0) verticalOffset--;
						else verticalOffset = 0;
				}
			}

			if (vMouse.y <= location.y + bracketHeight) {	// If in the first bracket (hud tabs line)
				int t = 0;
				int horizontalPos = 0;
				int verticalPos = location.y + 1;
				for (auto& tab : hudTabs) {
					olc::vi2d s = cScreen->GetTextSize(tab);
					if (vMouse.x <= location.x + horizontalPos + s.x + 4) {
						cScreen->DrawRect({ horizontalPos + 1,verticalPos }, { s.x + 2, bracketHeight - 2 }, olc::RED);
						if (t != activeTab) {	// If the active tab is being hovered, there is no action required
							if (cScreen->GetMouse(0).bPressed) {
								activeTab = t;
								verticalOffset = 0;
							}
						}
						break;
					}
					t++;
					horizontalPos += s.x + 4;
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
	//hudItems.clear();
	// Effectively autosize
	size.x = 0;
	for (auto& tab : hudTabs) {
		olc::vi2d s = cScreen->GetTextSize(tab);
		size.x += s.x + 4;
	}
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