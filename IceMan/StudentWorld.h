#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init()
	{
		Ice_init();
		All_Actor.push_back(new IceMan(30, 60));
		All_Actor.push_back(new RegularProtestor(60,60));
		All_Actor.push_back(new HardcoreProtestor(57, 60));
		All_Actor.push_back(new Boulder(0, 60));
		All_Actor.push_back(new Oil(4, 60));
		All_Actor[4]->setVisible(true);
		All_Actor.push_back(new Gold(8, 60));
		All_Actor.push_back(new Water(12, 60));
		All_Actor.push_back(new Sonar(16, 60));
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
		int k;


		if (getKey(k)) {
			if (k == KEY_PRESS_ESCAPE) {
				return GWSTATUS_PLAYER_DIED;
			}
			else return GWSTATUS_CONTINUE_GAME;
		}
		else return  GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
		delete_Ice_field(I);
	}

private:
	const int w = 64;
	const int h = 60;
	Ice* I[64][60];
	std::vector<Actor*> All_Actor;
	void Ice_init();
	void delete_Ice_field(Ice* someIce[64][60]);
};

#endif // STUDENTWORLD_H_
