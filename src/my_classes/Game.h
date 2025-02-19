#ifndef Game_h_
#define Game_h_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <typeinfo>

class Game
{
public:
    Game() :cnt(0), begin(false),lost(0), win(0), window(nullptr), gameOver_texture(nullptr) {}
    ~Game();

    void init(const char *title, int xpos, int ypos, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }
    bool isNotGameOver() { return !(lost||win); }
    void gameOver_loadTexture(SDL_Renderer *tex_renderer);
    static SDL_Renderer *renderer;
private:
    int cnt;
    bool isRunning;
    bool begin, lost, win;
    SDL_Window *window;
    SDL_Texture *gameOver_texture;
};

#endif