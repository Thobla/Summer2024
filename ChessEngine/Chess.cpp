#include<iostream>
#include<algorithm>
#include<math.h>

short board[8][8];


int legal_move(int start_x, int start_y, int end_x, int end_y, short *board){
    short piece = *board[start_y][start_x];
    short is_white = piece > 0;

    if (piece == 1){return pawn_rule(start_x, start_y, end_x, end_y, board, is_white);}
    else if (piece == 2){return knight_rule(start_x, start_y, end_x, end_y, board, is_white);}
    else if (piece == 3){return bishop_rule(start_x, start_y, end_x, end_y, board, is_white);}
    else if (piece == 4){return rook_rule(start_x, start_y, end_x, end_y, board, is_white);}
    else if (piece == 5){return queen_rule(start_x, start_y, end_x, end_y, board, is_white);}
    else if (piece == 6){return nils_rule(start_x, start_y, end_x, end_y, board, is_white);}
    return 0
    
};

int main(){
    // Initiallizing the board
    board[0] = {4, 2, 3, 6, 5, 3, 2, 4};
    board[7] = {-4, -2, -3, -6, -5, -3, -2, -4};
    for (int i = 1; i < 7; i++){ 
        for (int j = 0; j < 8; j++){ 
            if (i == 2 || i == 7){ board[j][i] = 1;};
            board[i][j] = 0;
        };
    };

    legal_move(start_x, start_y, end_x, end_y);
        
};

