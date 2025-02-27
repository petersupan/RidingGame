#include "TimeRenderer.h"
#include "TextureRessourceManager.h"
#include "SDL/SDL.h"
#include "AnimatedTexture.h"

TimeRenderer::TimeRenderer()
{
	numberTexture = TextureRessourceManager::LoadAnimatedTexture("../images/numbers.bmp", 11);
	description = TextureRessourceManager::loadTexture("../images/timeImage.bmp");


	if(numberTexture != 0)
	{
		numberTexture->GetSurface()->format->Amask = 0xff000000;
		numberTexture->GetSurface()->format->Ashift = 24;
		SDL_SetAlpha(numberTexture->GetSurface(), SDL_SRCALPHA | SDL_RLEACCEL, 255);
	}

	if (description != 0)
	{
		description->surface->format->Amask = 0xff000000;
		description->surface->format->Ashift = 24;
		SDL_SetAlpha(description->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);
	}
}

TimeRenderer::~TimeRenderer()
{
	TextureRessourceManager::freeAnimatedTexture(numberTexture);
	TextureRessourceManager::freeTexture(description);
}

void TimeRenderer::RenderNumber(Texture* sb, int number, int x, int y)
{
	static SDL_Rect sourceRect;
	sourceRect.x = 0;

	sourceRect.y = (short)(number * numberTexture->mHeight);
	sourceRect.w = (unsigned short)numberTexture->mWidth;
	sourceRect.h = (unsigned short)numberTexture->mHeight;

	SDL_Rect destRect;
	destRect.x = (short)x;
	destRect.y = (short)y;

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(numberTexture->GetSurface(), &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
}

void TimeRenderer::RenderTime(Texture* sb, int x, int y, int timeInMilliseconds)
{
	int hundreds = timeInMilliseconds % 1000000 / 100000;
	int tens = timeInMilliseconds % 100000 / 10000;
	int ones = timeInMilliseconds % 10000 / 1000;
	int oneDivtens = timeInMilliseconds % 1000 / 100;
	//int oneDivHundreds = timeInMilliseconds % 100 / 10;

	RenderNumber(sb, hundreds, x, y);
	RenderNumber(sb, tens, x+30, y);
	RenderNumber(sb, ones, x+60, y);
	RenderNumber(sb, 10, x+80, y);
	RenderNumber(sb, oneDivtens, x+100, y);
	//RenderNumber(sb, oneDivHundreds, x+230, y);
}

void TimeRenderer::RenderDescription(Texture* sb, int x, int y)
{
	static SDL_Rect sourceRect;
	sourceRect.x = 0;

	sourceRect.y = 0;
	sourceRect.w = (unsigned short)description->mWidth;
	sourceRect.h = (unsigned short)description->mHeight;

	SDL_Rect destRect;
	destRect.x = (short)x;
	destRect.y = (short)y;

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(description->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
}
