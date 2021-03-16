//
//  Field.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/3/21.
//
// Field class

#pragma once

#include <vector>

#include "Vector.h"
#include "SDL.h"

//class Game;

using namespace std;

class Field {
    
public:
    
    Field(class Game* game);
    
    // Initialize the field and randomize values
    void Initialize(int screenWidth, int screenHeight);
    
    // Will draw the field to the screen
    void DrawToScreen(SDL_Renderer* renderer);
    
    // Getter function for returning vertex coordinates
    vector<Vector2> getVertexCoordinates();
    
    // Returns Width of the field
    float getWidth();
    
    // Returns Height of the field
    float getHeight();
    
    // Returns top line vector
    vector<Vector2> getTopLineVector();
    
    // Generates pockets coordinates based on ball radius
    void generatePocketCoords();
    
private:
  
    // Vertex coordinates for the field
    vector<Vector2> mVertexCoordinates;
    
    // Dependency injection to game object
    Game* gameRef;
    
    // Width of the field
    float width;
    
    // Height of the field
    float height;
    
    vector<Vector2> topLine;
    vector<Vector2> bottomLine;
    vector<Vector2> rightLine;
    vector<Vector2> leftLine;
    
    Vector2 topLeftPocket;
    Vector2 topRightPocket;
    Vector2 bottomRightPocket;
    Vector2 bottomLeftPocket;
    
    // Flag indicating that pockets were generated
    bool pocketsGenerated;
    
};


