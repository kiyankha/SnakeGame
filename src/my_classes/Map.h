#ifndef Map_h_
#define Map_h_

#include "Game.h"

class Map
{
public:
    Map();
    ~Map();

    // void LoadMap(int arr[20][25]);
    void LoadMap();
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;

    int map[20][25];
    std::deque<SDL_Rect> apples;
};

#endif