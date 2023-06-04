#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <vector>
#include "Actor.h"

class Actor;
class Ice;

class StudentWorld : public GameWorld {
public:
	StudentWorld(std::string assetDir);
	~StudentWorld();
	int get_w_Ice() { return w_Ice; }
	int get_h_Ice() { return h_Ice; }

	void de_allocate();
	void delete_Ice_square(int X, int Y);
	void Hurt_Iceman(int howmuch);
	void make_Squirt(int X, int Y, GraphObject::Direction D);

	int getW() const;
	int getH() const;

	double how_Far_From_IceMan(int x, int y);
	double how_Far_From_Protestor(int x, int y);
	int set_Player_NewX(int X);
	int set_Player_NewY(int y);
	int set_Protest_NewX(int X);
	int set_Protest_NewY(int y);
	int decrease_Barrels();
	void increase_Score(int score);
	
	bool is_Iceman_here(int X, int Y);
	bool isIce(int X, int Y);
	bool is_Boulder_here(int X, int Y) { return false; }
	void delete_boulder_Ice(int x, int y);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
private:
	int current_level_number;
	int w_Game;
	int h_Game;
	int w_Ice;
	int h_Ice;
	int X_Player;
	int Y_Player;
	int X_Protest;
	int Y_Protest;
	int num_Oil;
	Ice* I[64][60];
	std::vector<Actor*> All_Actor;
	void Ice_init();
	void delete_Ice_field(Ice* someIce[64][60]);
};

#endif // STUDENTWORLD_H_