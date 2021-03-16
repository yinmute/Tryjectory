//
//  Ball.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/5/21.
//
// Ball class definition

#pragma once

#include "Vector.h"
#include "SDL.h"

class Ball {
  
public:
    
    Ball(class Game* game);
    
    // Initialize the field and randomize values
    void Initialize();
    
    // Will draw the field to the screen
    void DrawToScreen(SDL_Renderer* renderer);
    
    // Function to update ball
    void UpdateBall(float deltaTime);
    
    // Getter function for returning coordinates of center of the ball
    Vector2 getCoordinate();
    
    // Getter function for returning vector of the speed
    Vector2 getSpeed();
    
    // Getter function for ball's status
    int getStatus();
    
    // Returns ball's radius
    float getRadius();
    
    
private:
    
    Vector2 coordinates;
    Vector2 speed;
    float radius;
    int status; // 0 - not active
                // 1 - active
    
    // Dependency injection to game object
    class Game* gameRef;
    
};
