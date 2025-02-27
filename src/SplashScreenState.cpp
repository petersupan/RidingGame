#include "SplashScreenState.h"
#include "TextureRessourceManager.h"
//#include "MainProgram.h"
#include "Texture.h"
#include "SDL/sdl_events.h"
#include "SDL/SDL.h"
#include "MenuSelector.h"
#include "GameLogic.h"
#include <assert.h>

static const char splashDisclaimer[] = "../images/disclaimer.bmp";
static const char splashTitle[] = "../images/title.bmp";
static const char splashBetweenLevels[] = "../images/betweenLevels.bmp";
static const char splashAfterLevel2[] = "../images/AfterLevel2.bmp";
static const char splashTutorial[] = "../images/TutorialScreen.bmp";

static const char* textureFileNames[] = {splashDisclaimer, splashTitle, splashBetweenLevels, splashAfterLevel2, splashTutorial};

static const int Textures = 3;

void SplashScreenState::Render(Texture* sb)
{
	SDL_Rect sourceRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = (unsigned short)screenTex->mWidth;
	sourceRect.h = (unsigned short)screenTex->mHeight;

	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;

	if(SDL_BlitSurface(screenTex->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
}

void SplashScreenState::Update(float timePassed)
{
	(void*)&timePassed;
}

bool SplashScreenState::HandleInput(SDL_Event& event)
{
    switch( event.type )
	{
        /* Look for a keypress */
        case SDL_KEYDOWN:
			//MainProgram::getInstance()->SwitchToState(MainProgram::STATE_HORSESELECT);
			MenuSelector::getInstance()->SwitchToNext();
            break;
	}
	return true;
}

void SplashScreenState::Init()
{
	//screenTex = TextureRessourceManager::loadTexture("../images/splashscreen.bmp");
	switch (MenuSelector::getInstance()->GetCurrentMenu())
	{
	case MenuSelector::MENU_DISCLAIMER:
		screenTex = TextureRessourceManager::loadTexture(textureFileNames[0]);
		break;
	case MenuSelector::MENU_TITLE:
		screenTex = TextureRessourceManager::loadTexture(textureFileNames[1]);
		break;
	case MenuSelector::MENU_BETWEENLEVELS:
		if (GameLogic::getInstance()->GetLevel() < 2)
			screenTex = TextureRessourceManager::loadTexture(textureFileNames[2]);
		else
			screenTex = TextureRessourceManager::loadTexture(textureFileNames[3]);
		break;
	case MenuSelector::MENU_TUTORIAL:
		screenTex = TextureRessourceManager::loadTexture(textureFileNames[4]);
		break;
	default:
		assert(false);
		break;
	}
}

void SplashScreenState::Exit()
{
	TextureRessourceManager::freeTexture(screenTex);
}
