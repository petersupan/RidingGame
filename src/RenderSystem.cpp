#include "RenderSystem.h"
#include "Singleton.h"
#include "TextureRessourceManager.h"
#include <math.h>
#include "Texture.h"



RenderSystem::RenderSystem(Texture* screenBuf, Level* level) 
{
    mScreenBuf = screenBuf;
}


void RenderSystem::render() 
{

}


//SINGLETONFUNCTIONS(RenderSystem)


