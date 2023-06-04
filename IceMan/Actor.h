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
	bool Active;
public:
	Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth);
	virtual ~Actor() {}
	void setX(int X) { posX = X; }
	void setY(int Y) { posY = Y; }
	bool isAlive();
	bool setState(bool life);
	virtual void doSomething() = 0;
};

//////////////////////////////////////////////////   ACTIVATINGOBJECT     //////////////////////////////////////////////////////////////
class ActivatingObject : public Actor {
private:
	StudentWorld* SW;
	bool temp_state;
public:
	ActivatingObject(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* point);
	virtual ~ActivatingObject() {}
	virtual void doSomething() {}
	bool isTemp();
	bool setTemp(bool temp);
};

//////////////////////////////////////////////////////    PERSON     //////////////////////////////////////////////////////////////////

class Person :public Actor {
private:
	int health;
public:
	Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth);
	virtual ~Person() {}

	int getHealth() { return health; }
	void setHealth(int hp) { health = hp; }


	virtual void doSomething() = 0;

};

////////////////////////////////////////////////////////    ICE     ////////////////////////////////////////////////////////////////
class Ice : public Actor {
public:
	Ice(int X, int Y);
	virtual void doSomething() {}
	virtual ~Ice() {}
};

///////////////////////////////////////////////////////    PROTESTOR     /////////////////////////////////////////////////////////////////
class Protestor : public Person {
private:
	bool leaving;
public:
	Protestor(bool leaving, int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth);
	virtual void doSomething() {}
	virtual ~Protestor() {}
};

////////////////////////////////////////////////////////    REGULAR PROTESTOR     ////////////////////////////////////////////////////////////////
class RegularProtestor : public Protestor {
private:

public:
	RegularProtestor(int X, int Y);
	virtual void doSomething() {}
	virtual ~RegularProtestor() {}
};

//////////////////////////////////////////////////////////    HARDCORE PROTESTOR     //////////////////////////////////////////////////////////////
class HardcoreProtestor : public Protestor {
private:

public:
	HardcoreProtestor(int X, int Y);
	virtual void doSomething() {}
	virtual ~HardcoreProtestor() {}
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

///////////////////////////////////////////////////////////    SONAR     //////////////////////////////////////////////////////////////
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
};

#endif // ACTOR_H_