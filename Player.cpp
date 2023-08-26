//
//  Player.cpp
//

#include <string>
#include <vector>
#include <iostream>
#include "Side.h"
#include "Board.h"
#include "Player.h"
using std::string, std::cin, std::cout, std::cerr, std::endl, std::vector, std::max, std::min;
const int DEPTH = 9;      // SET DEPTH HERE
                          // g32fast allows a max depth of 9

Player::Player(string name) : name_(name) {}
bool Player::isInteractive() const { return false; };
Player::~Player() {}


HumanPlayer::HumanPlayer(string name) : Player(name) {}
bool HumanPlayer::isInteractive() const { return true; }
int HumanPlayer::chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == 0) return -1;
    unsigned int hole;
    cout << "Select a hole, " << this->name() << ": ";
    cin >> hole;
    while (hole < 1  ||  hole > b.holes()) {
        cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        cout << "Select a hole, " << this->name() << ": ";
        cin >> hole;
    }
    while (b.beans(s, hole) == 0) {
        cout << "There are no beans in that hole." << endl;
        cout << "Select a hole, " << this->name() << ": ";
        cin >> hole;
    }
    return hole;
}
HumanPlayer::~HumanPlayer() {}


BadPlayer::BadPlayer(string name) : Player(name) {}
int BadPlayer::chooseMove(const Board& b, Side s) const {
    if (b.beansInPlay(s) == 0) return -1;
    int hole = 1;
    for (int i = 1; i <= b.holes(); ++i)
        if (b.beans(s, i) != 0) {
            hole = i;
            break;
        }
    return hole;
}
BadPlayer::~BadPlayer() {}


SmartPlayer::SmartPlayer(string name) : Player(name) {}
int SmartPlayer::chooseMove(const Board& b, Side s) const {
    Timer timer;
    timer.start();
    int best_hole, val;
    int alpha = NEG_INF; int beta = INF;
    minimax(s, b, best_hole, val, DEPTH, alpha, beta);
    cerr << timer.elapsed() << " ms" << endl;
    return best_hole;
}

void SmartPlayer::minimax(Side player, const Board& b, int& bestHole, int& eval, int depth, int alpha, int beta) const {
    if (b.beansInPlay(player) == 0) {
        bestHole = -1;
        eval = evaluate(b); //inf, -inf, 0
        return;
    }
    if (depth == 0) {
        bestHole = -1;
        eval = evaluate(b);
        return;
    }
    
    if (player == SOUTH)
        eval = NEG_INF;
    else
        eval = INF;
    
    vector<int> validHoles = getValidHoles(b, player);
    
    bool foundMove = false;
    
    for (int i = 0; i < validHoles.size(); ++i) {
        int hole = validHoles[i];
        Side endSide;
        int  endHole;
        
        vector<Board> validBoards;
        findAllBoards(b, player, hole, endSide, endHole, validBoards);
        
        for (int k = 0; k < validBoards.size(); ++k) {
            const Board& newBoard = validBoards[k];
            int tempHole, tempEval;
            minimax(opponent(player), newBoard, tempHole, tempEval, depth - 1, alpha, beta);
            
             // if the function call at the bottom of the stack
             // returns false for this if-condition, then bestHole
             // will be uninitialized and a garbage value is returned
            if ((player == SOUTH && tempEval > eval) || (player == NORTH && tempEval < eval)) {
                eval = tempEval;
                bestHole = hole;
                foundMove = true;
            }
            
            // Alpha-beta pruning
            if (player == SOUTH) {
                alpha = max(alpha, eval);
                if (alpha >= beta) return;
            } else {
                beta = min(beta, eval);
                if (beta <= alpha) return;
            }
        }
        
    }
  if (!foundMove) bestHole = validHoles[0];
}
 
int SmartPlayer::evaluate(const Board& b) const {
    if (b.beans(SOUTH, POT) > b.totalBeans() / 2) return INF;
    else if (b.beans(NORTH, POT) > b.totalBeans() / 2) return NEG_INF;
    return b.beans(SOUTH, POT) - b.beans(NORTH, POT);
}

 // return an array of Boards holding every possible Board combination for the Player's current turn
void SmartPlayer::findAllBoards(const Board& b, Side player, int hole, Side& endSide, int& endHole, vector<Board>& boards) const {
    Board board_copy = b;
    board_copy.sow(player, hole, endSide, endHole);
    
    if (endHole != POT && endSide == player && board_copy.beans(player, endHole) == 1 && board_copy.beans(opponent(player), endHole) > 0) {
        board_copy.moveToPot(player, endHole, player);
        board_copy.moveToPot(opponent(player), endHole, player);
        boards.push_back(board_copy);
        return;
    }
    
   if (! (endSide == player && endHole == POT && board_copy.beansInPlay(player) > 0) ) {
       boards.push_back(board_copy);
       return;
   }
    
     // recursive case to keep testing more holes if Player gets to make another turn
    vector<int> validHoles = getValidHoles(board_copy, player);
    for (int k = 0; k < validHoles.size(); ++k)
        findAllBoards(board_copy, player, validHoles[k], endSide, endHole, boards);
    
    // make the move on hole
    // if it's not my turn
    //  append the current board to vector: boards -> return;
    // if i capture (thus surrenduring my turn)
    //  make capture -> append board to vector: boards -> return;
    // find all valid holes with the current state of the new board
    // iterate over all valid holes of the new board
    // find all boards on each hole using findAllBoards
}
SmartPlayer::~SmartPlayer() {}
