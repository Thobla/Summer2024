#include<iostream>
#include<algorithm>
#include<math.h>
#include <vector>
#include"Game.h"

/*
 * 
class Game {
    public:
        Game();
        void startGame();
        void swapPlayer();
        void play();

    private:
        Board board;
        Judge judge;
        Gui gui;
        int currPlayer;
};

 */
Game::Game() : board(Board()), gui(Gui()), judge(Judge()), currPlayer(0){};

void Game::startGame(){};

void Game::swapPlayer(){};
void Game::play(){
    gui.displayBoard(board);
    gui.makeMove(board, judge);
    gui.displayBoard(board);
    gui.makeMove(board, judge);
    gui.displayBoard(board);
    gui.makeMove(board, judge);
    gui.displayBoard(board);
    gui.makeMove(board, judge);
    gui.displayBoard(board);
    gui.makeMove(board, judge);
    gui.displayBoard(board);


};
    
int main(){
    Game game;
    game.play();

}
