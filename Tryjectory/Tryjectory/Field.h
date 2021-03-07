//
//  Field.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/3/21.
//
// Field class

#pragma once
#include "Vector.h"
#include <vector>
#include "SDL.h"
//#include "Game.h"

class Game;

using namespace std;

class Field {
    
    
public:
    
    Field(Game* game);
    
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
    
};


