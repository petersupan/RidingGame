#include "../inc/LevelCollider.h"
#include "SDL/SDL.h"
#include "Texture.h"

LevelCollider::LevelCollider(Texture* lev) :
	xPos(400),
	yPos(50),
	currentGround(0)
{
	collTexture = lev;
}

int LevelCollider::GetHighestFloor(void)
{
	unsigned char* pixels = (unsigned char*)collTexture->mPixels[0];
	int i = 0;
	for (i = 0; i < (int)collTexture->mHeight; i++)
	{
		int index = i*collTexture->mWidth + xPos;
		if(pixels[index] < 250)
		{
			currentGround = pixels[index+ collTexture->mWidth*2];
			return i;
		}
	}
	return i;
}

int LevelCollider::GetFloorBelow()
{
	return GetFloorBelow(xPos, yPos);
}

int LevelCollider::GetSlope(int currentHeight)
{
	currentHeight = GetFloorBelow(xPos - 20, yPos);
	int futureHeight = GetFloorBelow(xPos + 20, yPos);
	int difference = futureHeight - currentHeight;
	return difference;
}

int LevelCollider::GetFloorBelow(int x, int y)
{
	unsigned char* pixels = (unsigned char*)collTexture->mPixels[0];
	int i = 0;
	if (pixels[(y-3)*collTexture->mWidth + x] < 250)
	{
        for (i = y-3; i > 0; i--)
        {
            int index = i*collTexture->mWidth + x;
            if(pixels[index] > 249)
            {
                currentGround = pixels[index+ collTexture->mWidth*2];
                return i;
            }
        }
	}
	else
	{
        for (i = y-3; i < (int)collTexture->mHeight; i++)
        {
            int index = i*collTexture->mWidth + x;
            if(pixels[index] < 250)
            {
                currentGround = pixels[index+ collTexture->mWidth*2];
                return i;
            }
        }
	}
	return i;
}

float LevelCollider::GetCurrentGroundSpeed(void)
{

	float groundSpeed = 255.0f-(float)currentGround;
	groundSpeed /= 255.0f;
	return groundSpeed;
}






//void LevelRenderer::Render(Texture* sb)
//{
//	SDL_Rect sourceRect;
//	sourceRect.x = (short)xScroll;
//	sourceRect.y = (short)yScroll;
//	sourceRect.w = (unsigned short)levelTexture->mWidth;
//	sourceRect.h = (unsigned short)levelTexture->mHeight;
//
//
//	SDL_Rect destRect;
//	destRect.x = 0;
//	destRect.y = 0;
//	//destRect.w = sb->mWidth;
//	//destRect.h = sb->mHeight;
//	//if (levelTexture->surface->w > sb->surface->w)
//
//	/* Blit onto the screen surface */
//	if(SDL_BlitSurface(levelTexture->surface, &sourceRect, sb->surface, &destRect) < 0)
//        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
//
//	SDL_UpdateRect(sb->surface, 0, 0, sb->mWidth, sb->mHeight);
//}
