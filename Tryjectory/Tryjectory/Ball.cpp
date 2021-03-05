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

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

Ball::Ball(Game* game) {
    gameRef = game;
}

void Ball::Initialize() {
    coordinates = { 500, 500 };
    float fieldHeight = gameRef->mGameField.getHeight();
    float fieldWidth = gameRef->mGameField.getWidth();
    radius = 20;
}

void Ball::DrawToScreen(SDL_Renderer* renderer) {
    
    SDL_RenderFillCircle(renderer, int(coordinates.x), int(coordinates.y), int(radius));
    
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
