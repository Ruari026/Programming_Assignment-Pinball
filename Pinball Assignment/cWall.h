/*
=================
cWall.h
- Header file for class definition - SPECIFICATION
- Header file for the Wall class which is a child of cSprite class
=================
*/
#ifndef _CWALL_H
#define _CWALL_H
#include "cSprite.h"

class cWall : public cSprite
{
private:

public:
	void initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path);
	void update(double deltaTime);		// Ball update method
	
};
#endif