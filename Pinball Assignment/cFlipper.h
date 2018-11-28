/*
=================
cFlipper.h
- Header file for class definition - SPECIFICATION
- Header file for the Flipper class which is a child of cSprite class
=================
*/
#ifndef _CFLIPPER_H
#define _CFLIPPER_H
#include "cSprite.h"

class cFlipper : public cSprite
{
private:
	FlipperType currentType;

	//Calculating Flipper Rotation and Position
	float flipperRotAngle = 0;
	SDL_Point flipperRotationPoint;
	vector<SDL_Point> rotatedCollisionPoints;

	//Running Flipper Animation
	bool activated = false;
	bool direction = true;


public:
	void initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path);
	void update(double deltaTime);		// Flipper update method

	void SetFlipperType(FlipperType newType);

	void SetFlipperRotation(float rotationAmount);
	float GetFlipperRotation();
	void SetFlipperRotationPoint(SDL_Point);
	void RotateCollisionPoints(float rotationAmount);
	vector<SDL_Point> GetRotatedCollisionPoints();
	SDL_Point RotateAroundPoint(SDL_Point pointToRotate, SDL_Point pointAround, float rotationAmount);

	void Activate();
	void LeftRotationAnimation(float deltaTime);
	void RightRotationAnimation(float deltaTime);
};
#endif