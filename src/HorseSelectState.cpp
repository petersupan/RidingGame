#include "Defines.h"
#include "HorseSelectState.h"
#include "TextureRessourceManager.h"
#include "GameLogic.h"
#include "MenuSelector.h"
#include "Texture.h"
#include "SDL/sdl_events.h"
#include "SDL/SDL.h"
#include <assert.h>

const char horseMatrix[] = "../images/horses/Matrix.bmp";
const char horseGlueck[] = "../images/horses/Gluecksfee.bmp";

const char* textureFileNames[] = {horseMatrix, horseGlueck};

const int nrHorses = 2;

HorseSelectState::HorseSelectState() :
	currentActive(0),
	nrTextures(nrHorses)
{
}

HorseSelectState::~HorseSelectState()
{

}

void HorseSelectState::Render(Texture* sb)
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

void HorseSelectState::ChangeActive(int value)
{
	currentActive = currentActive + value;
	currentActive = currentActive >= 0 ? currentActive : 0;
	currentActive = currentActive < nrTextures ? currentActive : nrTextures-1;
	//currentActive = currentActive % nrTextures;
	assert(currentActive >= 0 && currentActive < nrTextures);
}

void HorseSelectState::Update(float timePassed)
{
	(void*)&timePassed;
}

bool HorseSelectState::HandleInput(SDL_Event& event)
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
					GameLogic::getInstance()->SetHorse(currentActive);
					//MainProgram::getInstance()->SwitchToState(MainProgram::STATE_RIDERSELECT);
					MenuSelector::getInstance()->SwitchToNext();
					break;
                default:
                    break;
            }

            break;
	}
	return true;
}

void HorseSelectState::Init()
{
	for (int i = 0; i < nrTextures; i++)
	{
		Texture* tex = TextureRessourceManager::loadTexture(textureFileNames[i]);
		textures.push_back(tex);
	}
}

void HorseSelectState::Exit()
{
	for (int i = 0; i < nrTextures; i++)
	{
		TextureRessourceManager::freeTexture(textures[i]);
		//SAFE_DELETE(textures[i]);
	}
}

