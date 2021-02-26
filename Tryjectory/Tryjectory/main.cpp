//
//  main.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 2/25/21.
//

#include <iostream>
#include "SDL.h"
#include "Game.h"

int main(int argc, const char * argv[]) {
    Game game;
    bool success = game.Initialize();
    
    if (success) {
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
