#include "Defines.h"
#include "RiderSelectState.h"
#include "TextureRessourceManager.h"
#include "GameLogic.h"
#include "MenuSelector.h"
#include "Texture.h"
#include "SDL/sdl_events.h"
#include "SDL/SDL.h"
#include <assert.h>

static const char riderVicky[] = "../images/riders/Vici.bmp";
static const char riderRainer[] = "../images/riders/Rainer.bmp";
static const char riderLuky[] = "../images/riders/Luky.bmp";

static const char* textureFileNames[] = {riderVicky, riderRainer, riderLuky};

static const int nrRiders = 3;

RiderSelectState::RiderSelectState() :
	currentActive(0),
	nrTextures(nrRiders)
{
}

RiderSelectState::~RiderSelectState()
{

}

void RiderSelectState::Render(Texture* sb)
{
	Texture* activeTex = textures[currentActive];
	SDL_Rect sourceRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = (unsigned short)activeTex->mWidth;
	sourceRect.h = (unsigned short)activeTex->mHeight;

	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;



	if(SDL_BlitSurface(activeTex->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
}

void RiderSelectState::ChangeActive(int value)
{
	currentActive = currentActive + value;
	currentActive = currentActive >= 0 ? currentActive : 0;
	currentActive = currentActive < nrTextures ? currentActive : nrTextures-1;
	//currentActive = currentActive % nrTextures;
	assert(currentActive >= 0 && currentActive < nrTextures);
}

void RiderSelectState::Update(float timePassed)
{
	(void*)&timePassed;
}

bool RiderSelectState::HandleInput(SDL_Event& event)
{
    switch( event.type )
	{
        /* Look for a keypress */
        case SDL_KEYDOWN:
		    /* Check the SDLKey values */
            switch( event.key.keysym.sym ){
				case SDLK_LEFT:
					ChangeActive(-1);
					break;
				case SDLK_RIGHT:
					ChangeActive(1);
				break;
				case SDLK_SPACE:
					GameLogic::getInstance()->SetRider(currentActive);
					//MainProgram::getInstance()->SwitchToState(MainProgram::STATE_RIDING);
					MenuSelector::getInstance()->SwitchToNext();
					break;
                default:
                    break;
            }

            break;
	}
	return true;
}

void RiderSelectState::Init()
{
	for (int i = 0; i < nrTextures; i++)
	{
		Texture* tex = TextureRessourceManager::loadTexture(textureFileNames[i]);
		textures.push_back(tex);
	}
}

void RiderSelectState::Exit()
{
	for (int i = 0; i < nrTextures; i++)
	{
		TextureRessourceManager::freeTexture(textures[i]);
		//SAFE_DELETE(textures[i]);
	}
}
