//
//  Game.h
//

#ifndef GAME_H
#define GAME_H

#include "Side.h"
class Board;
class Player;

class Game {
  public:
    Game(const Board& b, Player* south, Player* north);
    ~Game();
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
    
  private:
    Board*  board_;
    Player* south_; // Player 1
    Player* north_; // Player 2
};

#endif
