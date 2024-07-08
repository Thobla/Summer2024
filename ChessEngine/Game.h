#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Judge.h"
#include "Gui.h"

class Game {
    public:
        Game();
        void startGame();
        void swapPlayer();
        void play();

    private:
        Board board;
        Judge judge;
        Gui gui;
        int currPlayer;
};

#endif // GAME_H
