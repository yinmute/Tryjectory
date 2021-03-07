//
//  Ball.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/5/21.
//
// Implementation of the ball class

#include "Ball.h"
#include "SDL.h"
#include "Game.h"
#include <cmath>
#include <iostream>
#include "Field.h"

using namespace std;


int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

Ball::Ball(Game* game) {
    gameRef = game;
}

void Ball::Initialize() {
    coordinates = { 500, 500 };
    float fieldHeight = gameRef->mGameField.getHeight();
    float fieldWidth = gameRef->mGameField.getWidth();
    radius = 0.04 * sqrt(pow(fieldHeight,2) + pow(fieldWidth, 2));
    speed.x = 300.0;
    speed.y = -300.0;
}

void Ball::DrawToScreen(SDL_Renderer* renderer) {
    
    SDL_RenderFillCircle(renderer, int(coordinates.x), int(coordinates.y), int(radius));
    
}

void Ball::UpdateBall(float deltaTime) {
    
    //cout << coordinates.y + radius << endl;
    //cout << gameRef->mGameField.getTopLineVector()[0].y;
    
    // Check collision with top wall
    //if ( (coordinates.y - radius) < gameRef->mGameField.getTopLineVector()[0].y ) {
    if ( (coordinates.y - radius) < gameRef->mGameField.getVertexCoordinates()[0].y ) {
        speed.y *= -1;
    }
    
    // Check collision with right wall
    if ( (coordinates.x + radius) > gameRef->mGameField.getVertexCoordinates()[1].x ) {
        speed.x *= -1;
    }
    
    // Check collision with bottom wall
    if ( (coordinates.y + radius) > gameRef->mGameField.getVertexCoordinates()[2].y ) {
        speed.y *= -1;
    }
    
    // Check collision with left wall
    if ( (coordinates.x - radius) < gameRef->mGameField.getVertexCoordinates()[0].x ) {
        speed.x *= -1;
    }
    
    // Update coordinates accordingly to passed time
    coordinates.x += speed.x * deltaTime;
    coordinates.y += speed.y * deltaTime;
    
}


// function to render filled circle
// taken from https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c#file-circle-cpp-L58
int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
