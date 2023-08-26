//
//  Game.cpp
//

#include <iostream>
#include <string>
#include "Side.h"
#include "Board.h"
#include "Player.h"
#include "Game.h"
using std::string, std::cin, std::cout, std::endl;

                            // Player 1    // Player 2
Game::Game(const Board& b, Player* south, Player* north)
: board_(new Board(b)), south_(south), north_(north) {}

Game::~Game() { delete board_; }

void Game::display() const {
    cout << string(1.7 * board_->holes(), ' ') << north_->name() << endl;
    for (int i = 1; i <= board_->holes(); ++i)
        cout << "   " << board_->beans(NORTH, i);
    cout << endl;
    cout << board_->beans(NORTH, POT) << string(4.3 * board_->holes(), ' ') << board_->beans(SOUTH, POT) << endl;
    for (int i = 1; i <= board_->holes(); ++i)
        cout << "   " << board_->beans(SOUTH, i);
    cout << endl;
    cout << string(1.7 * board_->holes(), ' ') << south_->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
    over = false;
    hasWinner = false;
    
    if (board_->beansInPlay(NORTH) == 0  &&  board_->beansInPlay(SOUTH) == 0) {
        if (board_->beans(SOUTH, POT) > board_->beans(NORTH, POT)) {
            winner = SOUTH;
            hasWinner = true;
        } else if (board_->beans(SOUTH, POT) < board_->beans(NORTH, POT)) {
            winner = NORTH;
            hasWinner = true;
        } else
            hasWinner = false;
        over = true;
    }
}

bool Game::move(Side s) {
    int hole;
    
     // decide whose move it is
    if (s == NORTH)
        hole = north_->chooseMove(*board_, s);
    else
        hole = south_->chooseMove(*board_, s);
    

     // if player has no moves left
    if (hole == -1) {
        
         // check if opponent has beans to sweep
        if (board_->beansInPlay(opponent(s)) != 0) {
            if (s == NORTH) {
                cout << north_->name() << " has no beans left to sow." << endl;
                cout << "Sweeping remaining beans into " << south_->name() << "'s pot." << endl;
            }
            else {
                cout << south_->name() << " has no beans left to sow." << endl;
                cout << "Sweeping remaining beans into " << north_->name() << "'s pot." << endl;
            }
             // sweep
            for (int i = 1; i <= board_->holes(); ++i)
                board_->moveToPot(opponent(s), i, opponent(s));
            display();
        }
         // move could not be completed
        return false;
    }
    
    
    Side end_side;
    int  end_hole;
     // make move
    board_->sow(s, hole, end_side, end_hole);
    
    
     // if player is an NPC state their move
    if ( (s == NORTH && !north_->isInteractive())  ||  (s == SOUTH && !south_->isInteractive()) ) {
        if (s == NORTH)
            cout << north_->name() << " chooses hole " << hole << endl;
        else
            cout << south_->name() << " chooses hole " << hole << endl;
    }
    
    
     // capturing mechanism
    if (end_hole != POT && end_side == s && board_->beans(s, end_hole) == 1 && board_->beans(opponent(s), end_hole) > 0) {
        board_->moveToPot(s, end_hole, s);
        board_->moveToPot(opponent(s), end_hole, s);
        return true;
    }
    
     // take another turn
    if (end_side == s && end_hole == POT && board_->beansInPlay(s) > 0) {
        display();
        if (s == NORTH)
            cout << north_->name() << " gets another turn." << endl;
        else
            cout << south_->name() << " gets another turn." << endl;
        move(s);
    }

     // in case a player makes their very last turn and the game is essentially over when opponent makes their move
    if (end_side == s && end_hole == POT && board_->beansInPlay(s) == 0) {
         // check if it's possible for opponent to potentially elongate the game
        if (opponent(s) == NORTH) {
          for (int hole = 1; hole <= board_->holes(); ++hole)
              if (beans(opponent(s), hole) >= hole) {
                  display();
                  break;
              }
        } else {
          for (int hole = 1; hole <= board_->holes(); ++hole)
              if (beans(opponent(s), hole) >= (board_->holes() - hole + 1)) {
                  display();
                  break;
              }
        }
         // this case is reached if the opponent cannot possibly elongate the game
        display();
        for (int i = 1; i <= board_->holes(); ++i)
            board_->moveToPot(opponent(s), i, opponent(s));
        if (s == NORTH) {
            cout << north_->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << south_->name() << "'s pot." << endl;
        }
        else {
            cout << south_->name() << " has no beans left to sow." << endl;
            cout << "Sweeping remaining beans into " << north_->name() << "'s pot." << endl;
        }
    }
    return true;
}
 
void Game::play() {
    display();
    bool is_over, has_winner;
    bool trueMoveSouth, trueMoveNorth;
    Side winner;
    while (true) {
        trueMoveSouth = move(SOUTH);
        if (trueMoveSouth)
            display();
        
        trueMoveNorth = move(NORTH);
        if (trueMoveNorth)
            display();
        
        status(is_over, has_winner, winner);
        if (is_over) break;
        
        if (!south_->isInteractive() && !north_->isInteractive()) {
            cout << "Press ENTER to continue.";
            cin.ignore();
        }
    }
    if (winner == NORTH)
        cout << "The winner is " << north_->name() << "!" << endl;
    else if (winner == SOUTH)
        cout << "The winner is " << south_->name() << "!" << endl;
    else
        cout << "It's a tie!" << endl;
}

int Game::beans(Side s, int hole) const { return board_->beans(s, hole); }
