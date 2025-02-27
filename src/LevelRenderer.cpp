#include "../inc/LevelRenderer.h"
#include "SDL/SDL.h"
#include "Texture.h"

LevelRenderer::LevelRenderer() : foreGroundTexture(0),
	middleGroundTexture(0),
	xScroll(0),
	yScroll(0)
{
}

void LevelRenderer::Exit(void)
{
}

void LevelRenderer::Init(Texture* foreGround, Texture* middleGround, Texture* backGround)
{
	xScroll =0;
	yScroll = 0;
	foreGroundTexture = foreGround;
	middleGroundTexture = middleGround;
	backGroundTexture = backGround;

	//for (int i = 0; i < foreGroundTexture->mWidth*foreGroundTexture->mHeight; i++)
	//{
	//	unsigned int pixel = ((unsigned int*)(foreGroundTexture->surface->pixels))[i];
	//	unsigned int* ppixel = ((unsigned int*)(foreGroundTexture->surface->pixels))+i;
	//	if( pixel != 0x00000000)
	//	{
	//		unsigned int alpha = pixel & 0xff000000;
	//		alpha = alpha >> 24;
	//	}
	//}

	// hack
	foreGroundTexture->surface->format->Amask = 0xff000000;
	foreGroundTexture->surface->format->Ashift = 24;
	if (foreGroundTexture != 0)
		SDL_SetAlpha(foreGroundTexture->surface, SDL_SRCALPHA | SDL_RLEACCEL, 128);
		//SDL_SetColorKey(foreGroundTexture->surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0x00000000);

	middleGroundTexture->surface->format->Amask = 0xff000000;
	middleGroundTexture->surface->format->Ashift = 24;
	if (middleGroundTexture != 0)
		SDL_SetAlpha(middleGroundTexture->surface, SDL_SRCALPHA | SDL_RLEACCEL, 128);
		//SDL_SetColorKey(middleGroundTexture->surface, SDL_SRCCOLORKEY | SDL_RLEACCEL, 0x00000000);



}

void LevelRenderer::Render(Texture* sb, int layer)
{
	SDL_Rect sourceRect;
	sourceRect.x = (short)xScroll;
	sourceRect.y = (short)yScroll;
	sourceRect.w = (unsigned short)foreGroundTexture->mWidth;
	sourceRect.h = (unsigned short)foreGroundTexture->mHeight;

	SDL_Rect bgSourceRect;
	bgSourceRect.x = (short)xScroll/2;
	bgSourceRect.y = (short)yScroll;
	bgSourceRect.w = (unsigned short)foreGroundTexture->mWidth;
	bgSourceRect.h = (unsigned short)foreGroundTexture->mHeight;


	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	//destRect.w = sb->mWidth;
	//destRect.h = sb->mHeight;
	//if (levelTexture->surface->w > sb->surface->w)

	/* Blit onto the screen surface */
	if (layer == 0)
	{
		if(SDL_BlitSurface(backGroundTexture->surface, &bgSourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	}
	else if (layer == 1)
	{
		if(SDL_BlitSurface(middleGroundTexture->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	}
	else if (layer == 2)
	{
		if(SDL_BlitSurface(foreGroundTexture->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	}


	//SDL_UpdateRect(sb->surface, 0, 0, sb->mWidth, sb->mHeight);
}
