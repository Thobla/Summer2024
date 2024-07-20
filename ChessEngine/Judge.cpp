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

bool Judge::isCheck(Board &board, int color){
    return (color == 0) ? (*board.getBitboard('k') & blackAttackSquares(board)) : (*board.getBitboard('K') & whiteAttackSquares(board));
};

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

long long Judge::whiteAttackSquares(Board &board){
    long long attackSquares = 0;
    char pieceType;

    for (int x = 0; x <= 7; x++) {
        for (int y = 0; y <= 7; y++){
            pieceType = board.getSquareType(x, y);
            switch (pieceType) {
                case ' ' : break;
                case 'p' : attackSquares |= generatePawnAttacks(0, x, y);
                case 'h' : attackSquares |= generatePonyAttacks(x, y);
                case 'b' : attackSquares |= generateBishopAttacks(board, x, y);
                case 'r' : attackSquares |= generateRookAttacks(board, x, y);
                case 'q' : attackSquares |= generateQueenAttacks(board, x, y);
                case 'k' : attackSquares |= generateKingAttacks(x, y);
            }

        }
    }
    return attackSquares;
};

long long Judge::blackAttackSquares(Board &board){
    long long attackSquares = 0;
    char pieceType;

    for (int x = 0; x <= 7; x++) {
        for (int y = 0; y <= 7; y++){
            pieceType = board.getSquareType(x, y);
            switch (pieceType) {
                case ' ' : break;
                case 'P' : attackSquares |= generatePawnAttacks(1, x, y);
                case 'H' : attackSquares |= generatePonyAttacks(x, y);
                case 'B' : attackSquares |= generateBishopAttacks(board, x, y);
                case 'R' : attackSquares |= generateRookAttacks(board, x, y);
                case 'Q' : attackSquares |= generateQueenAttacks(board, x, y);
                case 'K' : attackSquares |= generateKingAttacks(x, y);
            }
        }
    }
    return attackSquares;
};



long long Judge::generatePawnAttacks(int color, int xPos, int yPos){
    long long attackSquares = 0;
    int direction = (color == 0) ? 1 : -1;

    if (xPos > 0) attackSquares |= (1ULL << ((yPos + direction) * 8 + (xPos - 1)));
    if (xPos < 7) attackSquares |= (1ULL << ((yPos + direction) * 8 + (xPos + 1)));
    return attackSquares;
};

long long Judge::generatePonyAttacks(int xPos, int yPos){
    long long attackSquares = 0;

    if (xPos > 1 && yPos > 0) attackSquares |= (1ULL << ((yPos - 1) * 8 + (xPos - 2)));
    if (xPos < 6 && yPos < 7) attackSquares |= (1ULL << ((yPos + 1) * 8 + (xPos + 2)));
    if (xPos > 1 && yPos < 7) attackSquares |= (1ULL << ((yPos + 1) * 8 + (xPos - 2)));
    if (xPos < 6 && yPos > 0) attackSquares |= (1ULL << ((yPos - 1) * 8 + (xPos + 2)));
    if (xPos > 0 && yPos > 1) attackSquares |= (1ULL << ((yPos - 2) * 8 + (xPos - 1)));
    if (xPos > 0 && yPos < 6) attackSquares |= (1ULL << ((yPos + 2) * 8 + (xPos - 1)));
    if (xPos < 7 && yPos > 1) attackSquares |= (1ULL << ((yPos - 2) * 8 + (xPos + 1)));
    if (xPos < 7 && yPos < 6) attackSquares |= (1ULL << ((yPos + 2) * 8 + (xPos + 1)));
    return attackSquares;
};

long long Judge::generateBishopAttacks(Board &board, int xPos, int yPos){
    long long attackSquares = 0;
    long long currSquare;
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (auto &dir : directions){
        int dirX = dir[0], dirY = dir[1];
        int currX = xPos + dirX, currY = yPos + dirY;
        while (currX >= 0 && currX <= 7 && currY >= 0 && currY <= 8){
            currSquare = (1ULL << (currY * 8 + currX));
            attackSquares |= currSquare;
            if ((board.occupiedSquares & currSquare) == 1) break;
            currX += dirX;
            currY += dirY;
        };
    };
    return attackSquares;
};

long long Judge::generateRookAttacks(Board &board, int xPos, int yPos){
    long long attackSquares = 0;
    long long currSquare;

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto &dir : directions){
        int dirX = dir[0], dirY = dir[1];
        int currX = xPos + dirX, currY = yPos + dirY;
        while (currX >= 0 && currX <= 7 && currY >= 0 && currY <= 7){
            currSquare = (1ULL << (currY * 8 + currX));
            attackSquares |= currSquare;
            if ((board.occupiedSquares & currSquare) == 1) break;
            currX += dirX;
            currY += dirY;
        };
    };
    return attackSquares;
};

long long Judge::generateQueenAttacks(Board &board, int xPos, int yPos){
    return generateRookAttacks(board, xPos, yPos) | generateBishopAttacks(board, xPos, yPos);
};

long long Judge::generateKingAttacks(int xPos, int yPos){
    int attackSquares = 0;
    int directions[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    for (auto &dir : directions){
        attackSquares |= (1ULL << ((xPos + dir[0]) + (yPos + dir[1])* 8 ));
    };

    return attackSquares;
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











