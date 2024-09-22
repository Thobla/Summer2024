#ifndef JUDGE_H
#define JUDGE_H

#include <vector>

class Board;

class Judge{
    public:
        bool isMoveLegal(Board &board, int startX, int startY, int endX, int endY, char startType, char endType, int currPlayer);
        //std::vector<std::tuple<int, int, int, int>> getLegalMoves(Board &board);
        // Table of the current legal moves to make, if there are none, its mate or pate
        std::vector<int> legalMoves[64];
        // Method for calculating all the legal moves.
        void findLegalMoves(Board &board, int currPlayer);
        void findLegalPawnMoves(Board &board, int currPlayer, int x, int y);
        void findLegalHorseMoves(Board &board, int currPlayer, int x, int y);
        void findLegalBishopMoves(Board &board, int currPlayer, int x, int y);
        void findLegalRookMoves(Board &board, int currPlayer, int x, int y);
        void findLegalQueenMoves(Board &board, int currPlayer, int x, int y);
        void findLegalKingMoves(Board &board, int currPlayer, int x, int y);

        struct p_moves;struct P_moves;struct kK_moves;struct qQ_moves; struct bB_moves;struct rR_moves;struct hH_moves;

        // Tables for all generally possible moves (not necissarily legal ones) for efficiency. 
        // int p_possible_moves[64][64];
        // int P_possible_moves[64][64];
        // int qQ_possible_moves[64][64];
        // int hH_possible_moves[64][64];
        // int bB_possible_moves[64][64];
        // int rR_possible_moves[64][64];
        // int kK_possible_moves[64][64];
        // void innitialize_possible_moves();

        bool isCheck(Board &board, int color);
        bool isMate(Board &board, int color);
        bool isStale(Board &board);
        bool moveSelfcheckSafe(Board &board, int startX, int startY, int endX, int endY, char startType, char endType, int currPlayer);

        bool wPawnRule(Board &board, int startX, int startY, int endX, int endY);
        bool wPonyRule(Board &board, int startX, int startY, int endX, int endY);
        bool wBishopRule(Board &board, int startX, int startY, int endX, int endY);
        bool wRookRule(Board &board, int startX, int startY, int endX, int endY);
        bool wQueenRule(Board &board, int startX, int startY, int endX, int endY);
        bool wKingRule(Board &board, int startX, int startY, int endX, int endY);


        void pawnEndOfFile(Board & board, int endX, int endY, int wOrB);

        long long generatePawnAttacks(int color, int xPos, int yPos);
        long long generatePonyAttacks(int xPos, int yPos);
        long long generateBishopAttacks(Board &board,int xPos, int yPos);
        long long generateRookAttacks(Board &board, int xPos, int yPos);
        long long generateQueenAttacks(Board &board,int xPos, int yPos);
        long long generateKingAttacks(int xPos, int yPos);

        unsigned long long attackSquares;
        long long whiteAttackSquares(Board &board);
        long long blackAttackSquares(Board &board);
        void printAttackSquares(unsigned long long attackSquares);

        bool bPawnRule(Board &board, int startX, int startY, int endX, int endY);
        bool bPonyRule(Board &board, int startX, int startY, int endX, int endY);
        bool bBishopRule(Board &board, int startX, int startY, int endX, int endY);
        bool bRookRule(Board &board, int startX, int startY, int endX, int endY);
        bool bQueenRule(Board &board, int startX, int startY, int endX, int endY);
        bool bKingRule(Board &board, int startX, int startY, int endX, int endY);

        bool pathCleared(Board &board, int startX, int startY, int endX, int endY);
        bool pathSemiCleared(Board &board, int startX, int startY, int endX, int endY);


};


#endif // JUDGE_H
