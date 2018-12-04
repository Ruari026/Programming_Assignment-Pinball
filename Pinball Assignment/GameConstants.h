#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Windows & SDL 
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std::chrono;

#include <SDL.h>
// Image Texture loading library
#include <SDL_image.h>
// Font loading library
#include <SDL_ttf.h>
// Sound loading library
#include <SDL_mixer.h>

// Maths functions
#include <math.h>
constexpr auto PI = 3.14159265;

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "Programming Assignment - Pinball"

//Defining the window size
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1000

// This header file contains all the constants & enumarated types for the game
typedef struct fpoint
{
	float  X;
	float  Y;
}FPoint;

inline SDL_Point operator+(SDL_Point const &a, SDL_Point const &b)
{
	return SDL_Point{ a.x + b.x , a.y + b.y };
}

enum class gameState {mainMenu, instructions, gameScene, hiScores, exit};
enum class textType { solid, blended, shaded };
enum class soundType {music, sfx };
enum class FlipperType { LEFT, RIGHT };
enum class ButtonType {play,instruction,exit};

#endif