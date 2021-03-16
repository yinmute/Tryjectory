//
//  Ball.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/5/21.
//
// Implementation of the ball class

#include <cmath>
#include <iostream>

#include "Ball.h"
#include "SDL.h"
#include "Game.h"
#include "Field.h"

using namespace std;

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

Ball::Ball(Game* game) {
    gameRef = game;
}

void Ball::Initialize() {
    coordinates = { 900, 300 };
    float fieldHeight = gameRef->mGameField->getHeight();
    float fieldWidth = gameRef->mGameField->getWidth();
    radius = 0.04 * sqrt(pow(fieldHeight,2) + pow(fieldWidth, 2));
    
    // example of random speed vector
    speed.x = 300.0;
    speed.y = -300.0;
    
    // example of top left pocket vector
    //speed.x = -(coordinates.x - (gameRef->mGameField->getVertexCoordinates()[0].x + radius));
    //speed.y = -(coordinates.y - (gameRef->mGameField->getVertexCoordinates()[0].y + radius));
    
    // example of top right pocket vector
    //speed.x =  (gameRef->mGameField->getVertexCoordinates()[1].x - radius - coordinates.x)*0.7;
    //speed.y = -(coordinates.y - (gameRef->mGameField->getVertexCoordinates()[0].y + radius))*0.7;
    
    // example of bottom right pocket vector
    //speed.x = gameRef->mGameField->getVertexCoordinates()[1].x - radius - coordinates.x;
    //speed.y = gameRef->mGameField->getVertexCoordinates()[2].y - radius - coordinates.y;
    
    // example of bottom left pocket vector
    //speed.x = gameRef->mGameField->getVertexCoordinates()[3].x + radius - coordinates.x;
    //speed.y = gameRef->mGameField->getVertexCoordinates()[3].y - radius - coordinates.y;
    
}

void Ball::DrawToScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillCircle(renderer, int(coordinates.x), int(coordinates.y), int(radius));
    
}

void Ball::UpdateBall(float deltaTime) {
    
    // Allowed variance for checking if ball center, pocket and ball speed vectors are on one line
    float oneLineEpsilon = 10;
    // Allowed variance to check if the next ball point is within the pocket point
    float pocketPointEpsilon = 10;
    
    // Calculate next point prediction
    float next_coord_x = coordinates.x + speed.x * deltaTime;
    float next_coord_y = coordinates.y + speed.y * deltaTime;
    
    // check top left pocket collision
    float x1 = coordinates.x + speed.x;
    float y1 = coordinates.y + speed.y;
    float x2 = coordinates.x;
    float y2 = coordinates.y;
    float x3 = gameRef->mGameField->getVertexCoordinates()[0].x + radius;
    float y3 = gameRef->mGameField->getVertexCoordinates()[0].y + radius;
    float oneLine = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
        
    if (oneLine < oneLineEpsilon) {
        //cout << next_coord_x << " " << gameRef->mGameField->getVertexCoordinates()[0].x + radius << endl;
        //cout << next_coord_y << " " << gameRef->mGameField->getVertexCoordinates()[0].y + radius << endl;
        bool nextPointPassPocketPoint = next_coord_x <= gameRef->mGameField->getVertexCoordinates()[0].x + radius &&
        next_coord_y <= gameRef->mGameField->getVertexCoordinates()[0].y + radius;
        bool nextPointNearPocketPoint = twoPointsCompare(next_coord_x, next_coord_y, gameRef->mGameField->getVertexCoordinates()[0].x + radius, gameRef->mGameField->getVertexCoordinates()[0].y + radius, pocketPointEpsilon) == true;
        
        if (nextPointPassPocketPoint || nextPointNearPocketPoint) {
            coordinates.x = gameRef->mGameField->getVertexCoordinates()[0].x + radius;
            coordinates.y = gameRef->mGameField->getVertexCoordinates()[0].y + radius;
            cout << "topLeftPocket!" << endl;
            return;
        }
    }
    
    // check top right pocket collision
    x3 = gameRef->mGameField->getVertexCoordinates()[1].x - radius;
    y3 = gameRef->mGameField->getVertexCoordinates()[0].y + radius;
    oneLine = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    
    if (oneLine < oneLineEpsilon) {
        //cout << next_coord_x << " " << gameRef->mGameField->getVertexCoordinates()[0].x + radius << endl;
        //cout << next_coord_y << " " << gameRef->mGameField->getVertexCoordinates()[0].y + radius << endl;
        bool nextPointPassPocketPoint = next_coord_x >= gameRef->mGameField->getVertexCoordinates()[1].x - radius &&
        next_coord_y <= gameRef->mGameField->getVertexCoordinates()[0].y + radius;
        bool nextPointNearPocketPoint = twoPointsCompare(next_coord_x, next_coord_y, gameRef->mGameField->getVertexCoordinates()[1].x - radius, gameRef->mGameField->getVertexCoordinates()[0].y + radius, pocketPointEpsilon) == true;
        
        if (nextPointPassPocketPoint || nextPointNearPocketPoint) {
            coordinates.x = gameRef->mGameField->getVertexCoordinates()[1].x - radius;
            coordinates.y = gameRef->mGameField->getVertexCoordinates()[0].y + radius;
            cout << "topRightPocket!" << endl;
            return;
        }
    }
    
    
    // check bottom right pocket collision
    x3 = gameRef->mGameField->getVertexCoordinates()[1].x - radius;
    y3 = gameRef->mGameField->getVertexCoordinates()[2].y - radius;
    oneLine = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    
    if (oneLine < oneLineEpsilon) {
        //cout << next_coord_x << " " << gameRef->mGameField->getVertexCoordinates()[0].x + radius << endl;
        //cout << next_coord_y << " " << gameRef->mGameField->getVertexCoordinates()[0].y + radius << endl;
        bool nextPointPassPocketPoint = next_coord_x >= gameRef->mGameField->getVertexCoordinates()[1].x - radius &&
        next_coord_y >= gameRef->mGameField->getVertexCoordinates()[2].y - radius;
        bool nextPointNearPocketPoint = twoPointsCompare(next_coord_x, next_coord_y, gameRef->mGameField->getVertexCoordinates()[1].x - radius, gameRef->mGameField->getVertexCoordinates()[2].y - radius, pocketPointEpsilon) == true;
        
        if (nextPointPassPocketPoint || nextPointNearPocketPoint) {
            coordinates.x = gameRef->mGameField->getVertexCoordinates()[1].x - radius;
            coordinates.y = gameRef->mGameField->getVertexCoordinates()[2].y - radius;
            cout << "bottomRightPocket!" << endl;
            return;
        }
    }
    
    // check bottom left pocket collision
    x3 = gameRef->mGameField->getVertexCoordinates()[3].x + radius;
    y3 = gameRef->mGameField->getVertexCoordinates()[3].y - radius;
    oneLine = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    
    if (oneLine < oneLineEpsilon) {
        //cout << next_coord_x << " " << gameRef->mGameField->getVertexCoordinates()[0].x + radius << endl;
        //cout << next_coord_y << " " << gameRef->mGameField->getVertexCoordinates()[0].y + radius << endl;
        bool nextPointPassPocketPoint = next_coord_x <= gameRef->mGameField->getVertexCoordinates()[3].x + radius &&
        next_coord_y >= gameRef->mGameField->getVertexCoordinates()[3].y - radius;
        bool nextPointNearPocketPoint = twoPointsCompare(next_coord_x, next_coord_y, gameRef->mGameField->getVertexCoordinates()[3].x + radius, gameRef->mGameField->getVertexCoordinates()[3].y - radius, pocketPointEpsilon) == true;
        
        if (nextPointPassPocketPoint || nextPointNearPocketPoint) {
            coordinates.x = gameRef->mGameField->getVertexCoordinates()[3].x + radius;
            coordinates.y = gameRef->mGameField->getVertexCoordinates()[3].y - radius;
            cout << "bottomLeftPocket!" << endl;
            return;
        }
    }
    
    // Check collision with top wall
    //if ( (coordinates.y - radius) < gameRef->mGameField->getVertexCoordinates()[0].y ) {
    //    speed.y *= -1;
    //}
    if ( (next_coord_y - radius) < gameRef->mGameField->getVertexCoordinates()[0].y ) {
        float distance_to_wall = coordinates.y - gameRef->mGameField->getVertexCoordinates()[0].y - radius;
        float time_to_wall = abs(distance_to_wall / speed.y);
        float time_diff = deltaTime - time_to_wall;
        coordinates.x += speed.x * deltaTime;
        speed.y *= -1;
        coordinates.y = gameRef->mGameField->getVertexCoordinates()[0].y + radius + speed.y * time_diff;
        return;
    }
    
    // Check collision with right wall
    //if ( (coordinates.x + radius) > gameRef->mGameField->getVertexCoordinates()[1].x ) {
    //    speed.x *= -1;
    //}
    if ( (next_coord_x + radius) > gameRef->mGameField->getVertexCoordinates()[1].x ) {
        float distance_to_wall = gameRef->mGameField->getVertexCoordinates()[1].x - coordinates.x - radius;
        float time_to_wall = abs(distance_to_wall / speed.x);
        float time_diff = deltaTime - time_to_wall;
        coordinates.y += speed.y * deltaTime;
        speed.x *= -1;
        coordinates.x = gameRef->mGameField->getVertexCoordinates()[1].x - radius + speed.x * time_diff;
        return;
    }

    
    // Check collision with bottom wall
    //if ( (coordinates.y + radius) > gameRef->mGameField->getVertexCoordinates()[2].y ) {
    //    speed.y *= -1;
    //}
    if ( (next_coord_y + radius) > gameRef->mGameField->getVertexCoordinates()[2].y ) {
        float distance_to_wall = gameRef->mGameField->getVertexCoordinates()[2].y - coordinates.y - radius;
        float time_to_wall = abs(distance_to_wall / speed.y);
        float time_diff = deltaTime - time_to_wall;
        coordinates.x += speed.x * deltaTime;
        speed.y *= -1;
        coordinates.y = gameRef->mGameField->getVertexCoordinates()[2].y - radius + speed.y * time_diff;
        return;
    }
    
    // Check collision with left wall
    //if ( (coordinates.x - radius) < gameRef->mGameField->getVertexCoordinates()[0].x ) {
    //    speed.x *= -1;
    //}
    if ( (next_coord_x - radius) < gameRef->mGameField->getVertexCoordinates()[0].x ) {
        float distance_to_wall = coordinates.x - gameRef->mGameField->getVertexCoordinates()[0].x - radius;
        float time_to_wall = abs(distance_to_wall / speed.x);
        float time_diff = deltaTime - time_to_wall;
        coordinates.y += speed.y * deltaTime;
        speed.x *= -1;
        coordinates.x = gameRef->mGameField->getVertexCoordinates()[0].x + radius + speed.x * time_diff;
        return;
    }

    // Update coordinates accordingly to passed time if no collision happened
    coordinates.x += speed.x * deltaTime;
    coordinates.y += speed.y * deltaTime;
    
}


// function to render filled circle
// taken from https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c#file-circle-cpp-L58
int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
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

float Ball::getRadius() {
    return radius;
}
