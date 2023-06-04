#include "Actor.h"
#include "StudentWorld.h"
#include <queue>
using namespace std;

/////////////////////////////////////////////////           ICE           ////////////////////////////////////////////////////////////
Ice::Ice(int X, int Y, StudentWorld* p ) : Actor(IID_ICE, X, Y, right, 0.25, 3, p ) {}

/////////////////////////////////////////////////    ICE MAN  FUNCTIONS   ////////////////////////////////////////////////////////////
void IceMan::move() {
	int upper_Y_limit = getWorld()->get_h_Ice();
	int lower_Y_limit = 0;
	int upper_X_limit = getWorld()->get_w_Ice() - 4;
	int lower_X_limit = 0;
	int k;

	getWorld()->getKey(k);
	switch (k) {
	case KEY_PRESS_DOWN:
		if (getDirection() != down) setDirection(down);
		else {
			if (getY() > lower_Y_limit
				&& !is_current_direction_blocked_by_Boulder(down)) {
				setY(getY() - 1);
				moveTo(getX(), getY() - 1);
        getWorld()->set_Player_NewX(getX());
				getWorld()->set_Player_NewY(getY() - 1);
			}
		}
		break;
	case KEY_PRESS_LEFT:
		if (getDirection() != left) setDirection(left);
		else {
			if (getX() > lower_X_limit
				&& !is_current_direction_blocked_by_Boulder(left)) {
				setX(getX() - 1);
				moveTo(getX() - 1, getY());
        getWorld()->set_Player_NewX(getX() - 1);
				getWorld()->set_Player_NewY(getY());
				//cout << "ofcourse can move left" << endl;
			}
		}
		break;
	case KEY_PRESS_UP:
		if (getDirection() != up) setDirection(up);
		else {
			if (getY() < upper_Y_limit
				&& !is_current_direction_blocked_by_Boulder(up)) {
				setY(getY() + 1);
				moveTo(getX(), getY() + 1);
        getWorld()->set_Player_NewX(getX() + 1);
				getWorld()->set_Player_NewY(getY());
			}
		}
		break;
	case KEY_PRESS_RIGHT:
		if (getDirection() != right) setDirection(right);
		else {
			if (getX() < upper_X_limit
				&& !is_current_direction_blocked_by_Boulder(right)) {
				setX(getX() + 1);
				moveTo(getX() + 1, getY());
        getWorld()->set_Player_NewX(getX() + 1);
				getWorld()->set_Player_NewY(getY());
			}
		}
		break;
  case KEY_PRESS_SPACE:
		if (Squirt > 0) {
			Squirt--;
			getWorld()->playSound(SOUND_PLAYER_SQUIRT);
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
		for (int j = getY(); j < getY() + 4 && j < getWorld()->get_h_Ice(); j++) {
			if (isOverlap()) {
				getWorld()->playSound(SOUND_DIG);
			}
			//std::cout << i << " " << j << "\n";
			getWorld()->delete_Ice_square(i, j);
		}
	}
}

IceMan::IceMan(int X, int Y, StudentWorld* p) : Person(10, IID_PLAYER, X, Y, right, 1, 0, p), Squirt(5),Sonar(1), Gold(0) {
	setWorld(p);
	setHealth(10);
	Squirt = 5;
	Sonar = 1;
	Gold = 0;
}

bool IceMan::isOverlap() {
	for (int i = getX(); i < getX() + 4; i++) {
		for (int j = getY(); j < getY() + 4; j++) {
			if (getWorld()->isIce(i, j)) return true;
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

void IceMan::dec_health(int howmuch) {
	if (getHealth() - howmuch <= 0) setAlive(false);
	else {
		setHealth(getHealth() - howmuch);
	}
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
    
///////////////////////////////////////////////// ACTIVATINGOBJECT FUNCTION //////////////////////////////////////////////////////////
ActivatingObject::ActivatingObject(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p)
	: temp_state(false), SW(point), Actor(ID, X, Y, direct, size, depth, p) {}

bool ActivatingObject::isTemp() {
	return temp_state;
}

bool ActivatingObject::setTemp(bool temp) {
	return temp_state = temp;
}

/////////////////////////////////////////////////    ACTOR  FUNCTIONS     ////////////////////////////////////////////////////////////
Actor::Actor(int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p) : SW(p),
	posX(X), posY(Y), Alive(true), GraphObject(ID, X, Y, direct, size, depth) {
	this->setVisible(true);
}

bool Actor::isAlive() {
	return Alive;
}

void Actor::setAlive(bool isAlive) {
	Alive = isAlive;
}

StudentWorld* Actor::getWorld() const
{
	return SW;
}

void Actor::setWorld(StudentWorld* p) {
	SW = p;
}

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
  
Person::Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p) : health(hp)
, Actor(ID, X, Y, direct, size, depth, p) {}

void Person::setHealth(int hp) {
	if (hp <= 0) setAlive(false);
	else {
		health = hp;
	}
}

/////////////////////////////////////////////////    PERSON  FUNCTION     ////////////////////////////////////////////////////////////
Person::Person(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth) : health(hp)
, Actor(ID, X, Y, direct, size, depth) {}

bool Person::check_left(int endX) {
    StudentWorld* world = getWorld();
    for(int i = getY(); i < getY() +4; i++) {
        if(endX < 0 || world->isIce(endX, i) || world->is_Boulder_here(endX, i)) {
            //cout << "saw ice or boulder" << endl;
            return false;
        }
    }
    return true;
}

bool Person::check_right(int endX) {
    StudentWorld* world = getWorld();
    for(int i = getY(); i < getY() +4; i++) {
        if(endX > 63 || world->isIce(endX, i) || world->is_Boulder_here(endX, i)) {
            //cout << "saw ice or boulder" << endl;
            return false;
        }
    }
    return true;
}

bool Person::check_up(int endY) {
    StudentWorld* world = getWorld();
    for(int i = getX(); i < getX() +4; i++) {
        if(endY > 63 || world->isIce(i, endY) || world->is_Boulder_here(i, endY)) {
            //cout << "saw ice or boulder" << endl;
            return false;
        }
    }
    return true;
}

bool Person::check_down(int endY) {
    StudentWorld* world = getWorld();
    for(int i = getX(); i < getX() +4; i++) {
        if(endY < 0 || world->isIce(i, endY) || world->is_Boulder_here(i, endY)) {
            //cout << "saw ice or boulder" << endl;
            return false;
        }
    }
    return true;
}

void Protestor::shout(Direction dir) {
	//cout << "shout" << endl;
	switch (dir) {
	case left:
		setDirection(left);
		getWorld()->playSound(SOUND_PROTESTER_YELL);
		break;
	case right:
		setDirection(right);
		getWorld()->playSound(SOUND_PROTESTER_YELL);
		break;
	case up:
		setDirection(up);
		getWorld()->playSound(SOUND_PROTESTER_YELL);
		break;
	case down:
		setDirection(down);
		getWorld()->playSound(SOUND_PROTESTER_YELL);
		break;
	}
}
    
////////////////////////////////////////////////////    PROTESTER FUNCTION     ///////////////////////////////////////////////////////
Protestor::Protestor(int hp, int ID, int X, int Y, Direction direct, float size, unsigned int depth, StudentWorld* p) :
	leaving(false), ticksToWaitBetweenMoves( max(0, 3 - (int(p->getLevel()) / 4))) , non_resting_tick(0), perpendicular_turn_tick(200), numSquaresToMoveInCurrentDirection(30),
	Person(hp, ID, X, Y, direct, size, depth, p) {}

void Protestor::move(Direction direction) {
	int upper_Y_limit = getWorld()->get_h_Ice();
	int lower_Y_limit = 0;
	int upper_X_limit = getWorld()->get_w_Ice() - 4;
  int lower_X_limit = 0;
  	
	switch (direction) {
	case down:
		if (getDirection() != down) setDirection(down);
		else {
			if (getY() > lower_Y_limit && check_down(getY() - 1)) {
				setY(getY() - 1);
				moveTo(getX(), getY() - 1);
			}
			else {
				set_NumSquare_toMove(0);
			}
		}
		break;
	case left:
		if (getDirection() != left) setDirection(left);
		else {
			if (getX() > lower_X_limit && check_left(getX()-1)) {
				setX(getX() - 1);
				moveTo(getX() - 1, getY());
			}
			else {
				set_NumSquare_toMove(0);
			}
		}
		break;
	case up:
		if (getDirection() != up) setDirection(up);
		else {
			if (getY() < upper_Y_limit && check_up(getY() + 4)) {
				setY(getY() + 1);
				moveTo(getX(), getY() + 1);
			}
			else {
				set_NumSquare_toMove(0);
			}
		}
		break;
	case right:
		if (getDirection() != right) setDirection(right);
		else {
			if (getX() < upper_X_limit && check_right(getX() +4)) {
				setX(getX() + 1);
				moveTo(getX() + 1, getY());
			}
			else {
				set_NumSquare_toMove(0);
			}
		}
		break;
	}
}

void Protestor::move_leaving() {
	cout << "x: " << getX() << " Y:" << getY()<< endl;
	int x = getX();
	int y = getY();
	bool no_way_left = false;

	if (check_up(getY() + 4)) {
		cout << "up is clear" << endl;
		if (getWorld()->should_going_to(up, getX(), getY()) ) {
			cout << "shoud going up: " << getWorld()->should_going_to(up, getX(), getY()) << endl;
			cout << getWorld()->get_value_self_path(getX() , getY() ) << endl;
			setDirection(up);
			move(up);
			no_way_left = false;
		}
		else {
			cout << "shoud NOT going up: " << getWorld()->should_going_to(up, getX(), getY()) << endl;
			no_way_left = true;
		}
	}
	if (check_right(getX() + 4)) {
		cout << "right is clear" << endl;
		if (getWorld()->should_going_to(right, getX(), getY())) {
			cout << "shoud going right: " << getWorld()->should_going_to(up, getX(), getY()) << endl;
			cout << getWorld()->get_value_self_path(getX(), getY()) << endl;
			setDirection(right);
			move(right);
			no_way_left = false;
		}
		else {
			cout << "shoud Not going right: " << getWorld()->should_going_to(right, getX(), getY()) << endl;
			no_way_left = true;
		}
	}
	if (check_left(getX() - 1)) {
		cout << "left is clear" << endl;
		if (getWorld()->should_going_to(left, getX(), getY())) {
			cout << "shoud going left: " << getWorld()->should_going_to(up, getX(), getY()) << endl;
			cout << getWorld()->get_value_self_path(getX(), getY()) << endl;
			setDirection(left);
			move(left);
			no_way_left = false;
		}
		else {
			cout << "shoud NOT going left: " << getWorld()->should_going_to(left, getX(), getY()) << endl;
			no_way_left = true;
		}
	}
	if (check_down(getY() - 1)) {
		cout << "down is clear" << endl;
		if (getWorld()->should_going_to(down, getX(), getY())
			) {
			cout << "shoud going down: " << getWorld()->should_going_to(up, getX(), getY()) << endl;
			cout << getWorld()->get_value_self_path(getX() , getY() ) << endl;
			setDirection(down);
			move(down);
			no_way_left = false;
		}
		else {
			cout << "shoud Not going down: " << getWorld()->should_going_to(down, getX(), getY()) << endl;
			no_way_left = true;
		}
	}
	if(no_way_left) {
		getWorld()->mark_maze_went_through(x, y);
		move(getDirection());
	}
}

void Protestor::dec_health(int howmuch) {
	if (getHealth() - howmuch <= 0) {
		getWorld()->bfs_maze(getX(), getY(), 60, 60);
		getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
		leaving = true;
	}
	else {
		getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
		setTick(max(50, 100 - int(getWorld()->getLevel()) * 10));
		setHealth(getHealth() - howmuch);
	}
}

bool Protestor::is_Iceman_around(Direction& direct) {
	bool (StudentWorld::*func) (int, int);
	func = & StudentWorld::is_Iceman_here;
    //check left
    if( getWorld()->is_Iceman_here(getX()-1, getY())&&
        getWorld()->is_Iceman_here(getX()-1,getY()+1)&&
        getWorld()->is_Iceman_here(getX()-1, getY()+2)&&
        getWorld()->is_Iceman_here(getX()-1, getY()+3)){
        
        direct = left;
        return true;
    }
    //check right
    else if( getWorld()->is_Iceman_here(getX()+4, getY())&&
        getWorld()->is_Iceman_here(getX()+4,getY()+1)&&
        getWorld()->is_Iceman_here(getX()+4, getY()+2)&&
        getWorld()->is_Iceman_here(getX()+4, getY()+3)){
        
        direct = right;
        return true;
    }
    //check up
    else if( getWorld()->is_Iceman_here(getX(), getY()+4)&&
        getWorld()->is_Iceman_here(getX()+1,getY()+4)&&
        getWorld()->is_Iceman_here(getX()+2, getY()+4)&&
        getWorld()->is_Iceman_here(getX()+3, getY()+4)){
        
        direct = up;
        return true;
    }
    
    else if( getWorld()->is_Iceman_here(getX(), getY()-1)&&
        getWorld()->is_Iceman_here(getX()+1,getY()-1)&&
        getWorld()->is_Iceman_here(getX()+2, getY()-1)&&
        getWorld()->is_Iceman_here(getX()+3, getY()-1)){
        
        direct = down;
        return true;
    }
	return false;
}

bool Protestor::is_Ice_or_Boulder_around_ahead() {
	Direction direction = getDirection();
	switch (direction) {
	case up:
		if (!check_up(getY() + 4)) return true;
		else return false;
	case down:
		if (!check_down(getY() - 1)) return true;
		else return false;
	case left:
		if (!check_left(getX() - 1)) return true; 
		else return false;
	case right:
		if (!check_right(getX() + 4)) return true;
		else return false;
	}
}

void Protestor::change_direction() {
	srand(time(nullptr));
	int random_integer = rand() % 4 + 1;
	srand(time(nullptr));
	int random_num_square_toMove = rand() % 52 + 8;
	//set_NumSquare_toMove(random_num_square_toMove);
	//cout << random_integer << endl;
	//cout << random_num_square_toMove << endl;
	switch (random_integer) {
		case 1:
			if (check_up(getY() + 4)) {
				//cout << "change up" << endl;
				setDirection(up);
				break;
			}
		case 2:
			if (check_down(getY() - 1)) {
				//cout << "change down" << endl;
				setDirection(down);
				break;
			}
		case 3:
			if (check_left(getX() - 1)) {
				//cout << "change left" << endl;
				setDirection(left);
				break;
			}
		case 4:
			if (check_right(getX() + 4)) {
				//cout << "change right" << endl;
				setDirection(right);
				break;
			}
		default:
			set_NumSquare_toMove(0);
			//cout << "recursive call change_direction" << endl;
	}
}

void Protestor::reset_numSquare_toMove() {
	srand(time(0));
	int random_num_square_toMove = rand() % 52 + 8;
	numSquaresToMoveInCurrentDirection = random_num_square_toMove;
}

bool Protestor::is_current_direction_blocked_by_Boulder_or_Ice(Direction direction) {
	switch (direction) {
	case up:
		if (!check_up(getY() + 4)) {
			return true;
		}
		else return false;
	case down:
		if (!check_down(getY() - 1)) {
			return true;
		}
		else return false;
	case left:
		if (!check_left(getX() - 1)) {
			return true;
		}
		else return false;
	case right:
		if (!check_right(getX() + 4)) {
			return true;
		}
		else return false;
	}
}

bool Protestor::is_sitting_interstion(Direction& direction) {
	
	if (getDirection() == up || getDirection() == down) {
		//cout << "intersection neither up or down" << endl;
		if (check_left(getX() - 1) && check_right(getX() + 4)) {
			srand(time(nullptr));
			int random_integer = rand() % 2 + 1;
			if (random_integer == 1) {
				direction = left;
				return true;
			}
			else {
				direction = right;
				return true;
			}
		}
		else if (check_left(getX() - 1) || check_right(getX() + 4)) {
			srand(time(nullptr));
			int random_integer = rand() % 2 + 1;
			if (check_left(getX() - 1)) {
				direction = left;
				return true;
			}
			if (check_right(getX() - 4)) {
				direction = right;
				return true;
			}
		}
		else return false;
	}
	else {
		if (check_down(getY() - 1) && check_up(getY() + 4)) {
			int random_integer = rand() % 2 + 1;
			srand(time(0));
			if (random_integer == 1) {
				direction = up;
				return true;
			}
			else {
				direction = down;
				return true;
			}
		}
		else if (check_down(getY() - 1) || check_up(getY() + 4)) {
			if (check_down(getY() - 1)) {
				direction = down;
				return true;
			}
			if (check_up(getY() - 4)) {
				direction = up;
				return true;
			}
		}
		else {
			//cout << " no intersect up or down" << endl;
			return false;
		}
	}
	return false;
}

bool Protestor::looking_for_Iceman(Direction &direction) {
    StudentWorld* world = getWorld();
    //////////////////// check left////////////////////////
    for(int i = getX() - 1 ; i >= 0 ; i-- ) {
        if(check_left(i)) {
            if (world->is_Iceman_here(i, getY()) &&
                world->is_Iceman_here(i, getY() +1) &&
                world->is_Iceman_here(i, getY() +2) &&
                world->is_Iceman_here(i, getY() +3)) {
                //cout << "saw iceman loop" << endl;
                direction = left;
                return true;
            }
        }
        else break;
    }
    //////////////////// check down////////////////////////
    for(int i = getY() - 1 ; i >= 0 ; i-- ) {
        if(check_down(i)) {
            if (world->is_Iceman_here(getX()   , i) &&
                world->is_Iceman_here(getX() +1, i) &&
                world->is_Iceman_here(getX() +2, i) &&
                world->is_Iceman_here(getX() +3, i)) {
                //cout << "saw iceman loop" << endl;
                direction = down;
                return true;
            }
        }
        else break;
    }
    //////////////////// check right////////////////////////
    for(int i = getX() +4 ; i < 64 ; i++ ) {
        if(check_right(i)) {
            if (world->is_Iceman_here(i, getY()) &&
                world->is_Iceman_here(i, getY() +1) &&
                world->is_Iceman_here(i, getY() +2) &&
                world->is_Iceman_here(i, getY() +3)) {
                //cout << "saw iceman loop" << endl;
                direction = right;
                return true;
            }
        }
        else break;
    }
    //////////////////// check up////////////////////////
    for(int i = getY() +4 ; i < 64 ; i++ ) {
        if(check_up(i)) {
            if (world->is_Iceman_here(getX()   ,i) &&
                world->is_Iceman_here(getX() +1,i) &&
                world->is_Iceman_here(getX() +2,i) &&
                world->is_Iceman_here(getX() +3,i)) {
                //cout << "saw iceman loop" << endl;
                direction = up;
                return true;
            }
        }
        else break;
    }
    return false;
}

bool Protestor::isLeaving() {
	return leaving;
}

void Protestor::reset_tick() {
	ticksToWaitBetweenMoves = max(0, 3 - (int(getWorld()->getLevel()) / 4));
}

bool Person::is_current_direction_blocked_by_Boulder(Direction direction) {
	switch (direction) {
	case up:
		for (int i = getX(); i < getX() + 4; i++) {
			if (getWorld()->is_Boulder_here(i, getY() + 4)) {
				return true;
			}
		}
		return false;
	case down:
		for (int i = getX(); i < getX() + 4; i++) {
			if (getWorld()->is_Boulder_here(i, getY() - 1)) {
				return true;
			}
		}
		return false;
	case left:
		for (int i = getY(); i < getY() + 4; i++) {
			if (getWorld()->is_Boulder_here(getX()-1, i)) {
				return true;
			}
    }
		return false;
	case right:
		for (int i = getY(); i < getY() + 4; i++) {
			if (getWorld()->is_Boulder_here(getX() +4, i)) {
				return true;
			}
		}
		return false;
	}
}

/////////////////////////////////////////////////    REGULAR PROTESTOR     ///////////////////////////////////////////////////////////////////////

RegularProtestor::RegularProtestor(int X, int Y, StudentWorld* p) : Protestor(5, IID_PROTESTER, X, Y, left, 1, 0, p) { }

void RegularProtestor::doSomething() {
	if (isAlive()) {
		if (getTicks_remain() != 0) {
			setTick(getTicks_remain() - 1);
			return;
		}
		else {// if not in resting state
			set_nonresting_tick(get_nonresting() + 1);
			reset_tick();
			set_perpendicular_turn_tick(get_perpendicular_turn_tick() + 1);
			if (isLeaving()) {
				if (getX() == 60 && getY() == 60) {
					setAlive(false);
				}
				else {
					move_leaving();
				}
			}
			else { // if not leaving then search for iceman
				Direction dir;
				if (is_Iceman_around(dir)) {
					if (get_nonresting() >= 15) {
						//cout << get_nonresting() << endl;
						//cout << "shout" << endl;
						shout(dir);
						getWorld()->Hurt_Iceman(2);
						reset_nonresting_tick();
					}
				}
				else { // looking for iceman
					//cout << get_NumSquare_toMove() << endl;
					if (looking_for_Iceman(dir)) {
						//cout << dir << endl;
						setDirection(dir);
						move(dir);
						set_NumSquare_toMove(0);
					}
					else {
						set_NumSquare_toMove(get_NumSquare_toMove() - 1);
						if (get_NumSquare_toMove() <= 0) {
							change_direction();
							reset_numSquare_toMove();
							//move(getDirection());
						}
						else {
							Direction direction;
							if(is_sitting_interstion(direction) && get_perpendicular_turn_tick() >= 200){
								setDirection(direction);
								//move(direction);
								reset_numSquare_toMove();
								set_perpendicular_turn_tick(0);
							}
							else {
								if (is_current_direction_blocked_by_Boulder_or_Ice(getDirection())) {
									set_NumSquare_toMove(0);
								}
								else {
									move(getDirection());
								}
							}
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////    HARDCORE PROTESTOR     ///////////////////////////////////////////////////////////////////////

HardcoreProtestor::HardcoreProtestor(int X, int Y, StudentWorld* p) : Protestor(20, IID_HARD_CORE_PROTESTER, X, Y, left, 1, 0,p) {}

void HardcoreProtestor::doSomething() {
	if (isAlive()) {
		if (getTicks_remain() != 0) {
			setTick(getTicks_remain() - 1);
			return;
		}
		else {// if not in resting state
			set_perpendicular_turn_tick(get_perpendicular_turn_tick() + 1);
			if (isLeaving()) {
				if (getX() == 60 && getY() == 60) {
					setAlive(false);
				}
				else {
					//move_leaving();
				}
			}
			else { // if not leaving then search for iceman
				Direction dir;
				if (is_Iceman_around(dir)) {
					if (get_nonresting() >= 15) {
						//cout << get_nonresting() << endl;
						//cout << "shout" << endl;
						shout(dir);
						getWorld()->Hurt_Iceman(2);
						reset_nonresting_tick();
					}
				}
				else { // looking for iceman
					//cout << get_NumSquare_toMove() << endl;
					if (looking_for_Iceman(dir)) {
						//cout << dir << endl;
						setDirection(dir);
						move(dir);
						set_NumSquare_toMove(0);
					}
					else {
						set_NumSquare_toMove(get_NumSquare_toMove() - 1);
						if (get_NumSquare_toMove() <= 0) {
							change_direction();
							reset_numSquare_toMove();
							//move(getDirection());
						}
						else {
							Direction direction;
							if (is_sitting_interstion(direction) && get_perpendicular_turn_tick() >= 200) {
								setDirection(direction);
								//move(direction);
								reset_numSquare_toMove();
								set_perpendicular_turn_tick(0);
							}
							else {
								if (is_current_direction_blocked_by_Boulder_or_Ice(getDirection())) {
									set_NumSquare_toMove(0);
								}
								else {
									move(getDirection());
								}
							}
						}
					}
				}
			}
			set_nonresting_tick(get_nonresting() + 1);
			reset_tick();
		}
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
