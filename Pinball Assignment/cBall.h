/*
=================
cBall.h
- Header file for class definition - SPECIFICATION
- Header file for the Ball class which is a child of cSprite class
=================
*/
#ifndef _CBALL_H
#define _CBALL_H
#include "cSprite.h"

class cBall : public cSprite
{
private:
	double ballRotAngle;
	float ballPositionX, ballPositionY;
	FPoint ballVelocity;

public:
	void initialise();
	void update(double deltaTime);		// Ball update method
	void addForceToBall(int forceX, int forceY);   // Sets the velocity for the ball
	FPoint getBallVelocity();				 // Gets the ball's velocity
	void setBallRotation(double theRotAngle);   // Sets the rotation angle for the ball
	double getBallRotation();				 // Gets the rotation angle for the ball's velocity

	void CalculateBallVelocity();
	void CalculateBallPosition();
	void SetBallPosition();
	void DetectBasicCollisions();
	void CalculateCollisions(vector<SDL_Point> otherCollidablePoints); //Calculating if the ball has collided with anything
};
#endif