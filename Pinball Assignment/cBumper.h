/*
=================
cBumper.h
- Header file for class definition - SPECIFICATION
- Header file for the Wall class which is a child of cSprite class
=================
*/
#ifndef _CBUMPER_H
#define _CBUMPER_H
#include "cSprite.h"

class cBumper : public cSprite
{
private:
	float resetTimer;
	int bumperValue;

public:
	void initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path);
	void update(double deltaTime);		// Bumper update method

	void SetBumperValue(int value);
	int GetBumperValue();

	void SetResetTimer();
	bool GetTimerState();

};
#endif