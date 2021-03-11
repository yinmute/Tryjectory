//
//  Vector.cpp
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/3/21.
//

#include "Vector.h"
#include <cmath>

bool twoPointsCompare(float x1, float y1, float x2, float y2, float epsilon) {
    if (abs(x1 - x2) < epsilon && abs(y1 - y2) < epsilon) {
        return true;
    }
    return false;
}
    
