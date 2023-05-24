#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
/////////////////////////////////////////////////    ACTOR     ///////////////////////////////////////////////////////////////////////
class Actor :public GraphObject {
private:
	int posX;
	int posY;
	bool Active;
public:
	Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth);
	virtual ~Actor() {}
	void setX(int X) { posX = X ; }
	void setY(int Y) { posY = Y; }
	bool isAlive();
	
	virtual void doSomething() =0;
};
//////////////////////////////////////////////////////////   GOODIES     //////////////////////////////////////////////////////////////
class Goodie : public Actor {
private:
	
public:
	Goodie(int ID, int X, int Y, Direction direct, float size, unsigned int depth);
	virtual ~Goodie() {}

	virtual void doSomething() {}
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
private:

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
class Boulder : public Goodie {
public:
	Boulder(int X, int Y);
	virtual void doSomething() {}
	virtual ~Boulder() {}
};
//////////////////////////////////////////////////////////    OIL     //////////////////////////////////////////////////////////////
class Oil : public Goodie {
public:
	Oil(int X, int Y);
	virtual void doSomething() {}
	virtual ~Oil() {}
};
//////////////////////////////////////////////////////////    GOLD     //////////////////////////////////////////////////////////////
class Gold : public Goodie {
public:
	Gold(int X, int Y);
	virtual void doSomething() {}
	virtual ~Gold() {}
};

//////////////////////////////////////////////////////////    SONAR     //////////////////////////////////////////////////////////////
class Sonar : public Goodie {
public:
	Sonar(int X, int Y);
	virtual void doSomething() {}
	virtual ~Sonar() {}
};

//////////////////////////////////////////////////////////    WATER POOL     //////////////////////////////////////////////////////////////
class Water : public Goodie {
public:
	Water(int X, int Y);
	virtual void doSomething() {}
	virtual ~Water() {}
};

//////////////////////////////////////////////////////////    ICE MAN     //////////////////////////////////////////////////////////////
class IceMan : public Person {
private:
	int Squirt;
	int Sonar;
	int Gold;
	StudentWorld* SW;
	void move();
	void Digging();
	bool isOverlap();

public:
	IceMan(int X, int Y, StudentWorld* p);
	virtual void doSomething();
	virtual ~IceMan() {}
};

#endif // ACTOR_H_
