#include "../inc/ObstacleCollider.h"
#include "SDL/SDL.h"
#include "Texture.h"

ObstacleCollider::ObstacleCollider(Texture* lev) :
	xPos(50),
	yPos(50)
{
	collTexture = lev;
}

ObstacleCollider::~ObstacleCollider()
{

}

int ObstacleCollider::GetHighestObstacle(void)
{
	unsigned char* pixels = (unsigned char*)collTexture->mPixels[0];
	int i = 0;
	for (i = 0; i < (int)collTexture->mHeight; i++)
	{
		int index = i*collTexture->mWidth + xPos;
		if(pixels[index] == 0)
		{
			return i;
		}
	}
	return i;
}

int ObstacleCollider::GetObstacleBelow(void)
{
	unsigned char* pixels = (unsigned char*)collTexture->mPixels[0];
	int i = 0;
	//printf("starting at %i", yPos);
	for (i = yPos-30; i < (int)collTexture->mHeight; i++)
	{
		int index = i*collTexture->mWidth + xPos;
		if(pixels[index] == 0)
		{
			return i;
		}
	}
	return i;
}
