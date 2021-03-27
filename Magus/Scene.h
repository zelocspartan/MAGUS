#ifndef SCENE_H
#define SCENE_H

#include "olcPixelGameEngine.h"

#include <list>
#include <memory>

class HUD;
class ScreenManager;

class Scene {

	bool isActive;
	std::list<std::shared_ptr<HUD>> HUDs;

public:
	bool updateScene(olc::vd2d vMouse, ScreenManager* cScreen);


};



#endif	// SCENE_H