#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(StudentWorld *world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, derivedC dc):
GraphObject(imageID, startX, startY, dir, size, depth), m_world(world), alive(true), m_whatIam(dc), m_canBePickedUp(false)
{
    setVisible(true);
}
StudentWorld*  Actor::getWorld(){ return m_world; }
void Actor::die(){ alive = false; return;}
bool Actor::isalive() {return alive;}
void Actor::decHitP(int points){}
int Actor::getHitP(){return 100000;}
void Actor::setIsLeaving(){}
bool Actor::isBoulder(){
    return (m_whatIam == boulder);
}
bool Actor::isOil(){
    return (m_whatIam == oil);
}
bool Actor::isGold(){
    return (m_whatIam == gold);
}
//bool Actor::isSonar(){
//    return (m_whatIam == sonar);
//}
bool Actor::isPool(){
    return (m_whatIam == pool);
}
bool Actor::isRegPro(){
    return m_whatIam == regPro;
}
bool Actor::isSonar(){
    return (m_whatIam == sonar);
}
bool Actor::isHarPro(){
    return m_whatIam == harPro;
}
void Actor::setPickable(bool pickornot){m_canBePickedUp = pickornot;}
bool Actor::canBePickedUp(){return m_canBePickedUp;}
void Actor::getBribed(){}
void Actor::walkto(int x,int y){
    if (x < 0) x = 0;
    if (x > 60) x = 60;
    if (y < 0) y = 0;
    if (y > 60)  y = 60;
    GraphObject::moveTo(x, y);
}


LivingActor::LivingActor(StudentWorld *world, int imageID, int startX, int startY, Direction dir,int hitP, derivedC type):
Actor(world, imageID, startX, startY, dir, 1.0, 0, livingactor), m_hitP(hitP), m_livingActorType(type) {}
void LivingActor::getAnnoyed(int points){
    m_hitP -= points;
}

int LivingActor::getHitP(){return m_hitP;}

void LivingActor::moveOne(Direction dir){
    switch (dir) {
        case left:
            if (getDirection() == left){
                walkto(getX() - 1, getY());
            }
            else{
                setDirection(dir);
            }
            break;
        case right:
            if (getDirection() == right){
                walkto(getX() + 1, getY());
            }
            else{
                setDirection(dir);
            }
            break;
        case up:
            if (getDirection() == up){
                walkto(getX(), getY() + 1);
            }
            else{
                setDirection(dir);
            }
            break;
        case down:
            if (getDirection() == down){
                walkto(getX(), getY() - 1);
            }
            else{
                setDirection(dir);
            }
            break;
        
        default:
            break;
    }
}

void pickObj::disappear(int tick)
{
    if (m_tick == tick)
        die();
    else
        m_tick++;
}

TunnelMan::TunnelMan(StudentWorld *world, int hitP , int waters, int sonars , int nuggets ):
LivingActor(world, TID_PLAYER, 30, 60, right, 10, tunnelman),  m_water(waters), m_sonar(sonars), m_gold(nuggets){}

int TunnelMan::getwater(){return m_water;}
int TunnelMan::getsonar(){return m_sonar;}
int TunnelMan::getgold(){return m_gold;}
void TunnelMan::addwater(){ m_water += 5;}
void TunnelMan::addsonar(){ m_sonar++;}
void TunnelMan::addgold(){ m_gold++;}
void TunnelMan::decGold(){m_gold--;}

void TunnelMan::shoot(){
    Direction dir = getWorld()->getTunnelManDir();
    switch (dir) {
        case left:
            getWorld()->addActor(new Squirt(getWorld(), getWorld()->getTunnelManX() - 4,getWorld()->getTunnelManY(),getWorld()->getTunnelManDir()));
            break;
        case right:
        getWorld()->addActor(new Squirt(getWorld(), getWorld()->getTunnelManX() + 4,getWorld()->getTunnelManY(),getWorld()->getTunnelManDir()));
        break;
            
        case up:
        getWorld()->addActor(new Squirt(getWorld(), getWorld()->getTunnelManX(),getWorld()->getTunnelManY() + 4 ,getWorld()->getTunnelManDir()));
        break;
            
        case down:
        getWorld()->addActor(new Squirt(getWorld(), getWorld()->getTunnelManX(),getWorld()->getTunnelManY() - 4,getWorld()->getTunnelManDir()));
        break;
            
        default:
            break;
    }
    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
}

void TunnelMan::doSomething(){
    if (getWorld()->digEarth(getX(), getY())){
        getWorld()->playSound(SOUND_DIG);
    }
    int ch;
    if (getWorld()->getKey(ch)){
        switch (ch) {
            case KEY_PRESS_ESCAPE:
                die();
                break;
            case KEY_PRESS_UP:
                moveOne(up);
                
                break;
            case KEY_PRESS_DOWN:
                moveOne(down);
                break;
                
            case KEY_PRESS_LEFT:
                moveOne(left);
                break;
                
            case KEY_PRESS_RIGHT:
                moveOne(right);
                break;
                
            case KEY_PRESS_SPACE:
                if (m_water > 0){
                    m_water--;
                    shoot();
                }
                break;
            case KEY_PRESS_TAB:
                getWorld()->playerDropGold();
                break;
            //  press_z;
            case 'z':
            case 'Z':
                if (m_sonar > 0){
                    m_sonar--;
                    getWorld()->detectNearGoodies(getX(), getY(), 12);
                    getWorld()->playSound(SOUND_SONAR);
                }
                break;
            default:
                break;
        }
    }
    
}

Earth::Earth(StudentWorld *world, int startX, int startY):Actor(world, TID_EARTH, startX, startY, right, 0.25, 3, earth){
    setVisible(true);
}
void Earth::doSomething(){return;}
void Earth::getAnnoyed(int points){}

Boulder::Boulder(StudentWorld *world, int startX, int startY):
Actor(world,TID_BOULDER ,startX, startY, down, 1.0, 1, boulder), m_stable(true), m_tick(0), m_falling(false){
    setVisible(true);
    getWorld()->digEarth(startX, startY);
}

bool Boulder::check_stable(){
    if (getWorld()->isthereEarth(getX(), getY() - 1) || getWorld()->isthereEarth(getX() + 1, getY() - 1) || getWorld()->isthereEarth(getX() + 2, getY() - 1) || getWorld()->isthereEarth(getX() + 3, getY() - 1) ){
        
        return true;
    }
    else
        return false;
}
void Boulder::getAnnoyed(int points){}

void Boulder::doSomething(){
    if (!isalive())
        return;

    if (m_stable){
        if (check_stable()){
            return;
        }
        else{
            m_stable = false;
        }
    }
        // wait for 30 ticks; this is a function;
        // then fall; this is a function;
    if (m_tick == 30){
        m_falling = true;
        getWorld()->playSound(SOUND_FALLING_ROCK);
    }
    m_tick++;
    
    if (m_falling){
        // make the boulder fall to bottom;
        // if these happen, kill the boulder;
        
        if (check_stable() || getY() == 0 || getWorld()->isthereBoulder(getX(),getY()-4)){
            die();
        }
        else{
            walkto(getX(), getY() - 1);
            // annoyman;
            getWorld()->annoyTunnelman();
            getWorld()->annoyPros(getX(), getY());
        }
    }
}

// squirt constructor
Squirt::Squirt(StudentWorld *world, int startX, int startY, Direction dir):Actor(world, TID_WATER_SPURT, startX, startY, dir, 1.0, 1, squirt),m_dist(4){}

void Squirt::getAnnoyed(int points){}

void Squirt::doSomething(){
    //1. hit protesters;
    //2.set squirt to die if no distance

    if (getWorld()->isProInRadAndDecP(this, 3, getX(), getY()) || m_dist == 0){
        die();
        return;
    }
    else{
        // pass in squirt's x and y;
        if (getWorld()->isBlockingOnDir(getWorld()->getTunnelManDir(), getX(), getY())){
            die();
        }
        else{
            switch (getWorld()->getTunnelManDir()) {
                case left:
                    moveTo(getX() - 1, getY());
                    m_dist--;
                    break;
                case right:
                    moveTo(getX() + 1, getY());
                    m_dist--;
                    break;
                    
                case up:
                    moveTo(getX() , getY() + 1);
                    m_dist--;
                    break;
                    
                case down:
                    moveTo(getX() , getY() - 1);
                    m_dist--;
                    break;
                    
                default:
                    break;
            }
        }
    }
}
pickObj::pickObj(StudentWorld *world, int imageID, int startX, int startY, derivedC dc ):Actor(world, imageID, startX, startY, right, 1.0, 2, pickobj), m_tick(0), m_pickObjType(dc){
    setPickable(true);
    setVisible(false);
}

void pickObj::getAnnoyed(int points){}

bool pickObj::isGold(){ return m_pickObjType == gold;}
bool pickObj::isOil(){return m_pickObjType == oil;}
bool pickObj::isSonar(){return m_pickObjType == sonar;}
bool pickObj::isPool(){return m_pickObjType == pool;}

OilBarrel::OilBarrel(StudentWorld *world, int startX, int startY):pickObj(world, TID_BARREL, startX, startY, oil){}
void OilBarrel::getAnnoyed(int points){}
void OilBarrel::doSomething(){
    if (!isalive())
        return;
    else{
        if (!isVisible() && getWorld()->areTheyWithinRad(getX(), getY(), getWorld()->getTunnelManX(), getWorld()->getTunnelManY(), 4)){
            setVisible(true);
            return;
        }
        else{
            if (getWorld()->areTheyWithinRad(getX(), getY(), getWorld()->getTunnelManX(), getWorld()->getTunnelManY(), 3)){
                die();
                getWorld()->playSound(SOUND_FOUND_OIL);
                // tunnelman score add;
                getWorld()->increaseScore(1000);
                getWorld()->tunnelmanPickedOil();
            }
        }
    }
    
}
GoldNugget::GoldNugget(StudentWorld *world, int startX, int startY, bool istemp):pickObj(world, TID_GOLD, startX, startY, gold), m_istemp(istemp), m_tempStateTimeLeft(100) {
    if (m_istemp){
        setVisible(true);
    }
}

void GoldNugget::getAnnoyed(int points){}

void GoldNugget::doSomething()
{
    if(!isalive()) return;
    else{
        if (!isVisible() && getWorld()->isPlayerInRad(this, 4)){
            setVisible(true);
            return;
        }
        else{
            if (!m_istemp && getWorld()->isPlayerInRad(this, 3)){
                die();
                getWorld()->playSound(SOUND_GOT_GOODIE);
                getWorld()->increaseScore(10);
                getWorld()->tunnelmanPickedGold();
                m_istemp = true;
                return;
            }
            // else if is pickable by protesters, and within 3 rad
            // do the things to protesters;
            else if (m_istemp && getWorld()->isProInRadAndGetBribed(this, 3)){
                die();
                return;
            }
            if (m_istemp){
                m_tempStateTimeLeft--;
                if (m_tempStateTimeLeft == 0){
                    die();
                    return;
                }
            }
            
        }
    }
}
Sonar::Sonar(StudentWorld *world, int startX, int startY):pickObj(world, TID_SONAR, startX, startY, sonar){
    setVisible(true);
}
void Sonar::getAnnoyed(int points){}
void Sonar::doSomething()
{
    if (!isalive()) return;
    else{
        if (getWorld()->isPlayerInRad(this, 3)){
            die();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->tunnelmanPickedSonar();
            getWorld()->increaseScore(75);
        }
    }
    disappear(max(100, 300 - 10 * int(getWorld()->getLevel()) ));
}
Pool::Pool(StudentWorld *world, int startX, int startY):pickObj(world, TID_WATER_POOL, startX, startY, pool){
    setVisible(true);
}
void Pool::getAnnoyed(int points){}
void Pool::doSomething()
{
    if (!isalive()) return;
    else{
        if (getWorld()->isPlayerInRad(this, 3)){
            die();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->tunnelmanPickedWater();
            getWorld()->increaseScore(100);
        }
    }
    disappear(max(100, 300 - 10 * int(getWorld()->getLevel()) ));
}
// protester constructor;
Protester::Protester(StudentWorld *world, int imageID, derivedC dc, int hitP): LivingActor(world, imageID, 60, 60, left, hitP, protester), m_protesterType(dc), m_shoutTick(0), m_noTurnTick(0), m_leaving(false)
{
    m_tick = max(0, 3 - int(getWorld()->getLevel() / 4));
    setNumInCurDirToMove();
}

void Protester::setNumInCurDirToMove(){
    srand(time(0));
    m_numSquaresToMoveInCur = rand()%53 + 8;
}

void Protester::Ticking()
{
    m_tick--;
}
void Protester::shoutTicking(){
    m_shoutTick++;
}
void Protester::NoTurnTicking(){
    m_noTurnTick++;
}

bool Protester::isLeaving()
{
    return getHitP() <= 0;
}

bool Protester::isFacingTunnelman(){
    switch (getDirection()) {
        case GraphObject::left:
            return getWorld()->getTunnelManX() <= getX();
            break;
        case GraphObject::right:
            return getWorld()->getTunnelManX() >= getX();
            break;
        case GraphObject::up:
            return getWorld()->getTunnelManY() >= getY();
            break;
        case GraphObject::down:
            return getWorld()->getTunnelManY() <= getY();
            break;
            
        default:
            break;
    }
    return false;
}

bool Protester::isThereBlocksToDest(Direction dir, int destx, int desty){
    if (destx != getX() && desty != getY()) return true;
    switch (dir) {
        case left:
            // destx < getx(pro's x); desty = gety;
            if (destx < getX() && desty == getY()){
                for (int i = destx; i <= getX()-5; i++){
                    if (getWorld()->isEarthOrBoulderInTargLoc(right, i, getY())){
                        return true; // yes there is block between pro and dest;
                    }
                }
            }
            break;
            
        case right:
        // destx < getx; desty = gety;
            if (destx > getX() && desty == getY()){
                for (int i = getX(); i <= destx-5; i++){
                    if (getWorld()->isEarthOrBoulderInTargLoc(right, i, getY())){
                        return true; // yes there is block between pro and dest;
                    }
                }
            }
        break;
            
        case up:
            if (destx == getX() && desty > getY()){
                for (int j = getY(); j <= desty - 5; j++){
                    if (getWorld()->isEarthOrBoulderInTargLoc(up, getX(), j)){
                        return true; // yes there is block between pro and dest;
                    }
                }
            }
        break;
            
        case down:
        // destx < getx; desty = gety;
            if (destx == getX() && desty < getY()){
                for (int j = desty; j <= getY()-5; j++){
                    if (getWorld()->isEarthOrBoulderInTargLoc(up, getX(), j)){
                        return true; // yes there is block between pro and dest;
                    }
                }
            }
        break;
            
        default:
            break;
    }
    return false;
}

Actor::Direction Protester::directionOfPlayer(){
    // get the tunnelman's location
    int tx = getWorld()->getTunnelManX();
    int ty = getWorld()->getTunnelManY();
    if (tx == getX() && ty == getY()){
        return getDirection();
    }
    if (getY() == ty){
        if (tx < getX()){
            return left;
        }
        if (tx > getX()){
            return right;
        }
    }
    if (getX() == tx){
        if (ty > getY()){
            return up;
        }
        if (ty < getY()){
            return down;
        }
    }
    return none;
}

Actor::Direction Protester::randDir(){
    srand(time(0));
    int r = rand()%4;
    switch (r) {
        case 0:
            return left;
            break;
        case 1:
            return right;
            break;
        case 2:
            return up;
            break;
        case 3:
            return down;
            break;
            
        default:
            break;
    }
    return none;
}

bool Protester::canMovePerp(){
    Direction dir = getDirection();
    if (dir == left || dir == right ){
        if (!getWorld()->isEarthOrBoulderInTargLoc(up, getX(), getY()) || !getWorld()->isEarthOrBoulderInTargLoc(down, getX(), getY())){
            return true;
        }
        else return false;
    }
    else{
        if (!getWorld()->isEarthOrBoulderInTargLoc(left, getX(), getY()) || !getWorld()->isEarthOrBoulderInTargLoc(right, getX(), getY())){
            return true;
        }
        else return false;
    }
}

Actor::Direction Protester::setViableDir(){
    Direction dir = getDirection();
    srand(time(0));
    int r = rand()%2;
    if (dir == left || dir == right ){
        if (!getWorld()->isEarthOrBoulderInTargLoc(up, getX(), getY())){
            return up;
            }
        else if(!getWorld()->isEarthOrBoulderInTargLoc(down, getX(), getY())){
            return down;
            }
        else{
                if (r == 0) return up;
                else return down;
            }
    }
    else{
        if (!getWorld()->isEarthOrBoulderInTargLoc(left, getX(), getY())){
            return left;
            }
        else if(!getWorld()->isEarthOrBoulderInTargLoc(right, getX(), getY())){
            return right;
            }
        else{
                if (r == 0) return left;
                else return right;
            }
    }
    return none;
}

void Protester::getStunned(){
    m_tick = max(50, 100 - int(getWorld()->getLevel()*10));
}

void Protester::getAnnoyed(int points){
    if(isLeaving()) return;
    LivingActor::getAnnoyed(points);
    if (getHitP() > 0 ){
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        getStunned();
    }
    else{
        // going to die();
        m_leaving = true;
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_tick = 0;
        if (points == 100 )
            getWorld()->increaseScore(500);
        else
            getWorld()->increaseScore(100);
    }
}

void Protester::getBribed(){
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    if (isRegPro()){
        getWorld()->increaseScore(25);
        m_leaving = true;
    }
    else{
        getWorld()->increaseScore(50);
        getStunned();
    }
}
void Protester::decHitP(int points){
    LivingActor::getAnnoyed(points);
}

void Protester::setIsLeaving(){m_leaving = true;}
// for hardcore;
bool Protester::isRegPro(){
    return m_protesterType == regPro;
}
bool Protester::isHarPro(){
    return m_protesterType == harPro;
}

void Protester::doSomething()
{
    srand(time(0));
    // step1
    
    if(!isalive()) return;
    if (m_tick > 0){ // is resting
        m_tick--;
        return;
    }
    else{ // do things; follow by step3;
        if (!m_leaving)
            m_tick = max(0, 3 - int(getWorld()->getLevel() / 4));
        shoutTicking();
        NoTurnTicking();
    }
    
    //step3, make a move;
    if (m_leaving){
        if (getX() == 60 && getY() == 60){
            die();
            return;
        }
        else{
            // move one step towards the exit;
            getWorld()->moveTowardsDest(this, 60, 60);
            return;
        }
    }
    //step4 shout if is close to player;
    if(getWorld()->isPlayerInRad(this, 4) && isFacingTunnelman()){
        if (m_shoutTick > 15){
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            getWorld()->proAnnoyPlayer();
            m_shoutTick = 0;
            return;
        }
    }
    // step5 for hardCore pro;
    if (isHarPro()){
        int m = 16 + getWorld()->getLevel()*2;
        if (!getWorld()->isPlayerInRad(this, 4) && getWorld()->sensePlayerLocAndMove(this, getWorld()->getTunnelManX(), getWorld()->getTunnelManY(), m)){
            return;
        }
    }
    
    // step5, if player not within rad, and is in a direction of protester, there is not blocking in between pro and player;
    // 6 for hardcore;

    if (!getWorld()->isPlayerInRad(this, 4) && directionOfPlayer() != none && !isThereBlocksToDest(directionOfPlayer(), getWorld()->getTunnelManX(), getWorld()->getTunnelManY())){
        
        setDirection(directionOfPlayer());
        moveOne(directionOfPlayer());
        
        m_numSquaresToMoveInCur = 0;
        return;
        
    }
    
    // step6, current direction run over, change direction;
    m_numSquaresToMoveInCur--;
    if (m_numSquaresToMoveInCur <= 0){
        // change dir to a viable random dir;
        Direction rdir = randDir();
        while(getWorld()->isBlockingOnDir(rdir, getX(), getY())){
            rdir = randDir();
        }
        setDirection(rdir);
        setNumInCurDirToMove();
    }
    // at intersection, go perpendicular;
    
    else if (m_noTurnTick > 200 && canMovePerp()){
        // set direction to a viable dir;
        Direction dir = setViableDir();
        setDirection(dir);
        setNumInCurDirToMove();
        m_noTurnTick = 0;
    }
    moveOne(getDirection());
    if (getWorld()->isBlockingOnDir(getDirection(), getX(), getY())){
        m_numSquaresToMoveInCur = 0;
    }
    
    
}

