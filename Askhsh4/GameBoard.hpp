#ifndef _GAMEBOARD_HPP_
#define _GAMEBOARD_HPP_

#include <iostream>
#include "DeckBuilder.hpp"
#include "Player.hpp"

using  namespace std;

class GameBoard{
    private:
        DeckBuilder* Deck;
        list<Player*> Players;
    public:
        GameBoard();
        ~GameBoard();
        void initializeGameBoard(); 
        void printGameStatics();
        void gameplay();
        void startingPhase();
        void equipPhase();
        void battlePhase();
        void print(Player*);
        void battle(Player*, Player*);
        void CheckPlayers();
        void economyPhase();
        void endPhase();
        void printPlayers();
        void checkWinningCondition();
        void winningPhase();
    };


#endif