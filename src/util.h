#ifndef UTIL_H
#define UTIL_H

#include "SDL.h"
#include <iostream>
#include <string>
#include <utility>
#include <filesystem>
#include <unordered_map>
#include <random>
#include <vector>
#include <memory>

// Utility functions:
void ThrowError(std::string msg);
float RadToDeg(float n);
float DegToRad(float n);

// Global Variables:
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
namespace FS = std::filesystem;

struct Vector2 {
	Vector2() : _x(0), _y(0) {}

	Vector2(int x, int y) {
		_x = x;
		_y = y;
	}

	int _x;
	int _y;
};

#endif