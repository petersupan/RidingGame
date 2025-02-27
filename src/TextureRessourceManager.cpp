#include "Defines.h"
#include "../inc/TextureRessourceManager.h"
#include "../inc/Texture.h"
#include "../inc/AnimatedTexture.h"
#include "SDL/SDL.h"
#include <iostream>
#include <vector>


SDL_Surface* loadBmp(const char *file_name)
{
     SDL_Surface* image;
    /* Load the BMP file into a surface */
    image = SDL_LoadBMP(file_name);
    if (image == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        printf("couldnt load image");
        return 0;
    }
	//SDL_Surface* optImage;
	//Create an optimized image
   // optImage = SDL_DisplayFormat( image );
        
        //Free the old image
   // SDL_FreeSurface( image );
    printf("image loaded");
    return image;
}


TextureRessourceManager::TextureRessourceManager() {
    //Texture* texture = loadTexture("../images/maxi2.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/tree.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/bush.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/vase.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/duck.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/wallTexture2.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/wallTexture3.bmp");
    //mTextures.push_back(texture);
    //texture = loadTexture("../images/wallTexture4.bmp");
    //mTextures.push_back(texture);
}

AnimatedTexture* TextureRessourceManager::LoadAnimatedTexture(const char* fileName, int nrFrames)
{
	Texture* tex = loadTexture(fileName);
	AnimatedTexture* animTex = SAFE_NEW AnimatedTexture(tex, nrFrames);
	return animTex;
}

Texture* TextureRessourceManager::loadTexture(const char* fileName){
    SDL_Surface* surface = loadBmp(fileName);
    Texture* texture = SAFE_NEW Texture((surface->pixels), surface->w, surface->h, surface);//, surface->format->BytesPerPixel);
    return texture;
}

void TextureRessourceManager::freeTexture(Texture* tex)
{
	SDL_FreeSurface(tex->surface);
  	SAFE_DELETE(tex);
}

void TextureRessourceManager::freeAnimatedTexture(AnimatedTexture* tex)
{
	freeTexture(tex->GetTexture());
	//SDL_FreeSurface(tex->GetSurface());
	//SAFE_DELETE(tex->GetTexture());
	SAFE_DELETE(tex);
}

//Texture* TextureRessourceManager::getTexture(int id) {
//    TextureRessourceManager* manager = TextureRessourceManager::getInstance();
//    if(id < (int)manager->mTextures.size()) {
//        return manager->mTextures.at(id);
//    } else {
//        std::cout << std::endl << "invalid texture id error" << std::endl;
//        return manager->mTextures.at(0);
//    }
//}


TextureRessourceManager* TextureRessourceManager::mInstance = NULL;

TextureRessourceManager* TextureRessourceManager::getInstance() {

    if(!TextureRessourceManager::mInstance) {
        TextureRessourceManager::mInstance = SAFE_NEW TextureRessourceManager();
    }
    return TextureRessourceManager::mInstance;
}



