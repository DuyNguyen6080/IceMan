#include "StudentWorld.h"
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir) {
	return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir)
	: GameWorld(assetDir) {
	current_level_number = 0;
	w_Ice = 64;
	h_Ice = 60;
	w_Game = 64;
	h_Game = 64;
	X_Player = 30;
	Y_Player = 60;
}

StudentWorld::~StudentWorld() {
	de_allocate();
}

void StudentWorld::de_allocate() {
	delete_Ice_field(I);
	for (auto i : All_Actor) {
		delete i;
		i = nullptr;
	}
}

bool StudentWorld::isIce(int X, int Y) {
	if (X < w_Ice && Y < h_Ice) {
		if (I[X][Y] != nullptr) return true;
		else return false;
	}
	else return false;
}

void StudentWorld::delete_Ice_field(Ice* someIce[64][60]) {
	for (int col = 0; col < w_Ice; col++) {
		for (int row = 0; row < h_Ice; row++) {
			//std::cout << "deleting I [" << col << "][" << row << "]" << std::endl;
			if (I[col][row] != nullptr) {
				delete I[col][row];
				I[col][row] = nullptr;
			}
		}
	}
}

void StudentWorld::delete_Ice_square(int X, int Y) {
	//std::cout << X << " " << Y << " \n";
	if (I[X][Y] != nullptr) {
		delete I[X][Y];
		I[X][Y] = nullptr;
	}
}

//void StudentWorld::Hurt_Iceman(int howmuch){
//	All_Actor[0]->dec_health(howmuch);
//}

void StudentWorld::delete_boulder_Ice(int x, int y) {
		for (int i = x; i < (x + 4); i++) {
			for (int j = y; j < (y + 4); j++) {
				if (I[i][j] != nullptr) {
					delete I[i][j];
					I[i][j] = nullptr;
				}
			}
		}
}

int StudentWorld::getW() const {
	return w_Game;
}

int StudentWorld::getH() const {
	return h_Game;
}

double StudentWorld::how_Far_From_IceMan(int x, int y) {
	return sqrt(pow((x - X_Player), 2) + pow((y - Y_Player), 2));
}

double StudentWorld::how_Far_From_Protestor(int x, int y) {
	return sqrt(pow((x - X_Protest), 2) + pow((y - Y_Protest), 2));
}

int StudentWorld::set_Player_NewX(int X) {
	return X_Player = X;
}

int StudentWorld::set_Player_NewY(int Y) {
	return Y_Player = Y;
}

int StudentWorld::set_Protest_NewX(int X) {
	return X_Protest = X;
}

int StudentWorld::set_Protest_NewY(int Y) {
	return Y_Protest = Y;
}

int StudentWorld::decrease_Barrels() {
	return num_Oil - 1;
}

void StudentWorld::increase_Score(int score) {

}

void StudentWorld::make_Squirt(int X, int Y, GraphObject::Direction D) {
	if ((X <= w_Ice) && (X >= 0) && (Y <= h_Ice) && (Y >= 0))
		All_Actor.push_back(new Squirt(X, Y, this, D));
	else return;
}

///////////////////////////////////////////////////////    INIT   ///////////////////////////////////////////////////////

int StudentWorld::init() {
	Ice_init();
	srand((unsigned int)time(0));
	
	int B = min(current_level_number / 2 + 2, 9);
	int G = max(5 - current_level_number / 2, 2);
	int L = min(2 + current_level_number, 21);

	All_Actor.push_back(new IceMan(X_Player, Y_Player, this));
	All_Actor.push_back(new RegularProtestor(60, 60));
	All_Actor.push_back(new HardcoreProtestor(57, 60));

	for (int i = 0; i < B; i++) {
		int Bx = (rand() % 60 + 1);
		int By = (rand() % 36 + 20 + 1);
		delete_boulder_Ice(Bx, By);
		All_Actor.push_back(new Boulder(Bx, By, this));
		num_Oil = i + 1;
		//std::cout << "Boulder created at " << Bx << " " << By << endl;
	}

	for (int i = 0; i < L; i++) {
		int Lx = (rand() % 60 + 1);
		int Ly = (rand() % 56 + 1);
		All_Actor.push_back(new Oil(Lx, Ly, this));
		//std::cout << "Oil Barrel created at " << Lx << " " << Ly << endl;
	}

	//All_Actor[4]->setVisible(true);
	for (int i = 0; i < G; i++) {
		int Gx = (rand() % 60 + 1);
		int Gy = (rand() % 56 + 1);
		All_Actor.push_back(new Gold(Gx, Gy, this));
		//std::cout << "Gold Nugget created at " << Gx << " " << Gy << endl;
	}

	All_Actor.push_back(new Water(12, 60, this));
	All_Actor.push_back(new Sonar(16, 60, this));
	return GWSTATUS_CONTINUE_GAME;
}

inline int StudentWorld::move() {
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	
	auto Act = [&](Actor* it) {
		if (it->isAlive()) {
			it->doSomething();
		}
	};

	for_each(All_Actor.begin(), All_Actor.end(), Act);
	/*for (auto it : All_Actor) {
	* 
		if (it->isAlive()) {
			it->doSomething();
		}

		if (!All_Actor[0]->isAlive()) return GWSTATUS_PLAYER_DIED;
		else return GWSTATUS_CONTINUE_GAME;

	}*/

	if (!All_Actor[0]->isAlive())
		return GWSTATUS_PLAYER_DIED;
	else
		return GWSTATUS_CONTINUE_GAME;
}

inline void StudentWorld::cleanUp() {
	de_allocate();
}

void StudentWorld::Ice_init() {
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

