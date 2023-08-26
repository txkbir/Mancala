#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests() {
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3, 0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
      //    Homer
      //   0  1  2
      // 0         0
      //   2  0  0
      //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
    g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   0  1  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(NORTH);
      //   1  0  0
      // 0         3
      //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

    g.move(SOUTH);
      //   1  0  0
      // 0         3
      //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
    g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

    g.move(NORTH);
      //   0  0  0
      // 1         4
      //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
    g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
    g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

void doPlayerTests() {
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3, 2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
}

void doBoardTests() {
    Board b(3, 2);
    assert(b.holes() == 3  &&  b.totalBeans() == 12  &&
                    b.beans(SOUTH, POT) == 0  &&  b.beansInPlay(SOUTH) == 6);
    b.setBeans(SOUTH, 1, 1);
    b.moveToPot(SOUTH, 2, SOUTH);
    assert(b.totalBeans() == 11  &&  b.beans(SOUTH, 1) == 1  &&
                b.beans(SOUTH, 2) == 0  &&  b.beans(SOUTH, POT) == 2  &&
        b.beansInPlay(SOUTH) == 3);
    Side es;
    int eh;
    b.sow(SOUTH, 3, es, eh);
    assert(es == NORTH  &&  eh == 3  &&  b.beans(SOUTH, 3) == 0  &&
                b.beans(NORTH, 3) == 3  &&  b.beans(SOUTH, POT) == 3  &&
        b.beansInPlay(SOUTH) == 1  &&  b.beansInPlay(NORTH) == 7);
}

void playGame() {
    HumanPlayer Player1("Takbir");
    SmartPlayer Player2("Mike");
    Board b1(6, 4);
    Board b2(6, 0);
    b2.setBeans(NORTH, POT, 3);
    b2.setBeans(SOUTH, 3, 1);
    Board b3(3, 0);
    b3.setBeans(NORTH, POT, 4);
    b3.setBeans(SOUTH, POT, 3);
    b3.setBeans(NORTH, 2, 1);
    b3.setBeans(NORTH, 1, 1);
    b3.setBeans(SOUTH, 1, 2);
    b3.setBeans(SOUTH, 2, 1);
    Board b4(3, 0);
    b4.setBeans(NORTH, POT, 4);
    b4.setBeans(SOUTH, POT, 6);
    b4.setBeans(NORTH, 1, 2);
    Board b5(4, POT);
    b5.setBeans(NORTH, 1, 3);
    b5.setBeans(NORTH, 3, 1);
    b5.setBeans(SOUTH, 1, 3);
    b5.setBeans(SOUTH, 2, 1);
    Board b6(6, 0);
    b6.setBeans(NORTH, 5, 2);
    b6.setBeans(NORTH, 1, 1);
    b6.setBeans(SOUTH, 4, 1);
    b6.setBeans(SOUTH, 5, 2);
    Game Kalah(b1, &Player1, &Player2);
    Kalah.play();
}

void doTest1() {
        Board board(3, 2);
    
            // Test holes() function
            assert(board.holes() == 3);
    
            // Test beans() function
            assert(board.beans(NORTH, 1) == 2);
            assert(board.beans(SOUTH, 2) == 2);
            assert(board.beans(SOUTH, 4) == -1);  // Invalid hole
    
            // Test beansInPlay() function
            assert(board.beansInPlay(NORTH) == 6);
            assert(board.beansInPlay(SOUTH) == 6);
    
            // Test totalBeans() function
            assert(board.totalBeans() == 12);
    
            // Test setBeans() function
            assert(board.setBeans(NORTH, 1, 3) == true);
            assert(board.beans(NORTH, 1) == 3);
    
            // Test sow() function
            Side endSide;
            int endHole;
            assert(board.sow(NORTH, 1, endSide, endHole) == true);
            assert(endSide == SOUTH);
            assert(endHole == 2);
            assert(board.beans(NORTH, 1) == 0);
            assert(board.beans(SOUTH, 2) == 3);
        // Test HumanPlayer
            HumanPlayer human("Alice");
            assert(human.name() == "Alice");
            assert(human.isInteractive() == true);
    
            // Test BadPlayer
            BadPlayer bad("Bob");
            assert(bad.name() == "Bob");
            assert(bad.isInteractive() == false);
    
            // Test SmartPlayer (implementation-specific tests)
            SmartPlayer smart("Charlie");
            assert(smart.name() == "Charlie");
            assert(smart.isInteractive() == false);
            // Test chooseMove() function - tested inside the other commented scenarios / mains
    
        // Create players
        HumanPlayer Newhuman("Alice");
        BadPlayer Newbad("Bob");
    
        // Create board
        Board Newboard(3, 2);
    
        // Test Game constructor
        Game game(board, &Newhuman, &Newbad);
        game.display();
    
        // move functions - tested inside the other commented scenarios / mains
    
        // Test status() function - tested inside other commented scenarios / mains
}

void testForBoard() {
    Board b(6, 4);
     // prove the Board was properly set up
    assert(b.holes() == 6 && b.totalBeans() == 48 && b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 24);
     // prove the Board properly swept one specific hole
    b.moveToPot(SOUTH, 3, SOUTH);
    assert(b.beans(SOUTH, POT) == 4);
    b.setBeans(SOUTH, POT, 0);
    b.setBeans(SOUTH, 3, 4);
    assert(b.beans(SOUTH, POT) == 0 && b.beans(SOUTH, 3) == 4);
    
     // to prove the Board sows properly (doesn't make captures an extra turns, simply just makes moves)
    Side endingSide;
    int  endingHole;
    b.sow(SOUTH, 6, endingSide, endingHole);
    assert(endingSide != SOUTH && endingHole != 6);
    assert(b.beans(SOUTH, POT) == 1);
    assert(b.beans(NORTH, 6) == 5 && b.beans(NORTH, 5) == 5 && b.beans(NORTH, 4) == 5);
    assert(b.beans(NORTH, 3) != 5 && b.beans(NORTH, 3) == 4);
    b.sow(SOUTH, 3, endingSide, endingHole);
    assert(endingSide == SOUTH && endingHole == POT);
    
     // invalid arguments
    assert(b.beans(SOUTH, 7) == -1);
    assert(!b.sow(SOUTH, 7, endingSide, endingHole));
}

void testForPlayer() {
     // compiler error because Player is an ABC
    // Player ABC;
    
    HumanPlayer victor("Victor");
    BadPlayer noah("Noah");
    SmartPlayer mike("Mike");
    
    assert(victor.name() == "Victor" && noah.name() == "Noah" && mike.name() == "Mike");
    assert(!noah.isInteractive() && !mike.isInteractive());
    assert(victor.isInteractive());
    
    Board miniboard(3, 2);
    Board board(6, 4);
    
     // BadPlayer always chooses the first legal move
    assert(noah.chooseMove(board, SOUTH) == 1);
    assert(noah.chooseMove(miniboard, SOUTH) == 1);
    // The first move for SmartPlayer is ALWAYS the
    // turn that results in its extra turn
    assert(mike.chooseMove(board, NORTH) == 4);
    assert(mike.chooseMove(miniboard, SOUTH) == 2);
    
    Board victorBoard(3, 2);
    victorBoard.setBeans(SOUTH, 1, 0);
    int x = victor.chooseMove(victorBoard, SOUTH);
    assert(x == 2 || x == 3);
}

void testForGame() {
    BadPlayer* bp1 = new BadPlayer("Mike");
    BadPlayer* bp2 = new BadPlayer("Noah");
    Board b1(3, 2);
    //   2  2  2
    // 0         0
    //   2  2  2
    Game kalah(b1, bp1, bp2);
    
    assert(kalah.beans(SOUTH, POT) == 0 && kalah.beans(NORTH, POT) == 0);
    bool over = true, hasWinner = true;
    Side winner;
    kalah.status(over, hasWinner, winner);
    assert(!over && !hasWinner);
    
    kalah.move(SOUTH);
    //   2  2  2
    // 0         0
    //   0  3  3
    assert(kalah.beans(SOUTH, 2) == 3 && kalah.beans(SOUTH, 3) == 3);
    
    kalah.move(NORTH);
    //   0  2  2
    // 1         0
    //   1  3  3
    assert(kalah.beans(NORTH, POT) == 1 && kalah.beans(NORTH, POT) > kalah.beans(SOUTH, POT));

    kalah.move(NORTH);
    //   0  1  0
    // 5         0
    //   0  3  3
    assert(kalah.beans(NORTH, POT) == 5 && kalah.beans(NORTH, 1) == 0 && kalah.beans(NORTH, 2) == 1);
    
    kalah.move(SOUTH);
    //   0  1  1
    // 5         1
    //   0  0  4
    assert(kalah.beans(SOUTH, 3) == 4);
    assert(kalah.beans(SOUTH, POT) == 1);
    assert(kalah.beans(NORTH, POT) == 5);
    
    kalah.move(SOUTH);
    //   1  2  2
    // 5         2
    //   0  0  0
    for (int i = 1; i <= 3; ++i)
        assert(kalah.beans(SOUTH, i) == 0);
    assert(kalah.beans(SOUTH, POT) == 2);
    
    kalah.move(SOUTH);
    //   1  1  0
    // 8         2
    //   0  0  0
    kalah.status(over, hasWinner, winner);
    assert(over && hasWinner);
    assert(kalah.beans(NORTH, POT) == 10 && winner == NORTH);
    
    delete bp1;
    delete bp2;
}

int main() { playGame(); }
