#ifndef GUI_H
#define GUI_H
#include "Board.h"
#include "Judge.h"

class Gui {
    public:
        Gui();
        void displayBoard(Board &board);
        void getUserMove(int &startX, int &startY, int &endX, int &endY, int currPlayer);
        void makeMove(Board &board, Judge &judge, int currPlayer);

};


#endif // GUI_H
