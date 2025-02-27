#ifndef SCREENBUFFERFACTORY_H
#define SCREENBUFFERFACTORY_H
#include "Singleton.h"

class Texture;

/**
 * returns a screenBuffer to render to (for abstraction of sdl, opengl, screenbufferpointer or whatsoever)
 * will be used by spriteRenderer, RayCastRenderer and FloorRenderer
 */
class ScreenBufferFactory {
    public:
        static Texture* getScreenBufferTexture();
    private:
        SINGLETONDECLARATIONS(ScreenBufferFactory)

};

#endif
