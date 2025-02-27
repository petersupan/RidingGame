#include "../inc/AnimatedTexture.h"
#include "../inc/Texture.h"
#include "SDL/SDL.h"
#include <math.h>

AnimatedTexture::AnimatedTexture(Texture* tex, int _nrFrames)
{
	nrFrames = _nrFrames;
	imageDataTex = tex;
	mWidth = tex->mWidth;
	mHeight = tex->mHeight/nrFrames;
	currentFrame = 0;
	msecPerFrame = 100;
	loopStart = 0;
	loopEnd = 0;
	frameInState = 0;
	timeInState = 0.0f;
	loop = false;
}

AnimatedTexture::~AnimatedTexture()
{
}

void AnimatedTexture::AnimateFrames(int start, int end, bool _loop)
{
	frameInState = 0;
	timeInState = 0.0f;
	loopStart = start;
	loopEnd = end;
	loop = _loop;
}

void AnimatedTexture::SetAnimateOffset(int startFrame)
{
	loopEnd -= loopStart;
	loopEnd += startFrame;
	loopStart = startFrame;
}

void AnimatedTexture::Update(float timePassed)
{
	timeInState += timePassed;
	frameInState++;
	int texFrameInState = ((int)timeInState / (int)msecPerFrame) % (loopEnd - loopStart + 1);
	if (loop)
		currentFrame = loopStart + texFrameInState;
	else
		currentFrame = texFrameInState > (loopEnd-loopStart) ? loopEnd : (loopStart + texFrameInState);
}
