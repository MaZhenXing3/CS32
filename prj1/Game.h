//
//  Game.h
//  zion
//
//  Created by 李心怡 on 7/2/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Arena;
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

#endif /* Game_h */

