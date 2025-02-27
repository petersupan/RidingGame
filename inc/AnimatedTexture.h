#ifndef ANIMATEDTEXTURE_H_
#define ANIMATEDTEXTURE_H_

#include "Texture.h"
class Texture;
struct SDL_Surface;
/**
 * represents a texture with or without mipmaps
 */
class AnimatedTexture {
public:
	AnimatedTexture(Texture* tex, int nrFrames);
	~AnimatedTexture();

	void SetFrame(int frameNr) { currentFrame = frameNr; }
	int GetCurrentFrame(void) { return currentFrame; }
	void AnimateFrames(int start, int end, bool loop);
	void SetAnimateOffset(int newStartFrame);
	SDL_Surface* GetSurface(void) { return imageDataTex->surface; }
	void Update(float timePassed);
	Texture* GetTexture(void) { return imageDataTex; }

	unsigned int mWidth;
	unsigned int mHeight;
private:
	// speed in updates per frame
	int msecPerFrame;
	int frameInState;
	float timeInState;
	int nrFrames;
	int currentFrame;

	int loopStart;
	int loopEnd;
	bool loop;
	//unsigned char** mFrames;
	Texture* imageDataTex;
};

#endif
