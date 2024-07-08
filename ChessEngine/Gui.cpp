#include "Gui.h"
#include <iostream>

Gui::Gui(){}

void Gui::displayBoard(Board &board){
    int intIndex = -1;
    std::cout << "------------------\n";
    for (int i = 0; i < 8; i++) {
        std::cout << "|";
        for (int j = 0; j < 8; j++){
            std::cout << "|";
            for (char chars : board.getChars()){
                if(board.getBitboard(chars) & (1<<intIndex)){
                    std::cout << chars;
                    break;
                }
            }


            intIndex += 1;
        }
        std::cout << "|\n------------------" << std::endl;
    }
}

void Gui::getUserMove(int &startX, int &startY, int &endX, int &endY){};
