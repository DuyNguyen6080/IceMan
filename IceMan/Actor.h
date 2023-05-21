#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
/////////////////////////////////////////////////    ACTOR     ///////////////////////////////////////////////////////////////////////
class Actor :public GraphObject {
protected:
	int posX;
	int posY;
	bool Active;
public:
	Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
		posX(X), posY(Y), Active(true), GraphObject(ID, X, Y, direct, size, depth) {
		this->setVisible(true);
	}
	//virtual void doSomething() = 0;
	virtual void doSomething() {}
	virtual ~Actor() {}
};
//////////////////////////////////////////////////////////   GOODIES     //////////////////////////////////////////////////////////////
class Goodie : public Actor {
private:
	
public:
	Goodie(int ID, int X, int Y, Direction direct, float size, unsigned int depth)
		: Actor(ID, X, Y, direct, size, depth) {}
	virtual void doSomething() {}
	virtual ~Goodie() {}
};
//////////////////////////////////////////////////////    PERSON     //////////////////////////////////////////////////////////////////

class Person :public Actor {
private:
	int health;
public:
	Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) : health(hp)
		, Actor(ID, X, Y, direct, size, depth) {}
	//virtual void doSomething() = 0;
	int getHealth() { return health; }
	virtual void doSomething() {}
	virtual ~Person() {}

};
////////////////////////////////////////////////////////    ICE     ////////////////////////////////////////////////////////////////
class Ice : public Actor {
private:

public:
	Ice(int X, int Y) : Actor(IID_ICE, X, Y, right, 0.25, 3) {}
	virtual void doSomething() {}
	virtual ~Ice() {}
};

///////////////////////////////////////////////////////    PROTESTOR     /////////////////////////////////////////////////////////////////
class Protestor : public Person {
private:
	bool leaving;
public:
	Protestor(bool leaving, int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
		Person(hp, ID, X, Y, direct, size, depth) {}
	virtual void doSomething() {}
	virtual ~Protestor() {}
};
////////////////////////////////////////////////////////    REGULAR PROTESTOR     ////////////////////////////////////////////////////////////////
class RegularProtestor : public Protestor {
private:
	
public:
	RegularProtestor(int X, int Y) :  Protestor(false, 100, IID_PROTESTER, X, Y, left, 1, 0) {}
	virtual void doSomething() {}
	virtual ~RegularProtestor() {}
};
//////////////////////////////////////////////////////////    HARDCORE PROTESTOR     //////////////////////////////////////////////////////////////
class HardcoreProtestor : public Protestor {
private:
	
public:
	HardcoreProtestor(int X, int Y) :  Protestor(false, 100, IID_HARD_CORE_PROTESTER, X, Y, left, 1, 0) {}
	virtual void doSomething() {}
	virtual ~HardcoreProtestor() {}
};
//////////////////////////////////////////////////////////    BOULDER     //////////////////////////////////////////////////////////////
class Boulder : public Goodie {
public:
	Boulder(int X, int Y) : Goodie(IID_BOULDER, X, Y, down, 1, 1) {}
	virtual void doSomething() {}
	virtual ~Boulder() {}
};
//////////////////////////////////////////////////////////    OIL     //////////////////////////////////////////////////////////////
class Oil : public Goodie {
public:
	Oil(int X, int Y) : Goodie(IID_BARREL, X, Y, right, 1, 2) {
		this->setVisible(false); //fix this
	}
	virtual void doSomething() {}
	virtual ~Oil() {}
};
//////////////////////////////////////////////////////////    GOLD     //////////////////////////////////////////////////////////////
class Gold : public Goodie {
public:
	Gold(int X, int Y) : Goodie(IID_GOLD, X, Y, right, 1, 2) {
		this->setVisible(true); //fix this
	}
	virtual void doSomething() {}
	virtual ~Gold() {}
};

//////////////////////////////////////////////////////////    SONAR     //////////////////////////////////////////////////////////////
class Sonar : public Goodie {
public:
	Sonar(int X, int Y) : Goodie(IID_SONAR, X, Y, right, 1, 2) {
		
	}
	virtual void doSomething() {}
	virtual ~Sonar() {}
};

//////////////////////////////////////////////////////////    WATER POOL     //////////////////////////////////////////////////////////////
class Water : public Goodie {
public:
	Water(int X, int Y) : Goodie(IID_WATER_POOL, X, Y, right, 1, 2) {
		
	}
	virtual void doSomething() {}
	virtual ~Water() {}
};

//////////////////////////////////////////////////////////    ICE MAN     //////////////////////////////////////////////////////////////
class IceMan : public Person {
public:
	IceMan(int X, int Y) : Person(10, IID_PLAYER, X,Y, right , 1  , 0 ) {

	}
	virtual void doSomething() {}
	virtual ~IceMan() {}
};

#endif // ACTOR_H_
