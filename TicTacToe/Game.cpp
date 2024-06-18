#include<iostream>
#include<string>
#include<algorithm>
#include<math.h>
#include<vector>
#include <array>
#include<sstream>

/*
 * Helper functions
 */

std::vector<std::string> split(std::string &s, char delimiter){
    std::vector<std::string> final_s;
    std::string temp_s;
    std::istringstream stream(s);

    while (std::getline(stream, temp_s, delimiter)){
        final_s.push_back(temp_s);
    };

    return final_s;
};

class Tic_Tac_Game{
    public:
        Tic_Tac_Game(){};

        void run(){
            while (!state.terminated){
                step(0);
                draw_board();
            }
        };
        struct Board{
            int x_table;
            int o_table;
            int blank_table;
            Board() : x_table(0), o_table(0), blank_table((1<<9) - 1) {};
        };
        struct Game_state{
            int terminated;
            int curr_player;
            Game_state() : terminated(0), curr_player(0) {};
        };

        struct Environment{
            int x_table;
            int o_table;
            int blank_table;
            int reward;
            int curr_player;
            int terminated;
        };



        Board get_board(){return tic_tac_board;};
        Game_state get_state(){return state;};

        void reset_game(){
            tic_tac_board.x_table = 0;
            tic_tac_board.o_table = 0;
            tic_tac_board.blank_table = (1<<9) - 1;
            state.terminated = 0;
            state.curr_player = 0;
        }

        Environment step(int abstract = 0, std::array<int, 2> xy = {0, 0}){
            int x = xy[0];
            int y = xy[1];
            int reward = 0;
            Environment env;
            if(!abstract){
                std::string input;
                std::vector<std::string> command = {"0", "0"};
                if (state.curr_player == 0){
                    std::cout << "p1's your move \n";
                }
                else if (state.curr_player == 1){
                    std::cout << "p2's your move \n";
                };

                std::cout <<"type in your move as 'x y'." << std::endl;
                std::getline(std::cin, input); //Need to refactor at some time to check input correctness
                command = split(input, ' ');
                x = stoi(command[0]);
                y = stoi(command[1]);
            }

            if (valid_move(x, y)){
                perform_placement(x, y, state.curr_player);
            }
            else{
                if(!abstract){}
                std::cout << "Not a valid placement" << std::endl;
                return env;
            };
            state.terminated = game_done();
            if(!abstract){
                if(state.terminated == 1){std::cout << "No winner" << std::endl;}
                if(state.terminated == 2){std::cout << "Winner is player " << state.curr_player + 1 << std::endl;}
            }
            state.curr_player = (state.curr_player + 1) % 2;
            if(state.terminated == 2){reward = 1;}
            else{reward = 0;};
            env = {tic_tac_board.x_table, tic_tac_board.o_table, tic_tac_board.blank_table, reward, state.curr_player, state.terminated};
            return env;
        };

        std::vector<int> legal_moves(){
            std::vector<int> legal_moves;
            for (int i = 0; i < 9; i++) {
                if((tic_tac_board.blank_table & (1<<i)) == 1){legal_moves.push_back(i);};
            }
            return legal_moves;
        };

    private:
        Board tic_tac_board;
        Game_state state; 

        void perform_placement(int x, int y, int curr_player){
            int pos;
            pos = 1 << ((y - 1)*3 + x - 1);
            if(curr_player == 0){tic_tac_board.x_table += pos;}
            else{tic_tac_board.o_table += pos;};

            tic_tac_board.blank_table -= pos;
        }

        int valid_move(int x, int y){
            if ((x <= 3 && x >= 1) && (y <= 3 && y >= 1)){
                if(1 << (y-1)*3 + x-1 & tic_tac_board.blank_table){
                    return 1;
                }
            }
            return 0;
        }

        int game_done(){
            int table;
            if(state.curr_player == 0){table = tic_tac_board.x_table;}
            else{table = tic_tac_board.o_table;};

            if(table & (1<<0) && table & (1<<4) && table & (1<<8)){return 2;}
            if(table & (1<<2) && table & (1<<4) && table & (1<<6)){return 2;}

            for(int i = 0; i < 3; i++){
                if(table & (1<<i) && table & (1<<i + 3) && table & (1<<i + 6)){
                    return 2;
                }
                if(table & (1<<i*3) && table & (1<<i*3 + 1) && table & (1<<i*3 + 2)){
                    return 2;
                }
                if(table & (1<<i) && table & (1<<i + 3) && table & (1<<i + 6)){
                    return 2;
                }
            }
            if(tic_tac_board.blank_table == 0){
                return 1;
            }

            return 0;

        }

        void draw_board(){
            int k = 6;
            std::cout << "\n";
            for(int i = 0; i < 3; i++){

                for(int j = 0; j < 3; j++){
                    if((1 << k) & tic_tac_board.x_table){
                        std::cout << "x";
                    }
                    else if((1 << k) & tic_tac_board.o_table){
                        std::cout << "o";
                    }
                    else {std::cout << " ";};
                    k += 1;
                }
                k -= 6;
                std::cout << "\n";
            }
        }
};
