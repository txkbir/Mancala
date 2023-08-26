//
//  Board.h
//

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Side.h"

class Board {
  public:
    Board(int nHoles, int nInitialBeansPerHole);
    
    inline
    int holes() const { return holes_; }
    
    inline
    int beans(Side s, int hole) const {
        if (hole < POT  ||  hole > holes_) return -1;
        return board_[s][hole];
    }
    
    inline
    int beansInPlay(Side s) const {
        int numBeans = 0;
        for (int i = 1; i <= holes_; ++i)
            numBeans += beans(s, i);
        return numBeans;
    }
    
    inline
    int totalBeans() const { return beansInPlay(NORTH) + beansInPlay(SOUTH) + board_[NORTH][POT] + board_[SOUTH][POT]; }
    
    inline
    bool moveToPot(Side s, int hole, Side potOwner) {
        if (hole <= POT  ||  hole > holes_) return false;
        board_[potOwner][POT] += beans(s, hole);
        board_[s][hole] = 0;
        return true;
    }
    
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool setBeans(Side s, int hole, int beans);
    
  private:
    int holes_;
    std::vector<std::vector<int>> board_;
};

#endif
