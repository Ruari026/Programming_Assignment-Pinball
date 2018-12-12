/*
=================
cBall.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBall.h"

/*
=================================================================
Initialise the sprite variables
=================================================================
*/
void cBall::initialise()
{
	ballPositionX = (WINDOW_WIDTH / 2 - 25);
	ballPositionY = ((WINDOW_HEIGHT / 2) - 100);
	setSpritePos({ (int)ballPositionX,(int)ballPositionY });

	//Randomiser
	random_device rd;
	mt19937 gen{ rd() };
	uniform_int_distribution<> random{ 0,1 };
	int direction = random(gen);
	if (direction == 0)
	{
		ballVelocity.X = 10;
	}
	else
	{
		ballVelocity.X = -10;
	}
	ballVelocity.Y = 0;
}


/*
=================================================================
Update the sprite position
=================================================================
*/
void cBall::update(double deltaTime)
{

}


/*
=================================================================
  Movement Calculation Based on forces acting on the ball
=================================================================
*/
void cBall::CalculateBallVelocity()
{
	float gravity = -2; //Only Acts On the Y Axis
	float timeStep = 0.5f;
	float airResistance = 0.02f; //Acts On The X and Y Axis

	ballVelocity.X = ((ballVelocity.X) / (-1 * airResistance)) * (-1 * airResistance) * exp(-1 * airResistance*timeStep);
	ballVelocity.Y = (-1 * airResistance) * (((ballVelocity.Y) + (gravity / airResistance)) / (-1 * airResistance)) * exp((-1 * airResistance * timeStep)) - ((gravity) / (airResistance));

	float velocityMagnitude = sqrt((ballVelocity.X * ballVelocity.X) + (ballVelocity.Y * ballVelocity.Y));
}

void cBall::CalculateBallPosition()
{
	float gravity = 2; //Only Acts on the Y Axis
	float timeStep = 0.5f;
	float airResistance = 0.02f; //Acts On The X and Y Axis

	ballPositionX = (ballPositionX - (ballVelocity.X / (-1 * airResistance))) + (ballVelocity.X / (-1 * airResistance))*exp(-1 * airResistance * timeStep);
	ballPositionY = ((gravity * timeStep) / 2) + (ballVelocity.Y * timeStep) + ballPositionY;
}

void cBall::SetBallPosition()
{
	SDL_Point newPos = { getSpritePos().x, getSpritePos().y };

	newPos.x = (int)ballPositionX;
	newPos.y = (int)ballPositionY;

	setSpritePos(newPos);
}


/*
=================================================================
  Sets the velocity for the ball
=================================================================
*/
void cBall::DetectBasicCollisions()
{
	//Top Wall
	if (ballPositionY < 0 && ballVelocity.Y < 0)
	{
		ballPositionY = 0;
		ballVelocity.Y *= -0.9;
	}

	//Left Wall
	if (ballPositionX < 0 && ballVelocity.X < 0)
	{
		ballPositionX = 0;
		ballVelocity.X *= -0.9;
	}

	//Bottom Wall
	if (ballPositionY > (WINDOW_HEIGHT - 50) && ballVelocity.Y > 0)
	{
		ballPositionY = (WINDOW_HEIGHT - 50);
		ballVelocity.Y *= -0.9;
	}

	//Right Wall
	if (ballPositionX > (WINDOW_WIDTH - 50) && ballVelocity.X > 0)
	{
		ballPositionX = (WINDOW_WIDTH - 50);
		ballVelocity.X *= -0.9;
	}
}


/*
=================================================================
  Sets the velocity for the ball
=================================================================
*/
void cBall::addForceToBall(int forceX, int forceY)
{
	ballVelocity.X += forceX;
	ballVelocity.Y += forceY;
}


/*
=================================================================
  Gets the ball's velocity
=================================================================
*/
FPoint cBall::getBallVelocity()
{
	return ballVelocity;
}


/*
=================================================================
  Respawning the ball
=================================================================
*/
void cBall::RespawnBall(int posX, int posY)
{
	ballPositionX = posX;
	ballPositionY = posY;

	ballVelocity.X = 0;
	ballVelocity.Y = 0;
}


/*
=================================================================
Sets the rotation angle for the ball
=================================================================
*/
void cBall::setBallRotation(double theRotAngle)
{
	ballRotAngle = theRotAngle;
}


/*
=================================================================
Gets the rotation angle for the ball
=================================================================
*/
double cBall::getBallRotation()
{
	return ballRotAngle;
}

/*
=================================================================
Determining if the ball has collided with anything
=================================================================
*/
void cBall::CalculateCollisions(vector<SDL_Point> otherCollidablePoints)
{
	vector<SDL_Point> collisionPoints;

	//Find what pixels are being collided with
	for (int i = 0; i < otherCollidablePoints.size(); i++)
	{
		SDL_Point pixelPos = otherCollidablePoints[i];
		SDL_Point ballPos = { (ballPositionX + getSpriteCentre().x), (ballPositionY + getSpriteCentre().y) };

		float distanceX = pixelPos.x - ballPos.x;
		float distanceY = pixelPos.y - ballPos.y;

		float distanceToPixel = sqrt((distanceX*distanceX) + (distanceY*distanceY));

		if (distanceToPixel < getSpriteCentre().x)
		{
			collisionPoints.push_back(pixelPos);
		}
	}

	if (collisionPoints.size() > 1 && canCollide)
	{
		cout << "-Collision-" << endl;
		cout << "--------------------" << endl;

		//Calculating the reflection line
		cout << "Reflection Calculation" << endl;
		SDL_Point collisionSurface = { (collisionPoints[collisionPoints.size() - 1].x - collisionPoints[0].x),(collisionPoints[collisionPoints.size() - 1].y - collisionPoints[0].y) };
		cout << "- Collision Surface: " << collisionSurface.x << " " << collisionSurface.y << endl;

		if (collisionSurface.x == 0)
		{
			cout << "- Surface Angle: 90" << endl;
		}
		else
		{
			float angle = (0 - collisionSurface.y) / (0 - collisionSurface.x);
			angle = atan(angle);
			cout << "- Surface Angle: " << angle << endl;
		}

		float normalRotRadians = 90 * PI / 180;
		float surfaceNormalX = (collisionSurface.y * -1);
		float surfaceNormalY = (collisionSurface.x);

		float degrees;
		if (surfaceNormalX == 0)
		{
			degrees = 90;
		}
		else
		{
			degrees = (atan(surfaceNormalY / surfaceNormalX)) * 180 / PI;
		}
		cout << "- Normal Degrees: " << degrees << endl;

		//Reflecting the ball's velocity
		float inputVelocityX = ballVelocity.X * -0.8f;
		float inputVelocityY = ballVelocity.Y * -0.8f;
		cout << "- Input Velocity: " << inputVelocityX << " " << inputVelocityY << endl;

		float reflectionRadians = degrees * PI / 180;

		float outputVelocityX = (inputVelocityX * cos(2 * reflectionRadians)) + (inputVelocityY * sin(2 * reflectionRadians));
		float outputVelocityY = (inputVelocityX * sin(2 * reflectionRadians)) - (inputVelocityY * cos(2 * reflectionRadians));
		cout << "- Output Velocity: " << outputVelocityX << " " << outputVelocityY << endl << endl;

		//Setting the new velocity
		ballVelocity.X = (int)outputVelocityX;
		ballVelocity.Y = (int)outputVelocityY;

		//Moving the ball outside of the collider
		cout << "Position Calculation" << endl;
		cout << "- Ball Start: " << (ballPositionX + getSpriteCentre().x) << " " << (ballPositionY + getSpriteCentre().y) << endl;
		SDL_Point closestPixel = otherCollidablePoints[0];
		float distanceToClosest = sqrt((((ballPositionX + getSpriteCentre().x) - closestPixel.x)*((ballPositionX + getSpriteCentre().x) - closestPixel.x)) + (((ballPositionY + getSpriteCentre().y) - closestPixel.y)*((ballPositionY + getSpriteCentre().y) - closestPixel.y)));
		for (int i = 1; i < otherCollidablePoints.size(); i++)
		{
			SDL_Point nextPixel = otherCollidablePoints[i];
			float distanceToNext = sqrt((((ballPositionX + getSpriteCentre().x) - nextPixel.x)*((ballPositionX + getSpriteCentre().x) - nextPixel.x)) + (((ballPositionY + getSpriteCentre().y) - nextPixel.y)*((ballPositionY + getSpriteCentre().y) - nextPixel.y)));

			if (distanceToNext < distanceToClosest)
			{
				closestPixel = nextPixel;
				distanceToClosest = distanceToNext;
			}
		}
		cout << "- Reference Point: " << closestPixel.x << " " << closestPixel.y << endl;

		float movementX = (ballPositionX + getSpriteCentre().x) - closestPixel.x;
		float movementY = (ballPositionY + getSpriteCentre().y) - closestPixel.y;
		cout << "- Movement Direction: " << movementX << " " << movementY << endl;

		float magnitude = sqrt((movementX*movementX) + (movementY*movementY));
		cout << "- Movement Magnitude: " << magnitude << endl;
		movementX /= magnitude;
		movementY /= magnitude;

		cout << "- Normalized Movement: " << movementX << " " << movementY << endl;
		while (collisionPoints.size() > 0)
		{
			ballPositionX += movementX;
			ballPositionY += movementY;

			//Checking if the ball is still colliding with any pixels
			collisionPoints.clear();
			for (int i = 0; i < otherCollidablePoints.size(); i++)
			{
				SDL_Point pixelPos = otherCollidablePoints[i];
				SDL_Point ballPos = { (ballPositionX + getSpriteCentre().x), (ballPositionY + getSpriteCentre().y) };

				float distanceX = pixelPos.x - ballPos.x;
				float distanceY = pixelPos.y - ballPos.y;

				float distanceToPixel = sqrt((distanceX*distanceX) + (distanceY*distanceY));

				if (distanceToPixel < 25)
				{
					collisionPoints.push_back(pixelPos);
				}
			}
		}
		cout << "- Ball End: " << ballPositionX << " " << ballPositionY << endl;
		canCollide = false;
		cout << "--------------------" << endl << endl;
	}
}
