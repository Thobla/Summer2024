#ifndef GUI_H
#define GUI_H
#include "Board.h"

class Gui {
    public:
        Gui();
        void displayBoard(Board &board);
        void getUserMove(int &startX, int &startY, int &endX, int &endY);

};


#endif // GUI_H
