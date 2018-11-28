/*
=================
cFlipper.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cFlipper.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/
void cFlipper::initialise(SDL_Window* theWindow, SDL_Renderer* theRenderer, string path)
{

	//Box Collision
	SetBoundingRect();

	//Per Pixel Collision
	SetCollidablePixels(theRenderer, theWindow, path);
	OptimizeCollidablePixels();
	SetPixelPositions();
	rotatedCollisionPoints = GetCollisionPoints();

	//Setting Rotation Variables (Dependant of what side the flipper is on)
	switch (currentType)
	{
		case (FlipperType::LEFT):
		{
			SetFlipperRotationPoint({ (getSpritePos().x + 25), (getSpritePos().y + 25) });
			SetFlipperRotation(20);
		}
		break;

		case (FlipperType::RIGHT):
		{
			SetFlipperRotationPoint({ (getSpritePos().x + 200 - 25), (getSpritePos().y + 25) });
			SetFlipperRotation(160);
		}
		break;
	}
}

void cFlipper::SetFlipperType(FlipperType newType)
{
	currentType = newType;
}


/*
=================================================================
Update the sprite
=================================================================
*/
void cFlipper::update(double deltaTime)
{
	//Running Animations
	if (activated)
	{
		switch (currentType)
		{
		case (FlipperType::LEFT):
			{
				LeftRotationAnimation(deltaTime);
			}
			break;

		case (FlipperType::RIGHT):
			{
				RightRotationAnimation(deltaTime);
			}
			break;
		}
	}

	//Updating Collision Points
	RotateCollisionPoints(flipperRotAngle);
}


/*
=================================================================
Sprite Rotation Methods
=================================================================
*/
void cFlipper::SetFlipperRotationPoint(SDL_Point newRotationPoint)
{
	flipperRotationPoint.x = newRotationPoint.x;
	flipperRotationPoint.y = newRotationPoint.y;
}

void cFlipper::SetFlipperRotation(float rotationAmount)
{
	flipperRotAngle = rotationAmount;

	SDL_Rect newPos = getSpritePos();

	float radians = (flipperRotAngle * (PI / -180.0f));

	newPos.x = (flipperRotationPoint.x - 100) - (-75 * cos(radians));
	newPos.y = (flipperRotationPoint.y - 25) - (75 * sin(radians));

	setSpritePos(newPos);
}

float cFlipper::GetFlipperRotation()
{
	return flipperRotAngle;
}


/*
=================================================================
Setting the Collision Points According to Rotation
=================================================================
*/
void cFlipper::RotateCollisionPoints(float rotationAmount)
{
	vector<SDL_Point> basePoints = GetCollisionPoints();

	for (int i = 0; i < rotatedCollisionPoints.size(); i++)
	{
		switch (currentType)
		{
			case (FlipperType::LEFT):
			{
				rotatedCollisionPoints[i] = RotateAroundPoint(basePoints[i], flipperRotationPoint, (rotationAmount * -1));
			}
			break;

			case (FlipperType::RIGHT):
			{
				rotatedCollisionPoints[i] = { (basePoints[i].x + 150),basePoints[i].y };
				rotatedCollisionPoints[i] = RotateAroundPoint(rotatedCollisionPoints[i], flipperRotationPoint, (rotationAmount));
			}
			break;
		}
	}
}

SDL_Point cFlipper::RotateAroundPoint(SDL_Point pointToRotate, SDL_Point pointAround, float rotationAmount)
{
	SDL_Point newPoint = pointToRotate;
	float newX = newPoint.x;
	float newY = newPoint.y;

	//Moving point to origin
	newX -= pointAround.x;
	newY -= pointAround.y;

	//Rotating around origin
	float radians = (rotationAmount * (PI / -180.0f));

	newX = (newX * cos(radians)) - (newY * sin(radians));
	newY = (newX * sin(radians)) + (newY * cos(radians));

	//Moving back to point
	newX += pointAround.x;
	newY += pointAround.y;

	newPoint.x = (int)newX;
	newPoint.y = (int)newY;
	return newPoint;
}

vector<SDL_Point> cFlipper::GetRotatedCollisionPoints()
{
	return rotatedCollisionPoints;
}


/*
=================================================================
Sprite Animation Methods
=================================================================
*/
void cFlipper::Activate()
{
	activated = true;
}

void cFlipper::LeftRotationAnimation(float deltaTime)
{
	//Getting the new rotation
	if (direction)
	{
		flipperRotAngle += (-180 * deltaTime);
	}
	else
	{
		flipperRotAngle += (180 * deltaTime);
	}

	//Halfway through animation
	if (direction && flipperRotAngle < -45)
	{
		direction = false;
	}

	//Animation End
	if (!direction && flipperRotAngle > 21)
	{
		flipperRotAngle = 20;
		direction = true;
		activated = false;
	}

	//Applys the needed rotation
	SetFlipperRotation(flipperRotAngle);
}

void cFlipper::RightRotationAnimation(float deltaTime)
{
	//Getting the new rotation
	if (direction)
	{
		flipperRotAngle += (180 * deltaTime);
	}
	else
	{
		flipperRotAngle += (-180 * deltaTime);
	}

	//Halfway through animation
	if (direction && flipperRotAngle > 225)
	{
		direction = false;
	}

	//Animation End
	if (!direction && flipperRotAngle < 159)
	{
		flipperRotAngle = 160;
		direction = true;
		activated = false;
	}

	//Applys the needed rotation
	SetFlipperRotation(flipperRotAngle);
}