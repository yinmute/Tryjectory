//
//  Field.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 2/25/21.
//
// Field class implementation

#include "Field.h"

Field::Field(Game* game) {
    gameRef = game;
}

void Field::Initialize() {
    
    mVertexCoordinates.push_back( {100.00, 100.00} );
    mVertexCoordinates.push_back( {900.00, 100.00} );
    mVertexCoordinates.push_back( {900.00, 600.00} );
    mVertexCoordinates.push_back( {100.00, 600.00} );

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


