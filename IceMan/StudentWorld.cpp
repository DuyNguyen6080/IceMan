#include "StudentWorld.h"
#include <string>
#include <queue>
#include <iomanip>
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
	w_maze = 64;
	h_maze = 64;
	w_Game = 64;
	h_Game = 64;
	X_Player = 30;
	Y_Player = 60;
	init_maze();

}

StudentWorld::~StudentWorld()
{
	de_allocate();
}

void StudentWorld::de_allocate()
{
	delete_Ice_field(I);
	for (auto i : All_Actor) {
		for (auto it : i) {
			delete it;
			it = nullptr;
		}
		i.resize(0);
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

bool StudentWorld::is_Boulder_here(int X, int Y)
{
	/*if (All_Actor[3].empty())
	{
		cout << "vector of boulder is empty" << endl;
		return true;
	}*/
	for (int i = 0; i < All_Actor[3].size(); i++) {
		///for each actor do the code below
		for (int x = All_Actor[3][i]->getX(); x < All_Actor[3][i]->getX() + 4; x++) {
			for (int y = All_Actor[3][i]->getY(); y < All_Actor[3][i]->getY() + 4; y++) { 
				if (X == x && Y == y) return true;
			}
		}
	}
	return false;
}

void StudentWorld::delete_Ice_field(Ice* someIce[64][60])
{
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

void StudentWorld::delete_Ice_square(int X, int Y)
{
	//std::cout << X << " " << Y << " \n";
	if (I[X][Y] != nullptr) {
		delete I[X][Y];
		I[X][Y] = nullptr;
	}
}

void StudentWorld::Hurt_Iceman(int howmuch)
{
	All_Actor[0][0]->dec_health(howmuch);
}

void StudentWorld::make_Squirt(int X, int Y, GraphObject::Direction direction)
{
}

void StudentWorld::init_maze()
{
	
	for (int row = h_maze-1; row >= 0; row--) {
		for (int col = 0; col < w_maze; col++) {
			maze[col][row] = -1;
			//cout <<maze[col][row] << endl;
		}
	}
	
}

void StudentWorld::bfs_maze(int endPointX, int endPointY, int startPointX, int startPointY)
{
	init_maze();
	
	queue<pair<pair<int, int>, const int>> q;
	pair<pair<int, int>, int> location_and_step;
	location_and_step.first.first = startPointX;
	location_and_step.first.second = startPointY;
	location_and_step.second = 0;
	q.push(location_and_step);
	int i = 0;
	while (!q.empty()) {
		
		i++;
		if (i == 70) {
			i = 0;
			//print_maze(); cout << endl << endl << endl;
		}
		location_and_step = q.front();
		q.pop();
		
		int x = location_and_step.first.first;
		int y = location_and_step.first.second;
		

		if (x == endPointX && y == endPointY ) {
			while (!q.empty()) {
				location_and_step = q.front();
				q.pop();

				int x = location_and_step.first.first;
				int y = location_and_step.first.second;

				maze[x][y] = location_and_step.second;
			}
			cout << "found end point" << location_and_step.first.first << " " << location_and_step.first.second << endl;
			cout << "value path in the queue: " << location_and_step.second << endl;
			//maze[x - 1][y] = location_and_step.second - 1;
			//print_maze(); cout << endl << endl << endl;
			//maze[x][y - 1] = location_and_step.second - 1;
			return;
		}
		else {
			if (maze[location_and_step.first.first][location_and_step.first.second] > -1) {
			
				continue;
			}
			else {
				
				//cout << "=== -1" << endl;
				
				maze[x][y] = location_and_step.second;
				

				//check left
				if (maze[x-1][y] == -1 && x -1 >=0
					&& !is_Boulder_here(x - 1, y)
					&& !isIce(x - 1, y)) {
					pair<pair<int, int>, int> temp;
					temp.first.first = x - 1;
					temp.first.second = y;

					temp.second = location_and_step.second + 1;
					q.push(temp);
				}
				//check down
				if (maze[x ][y-1] == -1 && y -1 >= 0
					&& !is_Boulder_here(x, y - 1)
					&& !isIce(x, y - 1)) {
					pair<pair<int, int>, int> temp;
					temp.first.first = x;
					temp.first.second = y - 1;

					temp.second = location_and_step.second +1 ;
					q.push(temp);
				}
				//check right

				if (maze[x+1][y] == -1 && x+1 < w_maze 
					&& !is_Boulder_here(x + 1, y)
					&& !isIce(x + 1, y)) {

					pair<pair<int, int>, int> temp;
					temp.first.first = x + 1;
					temp.first.second = y;

					temp.second = location_and_step.second +1;
					q.push(temp);
				}
				//check up
				if (maze[x][y+1] == -1 && y + 1 < h_maze 
					&&  !is_Boulder_here(x, y + 1)
					&&  !isIce(x, y + 1)) {
					pair<pair<int, int>, int> temp;
					temp.first.first = x;
					temp.first.second = y + 1;

					temp.second = location_and_step.second +1;
					q.push(temp);
				}
				
				
				
			}
		}
		
	}
	
}

void StudentWorld::print_maze()
{
	
	for (int row = h_maze - 1; row >= 0; row--) {
		cout << setw(3) << row;
		for (int col = 0; col < w_maze; col++) {
			
			if(maze[col][row] == - 1) cout << setw(3) << ".";
			else 
			cout << setw(3) << maze[col][row];
		}
		cout << endl ;
	}
	cout << "   ";
	for (int row = 0; row < h_maze; row++) {
		cout << setw(3) << row;
	}
	cout << endl;
	cout << endl << endl << endl;
}

void StudentWorld::make_Protestor_to_Quit()
{
	for (int i = 0; i < All_Actor[1].size(); i++) {
		All_Actor[1][i]->dec_health(100);
	}
	
}

int StudentWorld::getW() const
{
	return w_Game;
}

int StudentWorld::getH() const
{
	return h_Game;
}

bool StudentWorld::is_Iceman_here(int X, int Y) 
{
	
	int Iceman_X = All_Actor[0][0]->getX();
	int Iceman_Y = All_Actor[0][0]->getY();

	for (int i = Iceman_X; i < Iceman_X + 4; i++) {
		for (int j = Iceman_Y; j < Iceman_Y + 4; j++) {
			if (X == i && Y == j) return true;
		}
	}
	return false;
}
///////////////////////////////////////////////////////    INIT   ///////////////////////////////////////////////////////
int StudentWorld::init()
{
	Ice_init();
	init_maze();
	num_tick_elapsed = 0;
	Probability_Of_Hardcore = max(90, int(getLevel() * 10 + 30));
	P = min(15, 2 + int(getLevel() * 1.5));
	T = max(25, 200 - int(getLevel()));
	srand(time(nullptr));
	int random_integer = rand() % 99 + 1;

	All_Actor[0].push_back(new IceMan(30, 60, this));
	All_Actor[1].push_back(new RegularProtestor(30, 4, this));
	/*if (random_integer > Probability_Of_Hardcore ) {
		All_Actor[1].push_back(new RegularProtestor(56, 60, this));
	}
	else {
		All_Actor[2].push_back(new HardcoreProtestor(60, 60, this));
	}*/
	//All_Actor[3].push_back(new Boulder(0, 60, this));
	//All_Actor[3].push_back(new Boulder(30, 40, this));
	All_Actor[5].push_back(new Oil(4, 60, this));
	All_Actor[5][0]->setVisible(true);
	All_Actor[6].push_back(new Gold(8, 60, this));
	All_Actor[7].push_back(new Sonar(16, 60, this));
	All_Actor[8].push_back(new Water(12, 60, this));
	
	

	
	
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	de_allocate();
}

bool StudentWorld::should_going_to(GraphObject::Direction direction, int curentX, int curentY)
{
	int self_value = maze[curentX][curentY];
	cout << "current value" << maze[curentX][curentY] << endl;
	switch (direction) {
	case GraphObject::up:
		cout << " up  value : " << maze[curentX][curentY + 1] << endl;
		if (maze[curentX][curentY] == -1) {
			if (maze[curentX][curentY + 1] == -1) return false;
			else return true;
		}
		else {
			if (maze[curentX][curentY + 1] < self_value && maze[curentX][curentY + 1] != -1) return true;
			else return false;
		}
		break;
	case GraphObject::down:
		cout << " down  value " << maze[curentX][curentY - 1] << endl;
		if (maze[curentX][curentY] == -1) {
			if (maze[curentX][curentY - 1] == -1) return false;
			else return true;
		}
		else {
			if (maze[curentX][curentY-1] < self_value && maze[curentX][curentY -1 ] != -1) return true;
			else return false;
		}
		break;
	case GraphObject::left:
		cout << " left  value " << maze[curentX - 1][curentY] << endl;
		if (maze[curentX][curentY] == -1) {
			if (maze[curentX - 1][curentY] == -1) return false;
			else return true;
		}
		else {
			if (maze[curentX-1][curentY] < self_value && maze[curentX-1][curentY] != -1) return true;
			else return false;
		}
		break;
	case GraphObject::right:
		cout << " right  value" << maze[curentX + 1][curentY] << endl;

		if (maze[curentX][curentY] == -1) {
			if (maze[curentX + 1][curentY] == -1) return false;
			else return true;
		}
		else {
			if (maze[curentX + 1][curentY] < self_value && maze[curentX+1][curentY] != -1) return true;
			else return false;
		}
		break;
	}
}



inline int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	//All_Actor[1]->doSomething();
	
	num_tick_elapsed++;
	int num_of_protestor = All_Actor[1].size() + All_Actor[2].size();

	if (num_tick_elapsed > T && num_of_protestor < P) {
		srand(time(nullptr));
		int random_integer = rand() % 99 + 1;
		/*if (random_integer > Probability_Of_Hardcore) {
			All_Actor[1].push_back(new RegularProtestor(56, 60, this));
		}
		else {
			All_Actor[2].push_back(new HardcoreProtestor(60, 60, this));
		}*/
	}
	for (auto it : All_Actor) {
		for(auto it1: it)
		if (it1->isAlive()) {
			
			it1->doSomething();
			if (!All_Actor[0][0]->isAlive()) {
				//de_allocate();
				return GWSTATUS_PLAYER_DIED; 
			}
		}

		if (!All_Actor[0][0]->isAlive()) return GWSTATUS_PLAYER_DIED;
		//else return GWSTATUS_CONTINUE_GAME;
        
	}
	//init_maze();
	//bfs_maze(30, 4, 60, 60);
	//print_maze();
    return  GWSTATUS_CONTINUE_GAME;
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
				I[col][row] = new Ice(col, row, this);
			}
			

			else {
				I[col][row] = nullptr;
			}
		}
	}
}

