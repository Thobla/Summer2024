#include "Gui.h"
#include <string>
#include <vector>
#include <iostream>

Gui::Gui(){}

void Gui::displayBoard(Board &board){
    int intIndex = 0;
    std::vector<std::string> drawing;
    std::string currString;

    //std::cout << "------------------\n";
    for (int i = 0; i < 8; i++) {
        currString = "";
        currString += '|';
        for (int j = 0; j < 8; j++){
            for (char chars : board.getChars()){
                if(*(board.getBitboard(chars)) & (1LL<<intIndex)){
                    currString += chars;
                    intIndex += 1;
                    break;
                }
            }
            currString += '|';
        }
        drawing.push_back(currString);
    }
    for (int i = 7; i >= 0; i--) {
        std::cout << drawing[i] << "\n";
    }
    std::cout << std::endl;
}

void Gui::getUserMove(int &startX, int &startY, int &endX, int &endY, int currPlayer){
    if (!currPlayer) std::cout << "White's turn \n";
    else std::cout << "Black's turn \n";
    std::cout << "Type values for startX, startY, endX and endY, on the form: 'x y x y'";
    std::cin >> startX >> startY >> endX >> endY;
};

void Gui::makeMove(Board &board, Judge &judge, int currPlayer){
    int startX, startY, endX, endY;
    getUserMove(startX, startY, endX, endY, currPlayer);
    board.makeMove(startX, startY, endX, endY, judge, currPlayer);

};




