#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
class StudentWorld;

/////////////////////////////////////////////////    ACTOR     ///////////////////////////////////////////////////////////////////////
class Actor :public GraphObject {
private:
	int posX;
	int posY;
	bool Alive;
	StudentWorld* SW;
public:
	Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p);
	virtual ~Actor() {}
	void setX(int X) { posX = X; }
	void setY(int Y) { posY = Y; }
	virtual void setHealth(int howmuch) {}
	virtual void dec_health(int howmuch) {}
	//int getX() { return posX; }
	//int getY() { return posY; }
	virtual void set_Leaving(bool isleaving) {}
	bool isAlive();
	void setAlive(bool isAlive);
	StudentWorld* getWorld() const ;
	void setWorld(StudentWorld* p);

	virtual void doSomething() = 0;
};

//////////////////////////////////////////////////////    ACTIVATING OBJECT     //////////////////////////////////////////////////////////////////
class ActivatingObject : public Actor {
private:
	StudentWorld* SW;
	bool temp_state;
public:
	ActivatingObject(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p);
	virtual ~ActivatingObject() {}
	virtual void doSomething() = 0;
	bool isTemp();
	bool setTemp(bool temp);
  bool isAlive();
	bool setState(bool life)
};

//////////////////////////////////////////////////////    PERSON     //////////////////////////////////////////////////////////////////

class Person :public Actor {
private:
	int health;
public:
	Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p);
	virtual ~Person() {}

	int getHealth() const { return health; }
	int return_step_to_endPoint(int X, int Y);
	void setHealth(int hp);
	virtual void set_Leaving(bool isleaving) {}
	virtual void dec_health(int howmuch) {};
	virtual void doSomething() = 0;
	
	bool is_current_direction_blocked_by_Boulder(Direction direction);
	bool check_left(int endX);
	bool check_right(int endX);
	bool check_up(int endY);
	bool check_down(int endY);
};

////////////////////////////////////////////////////////    ICE     ////////////////////////////////////////////////////////////////
class Ice : public Actor {
public:
	Ice(int X, int Y, StudentWorld* p);
	virtual void doSomething() {}
	virtual ~Ice() {}
};

///////////////////////////////////////////////////////    PROTESTOR     /////////////////////////////////////////////////////////////////
class Protestor : public Person {
private:
	bool leaving;
	int numSquaresToMoveInCurrentDirection;
	int ticksToWaitBetweenMoves;
	int non_resting_tick;
	int perpendicular_turn_tick;
	
public:
	Protestor(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p);
	virtual ~Protestor() {}
	virtual void move(Direction direction);
	
	virtual void doSomething() {}
	virtual void dec_health(int howmuch);
	virtual void set_Leaving(bool isLeaving) { leaving = isLeaving; }
	
	int getTicks_remain() const { return ticksToWaitBetweenMoves; }
	int getNumSquare_ToMove() const { return numSquaresToMoveInCurrentDirection; }
	int get_nonresting() { return non_resting_tick; }
	int get_NumSquare_toMove() { return numSquaresToMoveInCurrentDirection; }
	int get_perpendicular_turn_tick() { return perpendicular_turn_tick; }

	
	void setTick(int tick) { ticksToWaitBetweenMoves = tick; }
	void reset_tick();
	void set_perpendicular_turn_tick(int howmuch) { perpendicular_turn_tick = howmuch; }
	void set_nonresting_tick(int tick) { non_resting_tick = tick; }
	void reset_nonresting_tick() { non_resting_tick = 0; }
	void set_NumSquare_toMove(int howmuch) { numSquaresToMoveInCurrentDirection = howmuch; }
	void change_direction();
	void move_leaving();

	void reset_numSquare_toMove();

	bool is_current_direction_blocked_by_Boulder_or_Ice(Direction direction);
	bool is_sitting_interstion(Direction &direction);
	bool looking_for_Iceman(Direction &direction);
	bool isLeaving();
	bool is_Iceman_around(Direction& direct);
	bool is_Ice_or_Boulder_around_ahead();
	
	void shout(Direction dir);

};

////////////////////////////////////////////////////////    REGULAR PROTESTOR     ////////////////////////////////////////////////////////////////
class RegularProtestor : public Protestor {
private:

public:
	RegularProtestor(int X, int Y, StudentWorld* p);
	virtual ~RegularProtestor() {};
	//virtual void move();
	virtual void doSomething();;
	
};

//////////////////////////////////////////////////////////    HARDCORE PROTESTOR     //////////////////////////////////////////////////////////////
class HardcoreProtestor : public Protestor {
private:

public:
	HardcoreProtestor(int X, int Y, StudentWorld* p);
	virtual ~HardcoreProtestor() {}
	virtual void doSomething();
};

//////////////////////////////////////////////////////////    BOULDER     //////////////////////////////////////////////////////////////
class Boulder : public Actor {
public:
	Boulder(int X, int Y, StudentWorld* p);
	virtual void doSomething();
	void Check_For_Falling();
	void Fall();
	virtual ~Boulder() {}
private:
	StudentWorld* SW;
	bool Stable;
	bool Waiting;
	bool Falling;
};

///////////////////////////////////////////////////////////    OIL     //////////////////////////////////////////////////////////////
class Oil : public ActivatingObject {
public:
	Oil(int X, int Y, StudentWorld* p);
	virtual void doSomething();
	virtual ~Oil() {}
private:
	StudentWorld* SW;
};

///////////////////////////////////////////////////////////    GOLD     //////////////////////////////////////////////////////////////
class Gold : public ActivatingObject {
public:
	Gold(int X, int Y, StudentWorld* p);
	Gold(int IceX, int IceY, StudentWorld* p, bool Temp);
	virtual void doSomething();
	virtual ~Gold() {}
private:
	StudentWorld* SW;
	bool IcePick;
	bool Temp;
};

//////////////////////////////////////////////////////////    SONAR     //////////////////////////////////////////////////////////////
class Sonar : public ActivatingObject {
public:
	Sonar(int X, int Y, StudentWorld* p);
	virtual void doSomething() {}
	virtual ~Sonar() {}
private:
	StudentWorld* SW;
};

//////////////////////////////////////////////////////////    WATER POOL     //////////////////////////////////////////////////////////////
class Water : public ActivatingObject {
public:
	Water(int X, int Y, StudentWorld* p);
	virtual void doSomething();
	virtual ~Water() {}
private:
	StudentWorld* SW;
};

//////////////////////////////////////////////////////////    SQUIRT     //////////////////////////////////////////////////////////////
class Squirt : public Actor {
public:
	Squirt(int X, int Y, StudentWorld* p, Direction D);
	virtual void doSomething();
	~Squirt() {}
private:
	StudentWorld* SW;
	void can_Move();
	int move_Dis;
};

//////////////////////////////////////////////////////////    ICE MAN     //////////////////////////////////////////////////////////////
class IceMan : public Person {
private:
	int Squirt;
	int Sonar;
	int Gold;
	int Score;
	StudentWorld* SW;
	void move();
	void Digging();
	bool isOverlap();
	void CreateSquirt();
	void dec_health(int h);
public:
	IceMan(int X, int Y, StudentWorld* p);
	virtual void doSomething();
	virtual ~IceMan() {}
	virtual void dec_health(int howmuch);
};

#endif // ACTOR_H_