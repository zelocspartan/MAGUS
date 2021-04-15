#ifndef RESOURCES_H
#define RESOURCES_H

#pragma region account constants


 
#define DefaultHealthPoint 10
#define DefaultDefense 10
#define DefaultAttributeValue 8
#define ModifierOffset 10

#pragma endregion

#pragma region HUD constants
#define SCREENWIDTH 1440
#define SCREENHIGHT 900

#define HUDBRACKETHEIGHT 20
#define HUDBRACKET_UL_LOC {0,0}
#define HUDBRACKET_UL_SIZE {20,20}
#define HUDBRACKET_UC_LOC {20,0}
#define HUDBRACKET_UC_SIZE {20,20}
#define HUDBRACKET_UR_LOC {40,0}
#define HUDBRACKET_UR_SIZE {20,20}
#define HUDBRACKET_ML_LOC {0,20}
#define HUDBRACKET_ML_SIZE {20,20}
#define HUDBRACKET_MC_LOC {20,20}
#define HUDBRACKET_MC_SIZE {20,20}
#define HUDBRACKET_MR_LOC {40,20}
#define HUDBRACKET_MR_SIZE {20,20}
#define HUDBRACKET_BL_LOC {0,40}
#define HUDBRACKET_BL_SIZE {20,20}
#define HUDBRACKET_BC_LOC {20,40}
#define HUDBRACKET_BC_SIZE {20,20}
#define HUDBRACKET_BR_LOC {40,40}
#define HUDBRACKET_BR_SIZE {20,20}
#define HUDBORDER_WIDTH 4

#define BUTTON_LEFT_LOC {0,0}
#define BUTTON_LEFT_SIZE {20,20}
#define BUTTON_CENTER_LOC {20,0}
#define BUTTON_CENTER_SIZE {20,20}
#define BUTTON_RIGHT_LOC {40,0}
#define BUTTON_RIGHT_SIZE {20,20}
#define BUTTON_ACTIVE_LEFT_LOC {0,20}
#define BUTTON_ACTIVE_LEFT_SIZE {20,20}
#define BUTTON_ACTIVE_CENTER_LOC {20,20}
#define BUTTON_ACTIVE_CENTER_SIZE {20,20}
#define BUTTON_ACTIVE_RIGHT_LOC {40,20}
#define BUTTON_ACTIVE_RIGHT_SIZE {20,20}
#define BUTTON_HOVER_LEFT_LOC {0,40}
#define BUTTON_HOVER_LEFT_SIZE {20,20}
#define BUTTON_HOVER_CENTER_LOC {20,40}
#define BUTTON_HOVER_CENTER_SIZE {20,20}
#define BUTTON_HOVER_RIGHT_LOC {40,40}
#define BUTTON_HOVER_RIGHT_SIZE {20,20}
#define BUTTONBORDER_WIDTH 3

enum HUDType {
	header
};

#pragma endregion


#pragma region Player HUD constants
#define HUD_MAINMENU_POS_SCALED  {5, 5}
#define HUD_MAINMENU_SIZE {3, 3}

#pragma endregion

#pragma region file locations

#define HUDTEXTURES "../Resources/Sprite/Border.png"
#define BUTTONTEXTURES "../Resources/Sprite/Button.png"
#define BGTEXTURES "../Resources/Sprite/Background.png"
#define CURSORTEXTURE "../Resources/Sprite/Culsor.png"



#pragma endregion

#endif	66RESOURCES_H