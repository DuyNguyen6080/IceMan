#include "Actor.h"
#include "StudentWorld.h"


// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
/////////////////////////////////////////////////    ACTOR     ///////////////////////////////////////////////////////////////////////
Actor::Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
	posX(X), posY(Y), Active(true), GraphObject(ID, X, Y, direct, size, depth) {
	this->setVisible(true);
}

bool Actor::isAlive()
{
	return Active;
}

Goodie::Goodie(int ID, int X, int Y, Direction direct, float size, unsigned int depth)
	: Actor(ID, X, Y, direct, size, depth) {}

Person::Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) : health(hp)
, Actor(ID, X, Y, direct, size, depth) {}

Ice::Ice(int X, int Y) : Actor(IID_ICE, X, Y, right, 0.25, 3) {}

Protestor::Protestor(bool leaving, int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
	Person(hp, ID, X, Y, direct, size, depth) {}

RegularProtestor::RegularProtestor(int X, int Y) : Protestor(false, 100, IID_PROTESTER, X, Y, left, 1, 0) {}

HardcoreProtestor::HardcoreProtestor(int X, int Y) : Protestor(false, 100, IID_HARD_CORE_PROTESTER, X, Y, left, 1, 0) {}

Boulder::Boulder(int X, int Y) : Goodie(IID_BOULDER, X, Y, down, 1, 1) {}

Oil::Oil(int X, int Y) : Goodie(IID_BARREL, X, Y, right, 1, 2) {
	this->setVisible(false); //fix this
}

Gold::Gold(int X, int Y) : Goodie(IID_GOLD, X, Y, right, 1, 2) {
	this->setVisible(true); //fix this
}

Sonar::Sonar(int X, int Y) : Goodie(IID_SONAR, X, Y, right, 1, 2) {

}

Water::Water(int X, int Y) : Goodie(IID_WATER_POOL, X, Y, right, 1, 2) {

}

void IceMan::move()
{
	int upper_Y_limit = SW->get_h_Ice();
	int lower_Y_limit = 0;
	int upper_X_limit = SW->get_w_Ice()-4;
	int lower_X_limit = 0;
	int k;

		SW->getKey(k);
		switch (k) {
		case KEY_PRESS_DOWN:
			if(getDirection() != down) setDirection(down);
			else {
				if (getY() > lower_Y_limit) {
					setY(getY() - 1);
					moveTo(getX(), getY() - 1);
				}
			}
			break;
		case KEY_PRESS_LEFT:
			if (getDirection() != left) setDirection(left);
			else {
				if (getX() > lower_X_limit) {
					setX(getX() - 1);
					moveTo(getX() - 1, getY());
				}
			}
			break;
		case KEY_PRESS_UP:
			if (getDirection() != up) setDirection(up);
			else {
				if (getY() < upper_Y_limit) {
					setY(getY() + 1);
					moveTo(getX(), getY() + 1);
				}
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getDirection() != right) setDirection(right); 
			else {
				if (getX() < upper_X_limit) {
					setX(getX() + 1);
					moveTo(getX() + 1, getY());
				}
			}
			break;

		}	
}

void IceMan::Digging()
{
	
	for (int i = getX(); i < getX() + 4; i++) {
		for (int j = getY(); j < getY() + 4 && j < SW->get_h_Ice(); j++) {
			
			
				if (isOverlap()) {
					SW->playSound(SOUND_DIG);
				}
				std::cout << i << " " << j << "\n";
				SW->delete_Ice_square(i, j);
			
		}
	}

	

	
}


IceMan::IceMan(int X, int Y, StudentWorld* p) : SW(p), Person(10, IID_PLAYER, X, Y, right, 1, 0) {
	setHealth(10);
	Squirt = 5;
	Sonar = 1;
	Gold = 0;
}

bool IceMan::isOverlap()
{
	for (int i = getX(); i < getX() + 4; i++) {
		for (int j = getY(); j < getY() + 4; j++) {
			if (SW->isIce(i,j)) return true;
		}
	}
	return false;
}

void IceMan::doSomething() {
	
	if (isAlive()) {
		move();
		Digging();
	}
	
	
}
