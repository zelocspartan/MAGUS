
#include "ScreenManager.h"
#include "HUD.h"

#pragma region HUDItem

HUDItem::HUDItem(int pos, HUDType t, std::shared_ptr<BaseClass> item) {
	Item = item;
	type = t;
	verticalPos = pos;
}

bool HUDItem::hover(olc::vd2d vMouse, ScreenManager* cScreen, int verticalOffset, int width, int bracketHeight, olc::vu2d HUDlocation) {
	int x = vMouse.x;
	int y = vMouse.y;
	if (x >= HUDlocation.x && x <= (HUDlocation.x + width))
		if (y >= ((verticalPos - verticalOffset) * bracketHeight) && y <= ((verticalPos - verticalOffset + 1) * bracketHeight) - 1) {
			DrawBracket(cScreen, width, bracketHeight, verticalOffset, olc::RED, olc::BLACK);
			return true;
		}
	return false;
}

void HUDItem::DrawBracket(ScreenManager* cScreen, int width, int bracketHeight, int verticalOffset, olc::Pixel border, olc::Pixel backround) {
	// Dont care about offscreen stuff
	if ((verticalPos - verticalOffset) < cScreen->ScreenHeight() / bracketHeight
		&& (verticalPos - verticalOffset) >= 0) {
		//cScreen->FillRect({ 1,(verticalPos - cScreen->verticalOffset + offset) * HUDBRACKETHEIGHT +1}, { HUDWIDTH - 3, HUDBRACKETHEIGHT - 2 }, backround);
		cScreen->DrawRect({ 1,(verticalPos - verticalOffset) * bracketHeight + 1 }, { width - 3, bracketHeight - 2 }, border);
		cScreen->DrawString({ 15, (verticalPos - verticalOffset) * bracketHeight + 5 }, name, olc::CYAN);
	}
}

bool HUDItem::updateBracket(
	ScreenManager* cScreen, olc::vd2d vMouse, olc::vu2d HUDlocation, 
	int verticalOffset, int width, int bracketHeight
) {
	// Dont care about offscreen stuff
	if ((verticalPos - verticalOffset) < cScreen->ScreenHeight() / bracketHeight
		&& (verticalPos - verticalOffset) >= 0) {
		if (hover(vMouse, cScreen, verticalOffset, width, bracketHeight, HUDlocation)) {
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
	cScreen->FillRect(location, size, bracketBackgroundColor);
	cScreen->DrawRect(location, size, borderColor);

	for (auto& item : hudItems) {
		item->DrawBracket(cScreen, size.y, bracketHeight, verticalOffset);
	}
}

bool HUD::hoverHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	int x = vMouse.x;
	int y = vMouse.y;
	if (x >= location.x && x <= (location.x + size.x))
		if (y >= location.y && y <= (location.y + size.y)) {

			int i = 0;
			for (auto& item : hudItems) {
				item->updateBracket(cScreen, vMouse, location, verticalOffset, size.y, bracketHeight);
				i++;
			}

			// Handle HUD input
			if (i > cScreen->ScreenHeight() / bracketHeight) {
				if (cScreen->GetMouseWheel() < 0)
					if (verticalOffset < i - cScreen->ScreenHeight() / bracketHeight) verticalOffset++;
					else verticalOffset = i - cScreen->ScreenHeight() / bracketHeight;

				if (cScreen->GetMouseWheel() > 0)
					if (verticalOffset > 0) verticalOffset--;
					else verticalOffset = 0;
			}

			return true;
		}
	return false;
}

bool HUD::updateHUD(olc::vd2d vMouse, ScreenManager* cScreen) {
	drawHUD(cScreen);
	return hoverHUD(vMouse, cScreen);
}


#pragma endregion