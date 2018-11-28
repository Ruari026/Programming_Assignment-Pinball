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
	ballPositionX = (WINDOW_WIDTH / 2) - 25;
	ballPositionY = (WINDOW_HEIGHT - 200);
	setSpritePos({ (int)ballPositionX,(int)ballPositionY });

	ballVelocity.X = 0;
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
	float gravity = 2; //Only Acts On the Y Axis
	float timeStep = 0.5f;
	float airResistance = 0.025f; //Acts On The X and Y Axis

	ballVelocity.X = ((ballVelocity.X) / (-1 * airResistance)) * (-1 * airResistance) * exp(-1 * airResistance*timeStep);
	ballVelocity.Y = (gravity * timeStep) + ballVelocity.Y;
}

void cBall::CalculateBallPosition()
{
	float gravity = 2; //Only Acts on the Y Axis
	float timeStep = 0.5f;
	float airResistance = 0.025f; //Acts On The X and Y Axis

	ballPositionX = (ballPositionX - (ballVelocity.X / (-1 * airResistance))) + (ballVelocity.X / (-1 * airResistance))*exp(-1 * airResistance * timeStep);
	ballPositionY = ((gravity * timeStep) / 2) + (ballVelocity.Y * timeStep) + ballPositionY;
}

void cBall::SetBallPosition()
{
	SDL_Rect newPos = getSpritePos();

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
		SDL_Point collisionSurface = { (collisionPoints[collisionPoints.size() - 1].x - collisionPoints[0].x),(collisionPoints[collisionPoints.size() - 1].y - collisionPoints[0].y) };
		cout << "Collision Surface: " << collisionSurface.x << " " << collisionSurface.y << endl;
		
		if (collisionSurface.x == 0)
		{
			cout << "Surface Angle: 90" << endl;
		}
		else
		{
			float angle = (0 - collisionSurface.y) / (0 - collisionSurface.x);
			angle = atan(angle);
			cout << "Surface Angle: " << angle << endl;
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
		cout << "Normal Degrees: " << degrees << endl;

		//Reflecting the ball's velocity
		float inputVelocityX = ballVelocity.X * -0.9f;
		float inputVelocityY = ballVelocity.Y * -0.9f;
		cout << "Input Velocity: " << inputVelocityX << " " << inputVelocityY << endl;

		float reflectionRadians = degrees * PI / 180;

		float outputVelocityX = (inputVelocityX * cos(2 * reflectionRadians)) + (inputVelocityY * sin(2 * reflectionRadians));
		float outputVelocityY = (inputVelocityX * sin(2 * reflectionRadians)) - (inputVelocityY * cos(2 * reflectionRadians));
		cout << "Output Velocity: " << outputVelocityX << " " << outputVelocityY << endl;

		//Setting the new velocity
		ballVelocity.X = (int)outputVelocityX;
		ballVelocity.Y = (int)outputVelocityY;

		//Moving the ball outside of the collider
		while (collisionPoints.size() > 0)
		{
			float magnitude = sqrt((outputVelocityX*outputVelocityX) + (outputVelocityY*outputVelocityY));
			float movementX = outputVelocityX / magnitude;
			float movementY = outputVelocityY / magnitude;

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

				if (distanceToPixel < 26)
				{
					collisionPoints.push_back(pixelPos);
				}
			}
		}
		canCollide = false;
		cout << "--------------------" << endl << endl;
	}
}
