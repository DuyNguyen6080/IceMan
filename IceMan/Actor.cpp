#include "Actor.h"
#include "StudentWorld.h"

/////////////////////////////////////////////////    ACTOR  FUNCTIONS     ////////////////////////////////////////////////////////////
Actor::Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
	posX(X), posY(Y), Active(true), GraphObject(ID, X, Y, direct, size, depth) {
	this->setVisible(true);
}

bool Actor::isAlive() {
	return Active;
}

bool Actor::setState(bool life) {
	return Active = life;
}

///////////////////////////////////////////////// ACTIVATINGOBJECT FUNCTION //////////////////////////////////////////////////////////
ActivatingObject::ActivatingObject(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* point)
	: temp_state(false), SW(point), Actor(ID, X, Y, direct, size, depth) {}

bool ActivatingObject::isTemp() {
	return temp_state;
}

bool ActivatingObject::setTemp(bool temp) {
	return temp_state = temp;
}

/////////////////////////////////////////////////    PERSON  FUNCTION     ////////////////////////////////////////////////////////////
Person::Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) : health(hp)
, Actor(ID, X, Y, direct, size, depth) {}

/////////////////////////////////////////////////           ICE           ////////////////////////////////////////////////////////////
Ice::Ice(int X, int Y) : Actor(IID_ICE, X, Y, right, 0.25, 3) {}

/////////////////////////////////////////////////    ICE MAN  FUNCTIONS   ////////////////////////////////////////////////////////////
void IceMan::move() {
	int upper_Y_limit = SW->get_h_Ice();
	int lower_Y_limit = 0;
	int upper_X_limit = SW->get_w_Ice() - 4;
	int lower_X_limit = 0;
	int k;

	SW->getKey(k);
	switch (k) {
	case KEY_PRESS_DOWN:
		if (getDirection() != down) setDirection(down);
		else {
			if (getY() > lower_Y_limit) {
				setY(getY() - 1);
				moveTo(getX(), getY() - 1);
				SW->set_Player_NewX(getX());
				SW->set_Player_NewY(getY() - 1);
			}
		}
		break;
	case KEY_PRESS_LEFT:
		if (getDirection() != left) setDirection(left);
		else {
			if (getX() > lower_X_limit) {
				setX(getX() - 1);
				moveTo(getX() - 1, getY());
				SW->set_Player_NewX(getX() - 1);
				SW->set_Player_NewY(getY());
			}
		}
		break;
	case KEY_PRESS_UP:
		if (getDirection() != up) setDirection(up);
		else {
			if (getY() < upper_Y_limit) {
				setY(getY() + 1);
				moveTo(getX(), getY() + 1);
				SW->set_Player_NewX(getX());
				SW->set_Player_NewY(getY() + 1);
			}
		}
		break;
	case KEY_PRESS_RIGHT:
		if (getDirection() != right) setDirection(right);
		else {
			if (getX() < upper_X_limit) {
				setX(getX() + 1);
				moveTo(getX() + 1, getY());
				SW->set_Player_NewX(getX() + 1);
				SW->set_Player_NewY(getY());
			}
		}
		break;
	case KEY_PRESS_SPACE:
		if (Squirt > 0) {
			Squirt--;
			SW->playSound(SOUND_PLAYER_SQUIRT);
			CreateSquirt();
		}
		break;
	case KEY_PRESS_ESCAPE:
		
		break;
	case KEY_PRESS_TAB:
		if (Gold >= 1) {
			Gold--;
		}
		break;
	default:
		break;
	}
}

void IceMan::Digging() {
	for (int i = getX(); i < getX() + 4; i++) {
		for (int j = getY(); j < getY() + 4 && j < SW->get_h_Ice(); j++) {
			if (isOverlap()) {
				SW->playSound(SOUND_DIG);
			}
			//std::cout << i << " " << j << "\n";
			SW->delete_Ice_square(i, j);
		}
	}
}

IceMan::IceMan(int X, int Y, StudentWorld* p) : SW(p), Person(10, IID_PLAYER, X, Y, right, 1, 0) {
	Squirt = 5;
	Sonar = 1;
	Gold = 0;
}

bool IceMan::isOverlap() {
	for (int i = getX(); i < getX() + 4; i++) {
		for (int j = getY(); j < getY() + 4; j++) {
			if (SW->isIce(i, j)) return true;
		}
	}
	return false;
}

void IceMan::CreateSquirt() {
	switch (getDirection()) {
	case up:
		SW->make_Squirt(getX(), getY() + 4, up);
		break;
	case down:
		SW->make_Squirt(getX(), getY() - 4, down);
		break;
	case left:
		SW->make_Squirt(getX() - 4, getY(), left);
		break;
	case right:
		SW->make_Squirt(getX() + 4, getY(), right);
		break;
	default:
		break;
	}
}

void IceMan::doSomething() {
	if (isAlive()) {
		move();
		Digging();
	}
}

////////////////////////////////////////////////////    BOULDER FUNCTION    //////////////////////////////////////////////////////////
Boulder::Boulder(int X, int Y, StudentWorld* p) : SW(p), Actor(IID_BOULDER, X, Y, down, 1, 1) {
	Stable = true;
	Waiting = true;
	Falling = false;
}

void Boulder::doSomething() {
	//std::cout << "Hello\n";
	if (isAlive()) {
		Check_For_Falling();
		if (Waiting == false)
			Fall();
	}
	else
		return;
}

void Boulder::Check_For_Falling() {
	if (Stable == true) {
		if (!(SW->isIce(getX(), getY() - 1)) && !(SW->isIce(getX() + 1, getY() - 1))
			&& !(SW->isIce(getX() + 2, getY() - 1)) && !(SW->isIce(getX() + 3, getY() - 1))) {
			Stable = false;
		}
		else
			Stable = true;
	}
	else {
		//std::cout << "No Ice below\n";
		if (Waiting == true) {
			SW->playSound(SOUND_FALLING_ROCK);
			Waiting = false;
		}
	}
}

void Boulder::Fall() {
	if (!(SW->isIce(getX(), getY() - 1)) && (getY() - 1) >= 0) {
		setY(getY() - 1);
		moveTo(getX(), getY() - 1);
	}
	else
		setState(false);
}

/////////////////////////////////////////////////      OIL  FUNCTION      ////////////////////////////////////////////////////////////
Oil::Oil(int X, int Y, StudentWorld* p) : SW(p), ActivatingObject(IID_BARREL, X, Y, right, 1, 2, p) {
	this->setVisible(false);
}

void Oil::doSomething() {
	if (isAlive()) {
		if (SW->how_Far_From_IceMan(getX(), getY()) <= 4.0) {
			this->setVisible(true);
			return;
		}
		else if (SW->how_Far_From_IceMan(getX(), getY()) <= 3.0) {
			setState(false);
			SW->playSound(SOUND_FOUND_OIL);
			SW->decrease_Barrels();
		}
	}
	else
		return;
}

////////////////////////////////////////////////////      GOLD FUNCTION        ///////////////////////////////////////////////////////
Gold::Gold(int X, int Y, StudentWorld* p) : SW(p), 
	IcePick(true), ActivatingObject(IID_GOLD, X, Y, right, 1, 2, p) {
	this->setVisible(false);
}

Gold::Gold(int IceX, int IceY, StudentWorld* p, bool Temp) : SW(p), 
	IcePick(false), Temp(Temp), ActivatingObject(IID_GOLD, IceX, IceY, right, 1, 2, p) {
	this->setVisible(true);
}

void Gold::doSomething() {
	if (isAlive()) {
		if (SW->how_Far_From_IceMan(getX(), getY()) <= 4) { // Reveal To Iceman
			this->setVisible(true);
			return;
		}
		else if (SW->how_Far_From_IceMan(getX(), getY()) <= 3 && IcePick == true) { // Iceman pick up
			//setState(false);
			SW->playSound(SOUND_GOT_GOODIE);
			return;
		}
		else if (SW->how_Far_From_Protestor(getX(), getY()) <= 3 && IcePick == false) { // Protestor pick up
			//setState(false);
			SW->playSound(SOUND_GOT_GOODIE);
			return;
		}
		else if (Temp = true) { // Remove self
			return;
		}
	}
	else return;
}

////////////////////////////////////////////////////      SQUIRT FUNCTION      ///////////////////////////////////////////////////////
Squirt::Squirt(int X, int Y, StudentWorld* p, Direction D)
	: SW(p), Actor(IID_WATER_SPURT, X, Y, D, 1.0, 1) {
	this->setVisible(true);
	move_Dis = 0;
}

void Squirt::doSomething() {
	if (SW->how_Far_From_Protestor(getX(), getY()) <= 3.0) { // Damage protestor function
		setState(false);
	}
	else if (move_Dis == 4) {
		setState(false);
	}
	else {
		can_Move();
	}
}

void Squirt::can_Move() {
	switch (getDirection()) {
	case up:
		if (!(SW->isIce(getX(), getY() + 1))) {
			setY(getY() + 1);
			moveTo(getX(), getY() + 1);
			move_Dis++;
		}
		else
			setState(false);
		break;
	case down:
		if (!(SW->isIce(getX(), getY() - 1))) {
			setY(getY() - 1);
			moveTo(getX(), getY() - 1);
			move_Dis++;
		}
		else
			setState(false);
		break;
	case left:
		if (!(SW->isIce(getX() - 1, getY()))) {
			setY(getX() - 1);
			moveTo(getX() - 1, getY());
			move_Dis++;
		}
		else
			setState(false);
		break;
	case right:
		if (!(SW->isIce(getX() + 1, getY()))) {
			setY(getX() + 1);
			moveTo(getX() + 1, getY());
			move_Dis++;
		}
		else
			setState(false);
		break;
	default:
		break;
	}	
}

/////////////////////////////////////////////////    SONAR   FUNCTION     ////////////////////////////////////////////////////////////
Sonar::Sonar(int X, int Y, StudentWorld* p) : ActivatingObject(IID_SONAR, X, Y, right, 1, 2, p) {

}

/////////////////////////////////////////////////    WATER   FUNCTION     ////////////////////////////////////////////////////////////
Water::Water(int X, int Y, StudentWorld* p) : SW(p),
	ActivatingObject(IID_WATER_POOL, X, Y, right, 1, 2, p) {
	this->setVisible(true);
}

void Water::doSomething() {
	if (isAlive()) {
		if (SW->how_Far_From_IceMan(getX(), getY()) <= 3.0) {
			setState(false);
			SW->playSound(SOUND_GOT_GOODIE);
		}
	}
	else
		return;
}

////////////////////////////////////////////////////    PROTESTER FUNCTION     ///////////////////////////////////////////////////////
Protestor::Protestor(bool leaving, int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) :
	Person(hp, ID, X, Y, direct, size, depth) {}

RegularProtestor::RegularProtestor(int X, int Y) : Protestor(false, 100, IID_PROTESTER, X, Y, left, 1, 0) {}

HardcoreProtestor::HardcoreProtestor(int X, int Y) : Protestor(false, 100, IID_HARD_CORE_PROTESTER, X, Y, left, 1, 0) {}
