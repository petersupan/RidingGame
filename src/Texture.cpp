#include "Defines.h"
#include "../inc/Texture.h"
#include <math.h>

Texture::Texture(unsigned char* pixels, unsigned int width, unsigned int height, SDL_Surface* surf, unsigned int bpp) {
	mWidth = width; 
	mHeight = height;
	surface = surf;
	frexp((double)mWidth-1, &mMipLevels);
	mMipLevels--;

	mPixels = SAFE_NEW unsigned char*[mMipLevels];
	unsigned int l = 0;
	// create memory for all mip map levels
	while(width > 1 && height > 1) {
		// very ineffective implementation
		mPixels[l] = SAFE_NEW unsigned char[width * height * 4];
		width /= 2;
		height /= 2;
		l++;
	}

	// fill the first mip map level with the input image
	if(bpp > 2) {
		for(unsigned int i = 0; i < mWidth*mHeight; i++) {
			mPixels[0][i*4] = pixels[i*bpp];
			mPixels[0][i*4+1] = pixels[i*bpp+1];
			mPixels[0][i*4+2] = pixels[i*bpp+2];
			if(bpp == 4) {
				//mPixels[i*4+3] = pixels[i*bpp+3];
				mPixels[0][i*4+3] = (unsigned char)1;
			}
			else {
				mPixels[0][i*4+3] = (unsigned char)1;
			}
		}
	} else {
		for(unsigned int i = 0; i < mWidth*mHeight; i++) {
			mPixels[0][i*4] = pixels[i*bpp];
			mPixels[0][i*4+1] = pixels[i*bpp];
			mPixels[0][i*4+2] = pixels[i*bpp];
			mPixels[0][i*4+3] = (unsigned char)1;
		}
	}
	this->createMipMaps();
}

Texture::Texture(unsigned int width, unsigned int height, bool mipMaps) {
	mWidth = width; 
	mHeight = height;

	if(mipMaps) {
		// calculate the number of necessary mip levels
		frexp((double)mWidth-1, &mMipLevels);

		mPixels = SAFE_NEW unsigned char*[mMipLevels];
		unsigned int i = 0;
		// create memory for all mip map levels
		while(width > 1 && height > 1) {
			mPixels[i] = SAFE_NEW unsigned char[width * height * 4];
			width /= 2;
			height /= 2;
			i++;
		}
	} else {
		mMipLevels = 1;
		mPixels = SAFE_NEW unsigned char*[1];
		mPixels[0] = SAFE_NEW unsigned char[width * height * 4];
	}
}

Texture::Texture(void* pixels, unsigned  int width, unsigned int height, SDL_Surface* surf) {
    mWidth = width; 
	mHeight = height;       
    mMipLevels = 0;
    mPixels = SAFE_NEW unsigned char*[1];
    mPixels[0] = (unsigned char*) pixels;   
	surface = surf;
}

Texture::~Texture() {
	//for(int i = 0; i < mMipLevels; i++) {
	//	delete[] mPixels[i];
	//}
	delete[] mPixels;
}

int Texture::lookup(int x, int y, int mask, int shift) {
     unsigned int* lt = (unsigned int*)(mPixels[0]);
     int colorValue = lt[(y * mWidth + x)];  
     return (colorValue & mask) << shift;  
}

void Texture::createMipMaps() {
	unsigned int width = mWidth/2;
	unsigned int height = mHeight/2;

	unsigned int i = 1;
	// for all mip map levels
	while((width > 1) && (height > 1)) {
		for(unsigned int j = 0; j < height; j++) {
			unsigned int bigIndex = 0;//j * width * 8;
			unsigned int littleIndex = 0;//j * width * 4;
			for(unsigned int k = 0; k < width; k++) {
				unsigned int sum = 0;
				bigIndex =  j * width * 16 + k * 8;
				littleIndex =  j * width * 4 + k * 4;
				
				// for every color
				for(unsigned int l = 0; l < 4; l++) {
					sum = mPixels[i-1][bigIndex];
					sum += mPixels[i-1][bigIndex + 4];
					sum += mPixels[i-1][bigIndex + width *8];
					sum += mPixels[i-1][bigIndex + width *8 + 4];
					sum /= 4;
					mPixels[i][littleIndex] = (unsigned char)sum;
					//mPixels[i][littleIndex] = width;
					bigIndex += 1;
					littleIndex += 1;
				}
			}
		}
		width /= 2;
		height /= 2;
		i++;
	}



}
