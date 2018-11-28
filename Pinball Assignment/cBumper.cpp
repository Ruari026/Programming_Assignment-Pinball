/*
=================
cBumper.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBumper.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/
void cBumper::initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path)
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
void cBumper::update(double deltaTime)
{

}


/*
=================================================================
Bumper Point Values
=================================================================
*/
void cBumper::SetBumperValue(int value)
{
	bumperValue = value;
}

int cBumper::GetBumperValue()
{
	return bumperValue;
}