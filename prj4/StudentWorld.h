#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    
    void updateDisplay();
    std::string displayText(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels);
    
    void addActor(Actor* actor);
    bool digEarth(int x, int y);
    bool isthereEarth(int x, int y);
    bool isEarthPixHere(int x, int y);
    bool isthereBoulder(int x, int y);
    bool isBoulderPixHere(int x, int y);
    bool areTheyWithinRad(int ax, int ay, int bx, int by, int rad);
    bool isPlayerInRad(Actor* actor, int rad);
    bool isProInRadAndGetBribed(Actor* actor, int rad);
    void playerDropGold(); // this is called by player when hit keys;
    
    bool decideIfActorNeedLoseHit(Actor *actor);
    bool isProInRadAndDecP(Actor *actor, int rad, int x, int y);
    void annoyTunnelman(); // should add annoy protesters later;
    void annoyPros(int bx, int by);
    void proAnnoyPlayer();
    
    void detectNearGoodies(int x, int y, int rad);

    bool isEarthOrBoulderInTargLoc(Actor::Direction dir, int sx, int sy);
    bool isBlockingOnDir(Actor::Direction, int x, int y); // x, y are player or pro's loc;
    bool checkEarthInDir(Actor::Direction, int x, int y);
    bool checkBoulderInDir(Actor::Direction, int x, int y);
    Actor::Direction getTunnelManDir();
    int getTunnelManX();
    int getTunnelManY();
    void tunnelmanPickedOil();
    void tunnelmanPickedGold();
    void tunnelmanPickedWater();
    void tunnelmanPickedSonar();
    // for protesters;
    
    void moveTowardsDest(Protester *prt, int dest_x, int dest_y);
    bool sensePlayerLocAndMove(Protester *prt, int dest_x, int dest_y, int m);
    bool actorsWithInRadius(int x, int y, int radius);
    void addBoulderorGoldorBarrel(int num, char actor);
    void addSonarNWater();
    void addProtesters();

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();


private:
    TunnelMan *m_TunnelMan;
    std::vector<Actor*> m_actors;
    Earth* m_field[64][64];
    int m_barrelsLeft;
    int m_prosInField;
    bool m_ifitsFirstTick;
    int m_tickSinceLast;
    
    int m_maze[64][64];
    struct grid{
        int m_x;
        int m_y;
        grid(int x, int y): m_x(x), m_y(y){}
    };
};

#endif // STUDENTWORLD_H_
