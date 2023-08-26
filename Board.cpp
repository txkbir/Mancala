//
//  Board.cpp
//

#include "Side.h"
#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole) : holes_(nHoles) {
    if (holes_ < 0) holes_ = 1;
    if (nInitialBeansPerHole < 0) nInitialBeansPerHole = 0;
    board_.resize(NSIDES, std::vector<int>(holes_ + 1, nInitialBeansPerHole));
    board_[NORTH][POT] = POT;
    board_[SOUTH][POT] = POT;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
    if (hole <= POT  ||  hole > holes_  ||  board_[s][hole] == 0) return false;
    int beans = board_[s][hole];
    board_[s][hole] = 0;
    while (beans > 0) {
    if (s == NORTH) {
        for (int i = hole - 1; i >= POT; --i) {
            board_[NORTH][i]++;
            endSide = NORTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
        if (beans == 0) break;
        for (int i = 1; i <= holes_; ++i) {
            board_[SOUTH][i]++;
            endSide = SOUTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
        if (beans == 0) break;
        for (int i = holes_; i >= hole; --i) {
            board_[NORTH][i]++;
            endSide = NORTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
    } else {
        for (int i = hole + 1; i <= holes_ + 1; ++i) {
            if (i > holes_) {
                board_[SOUTH][POT]++;
                endSide = SOUTH;
                endHole = POT;
                --beans;
                break;
            }
            board_[SOUTH][i]++;
            endSide = SOUTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
        if (beans == 0) break;
        for (int i = holes_; i > POT; --i) {
            board_[NORTH][i]++;
            endSide = NORTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
        if (beans == 0) break;
        for (int i = 1; i <= hole; ++i) {
            board_[SOUTH][i]++;
            endSide = SOUTH;
            endHole = i;
            --beans;
            if (beans == 0) break;
        }
    }
}
    return true;
}

bool Board::setBeans(Side s, int hole, int beans) {
    if (hole < POT  ||  hole > holes_  ||  beans < 0) return false;
    board_[s][hole] = beans;
    return true;
}

