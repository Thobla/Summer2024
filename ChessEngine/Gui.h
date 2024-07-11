#ifndef GUI_H
#define GUI_H
#include "Board.h"
#include "Judge.h"

class Gui {
    public:
        Gui();
        void displayBoard(Board &board);
        void getUserMove(int &startX, int &startY, int &endX, int &endY);
        void makeMove(Board &board, Judge &judge);

};


#endif // GUI_H
