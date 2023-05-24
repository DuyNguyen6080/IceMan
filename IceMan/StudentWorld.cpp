#include "StudentWorld.h"
#include <string>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp



StudentWorld::StudentWorld(std::string assetDir)
	: GameWorld(assetDir)
{
	w_Ice = 64;
	h_Ice = 60;
	X_Player = 30;
	Y_Player = 60;
}

StudentWorld::~StudentWorld()
{
	de_allocate();
}

void StudentWorld::de_allocate()
{
	delete_Ice_field(I);
	for (auto i : All_Actor) {
		delete i;
		i = nullptr;
	}
}

bool StudentWorld::isIce(int X, int Y)
{
	if (X < w_Ice && Y < h_Ice) {
		if (I[X][Y] != nullptr) return true;
		else return false;
	}
	else return false;
}

void StudentWorld::delete_Ice_field(Ice* someIce[64][60])
{
	for (int col = 0; col < w_Ice; col++) {
		for (int row = 0; row < h_Ice; row++) {
			std::cout << "deleting I [" << col << "][" << row << "]" << std::endl;
			if (I[col][row] != nullptr) {
				delete I[col][row];
				I[col][row] = nullptr;
			}
		}
	}
}

void StudentWorld::delete_Ice_square(int X, int Y)
{
	std::cout << X << " " << Y << " \n";
	if (I[X][Y] != nullptr) {
		delete I[X][Y];
		I[X][Y] = nullptr;
	}
}

int StudentWorld::init()
{
	Ice_init();

	All_Actor.push_back(new IceMan(X_Player, Y_Player, this));
	All_Actor.push_back(new RegularProtestor(60, 60));
	All_Actor.push_back(new HardcoreProtestor(57, 60));
	All_Actor.push_back(new Boulder(0, 60));
	All_Actor.push_back(new Oil(4, 60));
	All_Actor[4]->setVisible(true);
	All_Actor.push_back(new Gold(8, 60));
	All_Actor.push_back(new Water(12, 60));
	All_Actor.push_back(new Sonar(16, 60));
	return GWSTATUS_CONTINUE_GAME;
}

inline int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	
	for (auto it : All_Actor) {
		if (it->isAlive()) {
			it->doSomething();
		}
		
		if (!All_Actor[0]->isAlive()) return GWSTATUS_PLAYER_DIED;
		else return GWSTATUS_CONTINUE_GAME;
		
	}
}

inline void StudentWorld::cleanUp()
{
	de_allocate();
}

void StudentWorld::Ice_init()
{
		int tunel_X_lower_bound = 30;
	int tunel_X_upper_bound = 33;
	int tunel_Y_lower_bound = 4;
	int tunel_Y_upper_bound = 59;



	for (int col = 0; col < w_Ice; col++) {
		for (int row = 0; row < h_Ice; row++) {

			bool isTunel = col >= tunel_X_lower_bound && col <= tunel_X_upper_bound
				&& row >= tunel_Y_lower_bound && row <= tunel_Y_upper_bound;

			if (!isTunel) {
				I[col][row] = new Ice(col, row);
			}
			else {
				I[col][row] = nullptr;
			}
		}
	}
}


