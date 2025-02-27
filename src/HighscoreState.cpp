#include "HighscoreState.h"

#include "TextureRessourceManager.h"
#include "Texture.h"
#include "SDL/sdl_events.h"
#include "SDL/SDL.h"
#include "MenuSelector.h"
#include "GameLogic.h"
#include <assert.h>
#include <iostream>
#include <fstream>

void HighscoreState::Render(Texture* sb)
{
	RenderTexture(sb, backGroundTex, 0,0);

	for (int i = 0; i < 5; i++)
	{
		assert(entries[i].riderNameId < 3);
		assert(entries[i].horseNameId < 2);
		timeRend.RenderTime(sb, 560, 200+i*70, entries[i].time);
		RenderTexture(sb, riderNames[entries[i].riderNameId], 350, 169 + i * 70);
		RenderTexture(sb, horseNames[entries[i].horseNameId], 180, 179 + i * 70);
		if (currentRank == i)
		{
			RenderTexture(sb, winnerOverlayTex, 30, 175 + i*70);
		}
	}
}

void HighscoreState::RenderTexture(Texture* sb, Texture* tex, int x, int y)
{
	SDL_Rect sourceRect;
	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = (unsigned short)backGroundTex->mWidth;
	sourceRect.h = (unsigned short)backGroundTex->mHeight;

	SDL_Rect destRect;
	destRect.x = (short)x;
	destRect.y = (short)y;

	if(SDL_BlitSurface(tex->surface, &sourceRect, sb->surface, &destRect) < 0)
        fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
}

void HighscoreState::Update(float timePassed)
{
	(void*)&timePassed;
}

bool HighscoreState::HandleInput(SDL_Event& event)
{
    switch( event.type )
	{
        /* Look for a keypress */
		case SDL_KEYDOWN:
			GameLogic::getInstance()->SetLevel(0);
			//MainProgram::getInstance()->SwitchToState(MainProgram::STATE_HORSESELECT);
			MenuSelector::getInstance()->SwitchToNext();
            break;
	}
	return true;
}

void HighscoreState::Init()
{
	currentRank = 100;
	backGroundTex = TextureRessourceManager::loadTexture("../images/highscore/Background.bmp");

	winnerOverlayTex = TextureRessourceManager::loadTexture("../images/highscore/winnerOverlay.bmp");
	winnerOverlayTex->surface->format->Amask = 0xff000000;
	winnerOverlayTex->surface->format->Ashift = 24;
	SDL_SetAlpha(winnerOverlayTex->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	riderNames[0] = TextureRessourceManager::loadTexture("../images/highscore/Vici.bmp");
	riderNames[1] = TextureRessourceManager::loadTexture("../images/highscore/Rainer.bmp");
	riderNames[2] = TextureRessourceManager::loadTexture("../images/highscore/Luky.bmp");

	horseNames[0] = TextureRessourceManager::loadTexture("../images/highscore/Matrix.bmp");
	horseNames[1] = TextureRessourceManager::loadTexture("../images/highscore/Glucksfee.bmp");

	riderNames[0]->surface->format->Amask = 0xff000000;
	riderNames[0]->surface->format->Ashift = 24;
	SDL_SetAlpha(riderNames[0]->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	riderNames[1]->surface->format->Amask = 0xff000000;
	riderNames[1]->surface->format->Ashift = 24;
	SDL_SetAlpha(riderNames[1]->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	riderNames[2]->surface->format->Amask = 0xff000000;
	riderNames[2]->surface->format->Ashift = 24;
	SDL_SetAlpha(riderNames[2]->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	horseNames[0]->surface->format->Amask = 0xff000000;
	horseNames[0]->surface->format->Ashift = 24;
	SDL_SetAlpha(horseNames[0]->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);

	horseNames[1]->surface->format->Amask = 0xff000000;
	horseNames[1]->surface->format->Ashift = 24;
	SDL_SetAlpha(horseNames[1]->surface, SDL_SRCALPHA | SDL_RLEACCEL, 255);




	//entries[0].horseNameId = 0;
	//entries[0].riderNameId = 0;
	//entries[0].time = 113487;

	//entries[1].horseNameId = 0;
	//entries[1].riderNameId = 1;
	//entries[1].time = 114787;

	//entries[2].horseNameId = 1;
	//entries[2].riderNameId = 0;
	//entries[2].time = 115387;

	//entries[3].horseNameId = 1;
	//entries[3].riderNameId = 1;
	//entries[3].time = 116287;

	//entries[4].horseNameId = 1;
	//entries[4].riderNameId = 2;
	//entries[4].time = 117287;

	std::ifstream::pos_type inSize;
	std::ifstream file("../images/highscore/highscores.dat", std::ios::in|std::ios::binary);
	if (file.is_open())
	{
		HighScoreEntry currentEntry;
		GameLogic* gl = GameLogic::getInstance();
		currentEntry.horseNameId = gl->GetHorse();
		currentEntry.riderNameId = gl->GetRider();
		currentEntry.time = gl->GetTime();
		HighScoreEntry tempEntry = {0,0,0};

		bool needRead = true;
		for(int i = 0; i < 5; i++)
		{
			if (needRead)
				file.read((char*)(&tempEntry), 12);
			if (currentEntry.time < tempEntry.time)
			{
				entries[i] = currentEntry;
				needRead = false;
				currentEntry.time = 999999999;
				currentRank = i;
			}
			else
			{
				entries[i] = tempEntry;
				needRead = true;
			}
		}
		file.close();
	}

	std::ofstream ofile("../images/highscore/highscores.dat", std::ios::out|std::ios::binary);
	if (ofile.is_open())
	{
		ofile.write((const char*)entries, 12*5);
		ofile.close();
	}

}

void HighscoreState::Exit()
{
	 TextureRessourceManager::freeTexture(riderNames[0]);
	 TextureRessourceManager::freeTexture(riderNames[1]);
	 TextureRessourceManager::freeTexture(riderNames[2]);

	 TextureRessourceManager::freeTexture(horseNames[0]);
	 TextureRessourceManager::freeTexture(horseNames[1]);

	 TextureRessourceManager::freeTexture(backGroundTex);

	 TextureRessourceManager::freeTexture(winnerOverlayTex);
}
