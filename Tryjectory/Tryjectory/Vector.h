//
//  Vector.h
//  Tryjectory
//
//  Created by Nesiolovskiy, Artem on 3/3/21.
//
// Vector definition

#pragma once

struct Vector2 {
    float x;
    float y;
};

bool twoPointsCompare(float x1, float y1, float x2, float y2, float epsilon);
