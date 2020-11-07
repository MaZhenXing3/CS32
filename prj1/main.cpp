// zion_solution.cpp

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Robot.h"
#include "Player.h"
#include "Arena.h"
#include "globals.h"
#include "Game.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////
/*
const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 40;             // max number of columns in the arena
const int MAXROBOTS = 130;          // max number of robots allowed
const int MAXSHOTLEN = 5;           // max number of steps you can shoot
const int INITIAL_ROBOT_HEALTH = 2;

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;
*/
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////
/*
int decodeDirection(char dir);
void clearScreen();
*/
///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////


//class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Robot declaration.
/*
class Robot
{
  public:
        // Constructor
    Robot(Arena* ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool takeDamageAndLive();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};
*/
/*
class Player
{
  public:
        // Constructor
    Player(Arena *ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;

    int    computeDanger(int r, int c) const;
};
*/
/*
class Arena
{
  public:
        // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;

        // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    void   damageRobotAt(int r, int c);
    bool   moveRobots();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
};
*/
/*
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};
*/
///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////
/*
Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = INITIAL_ROBOT_HEALTH;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

void Robot::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
      case UP:     if (m_row > 1)               m_row--; break;
      case DOWN:   if (m_row < m_arena->rows()) m_row++; break;
      case LEFT:   if (m_col > 1)               m_col--; break;
      case RIGHT:  if (m_col < m_arena->cols()) m_col++; break;
    }
}

bool Robot::takeDamageAndLive()  // return true if not yet dead
{
    if (m_health > 0)
        m_health--;
    return m_health > 0;
}
*/
///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////
/*
Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;
}

string Player::takeComputerChosenTurn()
{
      // How dangerous is it to stand?
    int standDanger = computeDanger(m_row, m_col);

      // if it's not safe, see if moving is safer
    if (standDanger > 0)
    {
        int bestMoveDanger = standDanger;
        int bestMoveDir = UP;  // arbitrary initialization

          // check the four directions to see if any move is
          // better than standing, and if so, record the best
        if (m_row > 1)
        {
            int d = computeDanger(m_row-1, m_col);
            if (d < bestMoveDanger)
            {
                bestMoveDanger = d;
                bestMoveDir = UP;
            }
        }
        if (m_row < m_arena->rows())
        {
            int d = computeDanger(m_row+1, m_col);
            if (d < bestMoveDanger)
            {
                bestMoveDanger = d;
                bestMoveDir = DOWN;
            }
        }
        if (m_col > 1)
        {
            int d = computeDanger(m_row, m_col-1);
            if (d < bestMoveDanger)
            {
                bestMoveDanger = d;
                bestMoveDir = LEFT;
            }
        }
        if (m_col < m_arena->cols())
        {
            int d = computeDanger(m_row, m_col+1);
            if (d < bestMoveDanger)
            {
                bestMoveDanger = d;
                bestMoveDir = RIGHT;
            }
        }

          // if moving is better, move
        if (bestMoveDanger < standDanger)
        {
            move(bestMoveDir);
            return "Moved.";
        }
    }

      // If we're not going to move, we may as well shoot at the nearest
      // robot.  Search the four directions at increasing distances for
      // a robot.
    bool shot = false;
    bool shotSuccess;
    for (int k = 1; k < m_arena->rows() || k < m_arena->cols(); k++)
    {
        if (m_row-k >= 1  &&  m_arena->nRobotsAt(m_row-k, m_col) > 0)
        {
            shotSuccess = shoot(UP);
            shot = true;
            break;
        }
        if (m_row+k <= m_arena->rows()  &&  m_arena->nRobotsAt(m_row+k, m_col) > 0)
        {
            shotSuccess = shoot(DOWN);
            shot = true;
            break;
        }
        if (m_col-k >= 1  &&  m_arena->nRobotsAt(m_row, m_col-k) > 0)
        {
            shotSuccess = shoot(LEFT);
            shot = true;
            break;
        }
        if (m_col+k <= m_arena->cols()  &&  m_arena->nRobotsAt(m_row, m_col+k) > 0)
        {
            shotSuccess = shoot(RIGHT);
            shot = true;
            break;
        }
    }
    if (shot)
    {
        if (shotSuccess)
            return "Shot and hit!";
        else
            return "Shot and missed!";
    }

      // No robots to shoot.  Just stand, then.
    stand();
    return "Stood.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
      case UP:     if (m_row > 1)               m_row--; break;
      case DOWN:   if (m_row < m_arena->rows()) m_row++; break;
      case LEFT:   if (m_col > 1)               m_col--; break;
      case RIGHT:  if (m_col < m_arena->cols()) m_col++; break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 == 0)  // miss with 1/3 probability
        return false;

      // determine row and column delta for the direction
    int rDelta = 0;
    int cDelta = 0;
    switch (dir)
    {
      case UP:     rDelta = -1; break;
      case DOWN:   rDelta = +1; break;
      case LEFT:   cDelta = -1; break;
      case RIGHT:  cDelta = +1; break;
      default:     return false;  // Bad direction!
    }

      // check along the direction until we find a robot
      // or encounter the edge
    int r = row();
    int c = col();
    int distance = 0;
    do
    {
        if (m_arena->nRobotsAt(r, c) > 0)
        {
            m_arena->damageRobotAt(r, c);  // The shot damages one robot
            return true;
        }
        r += rDelta;
        c += cDelta;
        distance++;
    } while (r >= 1  &&  r <= m_arena->rows()  &&
             c >= 1  &&  c <= m_arena->cols()  && distance <= MAXSHOTLEN);
    return false;
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

int Player::computeDanger(int r, int c) const
{
      // danger is the number of robots who might move to
      // position r,c.  Notice that if r,c is at an edge,
      // then a robot at that position is dangerous,
      // because it might not be able to move off that spot
      // at its turn.

    int danger = 0;

    if (r > 1)
        danger += m_arena->nRobotsAt(r-1, c);
    else
        danger += m_arena->nRobotsAt(r,c);

    if (r < m_arena->rows())
        danger += m_arena->nRobotsAt(r+1, c);
    else
        danger += m_arena->nRobotsAt(r,c);

    if (c > 1)
        danger += m_arena->nRobotsAt(r, c-1);
    else
        danger += m_arena->nRobotsAt(r,c);

    if (c < m_arena->cols())
        danger += m_arena->nRobotsAt(r, c+1);
    else
        danger += m_arena->nRobotsAt(r,c);

    return danger;
}
*/
/*
///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRobots = 0;
}

Arena::~Arena()
{
    for (int k = 0; k < m_nRobots; k++)
        delete m_robots[k];
    delete m_player;
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nRobots; k++)
    {
        const Robot* rp = m_robots[k];
        if (rp->row() == r  &&  rp->col() == c)
            count++;
    }
    return count;
}

void Arena::display(string msg) const
{
      // Position (row,col) in the arena coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each robot's position
    for (int k = 0; k < m_nRobots; k++)
    {
        const Robot* rp = m_robots[k];
        char& gridChar = grid[rp->row()-1][rp->col()-1];
        switch (gridChar)
        {
          case '.':  gridChar = 'R'; break;
          case 'R':  gridChar = '2'; break;
          case '9':  break;
          default:   gridChar++; break;  // '2' through '8'
        }
    }

        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a robot there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
      // Dynamically allocate a new Robot and add it to the arena
    if (m_nRobots == MAXROBOTS)
        return false;
    m_robots[m_nRobots] = new Robot(this, r, c);
    m_nRobots++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::damageRobotAt(int r, int c)
{
    int k = 0;
    for ( ; k < m_nRobots; k++)
    {
        if (m_robots[k]->row() == r  &&  m_robots[k]->col() == c)
            break;
    }
    if (k < m_nRobots  &&  ! m_robots[k]->takeDamageAndLive())  // robot dies
    {
        delete m_robots[k];
        m_robots[k] = m_robots[m_nRobots-1];
        m_nRobots--;
    }
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++)
    {
        Robot* rp = m_robots[k];
        rp->move();
        if (rp->row() == m_player->row()  &&  rp->col() == m_player->col())
            m_player->setDead();
    }

      // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}
*/

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////
/*
Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots > MAXROBOTS)
    {
        cout << "***** Trying to create Game with " << nRobots
             << " robots; only " << MAXROBOTS << " are allowed!" << endl;
        exit(1);
    }

        // Create arena
    m_arena = new Arena(rows, cols);

        // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
          // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display("");
        return;
    }
    string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c/q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'c':  // computer moves player
                msg = p->takeComputerChosenTurn();
                break;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
              case 's':
                if (action.size() < 2)  // if no direction, nobody moves
                {
                    cout << '\a' << endl;  // beep
                    continue;
                }
                switch (action[1])
                {
                  default:   // if bad direction, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                  case 'u':
                  case 'd':
                  case 'l':
                  case 'r':
                    if (p->shoot(decodeDirection(action[1])))
                        msg = "Hit!";
                    else
                        msg = "Missed!";
                    break;
                }
                break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}
*/
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////
/*
int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}
*/
///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(3, 3, 2);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.
/*
#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
*/
