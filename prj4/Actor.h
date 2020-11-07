#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;



class Actor : public GraphObject
{
public:
    enum derivedC {earth, tunnelman, boulder, squirt, oil, gold, sonar, pool, protester ,regPro, harPro, livingactor, pickobj, goodie};
    
    // the base class for all of the objects in this project
    Actor(StudentWorld *world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, derivedC dc);
    StudentWorld*  getWorld();
    void walkto(int x, int y);
    virtual void getAnnoyed(int points) = 0;
    virtual void doSomething() = 0;
    void die();
    bool isalive();
    virtual void decHitP(int points);
    virtual int getHitP();
    virtual void setIsLeaving();
    bool isBoulder();

    virtual bool isOil();
    virtual bool isGold();
    virtual bool isSonar();
    virtual bool isPool();

    virtual bool isRegPro();
    virtual bool isHarPro();

    void setPickable(bool pickornot);
    bool canBePickedUp();
    virtual void getBribed();
    
private:
    StudentWorld * m_world;
    bool alive;
    derivedC m_whatIam;
    bool m_canBePickedUp;

};
// base class of tunnelman and protesters 
class LivingActor : public Actor
{
public:
    LivingActor(StudentWorld *world, int imageID, int startX, int startY, Direction dir,int hitP, derivedC type);
    
    virtual int getHitP();
    virtual void getAnnoyed(int points);
    virtual void doSomething() = 0;
    void moveOne(Direction dir);
    
private:
    derivedC m_livingActorType;
    int m_hitP;
};

class TunnelMan : public LivingActor
{
public:
    TunnelMan(StudentWorld *world, int hitP = 10, int waters = 5, int sonars = 1, int nuggets = 0);
    virtual void doSomething();
    int getwater();
    int getsonar();
    int getgold();
    void addwater();
    void addsonar();
    void addgold();
    void decGold();
    void shoot();
    
    ~TunnelMan(){}
    
private:
    // can squirt
    // can move
    // can get annoyed
    int m_water;
    int m_sonar;
    int m_gold;
    
};

class Earth : public Actor
{
    
public:
    Earth(StudentWorld *world, int startX, int startY);
    virtual void doSomething();
    virtual void getAnnoyed(int points);
private:
    
};

class Boulder : public Actor
{
public:
    Boulder(StudentWorld *world, int startX, int startY);
    
    bool check_stable();
    virtual void doSomething();
    virtual void getAnnoyed(int points);
    
private:
    bool m_stable;
    int m_tick;
    bool m_falling;
};

class Squirt : public Actor
{
public:
    Squirt(StudentWorld *world, int startX, int startY, Direction dir);
    
    virtual void doSomething();
    virtual void getAnnoyed(int points);
private:
    int m_dist;
};

class pickObj : public Actor
{
public:
    pickObj(StudentWorld *world, int imageID, int startX, int startY, derivedC dc );
    virtual void doSomething() = 0;
    virtual void getAnnoyed(int points);
    void disappear(int tick);
    virtual bool isGold();
    virtual bool isOil();
    virtual bool isSonar();
    virtual bool isPool();
    
private:
    int m_tick;
    derivedC m_pickObjType;
    
};

class OilBarrel : public pickObj
{
public:
    OilBarrel(StudentWorld *world, int startX, int startY);
    virtual void doSomething();
    virtual void getAnnoyed(int points);
private:

};

class GoldNugget : public pickObj
{
public:
    GoldNugget(StudentWorld *world, int startX, int startY, bool istemp);
    virtual void doSomething();
    virtual void getAnnoyed(int points);
    
private:
    bool m_istemp; // if false, then it's permanent, when begin game, is false; when drop, true;
    // istemp is true-> can be picked by pro; istemp false->can be picked by player;
    int m_tempStateTimeLeft;
    
};
class Sonar : public pickObj
{
public:
    Sonar(StudentWorld *world, int startX, int startY);
    virtual void doSomething();
    virtual void getAnnoyed(int points);
private:
};
class Pool : public pickObj
{
public:
    Pool(StudentWorld *world, int startX, int startY);
    virtual void doSomething();
    virtual void getAnnoyed(int points);
private:
};

class Protester : public LivingActor
{
public:
    Protester(StudentWorld *world, int imageID, derivedC dc, int hitP);
    void setNumInCurDirToMove();
    virtual void doSomething();
    void Ticking();
    void shoutTicking();
    void NoTurnTicking();
    bool isLeaving();
    bool isFacingTunnelman();
    bool isThereBlocksToDest(Direction dir, int destx, int desty);
    Direction directionOfPlayer();
    Direction randDir();
    bool canMovePerp();
    Direction setViableDir();
    void getStunned();
    virtual void getAnnoyed(int points);
    void getBribed();
    virtual void decHitP(int points);
    void setIsLeaving();
    // for hardcore;
    virtual bool isRegPro();
    virtual bool isHarPro();
    
private:
    int m_numSquaresToMoveInCur;
    int m_tick;
    derivedC m_protesterType;
    int m_shoutTick;
    int m_noTurnTick;
    bool m_leaving;
};

class RegProtester : public Protester
{
public:
    RegProtester(StudentWorld *world):Protester(world, TID_PROTESTER, regPro, 5){}
private:
};

class HardProtester : public Protester
{
public:
    HardProtester(StudentWorld *world):Protester(world, TID_HARD_CORE_PROTESTER, harPro, 20){}

private:
    
};


#endif // ACTOR_H_
