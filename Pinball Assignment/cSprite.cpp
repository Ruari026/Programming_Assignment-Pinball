/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	this->spritePos_2D = { 0, 0, 0, 0 };
	this->spriteTexture = NULL;
	this->spriteCentre = {0, 0};
	this->spriteScale = { 1, 1 };
}

cSprite::cSprite(cTexture* theSpriteTexture) 			// Default constructor
{
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight());
	this->spritePos_2D = { 0, 0, this->spriteTexture->getTWidth(), this->spriteTexture->getTHeight() };
	this->spriteCentre = { this->spritePos_2D.w / 2, this->spritePos_2D.h / 2};
	this->spriteScale = { 1, 1 };
}


/*
=================
- Destructor
=================
*/
cSprite::~cSprite()			// Destructor
{
}


/*
=================
- Return the sprites current position.
=================
*/
SDL_Rect cSprite::getSpritePos()  // Return the sprites current position
{
	return this->spritePos_2D;
}


/*
=================
- set the position of the sprite.
=================
*/
void cSprite::setSpritePos(SDL_Rect sPosition)  // set the position of the sprite
{
	this->spritePos_2D.x = sPosition.x;
	this->spritePos_2D.y = sPosition.y;
	this->spritePos_2D.w = sPosition.w;
	this->spritePos_2D.h = sPosition.h;
}


/*
=================
- Return the sprites current image.
=================
*/
cTexture* cSprite::getTexture()  // Return the sprites current image
{
	return this->spriteTexture;
}


/*
=================
- set the image of the sprite.
=================
*/
void cSprite::setTexture(cTexture* theSpriteTexture)  // set the image of the sprite
{
	this->spriteTexture = theSpriteTexture;
	this->setSpriteDimensions(spriteTexture->getTWidth(), spriteTexture->getTHeight());
	this->spritePos_2D.w = textureWidth;
	this->spritePos_2D.h = textureHeight;
	this->spriteCentre = { this->spritePos_2D.w / 2, this->spritePos_2D.h / 2 };
}

void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, theScaling);
}

void cSprite::render(SDL_Renderer* theRenderer, SDL_Rect* theSourceRect, SDL_Rect* theDestRect, double rotAngle, SDL_Point* spriteCentre, FPoint theScaling)
{
	this->spriteTexture->renderTexture(theRenderer, this->spriteTexture->getTexture(), theSourceRect, theDestRect, rotAngle, spriteCentre, theScaling);
}


/*
=================
- Set the sprite dimensions.
=================
*/
void cSprite::setSpriteDimensions(int tWidth, int tHeight)
{
	this->textureWidth = tWidth;
	this->textureHeight = tHeight;
	this->spriteDimensions = { 0, 0, tWidth, tHeight };
}


/*
=================
- Get the sprite dimensions.
=================
*/
SDL_Rect cSprite::getSpriteDimensions()
{
	return this->spriteDimensions;
}


/*
=================
- Return the sprite centre.
=================
*/
SDL_Point cSprite::getSpriteCentre()  // Return the sprites current position
{
	return this->spriteCentre;
}


/*
=================
- set the the sprite centre.
=================
*/
void cSprite::setSpriteCentre(SDL_Point sCentre)  // set the position of the sprite
{
	this->spriteCentre.x = sCentre.x;
	this->spriteCentre.y = sCentre.y;
}


/*
=================
- Return the sprite scaling.
=================
*/
FPoint cSprite::getSpriteScale()  // Return the sprites current scaling
{
	return this->spriteScale;
}


/*
=================
- set the the sprite scale.
=================
*/
void cSprite::setSpriteScale(FPoint sScale)  // set the sprites current scaling
{
	this->spriteScale.X += sScale.X;
	this->spriteScale.Y += sScale.Y;
}


/*
=================
- Update sprite scale.
=================
*/
void cSprite::scaleSprite()  // set the sprites current scaling
{
	// Scale sprite
	this->spritePos_2D.w = (int)(this->spriteDimensions.w * this->spriteScale.X);
	this->spritePos_2D.h = (int)(this->spriteDimensions.h * this->spriteScale.Y);
	// Scale Sprite Centre for rotation.
	this->spriteCentre.x = this->spritePos_2D.w / 2;
	this->spriteCentre.y = this->spritePos_2D.h / 2;
}


/*
=================================================================
- Box Collisions
=================================================================
*/
void cSprite::SetBoundingRect()
{
	SDL_Rect sPos = getSpritePos();
	SDL_Rect sDim = getSpriteDimensions();

	boxCollider = { sPos.x,sPos.y,sDim.w,sDim.h };
}

SDL_Rect cSprite::GetBoundingRect()
{
	return cSprite::boxCollider;
}

bool cSprite::CollidedWithBox(SDL_Rect* thisSprite, SDL_Rect* otherSprite)
{
	//Performs the intersection test
	if (SDL_HasIntersection(thisSprite, otherSprite))
		return true;
	else
		return false;
}


/*
=================================================================
- Per Pixel Collisions
=================================================================
*/
void cSprite::SetCollidablePixels(SDL_Renderer* theRenderer, SDL_Window* theWindow, string spritePath)
{
	//Getting the sprite
	SDL_Surface* loadedSurface = IMG_Load(spritePath.c_str());
	SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(theWindow), NULL);
	SDL_Texture* theTexture = SDL_CreateTexture(theRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);

	int pitch;
	void* pixels;

	SDL_LockTexture(theTexture, NULL, &pixels, &pitch);

	//Getting Pixel Information
	memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch*formattedSurface->h);
	Uint32* spritePixels = (Uint32*)pixels;
	int pixelCount = (textureWidth * textureHeight);

	pixelInformation = new bool*[textureHeight];
	for (int i = 0; i < textureHeight; i++)
	{
		pixelInformation[i] = new bool[textureWidth];
	}

	int h = 0, w = 0;
	for (int i = 0; i < pixelCount; ++i)
	{
		if (w >= textureWidth)
		{
			w = 0;
			h++;
		}

		//Getting the pixel's RGBA information
		Uint8 r, g, b, a;
		SDL_PixelFormat* mappingFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
		SDL_GetRGBA(spritePixels[i], mappingFormat, &r, &g, &b, &a);

		//Converts the values to a number between 0 & 255
		int rValue = (int)r, gValue = (int)g, bValue = (int)b, aValue = (int)a;

		//Acting on what colour the pixel is
		if (aValue < 50) //Transparent pixels
		{
			pixelInformation[h][w] = false;
		}
		else
		{
			pixelInformation[h][w] = true;
		}
		w++;
	}
}

void cSprite::OptimizeCollidablePixels()
{
	//Top Side of the Sprite
	for (int w = 0; w < textureWidth; w++)
	{
		bool b = false;

		for (int h = 0; h < textureHeight; h++)
		{
			if (!b)
			{
				if (pixelInformation[h][w] == true)
				{
					b = true;
					
					bool canAdd = true;
					for (int i = 0; i < collidablePoints.size(); i++)
					{
						if (collidablePoints[i].x == h)
						{
							if (collidablePoints[i].y == w)
							{
								canAdd = false;
							}
						}
					}

					if (canAdd)
					{
						collidablePoints.push_back({ h,w });
					}
				}
			}
		}
	}

	//Bottom Side of the Sprite
	for (int w = 0; w < textureWidth; w++)
	{
		bool b = false;

		for (int h = textureHeight - 1; h > 0; h--)
		{
			if (!b)
			{
				if (pixelInformation[h][w] == true)
				{
					b = true;

					bool canAdd = true;
					for (int i = 0; i < collidablePoints.size(); i++)
					{
						if (collidablePoints[i].x == h)
						{
							if (collidablePoints[i].y == w)
							{
								canAdd = false;
							}
						}
					}

					if (canAdd)
					{
						collidablePoints.push_back({ h,w });
					}
				}
			}
		}
	}

	//Right Side of the Sprite
	for (int h = 0; h < textureHeight; h++)
	{
		bool b = false;

		for (int w = 0; w < textureWidth; w++)
		{
			if (!b)
			{
				if (pixelInformation[h][w] == true)
				{
					b = true;

					bool canAdd = true;
					for (int i = 0; i < collidablePoints.size(); i++)
					{
						if (collidablePoints[i].x == h)
						{
							if (collidablePoints[i].y == w)
							{
								canAdd = false;
							}
						}
					}

					if (canAdd)
					{
						collidablePoints.push_back({ h,w });
					}
				}
			}
		}
	}

	//Left Side of the Sprite
	for (int h = 0; h < textureHeight; h++)
	{
		bool b = false;

		for (int w = textureWidth - 1; w > 0; w--)
		{
			if (!b)
			{
				if (pixelInformation[h][w] == true)
				{
					b = true;

					bool canAdd = true;
					for (int i = 0; i < collidablePoints.size(); i++)
					{
						if (collidablePoints[i].x == h)
						{
							if (collidablePoints[i].y == w)
							{
								canAdd = false;
							}
						}
					}

					if (canAdd)
					{
						collidablePoints.push_back({ h,w });
					}
				}
			}
		}
	}
}

void cSprite::SetPixelPositions()
{
	for (int i = 0; i < collidablePoints.size(); i++)
	{
		collidablePoints[i] = { (collidablePoints[i].y + getSpritePos().x),(collidablePoints[i].x + getSpritePos().y) };
	}
}

vector<SDL_Point> cSprite::GetCollisionPoints()
{
	return collidablePoints;
}

bool cSprite::CollidedWithPixels(SDL_Point ballPos, vector<SDL_Point> spriteCollisionPoints)
{
	vector<SDL_Point> collidedPoints;

	for (int i = 0; i < spriteCollisionPoints.size(); i++)
	{
		SDL_Point pixelPos = spriteCollisionPoints[i];

		float distanceX = pixelPos.x - ballPos.x;
		float distanceY = pixelPos.y - ballPos.y;

		float distanceToPixel = sqrt((distanceX*distanceX) + (distanceY*distanceY));

		if (distanceToPixel < 25)
		{
			collidedPoints.push_back(pixelPos);
		}
	}

	if (collidedPoints.size() > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}