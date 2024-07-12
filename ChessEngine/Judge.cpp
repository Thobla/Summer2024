/*         bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY);
        std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);

 */
#include "Judge.h"
#include "Board.h"
#include <iostream>
#include <math.h>

class Board;

bool Judge::isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char pieceType){
    if(pieceType == 'p'){
        if(!wPawnRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'P'){
        if(!bPawnRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'h'){
        if(!wPonyRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'H'){
        if(!bPonyRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'b'){
        if(!wBishopRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'B'){
        if(!bBishopRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'q'){
        if(!wQueenRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'Q'){
        if(!bQueenRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'k'){
        if(!wKingRule(board, startX, startY, endX, endY)){return false;};
    }
    else if(pieceType == 'K'){
        if(!bKingRule(board, startX, startY, endX, endY)){return false;};
    }




    return true;
}

bool Judge::bPawnRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    if(endY == startY-1){
        std::cout << "endY == startY-1 \n";
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        if((startX == endX+1 || startX == endX-1) && (board.whiteSquares & endSquare)){return true;};
        std::cout << "not allowed \n";
    }
    else if(endY == 4 && startY == 6){
        std::cout << "endY == startY-2 == 3 \n";
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        std::cout << "not allowed \n";
    };
    std::cout << "neither \n";
    return false;
};


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

bool Judge::wPonyRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool longY = (endX == startX + 1 || endX == startX - 1) && (endY == startY + 2 || endY == startY - 2);
    bool longX = (endY == startY + 1 || endY == startY - 1) && (endX == startX + 2 || endX == startX - 2);
    if(longY || longX){
        if(!((endSquare & board.whiteSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::bPonyRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool longY = (endX == startX + 1 || endX == startX - 1) && (endY == startY + 2 || endY == startY - 2);
    bool longX = (endY == startY + 1 || endY == startY - 1) && (endX == startX + 2 || endX == startX - 2);
    if(longY || longX){
        if(!((endSquare & board.blackSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::wBishopRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isDiagonal = std::abs(endY - startY) == std::abs(endX - startX);
    if(isDiagonal && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.whiteSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::bBishopRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isDiagonal = std::abs(endY - startY) == std::abs(endX - startX);
    if(isDiagonal && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.blackSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::wRookRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isLine = (std::abs(endY - startY) == 0 && std::abs(endX - startX) > 0) || (std::abs(endX - startX) == 0 && std::abs(endY - startY) > 0);
    if(isLine && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.whiteSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::bRookRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isLine = (std::abs(endY - startY) == 0 && std::abs(endX - startX) > 0) || (std::abs(endX - startX) == 0 && std::abs(endY - startY) > 0);
    if(isLine && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.blackSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::wQueenRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isLine = (std::abs(endY - startY) == 0 && std::abs(endX - startX) > 0) || (std::abs(endX - startX) == 0 && std::abs(endY - startY) > 0);
    bool isDiagonal = std::abs(endY - startY) == std::abs(endX - startX);
    if((isLine || isDiagonal) && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.whiteSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::bQueenRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool isLine = (std::abs(endY - startY) == 0 && std::abs(endX - startX) > 0) || (std::abs(endX - startX) == 0 && std::abs(endY - startY) > 0);
    bool isDiagonal = std::abs(endY - startY) == std::abs(endX - startX);
    if((isLine || isDiagonal) && pathSemiCleared(board, startX, startY, endX, endY)){
        if(!((endSquare & board.blackSquares) == endSquare)){
            return true;
        }
    }
    return false;
}

bool Judge::wKingRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool distIsOne = std::abs(endX - startX) < 2 && std::abs(endY - startY) < 2 && std::abs(endX - startX) + std::abs(endY - startY) > 0;
    if(!((endSquare & board.whiteSquares) == endSquare)){
        return true;
    }
    return false;
}

bool Judge::bKingRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool distIsOne = std::abs(endX - startX) < 2 && std::abs(endY - startY) < 2 && std::abs(endX - startX) + std::abs(endY - startY) > 0;
    if(!((endSquare & board.blackSquares) == endSquare)){
        return true;
    }
    return false;
}







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

bool Judge::pathSemiCleared(Board &board, int startX, int startY, int endX, int endY){
    int currX = startX;
    int currY = startY;
    unsigned long long currSquare;
    while(1){

        if(currX < endX){currX += 1;}
        else if(currX > endX){currX -= 1;};
        if(currY < endY){currY += 1;}
        else if(currY > endY){currY -= 1;};

        if (currX == endX && currY == endY){break;};
       
        currSquare = 1ull << (currX + 8*currY);
        if((board.occupiedSquares & currSquare) == currSquare){return false;};

 
    }

    return true;
};











