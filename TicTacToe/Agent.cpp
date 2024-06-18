#include<math.h>
#include<vector>
#include<array>
#include <random>
#include "Game.cpp"

class Agent{
    public:
        Agent(Tic_Tac_Game *ex_game, int episodes) :
            game(ex_game), map_act_pos(9), map_pos_act(3, std::vector<int>(3)), policy(episodes){
        };

        struct Policy{
            double eps;
            double lr;
            int episodes;
            std::vector<double> v_s;
            std::vector<int> policy_x;
            std::vector<int> policy_y;

            Policy(int e) : episodes(e), v_s(std::pow(3, 9)), policy_x(std::pow(3, 9)), policy_y(std::pow(3, 9)){
                std::random_device rand;
                std::mt19937 gen(rand());
                std::uniform_real_distribution<> dis(0.0, 1.0);

                for (auto &elem : v_s) { //Randomly initiallize states to value between 0 and 1
                    elem = dis(gen); 
                }
            };
        };
        void learn_MC(){
            // q(a, s) = r + lr(v(s'));
            int i = 0;
            int state = 0;
            int opt_action;
            int action;
            Tic_Tac_Game::Environment env;
            std::vector<int> legal_moves;
            std::vector<int> states;
            std::vector<int> actions;
            std::vector<std::vector<int>> legal_moves_all;
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            
            for(int eps = 0; eps < policy.episodes; eps++){
                while(1){
                    legal_moves = game->legal_moves();
                    if (i%2 == 0){opt_action = policy.policy_x[state];}
                    else{opt_action = policy.policy_y[state];};
                    if(policy.eps <= dis(gen)){
                        for(int elem : legal_moves){
                            if(opt_action == elem){
                                action = opt_action;
                            }
                        }
                    }
                    else{
                        action = legal_moves[get_random_index(legal_moves.size())];
                    }

                    states.push_back(state);
                    actions.push_back(action);
                    state += std::pow(3, i)*(game->get_state().curr_player + 1);
                    legal_moves_all.push_back(legal_moves);
                    env = step(action);

                    if(env.terminated){

                        for (int j = 0; j <= i; j++) {
                            policy.v_s[states[i-j]] += std::pow(-1, i) * std::pow(policy.lr, j)*env.reward - policy.v_s[states[i]];
                            opt_action = legal_moves_all[i-j][0];

                            if((i-j)%2 == 0){
                                for (int elem : legal_moves_all[i-j]) {
                                    if(policy.v_s[states[i-j] + std::pow(3, elem)] >= policy.v_s[states[i-j] + std::pow(3, opt_action)]){
                                        opt_action = elem;
                                    }
                                }
                                policy.policy_x[states[i-j]] = opt_action;
                            }
                            
                            else{
                                for (int elem : legal_moves_all[i-j]) {
                                    if(policy.v_s[states[i-j] + std::pow(3, elem)*2] <= policy.v_s[states[i-j] + std::pow(3, opt_action)*2]){
                                        opt_action = elem;
                                    }
                                }
                                policy.policy_y[states[i-j]] = opt_action;


                            }
                        }
                        break;
                    }
                    i++;
                }
            }
            
        }

    private:
        Tic_Tac_Game *game;
        std::vector<std::array<int, 2>> map_act_pos;
        std::vector<std::vector<int>> map_pos_act;
        Policy policy;

        Tic_Tac_Game::Environment step(int action){
            Tic_Tac_Game::Environment env = game->step(1, map_act_pos[action]);
            return env;
        };


        void init_maps(){
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    map_pos_act[i][j] = i*3 + j;
                    map_act_pos[i*3 + j] = {i, j};
                }
            }
        }

        int get_random_index(int size){
            std::random_device rand;
            std::mt19937 gen(rand());
            std::uniform_int_distribution<> dis(0, size-1);
            return dis(gen);
        }

};


