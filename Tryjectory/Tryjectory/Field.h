//
//  Field.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/3/21.
//
// Field class

#ifndef Field_h
#define Field_h


#endif /* Field_h */

#include "Vector.h"
#include <vector>
#include "Game.h"

using namespace std;

class Field {
    
    
public:
    
    // Dependency injection to game object
    Game* gameRef;
    
    Field(Game& game);
    
    // Initialize the field and randomize values
    void Initialize();
    
    //
    void DrawToScreen();
    
    // Getter function for returning vertex coordinates
    vector<Vector2> getVertexCoordinates();
    
private:
  
    // Vertex coordinates for the field
    vector<Vector2> vertexCoordinates;
    

    
    
};


