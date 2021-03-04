//
//  Field.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 2/25/21.
//
// Field class implementation

#include "Field.h"
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

Field::Field(Game* game) {
    gameRef = game;
}

void Field::Initialize(int screenWidth, int screenHeight) {
    
    /* initialize random seed: */
    srand (time(NULL));

    /* generate secret number between 9 and 11: */
    int random = rand() % 21 + 90;
    // Randomize size betwwen 0.9 and 1.1 of original size
    float sizeRandomSeed = random / 100.0;
    // Generate height
    float height = (3 * screenHeight) / 4;
    height *= sizeRandomSeed;
    cout << random << endl;
    random = rand() % 21 + 90;
    sizeRandomSeed = random / 100.0;
    // generate width
    float width = (3 * screenWidth) / 4;
    width *= sizeRandomSeed;
    cout << random << endl;
    
    float xStart = (screenWidth - width) / 2;
    float yStart = (screenHeight - height) / 2;
    
    mVertexCoordinates.push_back( {xStart, yStart} );
    mVertexCoordinates.push_back( {xStart + width, yStart} );
    mVertexCoordinates.push_back( {xStart + width, yStart + height} );
    mVertexCoordinates.push_back( {xStart, yStart + height} );
    
}

void Field::DrawToScreen(SDL_Renderer* renderer) {
    
    SDL_RenderDrawLine(renderer,
                       int(mVertexCoordinates[0].x), int(mVertexCoordinates[0].y),
                       int(mVertexCoordinates[1].x), int(mVertexCoordinates[1].y)
                       );
    
    SDL_RenderDrawLine(renderer,
                       int(mVertexCoordinates[1].x), int(mVertexCoordinates[1].y),
                       int(mVertexCoordinates[2].x), int(mVertexCoordinates[2].y)
                       );
    
    SDL_RenderDrawLine(renderer,
                       int(mVertexCoordinates[2].x), int(mVertexCoordinates[2].y),
                       int(mVertexCoordinates[3].x), int(mVertexCoordinates[3].y)
                       );
    
    SDL_RenderDrawLine(renderer,
                       int(mVertexCoordinates[3].x), int(mVertexCoordinates[3].y),
                       int(mVertexCoordinates[0].x), int(mVertexCoordinates[0].y)
                       );
    
}


