#ifndef BOARD_H
#define BOARD_H
#include <vector>

class Judge;

class Board{
    public:
        Board();
        void initializeBoard();
        void makeMove(int startX, int startY, int endX, int endY, Judge &judge, int currPlayer);
        unsigned long long *getBitboard(char pieceType);
        void updateBitboard(char pieceType, unsigned long long matchValue);
        void updateBitboardFromMove(char startType, char endType, unsigned long long startSquare, unsigned long long endSquare);
        unsigned long long occupiedSquares, freeSquares, whiteSquares, blackSquares, pessant;
        //unsigned long long pessant;
        // Square that keeps the legal enpessant square if there is any
        void setEnpessantSquare(unsigned long long square);
        bool pessantUpdated;
        char getSquareType(int x, int y);

    private:
        unsigned long long wPawns, wKnights, wBishops, wRooks, wQueens, wKing;
        unsigned long long bPawns, bKnights, bBishops, bRooks, bQueens, bKing;
        unsigned long long anpessantSquare;
        unsigned long long getSquareValue(int x, int y);
        void updateSquares();

};

#endif // BOARD_H
