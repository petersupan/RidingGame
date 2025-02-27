#include "Sound.h"
#include "SDL/SDL.h"   /* All SDL App's need this */
#include "SDL/SDL_audio.h"


static SDL_AudioSpec desired;

static Uint32    audioLen;    // Länge der Audiodatei 
static Uint8*    audioPos;    // aktuelle Position

void myAudioCallBack(void *pReserved, Uint8* stream, int len) 
{ 
    // Wenn kein Sound mehr, beenden 
    if(audioLen == 0) 
	{
		if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
			SDL_FreeWAV(audioPos);
        return; 
	}

    // Mix 
    len = ( len > audioLen ? audioLen : len ); 
    SDL_MixAudio(stream, audioPos, len, SDL_MIX_MAXVOLUME); 
    audioPos += len; 
    audioLen -= len; 
}

void Sound::exitAudio()
{
	if (SDL_GetAudioStatus() == SDL_AUDIO_STOPPED)
		SDL_FreeWAV(audioPos);
	SDL_CloseAudio();
}

void Sound::initAudio()
{
	/* Prototype of our callback function */
	//void my_audio_callback(void *userdata, Uint8 *stream, int len);


	/* Allocate a desired SDL_AudioSpec */
	//desired = //malloc(sizeof(SDL_AudioSpec));

	/* Allocate space for the obtained SDL_AudioSpec */
	//obtained = malloc(sizeof(SDL_AudioSpec));

	/* 22050Hz - FM Radio quality */
	desired.freq=44100;

	/* 16-bit signed audio */
	desired.format=AUDIO_S16LSB;

	/* Mono */
	desired.channels=2;

	/* Large audio buffer reduces risk of dropouts but increases response time */
	desired.samples=8192;

	/* Our callback function */
	desired.callback=myAudioCallBack;

	desired.userdata=NULL;

	/* Open the audio device */
	if ( SDL_OpenAudio(&desired, NULL) < 0 ){
	  printf("Couldn't open audio: %s\n", SDL_GetError());
	  exit(-1);
	}

	/* desired spec is no longer needed */
	//free(desired);
	//hardware_spec=&obtained;
}


void Sound::PlayMusic(bool play)
{
	if (play)
	{
		/* Load the WAV */
		if( SDL_LoadWAV("../sound/music.wav", &desired, &audioPos, &audioLen) == NULL ){
			printf("Could not open music.wav: %s\n", SDL_GetError());
			//exit(-1);
		}

		SDL_PauseAudio(0);
	}
	else
	{
		SDL_PauseAudio(1);
	}
}