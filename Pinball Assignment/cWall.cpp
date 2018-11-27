/*
=================
cWall.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cWall.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/
void cWall::initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path)
{
	//Box Collision
	SetBoundingRect();

	//Per Pixel Collision
	SetCollidablePixels(theRenderer, theWindow, path);
	OptimizeCollidablePixels();
	SetPixelPositions();

}


/*
=================================================================
Update the sprite
=================================================================
*/
void cWall::update(double deltaTime)
{

}