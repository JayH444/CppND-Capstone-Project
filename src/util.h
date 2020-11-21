#ifndef UTIL_H
#define UTIL_H

#include "SDL.h"
#include <iostream>
#include <string>

// Utility functions.

void ThrowError(std::string msg);

float RadToDeg(float n);
float DegToRad(float n);

/*struct Vector2 {

};*/

/*
// Some Python-esque utility functions:
int RandInt(int min, int max);
int RandFloat(float min, float max);
*/

#endif