#include "game.hpp"
#include "ui_game.hpp"

#include <iostream>

#define NUM_MINES 100

int main(int argc, char* argv[]){
    try{
        auto game = std::make_shared<Game>();
        game->FillBoardRandomMine(NUM_MINES);

        UIGame ui(game);
        ui.Setup();
        ui.Show();
    } catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

    return 0;
}