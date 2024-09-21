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
#include <vector>

class Board;

bool Judge::isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char pieceType, int currPlayer){
    // Print to test attack square calculations
    if (currPlayer == 0){printAttackSquares(blackAttackSquares(board));}
    else {printAttackSquares(whiteAttackSquares(board));}
    if (pieceType == ' ') return false;
    if(pieceType == 'p'){
        if(!wPawnRule(board, startX, startY, endX, endY) || currPlayer) return false;
    }
    else if(pieceType == 'h'){
        if(!wPonyRule(board, startX, startY, endX, endY) || currPlayer) return false;
    }
    else if(pieceType == 'b'){
        if(!wBishopRule(board, startX, startY, endX, endY) || currPlayer) return false;
    }
    else if(pieceType == 'q'){
        if(!wQueenRule(board, startX, startY, endX, endY) || currPlayer) return false;
    }
    else if(pieceType == 'k'){
        if(!wKingRule(board, startX, startY, endX, endY) || currPlayer) return false;
    }
    else if(pieceType == 'P'){
        if(!bPawnRule(board, startX, startY, endX, endY) || !currPlayer) return false;
    }
    else if(pieceType == 'H'){
        if(!bPonyRule(board, startX, startY, endX, endY) || !currPlayer) return false;
    }
    else if(pieceType == 'B'){
        if(!bBishopRule(board, startX, startY, endX, endY) || !currPlayer) return false;
    }
    else if(pieceType == 'Q'){
        if(!bQueenRule(board, startX, startY, endX, endY) || !currPlayer) return false;
    }
    else if(pieceType == 'K'){
        if(!bKingRule(board, startX, startY, endX, endY) || !currPlayer) return false;
    }

    return true;
}

bool Judge::isCheck(Board &board, int color){
    return (color == 0) ? (*board.getBitboard('k') & blackAttackSquares(board)) : (*board.getBitboard('K') & whiteAttackSquares(board));
};


// Currently, never becomes mate
//
// TODO: FIX THIS METHOD
bool Judge::isMate(Board &board, int color){
    return false;
}

void Judge::printAttackSquares(unsigned long long attackSquares){
    for (int j = 7; j >= 0; j--){
        for (int i = 0; i < 8; i++){
            // Prints 1 if square is under attack, 0 if not
            if (((1ull << (i + 8*j)) & attackSquares) == (1ull << (i + 8*j))){std::cout << 1;}
            else {std::cout << 0;}

        }
        std::cout << std::endl;
    }
}

bool Judge::bPawnRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    if(endY == startY-1){
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        if((startX == endX+1 || startX == endX-1) && (board.whiteSquares & endSquare)){return true;};

        if((startX == endX + 1 || startX == endX - 1) && (endSquare == board.pessant)){
            board.updateBitboard('p', 1ull << (endX + 8 * (endY + 2)));
            return true;
        }
    }
    else if(endY == 4 && startY == 6){
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){
            board.setEnpessantSquare(1ull << (startX + 8 * 6));
            return true;
        };
    };
    return false;
};

long long Judge::whiteAttackSquares(Board &board){
    unsigned long long attackSquares = 0;
    char pieceType;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++){
            pieceType = board.getSquareType(x, y);
            switch (pieceType) {
                case ' ' : break;
                case 'p' : attackSquares = attackSquares | generatePawnAttacks(0, x, y); break;
                case 'h' : attackSquares = attackSquares | generatePonyAttacks(x, y); break;
                case 'b' : attackSquares |= generateBishopAttacks(board, x, y); break;
                case 'r' : attackSquares |= generateRookAttacks(board, x, y); break;
                case 'q' : attackSquares |= generateQueenAttacks(board, x, y); break;
                case 'k' : attackSquares |= generateKingAttacks(x, y); break;
            }
        }
    }
    return attackSquares;
};

long long Judge::blackAttackSquares(Board &board){
    long long attackSquares = 0;
    char pieceType;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++){
            pieceType = board.getSquareType(x, y);
            switch (pieceType) {
                case ' ' : break;
                case 'P' : attackSquares |= generatePawnAttacks(1, x, y); break;
                case 'H' : attackSquares |= generatePonyAttacks(x, y); break;
                case 'B' : attackSquares |= generateBishopAttacks(board, x, y); break;
                case 'R' : attackSquares |= generateRookAttacks(board, x, y); break;
                case 'Q' : attackSquares |= generateQueenAttacks(board, x, y); break;
                case 'K' : attackSquares |= generateKingAttacks(x, y); break;
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
        while (currX >= 0 && currX <= 7 && currY >= 0 && currY <= 7){
            currSquare = (1ULL << (currY * 8 + currX));
            attackSquares |= currSquare;
            if ((board.occupiedSquares & currSquare) == currSquare) break;
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
    int dirX, currX, dirY, currY;
    for (auto &dir : directions){
        dirX = dir[0], dirY = dir[1];
        currX = xPos + dirX, currY = yPos + dirY;
        while (currX >= 0 && currX <= 7 && currY >= 0 && currY <= 7){
            currSquare = (1ULL << (currY * 8 + currX));
            attackSquares |= currSquare;
            if ((board.occupiedSquares & currSquare) == currSquare) break;
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
    unsigned long long attackSquares = 0;
    int directions[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int dirX, currX, dirY, currY;
    for (auto &dir : directions){
        dirX = dir[0], dirY = dir[1];
        currX = xPos + dirX, currY = yPos + dirY;
        if (currX >= 0 && currX < 8 && currY >= 0 && currY < 8){
            attackSquares |= (1ULL << (currX + currY*8 ));
        }
    };

    return attackSquares;
};


void Judge::pawnEndOfFile(Board &board, int endX, int endY, int currPlayer){

    // if black
    if (currPlayer == 1){
        if (endY == 0){
            board.updateBitboard('P', 1ull << (endX + endY * 8));
            board.updateBitboard('Q', 1ull << (endX + endY * 8));
        }
    }
    // if white
    else if (currPlayer == 0){
        if (endY == 7){
            board.updateBitboard('p', 1ull << (endX + endY * 8));
            board.updateBitboard('q', 1ull << (endX + endY * 8));
        }
    }
}

bool Judge::wPawnRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    if(endY == startY+1){
        if((startX == endX + 1 || startX == endX - 1) && (endSquare == board.pessant)) {
            board.updateBitboard('P', 1ull << (endX + (8 * (endY - 2))));
            return true;
        }
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){return true;};
        if((startX == endX+1 || startX == endX-1) && (board.blackSquares & endSquare)){return true;};
    }
    else if(endY == 3 && startY == 1){
        if(startX == endX && pathCleared(board, startX, startY, endX, endY)){
            board.setEnpessantSquare(1ull << (startX + 8 * startY));
            return true;
        };
    };
    // Queen if end of file
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
    if(!((endSquare & board.whiteSquares) == endSquare) && !((endSquare & blackAttackSquares(board)) == endSquare)){
        return true;
    }
    return false;
}

bool Judge::bKingRule(Board &board, int startX, int startY, int endX, int endY){
    unsigned long long endSquare = 1ull << (endX + 8*endY);
    bool distIsOne = std::abs(endX - startX) < 2 && std::abs(endY - startY) < 2 && std::abs(endX - startX) + std::abs(endY - startY) > 0;
    if(!((endSquare & board.blackSquares) == endSquare) && !((endSquare & whiteAttackSquares(board)) == endSquare)){
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


