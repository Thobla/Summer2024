#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Judge;

class Board{
    public:
        Board();
        void initializeBoard();
        void makeMove(int startX, int startY, int endX, int endY, Judge &judge);
        unsigned long long *getBitboard(char pieceType);
        void updateBitboard(char pieceType, unsigned long long matchValue);
        std::vector<char> getChars();

    private:
        unsigned long long wPawns, wKnights, wBishops, wRooks, wQueens, wKing;
        unsigned long long bPawns, bKnights, bBishops, bRooks, bQueens, bKing;
        unsigned long long occupiedSquares, freeSquares, whiteSquares, blackSquares;
        std::vector<char> chars;
        char getSquareType(int x, int y);
        unsigned long long getSquareValue(int x, int y);
        void updateSquares();

};

#endif // BOARD_H
