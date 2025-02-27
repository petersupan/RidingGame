#include "Defines.h"

#include <stdlib.h>
#ifdef VSTUDIO
#include <crtdbg.h>
#endif

#include <cstdlib>
#include <iostream>
#include "SDL/SDL.h"   /* All SDL App's need this */
#include "SDL/SDL_audio.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include "math.h"
#include "../inc/Texture.h"
#include "MainProgram.h"
//#include "../inc/RidingState.h"
//#include "../inc/BaseState.h"
//#include "../inc/Collider.h"
//#include "../inc/Level.h"
//#include "../inc/EntityManager.h"
//#include "../inc/LevelFactory.h"
//#include "../inc/Player.h"
//#include "RenderSystem.h"
#include <windows.h>
#include "Sound.h"


#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define ANGLECOUNT 512
#define ANGLECHALF (ANGLECOUNT/2)
#define ANGLECQUART (ANGLECOUNT/4)

bool running = true;


/* moving in x direction, y direction or turning */
static float posX, posY, angle;

Texture* screenTexture;
//Level* level;
SDL_Surface* screen;
//BaseState* riding;
//RenderSystem* renderSys;


/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
SDL_Surface *swSurface;

static float estFps = 60.0f;

static bool isActive = true;


void cleanUp() {
	delete screenTexture;
	Sound::exitAudio();
	SDL_Quit();
}



//static float rad2deg(float rad) {
//	return rad*ANGLECHALF/M_PI;
//}



void CalculateFrameRate()
{
	// Below we create a bunch of static variables because we want to keep the information
	// in these variables after the function quits.  We could make these global but that would
	// be somewhat messy and superfluous.  Note, that normally you don't want to display this to
	// the window title bar.  This is because it's slow and doesn't work in full screen.
	// Try using the 3D/2D font's.  You can check out the tutorials at www.gametutorials.com.

	static float framesPerSecond    = 0.0f;							// This will store our fps
    static float lastTime			= 0.0f;							// This will hold the time from the last frame
	//static char strFrameRate[50] = {0};								// We will store the string here for the window title

	// Here we get the current tick count and multiply it by 0.001 to convert it from milliseconds to seconds.
	// GetTickCount() returns milliseconds (1000 ms = 1 second) so we want something more intuitive to work with.
    float currentTime = SDL_GetTicks() * 0.001f;

	//unsigned char appState = SDL_GetAppState();
	//if (appState & SDL_APPACTIVE)
	//{
		// Increase the frame counter
  		++framesPerSecond;
	//}
	//else
	//{
	//	printf("not active");
	//}

	// Now we want to subtract the current time by the last time that was stored.  If it is greater than 1
	// that means a second has passed and we need to display the new frame rate.  Of course, the first time
	// will always be greater than 1 because lastTime = 0.  The first second will NOT be true, but the remaining
	// ones will.  The 1.0 represents 1 second.  Let's say we got 12031 (12.031) from GetTickCount for the currentTime,
	// and the lastTime had 11230 (11.230).  Well, 12.031 - 11.230 = 0.801, which is NOT a full second.  So we try again
	// the next frame.  Once the currentTime - lastTime comes out to be greater than a second (> 1), we calculate the
	// frames for this last second.
    if( currentTime - lastTime > 1.0f )
    {
		// Here we set the lastTime to the currentTime.  This will be used as the starting point for the next second.
		// This is because GetTickCount() counts up, so we need to create a delta that subtract the current time from.
	    lastTime = currentTime;

		// Copy the frames per second into a string to display in the window title bar
		printf("Current Frames Per Second: %d \n", int(framesPerSecond));
		estFps = framesPerSecond;

		// Set the window title bar to our string
		//SetWindowText(g_hWnd, strFrameRate);

		// Reset the frames per second
        framesPerSecond = 0;
    }
}

void pauseFrameCounting(bool pause)
{
	static float pauseTime = 0.0f;
	if (pause)
	{
		float time = SDL_GetTicks() * 0.001f;
		pauseTime = time;
		isActive = false;
	}
	else
	{
		float time = SDL_GetTicks() * 0.001f;
		pauseTime = time - pauseTime;
		isActive = true;
	}
}



void display() {
	MainProgram::getInstance()->Render(screenTexture);
	//SDL_LockSurface(screenTexture->surface);
	SDL_Flip(screenTexture->surface);
	//SDL_UnlockSurface(screenTexture->surface);
}



void idle() {
	//static double lastTime = 0.0;
	static LARGE_INTEGER lastTime;
	//lastTime.QuadPart = 0;
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	float elapsedTime;
	if(lastTime.QuadPart != 0)
	{
		long long int elapsedTicks = time.QuadPart - lastTime.QuadPart;
		double elapsedSeconds = (double)elapsedTicks / (double)(frequency.QuadPart);
		//double fElapsedMicroseconds = (double)elapsedMicroseconds;
		elapsedTime = (float)(elapsedSeconds * 1000.0);
		//double timeInSeconds = (double)time/(double)frequency;
		//double timeInMilliseconds = timeInSeconds*1000.0;
		//elapsedTime = (float)(timeInMilliseconds - lastTime);

	}
	else
 		elapsedTime = 0.0f;
	lastTime = time;

	if (elapsedTime < 16.0f)
	{
		//printf("sleeping %f milliseconds\n", 15.0f - elapsedTime);
		//Sleep(16.0f - elapsedTime);
	}

	//float elapsedTime;
	//if(estFps != 0.0f)
	//	elapsedTime = 1000.0f / estFps;
	//else
	//	elapsedTime = 0.1f;
	MainProgram::getInstance()->Update(elapsedTime);
}

void keyBoard() {
	SDL_Event sevent;
	/* Check for events */
    while( SDL_PollEvent( &sevent ) ){
        switch( sevent.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( sevent.key.keysym.sym )
				{
					case SDLK_q:
					case SDLK_ESCAPE:
						cleanUp();
						exit(0);
						break;
					case SDLK_w:

					break;
                    default:
                        break;
                }
			case SDL_ACTIVEEVENT:
				if (sevent.active.state & SDL_APPMOUSEFOCUS)
					printf("mouse%i\n", sevent.active.gain);
				if (sevent.active.state & SDL_APPINPUTFOCUS)
					printf("input%i\n", sevent.active.gain);
				if (sevent.active.state & SDL_APPACTIVE)
					printf("active%i\n", sevent.active.gain);
			break;
			default:
				//printf("unknown event %i", sevent.type);
				break;
		}
		MainProgram::getInstance()->HandleInput(sevent);
		//riding->HandleInput(event);
	}
}


void init() {
	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
	Uint32 rmask, gmask, bmask, amask;
    rmask = 0x00ff0000;
    gmask = 0x0000ff00;
    bmask = 0x000000ff;
    amask = 0xff000000;
    swSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 24,
                                   rmask, gmask, bmask, amask);

	screenTexture = SAFE_NEW Texture(screen->pixels, screen->w, screen->h, screen);

	//createEntities();

    //level = LevelFactory::getLevel(0);

    //Collider::setLevel(level);

    //renderSys = SAFE_NEW RenderSystem(screenTexture, level);

    //myCollider = SAFE_NEW Collider(level, 4.0f, 4.0f);

	SDL_SetAlpha(screen, SDL_RLEACCEL, SDL_ALPHA_OPAQUE);
	SDL_SetAlpha(swSurface, SDL_RLEACCEL, SDL_ALPHA_OPAQUE);

	// only for initializing
	posX = 0.0;
	posY = 0.0;
	//Player* pl = Player::getInstance();
	//pl->setPos((int)(2.9*4096), 2*4096, 2048);

	angle = 0.0f;//1.0f * M_PI /2.0f;
	//pl->setViewDir((int)rad2deg(angle));

	//riding = SAFE_NEW RidingState();
	//riding->Init();

}


int main(int argc, char *argv[])
{

	(void*)&argc;
	(void*)argv;

#ifdef VSTUDIO
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
#endif

    printf("Initializing SDL.\n");

    /* Initialize the SDL library */
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) {
        fprintf(stderr,
                "Couldn't initialize SDL: %s\n", SDL_GetError());
		printf("couldn't init sdl");
        exit(1);
    }

    /* Clean up on exit */
    //atexit(SDL_Quit);

    /*
     * Initialize the display in a 640x480 32bit true color mode,
     * requesting a software surface
     */
    //screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 32, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 32, SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_Rect scr;
	scr.x = 0;
	scr.y = 0;
	scr.w = (unsigned short)screen->w;
	scr.h = (unsigned short)screen->h;
	//SDL_SetClipRect(screen, &scr);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x32 video mode: %s\n",
                        SDL_GetError());
		printf("couldn't set video mode");
        exit(1);
    }

	if (0 == (screen->flags & SDL_HWSURFACE))
	{
	  printf("Can't get hardware surface\n");
	}

	init();
	Sound::initAudio();

	// the main loop
	while (running) {
		keyBoard();
		idle();
		display();
		CalculateFrameRate();
	}
	cleanUp();
	SDL_Quit();
	//exit(0);
    //system("PAUSE");
	return 0;
}
