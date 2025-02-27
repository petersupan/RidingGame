#ifndef TEXTURE_H_
#define TEXTURE_H_

struct SDL_Surface;
/**
 * represents a texture with or without mipmaps
 */
class Texture {
public:
	Texture(unsigned char* pixels, unsigned int width, unsigned int height, SDL_Surface* surf, unsigned int bpp = 4);
	Texture(unsigned int width, unsigned int height, bool mipMaps = false);
	Texture(void* pixels, unsigned  int width, unsigned int height, SDL_Surface* surf);
	~Texture();

    /// nearest neighbour lookup into the texture
    int lookup(int x, int y, int mask, int shift);
    /// all mip versions of the texture
	unsigned char** mPixels;
	unsigned int mWidth;
	unsigned int mHeight;
	SDL_Surface* surface;
	int mMipLevels;
private:
    /// create simple mip maps
	void createMipMaps();
};

#endif
