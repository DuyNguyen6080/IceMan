#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

void StudentWorld::Ice_init()
{
		int tunel_X_lower_bound = 30;
	int tunel_X_upper_bound = 33;
	int tunel_Y_lower_bound = 4;
	int tunel_Y_upper_bound = 59;



	for (int col = 0; col < w; col++) {
		for (int row = 0; row < h; row++) {

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

void StudentWorld::delete_Ice_field(Ice* someIce[64][60])
{
	for (int col = 0; col < w; col++) {
				for (int row = 0; row < h; row++) {
					std::cout << "deleting I [" << col << "][" << row << "]" << std::endl;
					if (I[col][row] != nullptr) delete I[col][row];
				}
			}
}
