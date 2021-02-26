//
//  Game.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 2/25/21.
//


#pragma once
#include "SDL.h"
#include <vector>


class Game {
    
public:
    Game();
    
    // Initialize the game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shut down the game
    void Shutdown();
    
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    // Window created by SDL
    SDL_Window* mWindow;
    // SDL Renderer
    SDL_Renderer* mRenderer;
    // Number of ticks since start of the game
    Uint32 mTicksCount;
    // Game should continue to run
    bool mIsRunning;
    
};
