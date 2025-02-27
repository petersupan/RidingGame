#include "../inc/SpriteRenderer.h"
#include "SDL/SDL.h"
#include "AnimatedTexture.h"
#include <assert.h>

SpriteRenderer::SpriteRenderer(AnimatedTexture* spr) :
	xPos(0),
	yPos(0)
{
	spriteTexture = spr;
	if(spr != 0)
	{
		spr->GetSurface()->format->Amask = 0xff000000;
		spr->GetSurface()->format->Ashift = 24;
		SDL_SetAlpha(spr->GetSurface(), SDL_SRCALPHA | SDL_RLEACCEL, 255);
		//SDL_SetColorKey(spr->GetSurface(), SDL_SRCCOLORKEY, 0x00000000);
		//for (int i = 0; i < spr->mWidth * spr->mHeight; i++)
		//{
		//	unsigned int* pixels = (unsigned int*)(spr->surface->pixels);
		//	unsigned int alpha = pixels[i] & spr->surface->format->Amask;
		//	if (alpha != 0)
		//		printf("alpha: %i\n", alpha);
		//}
	}
}


void SpriteRenderer::Render(Texture* sb)
{
	SDL_Rect sourceRect;
	sourceRect.x = 0;//(short)xPos;

	int curFrame = spriteTexture->GetCurrentFrame();
	sourceRect.y = (short)(curFrame * spriteTexture->mHeight);//(short)yPos;
	sourceRect.w = (unsigned short)spriteTexture->mWidth;//(unsigned short)levelTexture->mWidth;
	sourceRect.h = (unsigned short)spriteTexture->mHeight;//(unsigned short)levelTexture->mHeight;

	SDL_Rect destRect;
	destRect.x = (short)xPos;
	destRect.y = (short)yPos;
	//destRect.w = sb->mWidth;
	//destRect.h = sb->mHeight;
	//if (levelTexture->surface->w > sb->surface->w)

	/* Blit onto the screen surface */
	if(SDL_BlitSurface(spriteTexture->GetSurface(), &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());

	//SDL_UpdateRect(sb->surface, 0, 0, sb->mWidth, sb->mHeight);
}


void SpriteRenderer::SetPos(int x, int y, Position horizPos, Position vertPos)
{
	switch( horizPos )
	{
	case POS_LEFT:
		xPos = x;
		break;
	case POS_CENTER:
		xPos = x - spriteTexture->mWidth/2;
		break;
	case POS_RIGHT:
		xPos = x - spriteTexture->mWidth;
		break;
    default:
        assert(false);
    break;
	}

	switch( vertPos )
	{
	case POS_TOP:
		yPos = y;
		break;
	case POS_CENTER:
		yPos = y - spriteTexture->mHeight/2;
		break;
	case POS_BOTTOM:
		yPos = y - spriteTexture->mHeight;
		break;
    default:
        assert(false);
    break;
	}
}
