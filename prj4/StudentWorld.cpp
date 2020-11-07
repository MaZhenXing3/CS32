#include "StudentWorld.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>
#include <time.h>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
    : GameWorld(assetDir), m_barrelsLeft(0), m_ifitsFirstTick(true), m_tickSinceLast(0), m_prosInField(0)
{
    m_TunnelMan = nullptr;
    m_actors.clear();
    for (int i = 0; i < 64; i++){
        for (int j = 0; j < 64; j++){
            m_field[i][j] = nullptr;
        }
    }
}

void StudentWorld::addActor(Actor* actor){ m_actors.push_back(actor); }

Actor::Direction StudentWorld::getTunnelManDir(){return m_TunnelMan->getDirection();}
int StudentWorld::getTunnelManX(){return m_TunnelMan->getX();}
int StudentWorld::getTunnelManY(){return m_TunnelMan->getY();}

void StudentWorld::updateDisplay(){
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int health = m_TunnelMan->getHitP();
    int squirts = m_TunnelMan->getwater();
    int gold = m_TunnelMan->getgold();
    int sonar = m_TunnelMan->getsonar();

    string s = displayText(score, level, lives, health, squirts, gold, sonar, m_barrelsLeft);
    setGameStatText(s);
}

string StudentWorld::displayText(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels){
    stringstream s;

    s.fill('0');
    s << "Scr: ";
    s << setw(6) << score;

    s.fill(' ');
    s << " Lvl: ";
    s << setw(2) << level;

    s << " Lives: ";
    s << setw(1) << lives;

    s << "  Hlth: ";
    s << setw(3) << health * 10;
    s << '%';

    s << "  Wtr: ";
    s << setw(2) << squirts;

    s << "  Gld: ";
    s << setw(2) << gold;

    s << "  Sonar: ";
    s << setw(2) << sonar;

    s << "  Oil Left: ";
    s << setw(2) << barrels;

    return s.str();
}

// destroy earth when tunnelman passby
bool StudentWorld::digEarth(int x, int y){
    bool clear = false;
    for (int i = x; i < x + 4; i++){
        for (int j = y; j < y + 4; j++){
            if (m_field[i][j] != nullptr){
                delete m_field[i][j];
                m_field[i][j] = nullptr;
                clear = true;
            }
        }
    }
    return clear;
}

bool StudentWorld::isthereEarth(int x, int y)
{
    if (m_field[x][y] == nullptr)
        return false;
    else
        return true;
}

bool StudentWorld::isEarthPixHere(int x, int y)
{
    for (int i = x; i < x + 4; i++) {

        for (int j = y; j <y + 4; j++) {

            if (m_field[i][j] != nullptr)
                return true;
        }
    }
    return false;
}

bool StudentWorld::isthereBoulder(int x, int y){
    vector<Actor*>::iterator it;
    for(it = m_actors.begin(); it != m_actors.end(); it++){
        if ((*it)->isBoulder() && ((*it)->getX() == x && (*it)->getY() == y)){
            return true;
        }
    }
    return false;
}

bool StudentWorld::isBoulderPixHere(int x, int y){
    for (int i = x - 3; i <= x; i++){
        for (int j = y - 3; j <= y; j++ ){
            if (isthereBoulder(i, j))
                return true;
        }
    }
    return false;
}

bool StudentWorld::areTheyWithinRad(int ax, int ay, int bx, int by, int rad){
    if ((ax - bx)*(ax - bx) + (ay - by)*(ay - by) <= rad*rad)
        return true; // are in rad;
    else
        return false;
}

bool StudentWorld::isPlayerInRad(Actor* actor, int rad){
    return areTheyWithinRad(actor->getX(), actor->getY(), m_TunnelMan->getX(), m_TunnelMan->getY(), rad);
}
bool StudentWorld::isProInRadAndGetBribed(Actor* actor, int rad){
    vector<Actor*>::iterator it;
    for (it = m_actors.begin(); it != m_actors.end(); it++){
        if (((*it)->isRegPro() || (*it)->isHarPro()) && areTheyWithinRad((*it)->getX(), (*it)->getY(), actor->getX(), actor->getY(), rad)){
            (*it)->getBribed();
            return true;
        }
    }
    return false;
}
void StudentWorld::playerDropGold(){
    if (m_TunnelMan->getgold() > 0){
        addActor(new GoldNugget(this, getTunnelManX(), getTunnelManY(), true));
        m_TunnelMan->decGold();
    }
}

bool StudentWorld::isProInRadAndDecP(Actor *actor, int rad, int sqx, int sqy){
    vector<Actor*>::iterator it;
    bool result = false;
    for (it = m_actors.begin(); it != m_actors.end(); it++){
        if (((*it)->isRegPro() || (*it)->isHarPro()) && areTheyWithinRad((*it)->getX(), (*it)->getY(), sqx, sqy, rad)){
            (*it)->getAnnoyed(2);
            result = true;
        }
    }
    return result;
}
// this is used by boulder and pros;
void StudentWorld::annoyTunnelman()
{
    if (m_TunnelMan->isalive()){
        vector<Actor*>::iterator it;
        for (it = m_actors.begin(); it != m_actors.end(); it++){
            if (isPlayerInRad((*it), 3)){
                if ( (*it)->isBoulder() ){
                    m_TunnelMan->getAnnoyed(100);
                }
            }
            if (m_TunnelMan->getHitP() <= 0){
                m_TunnelMan->die();
            }
        }
    }
    else return;
}

void StudentWorld::proAnnoyPlayer(){
    m_TunnelMan->getAnnoyed(2);
    if (m_TunnelMan->getHitP() <= 0){
        m_TunnelMan->die();
    }
}

void StudentWorld::annoyPros(int boulderx, int bouldery){
    vector<Actor*>::iterator it;
    for (it = m_actors.begin(); it != m_actors.end(); it++){
        if ( (*it)->isHarPro() || (*it)->isRegPro() ){
            if(areTheyWithinRad(boulderx, bouldery, (*it)->getX(), (*it)->getY(), 3)){
                (*it)->decHitP(100);
                if ((*it)->getHitP() <= 0){
                    (*it)->setIsLeaving();
                    playSound(SOUND_PROTESTER_GIVE_UP);
                }
            }
        }
        
    }
    return;
}

void StudentWorld::detectNearGoodies(int x, int y, int rad){
    int a, b;
    vector<Actor*>::iterator it;
    for (it = m_actors.begin(); it != m_actors.end(); it++)
    {
        if ((*it)->isGold() || (*it)->isOil())
        {
            a = (*it)->getX(); b = (*it)->getY();
            if (areTheyWithinRad(x, y, a, b, rad))
                (*it)->setVisible(true);
        }
    }
}


bool StudentWorld::checkBoulderInDir(Actor::Direction dir, int x, int y){
    switch (dir) {
        case Actor::left:
            if (isBoulderPixHere(x-1, y) || isBoulderPixHere(x-1, y + 1) || isBoulderPixHere(x-1, y + 2) || isBoulderPixHere(x-1, y + 3)){
                return true;
            }
            break;
        case Actor::right:
            if (isBoulderPixHere(x+4, y) || isBoulderPixHere(x+4, y + 1) || isBoulderPixHere(x+4, y + 2) || isBoulderPixHere(x+4, y + 3)){
                return true;
            }
            break;
        case Actor::up:
            if (isBoulderPixHere(x + 1, y+4) || isBoulderPixHere(x+2, y + 4) || isBoulderPixHere(x+3, y + 4) || isBoulderPixHere(x+4, y + 4)){
                return true;
            }
            break;
        case Actor::down:
            if (isBoulderPixHere(x, y -1) || isBoulderPixHere(x+1, y - 1) || isBoulderPixHere(x+2, y -1) || isBoulderPixHere(x+3, y -1)){
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool StudentWorld::checkEarthInDir(Actor::Direction dir, int x, int y){
    switch (dir) {
        case Actor::left:
            if (isthereEarth(x-1, y) || isthereEarth(x-1, y + 1) || isthereEarth(x-1, y + 2) || isthereEarth(x-1, y + 3) ){
                return true;
            }
            
            break;
        case Actor::right:
            if (isthereEarth(x+4, y) || isthereEarth(x+4, y + 1) || isthereEarth(x+4, y + 2) || isthereEarth(x+4, y + 3)){
                return true;
            }
            break;
        case Actor::up:
            if (isthereEarth(x, y+4) || isthereEarth(x+1, y+4) || isthereEarth(x+2, y+4) ||         isthereEarth(x+3, y+4) ){
                return true;
            }
            break;
        case Actor::down:
            if (isthereEarth(x, y-1) || isthereEarth(x+1, y-1) || isthereEarth(x+2, y-1) ||        isthereEarth(x+3, y-1) ){
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool StudentWorld::isEarthOrBoulderInTargLoc(Actor::Direction dir ,int sx, int sy){
    
    if (checkEarthInDir(dir, sx, sy) || checkBoulderInDir(dir, sx, sy)){
        return true;
    }
    else return false;
}
bool StudentWorld::isBlockingOnDir(Actor::Direction dir, int x, int y){
    if (isEarthOrBoulderInTargLoc(dir, x, y)){
        return true;
    }
    if (dir == Actor::left){
        if (x == 0) return true;
    }
    if (dir == Actor::right){
        if (x == 60) return true;
    }
    if (dir == Actor::up){
        if (y == 60) return true;
    }
    if (dir == Actor::down){
        if (y == 0) return true;
    }
    return false;
}

void StudentWorld::tunnelmanPickedOil(){
    m_barrelsLeft--;
}

void StudentWorld::tunnelmanPickedGold(){
    m_TunnelMan->addgold();
}

void StudentWorld::tunnelmanPickedSonar(){
    m_TunnelMan->addsonar();
}
void StudentWorld::tunnelmanPickedWater(){
    m_TunnelMan->addwater();
}

void StudentWorld::moveTowardsDest(Protester *prt, int dest_x, int dest_y)
{
    // initialize the maze to all 0;
    for (int i = 0; i < 64; i++){
        for(int j = 0; j < 64; j++){
            m_maze[i][j] = 0;
        }
    }
    // make a queue; and push a grid that is at the exit;
    queue<grid> q;
    m_maze[dest_x][dest_y] = 1;
    q.push(grid(dest_x,dest_y));
    // now fill out empty grids with numbers
    while(!q.empty()){
        // x and y are the the current node that is going to do breadth seach;
        int x = q.front().m_x;
        int y = q.front().m_y;
        q.pop();
        
        if (!isBlockingOnDir(Actor::left, x, y)  && m_maze[x-1][y] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x-1][y] = m_maze[x][y] + 1;
            q.push(grid(x-1,y));
        }
        if (!isBlockingOnDir(Actor::right, x, y) && m_maze[x+1][y] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x+1][y] = m_maze[x][y] + 1;
            q.push(grid(x+1,y));
        }
        if (!isBlockingOnDir(Actor::up, x, y) && m_maze[x][y+1] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x][y+1] = m_maze[x][y] + 1;
            q.push(grid(x,y+1));
        }
        if (!isBlockingOnDir(Actor::down, x, y) && m_maze[x][y-1] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x][y-1] = m_maze[x][y] + 1;
            q.push(grid(x,y-1));
        }
    }
    // now the m_maze's empty spaces are filled with numbers;
    // the protester is currently an empty space on the maze, we move it one dir to the decending dir;
    int px = prt->getX();
    int py = prt->getY();
    
    if (!isBlockingOnDir(Actor::left, px, py) && m_maze[px-1][py] == m_maze[px][py] - 1){
        // move one step in left dir;
        prt->moveOne(Actor::left);
    }
    if (!isBlockingOnDir(Actor::right, px, py) && m_maze[px+1][py] == m_maze[px][py] - 1){
        prt->moveOne(Actor::right);
    }
    if (!isBlockingOnDir(Actor::up, px, py) && m_maze[px][py+1] == m_maze[px][py] - 1){
        prt->moveOne(Actor::up);
    }
    if (!isBlockingOnDir(Actor::down, px, py) && m_maze[px][py-1] == m_maze[px][py] - 1){
        prt->moveOne(Actor::down);
    }
}

bool StudentWorld::sensePlayerLocAndMove(Protester *prt, int dest_x, int dest_y, int m){
    // initialize the maze to all 0;
    for (int i = 0; i < 64; i++){
        for(int j = 0; j < 64; j++){
            m_maze[i][j] = 0;
        }
    }
    // make a queue; and push a grid that is at the exit;
    queue<grid> q;
    m_maze[dest_x][dest_y] = 1;
    q.push(grid(dest_x,dest_y));
    // now fill out empty grids with numbers
    while(!q.empty()){
        // x and y are the the current node that is going to do breadth seach;
        int x = q.front().m_x;
        int y = q.front().m_y;
        q.pop();
        
        if (!isBlockingOnDir(Actor::left, x, y)  && m_maze[x-1][y] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x-1][y] = m_maze[x][y] + 1;
            q.push(grid(x-1,y));
        }
        if (!isBlockingOnDir(Actor::right, x, y) && m_maze[x+1][y] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x+1][y] = m_maze[x][y] + 1;
            q.push(grid(x+1,y));
        }
        if (!isBlockingOnDir(Actor::up, x, y) && m_maze[x][y+1] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x][y+1] = m_maze[x][y] + 1;
            q.push(grid(x,y+1));
        }
        if (!isBlockingOnDir(Actor::down, x, y) && m_maze[x][y-1] == 0){
            // change the left node's number in maze to current + 1, and push the left node to pueue;
            m_maze[x][y-1] = m_maze[x][y] + 1;
            q.push(grid(x,y-1));
        }
    }
    // now the m_maze's empty spaces are filled with numbers;
    // the protester is currently an empty space on the maze, we move it one dir to the decending dir;
    int px = prt->getX();
    int py = prt->getY();
    if (m_maze[px][py] <= m+1){
        if (!isBlockingOnDir(Actor::left, px, py) && m_maze[px-1][py] == m_maze[px][py] - 1){
            // move one step in left dir;
            prt->moveOne(Actor::left);
            return true;
        }
        if (!isBlockingOnDir(Actor::right, px, py) && m_maze[px+1][py] == m_maze[px][py] - 1){
            prt->moveOne(Actor::right);
            return true;
        }
        if (!isBlockingOnDir(Actor::up, px, py) && m_maze[px][py+1] == m_maze[px][py] - 1){
            prt->moveOne(Actor::up);
            return true;
        }
        if (!isBlockingOnDir(Actor::down, px, py) && m_maze[px][py-1] == m_maze[px][py] - 1){
            prt->moveOne(Actor::down);
            return true;
        }
    }
    return false;
}

bool StudentWorld::actorsWithInRadius(int x, int y, int radius) {
    vector<Actor*>::iterator it;
    it = m_actors.begin();
    while (it != m_actors.end()){
        if (areTheyWithinRad(x,y, (*it)->getX(),(*it)->getY() ,radius))
            return true;
        it++;
    }
    return false;
}

void StudentWorld::addBoulderorGoldorBarrel(int num, char actor) {
    srand(time(0));
    int x, y;
    for (int i = 0; i < num; i++) {
        do {
            x = rand() % 60 + 1;
            if (actor == 'B') y = rand() % 36 + 1 + 20;
            else    y = rand() % 56 + 1;
        } while (actorsWithInRadius(x, y, 6) || (x > 26 && x < 34 && y>0));
        switch (actor) {
            case 'B':
                addActor(new Boulder(this, x, y));
                break;
            case 'G':
                addActor(new GoldNugget(this, x, y, false));
                break;
            case 'L':
                addActor(new OilBarrel(this, x, y));
                m_barrelsLeft++;
                break;
        }
    }
}
void StudentWorld::addSonarNWater()
{
    srand(time(NULL));
    int x, y;
    int G = (int)getLevel()*25 + 300;
    int r = rand();
    if (int(r % G) == 4) {
        if (int(r % 5)  == 4) {
            addActor(new Sonar(this, 0, 60));
        }
        else {
            x = rand() % 60 + 1;
            y = rand() % 60 + 1;
            while (isEarthPixHere(x, y)){
                x = rand() % 60 + 1;
                y = rand() % 60 + 1;
            }
            addActor(new Pool(this, x, y));
        }
    }
}

void StudentWorld::addProtesters()
{
    srand(time(NULL));
    int T = max(25, 200 - (int)getLevel());
    int P = fmin(15, 2 + getLevel() * 1.5);
    int probabilityOfHardcore = min(90, (int)getLevel() * 10 + 30);
    if (m_ifitsFirstTick || (m_tickSinceLast > T && m_prosInField < P)) {
        if (rand() % 100 + 1 < probabilityOfHardcore)
            addActor(new HardProtester(this));
        else addActor(new RegProtester(this));
        m_tickSinceLast = 0;
        m_prosInField++;
        m_ifitsFirstTick = false;
    }
    m_tickSinceLast++;
}
int StudentWorld::init()
{
    m_barrelsLeft = 0;
    m_ifitsFirstTick = true;
    m_tickSinceLast = 0;
    m_prosInField = 0;
    
    
    
    for (int i = 0; i < 64 ; i++){
        for (int j = 0; j < 60; j++){
            if (i < 30 || i > 33 || j < 4){
                m_field[i][j] = new Earth(this, i, j);
            }
        }
    }
    int B = min(int(getLevel()/2 + 2), 9);
    int G = max((int)getLevel()/2, 2);
    int L = min( 2 + (int)getLevel(), 21);
    m_TunnelMan = new TunnelMan(this);
    //add boulder, gold and oil as they are needed;
    addBoulderorGoldorBarrel(B, 'B');
    addBoulderorGoldorBarrel(L, 'L');
    addBoulderorGoldorBarrel(G, 'G');
    
    //// just for right now;
    //addActor(new Boulder(this, 20, 50));
    //addActor(new OilBarrel(this, 20, 40));
    //addActor(new GoldNugget(this, 20, 30, false));// temp is false which means it's pickable //by player;
    //addActor(new Sonar(this, 0,60));
    //addActor(new RegProtester(this));
    //addActor(new Pool(this, 10, 60));
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //decLives();
    //return GWSTATUS_PLAYER_DIED;
    updateDisplay();
    
    vector<Actor*>::iterator it;
    for(it = m_actors.begin(); it != m_actors.end(); it++){
        if ((*it)->isalive()){
            (*it)->doSomething();
        }
        if (!m_TunnelMan->isalive()) {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        if (m_barrelsLeft == 0) {
            return GWSTATUS_FINISHED_LEVEL;
        }
    }

    //add goodies and protesters as needed;
    addSonarNWater();
    addProtesters();
    
    m_TunnelMan->doSomething();
    // erase dead actors from the vector
    it = m_actors.begin();
    while(it != m_actors.end()) {
        if (!(*it)->isalive()) {
            delete *it;
            it = m_actors.erase(it);
        }
        else it++;
    }

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (int x = 0; x < 64; x++)
    {
        for (int y = 0; y < 60; y++)
        {
            delete m_field[x][y];
        }
    }
    for (Actor* a : m_actors){
        delete a;
    }
    m_actors.clear();
    delete m_TunnelMan;
    m_TunnelMan = nullptr;
}

 StudentWorld::~StudentWorld(){
    cleanUp();
}
