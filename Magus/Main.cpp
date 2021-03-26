#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "DM.h"
#include "Player.h"

#include <iostream>

int main()
{
	std::cout << "Adventurer[A] or DungeonMaster[DM]?" << std::endl;
	std::string startupChoice;

	while(true)
	{
		std::cin >> startupChoice;
		if (startupChoice == "A" || startupChoice == "a")
		{
			MagusClient<Type> demo;	// wrong type
			if (demo.Construct(1280, 720, 1, 1))
				demo.Start();
			break;
		}		
		else if (startupChoice == "DM" || startupChoice == "dm")
		{
			MagusServer<Type> demo;	// wrong type
			if (demo.Construct(1280, 720, 1, 1))
				demo.Start();
			break;
		}		
		else
		{
			std::cout << "Can not recognies choice, please choose again: [A/DM]" << std::endl;
		}
	}
	

	return 0;
}