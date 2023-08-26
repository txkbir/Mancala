//
//  Player.h
//

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Side.h"
#include "Board.h"
using std::string, std::vector;


class Player {
  public:
    Player(string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
    
    inline
    string name() const { return name_; }

  private:
    string name_;
};

class HumanPlayer : public Player {
  public:
    HumanPlayer(string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

class BadPlayer : public Player {
  public:
    BadPlayer(string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

class SmartPlayer : public Player {
  public:
    SmartPlayer(string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
    
  private:
    void minimax(Side player, const Board& b, int& bestHole, int& eval, int depth, int alpha, int beta) const;
    int evaluate(const Board& b) const;
    
    // create an array of valid holes a player can make with the current Board
    void findAllBoards(const Board& b, Side player, int hole, Side& endSide, int& endHole, vector<Board>& boards) const;
    inline vector<int> getValidHoles(const Board& b, Side s) const {
        vector<int> holes;
        for (int hole = 1; hole <= b.holes(); ++hole)
            if (b.beans(s, hole) != 0)
               holes.push_back(hole);
        return holes;
    }
};

#endif
