#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include "Actor.h"


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class Ice;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir);
	~StudentWorld();
	int get_w_Ice() { return w_Ice; }
	int get_h_Ice() { return h_Ice; }
	void de_allocate();
	bool isIce(int X, int Y);
	void delete_Ice_square(int X, int Y);
	virtual int init();
	virtual int move();
	virtual void cleanUp();

private:
	
	int w_Ice;
	int h_Ice;
	int X_Player;
	int Y_Player;
	Ice* I[64][60];
	std::vector<Actor*> All_Actor;
	void Ice_init();
	void delete_Ice_field(Ice* someIce[64][60]);
	
};

#endif // STUDENTWORLD_H_
