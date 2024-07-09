#include "Board.h"
#include <vector>

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

void Board::makeMove(int startX, int startY, int endX, int endY){};

unsigned long long Board::getBitboard(char pieceType){
    switch (pieceType) {
        case ' ': return freeSquares;
        case 'p': return wPawns;
        case 'h': return wKnights;
        case 'b': return wBishops;
        case 'r': return wRooks;
        case 'q': return wQueens;
        case 'k': return wKing;
        case 'P': return bPawns;
        case 'H': return bKnights;
        case 'B': return bBishops;
        case 'R': return bRooks;
        case 'Q': return bQueens;
        case 'K': return bKing;
        default: return 0;
    }
};

void Board::setBitboard(char pieceType, long long bitBoard){};

std::vector<char> Board::getChars(){return chars;};

void Board::updateSquares(){
    occupiedSquares = wPawns | wKnights | wBishops | wRooks | wQueens | wKing | bPawns | bKnights | bBishops |
        bRooks | bQueens | bKing;
    freeSquares = ~occupiedSquares;
};




