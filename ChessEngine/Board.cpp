#include "Board.h"
#include <math.h>
#include <vector>
#include <iostream>
#include "Judge.h"


Board::Board(){
    chars = {' ', 'p', 'h', 'b', 'r', 'q', 'k', 'P', 'H', 'B', 'R', 'Q', 'K'};
    initializeBoard();

};

void Board::initializeBoard(){
    wPawns = 0x000000000000FF00ULL;
    wKnights = 0x0000000000000042ULL;
    wBishops = 0x0000000000000024ULL;
    wRooks = 0x0000000000000081ULL;
    wQueens = 0x0000000000000008ULL;
    wKing = 0x0000000000000010ULL;

    bPawns = 0x00FF000000000000ULL;
    bKnights = 0x4200000000000000ULL;
    bBishops = 0x2400000000000000ULL;
    bRooks = 0x8100000000000000ULL;
    bQueens = 0x0800000000000000ULL;
    bKing = 0x1000000000000000ULL;

    updateSquares();
};

void Board::makeMove(int startX, int startY, int endX, int endY, Judge &judge, int currPlayer){
    unsigned long long startSquare = getSquareValue(startX, startY);
    unsigned long long endSquare = getSquareValue(endX, endY);
    char startType = getSquareType(startX, startY);
    char endType = getSquareType(endX, endY);

    if (judge.isMoveLegal(*this, startX, startY, endX, endY, startType, currPlayer)){

        updateBitboard(startType, startSquare); // remove type from startSquare
        updateBitboard(startType, endSquare); // add new type to endSquare
        updateBitboard(endType, endSquare); // remove previous endSquare type


        updateSquares();
    }

    //if(occupiedSquares & )

};

void Board::newPessant(unsigned long long square){
    if (pessantUpdated) return;
    pessant = square;
    pessantUpdated = true;
};

char Board::getSquareType(int x, int y){
    unsigned long long square = getSquareValue(x, y);
    if(whiteSquares & square){
        if(square & wPawns){return 'p';}
        else if(square & wKnights){return 'h';}
        else if(square & wBishops){return 'b';}
        else if(square & wRooks){return 'r';}
        else if(square & wQueens){return 'q';}
        else if(square & wKing){return 'k';}
    }
    else if(blackSquares & square){
        if(square & bPawns){return 'P';}
        else if(square & bKnights){return 'H';}
        else if(square & bBishops){return 'B';}
        else if(square & bRooks){return 'R';}
        else if(square & bQueens){return 'Q';}
        else if(square & bKing){return 'K';}
    }
   
    return ' ';
}

unsigned long long Board::getSquareValue(int x, int y){
    /*
    unsigned long long square;
    if(y == 0){
        if(x == 0){square = 0;}
        else {square = std::pow(2, x);}
    }
    else{
        if(x == 0){square = std::pow(2, 8*y);}
        else{square = std::pow(2, x) + std::pow(2, 8*y);};
    };

    return square;
    */
    return 1ull << (x + 8*y);
}

unsigned long long *Board::getBitboard(char pieceType){
    switch (pieceType) {
        case ' ': return &freeSquares;
        case 'p': return &wPawns;
        case 'h': return &wKnights;
        case 'b': return &wBishops;
        case 'r': return &wRooks;
        case 'q': return &wQueens;
        case 'k': return &wKing;
        case 'P': return &bPawns;
        case 'H': return &bKnights;
        case 'B': return &bBishops;
        case 'R': return &bRooks;
        case 'Q': return &bQueens;
        case 'K': return &bKing;
        default: return 0;
    }
};

/*
 * updates the piece's table by xor-ing the matchValue. if bitBoard contains the value, we remove it, if not, it adds it.
 * */
void Board::updateBitboard(char pieceType, unsigned long long matchValue){
    unsigned long long *bitBoard = getBitboard(pieceType);
    *bitBoard = *bitBoard ^ matchValue;
};

std::vector<char> Board::getChars(){return chars;};

void Board::updateSquares(){
    whiteSquares = wPawns | wKnights | wBishops | wRooks | wQueens | wKing;
    blackSquares = bPawns | bKnights | bBishops | bRooks | bQueens | bKing;
    occupiedSquares = whiteSquares | blackSquares;
    freeSquares = ~occupiedSquares;
    newPessant(0);
    pessantUpdated = false;

};




