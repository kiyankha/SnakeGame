#ifndef TextureManager_h_
#define TextureManager_h_

#include "Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

#endif