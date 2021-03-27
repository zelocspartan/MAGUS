
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "olcPixelGameEngine.h"

#include <vector>
#include <list>
#include <memory>

class Scene;


class ScreenManager : public olc::PixelGameEngine
{
public:
	enum screenLayer {
		background,
		foreground,
		hud,
		tooltip
	};
	std::vector<olc::Sprite*> screenLayers;
	std::list<std::shared_ptr<Scene>> scenes;


public:

	ScreenManager();
	bool OnUserUpdate(float fElapsedTime) override;
	virtual bool SubLoop(float fElapsedTime) = 0;







};


#endif	// SCREENMANAGER_H
