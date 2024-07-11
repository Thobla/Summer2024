/*         bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY);
        std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);

 */
#include "Judge.h"
#include "Board.h"
#include <iostream>

class Board;

bool Judge::isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char pieceType){
    if(pieceType == 'p'){
        if(!wPawnRule(board, startX, startY, endX, endY)){return false;};

    }
    return true;
}

bool Judge::wPawnRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    if(endY == startY+1){
        std::cout << "endY == startY+1 \n";
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        if((startX == endX+1 || startX == endX-1) && (board.blackSquares & endSquare)){return true;};
        std::cout << "not allowed \n";
    }
    else if(endY == 3 && startY == 1){
        std::cout << "endY == startY+2 == 3 \n";
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        std::cout << "not allowed \n";
    };
    std::cout << "neither \n";
    return false;
};

bool Judge::pathCleared(Board &board, int startX, int startY, int endX, int endY){
    int currX = startX;
    int currY = startY;
    unsigned long long currSquare;
    while(currX != endX || currY != endY){
        if(currX < endX){currX += 1;}
        else if(currX > endX){currX -= 1;};
        if(currY < endY){currY += 1;}
        else if(currY > endY){currY -= 1;};
        
        currSquare = 1ull << (currX + 8*currY);
        if((board.occupiedSquares & currSquare) == currSquare){return false;};
    }

    return true;
};










