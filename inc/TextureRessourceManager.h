#ifndef TEXTURERESSOURCEMANAGER_H
#define TEXTURERESSOURCEMANAGER_H

#include <vector>

class Texture;
class AnimatedTexture;

/**
 * responsible for loading textures and holding them in memory during runtime of the game
 */
class TextureRessourceManager {
public:
       /// load a texture from file
       static Texture* loadTexture(const char* fileName);
	   static void freeTexture(Texture* tex);
	   static void freeAnimatedTexture(AnimatedTexture* tex);
	   static AnimatedTexture* LoadAnimatedTexture(const char* fileName, int nrFrames = 1);
       /// get texture by id. \todo If it is not yet loaded, it will be
       static Texture* getTexture(int id);
private:
       TextureRessourceManager();
       //TextureRessourceManager(const TextureRessourceManager& cc){}
       /// the one and only instance
       static TextureRessourceManager* mInstance;
       static TextureRessourceManager* getInstance();
       // replace vector with a map to load textures on demand
       std::vector<Texture*> mTextures;
       /// the texture by id
       Texture* getTextureAt(int id);
};

#endif
