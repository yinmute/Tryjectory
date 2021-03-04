//
//  Game.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 2/25/21.
//

#include "Game.h"

using namespace std;



Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,mGameField(this)
{ }

bool Game::Initialize() {
    // Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    // Create an SDL Window
    mWindow = SDL_CreateWindow(
                           "Tryjectory", // Window title
                           SDL_WINDOWPOS_CENTERED, // Top left x-coordinate of window
                           SDL_WINDOWPOS_CENTERED, // Top left y-coordinate of window
                           1024, // Width of window
                           768, // Height of window
                           0 // Flags (0 for no flags set))
                           );

    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    
    // Create SDL renderer
    mRenderer = SDL_CreateRenderer(
                                   mWindow, // Window to create renderer for
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s ", SDL_GetError);
        return false;
    }
    
    mGameField.Initialize();
    
    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
                // If we get an SDL_QUIT event, end loop
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    
    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    
    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    
    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();
   
    
}

void Game::GenerateOutput() {
    // Set draw color to blue
    SDL_SetRenderDrawColor(
                           mRenderer,
                           168,
                           168,
                           168,
                           255);
    // Clear back buffer
    SDL_RenderClear(mRenderer);
    
    // Draw field
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    mGameField.DrawToScreen(mRenderer);
    
    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
    
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

