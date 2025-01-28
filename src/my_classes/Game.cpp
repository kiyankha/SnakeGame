#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

SDL_Texture *playerTex;
SDL_Rect srcR, destR;
SDL_Renderer *Game::renderer = nullptr;
GameObject *snake, *apples;
Snake *snake_ptr;
Apple *apples_ptr;
RedApple *red_apple;
YellowApple *yellow_apple;
Map *map;

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsytems Initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, window_width, window_height, flags);
        if (window)
        {
            std::cout << "Window Created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created" << std::endl;
        }
        isRunning = true;
    }

    snake = new Snake(500, 500, renderer);
    red_apple = new RedApple(renderer);
    yellow_apple = new YellowApple(renderer);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        snake_ptr = dynamic_cast<Snake *>(snake);
        if (event.key.keysym.sym == SDLK_UP)
        {
            snake_ptr->set_dir(UP);
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            snake_ptr->set_dir(DOWN);
        }

        else if (event.key.keysym.sym == SDLK_LEFT)
        {
            snake_ptr->set_dir(LEFT);
        }
        else if (event.key.keysym.sym == SDLK_RIGHT)
        {
            snake_ptr->set_dir(RIGHT);
        }
        break;
    default:
        break;
    }
}
void Game::update()
{
    snake_ptr = dynamic_cast<Snake *>(snake);
    snake_ptr->Update();
    red_apple->set_snake_position(snake_ptr->get_head_x(), snake_ptr->get_head_y());
    yellow_apple->set_snake_position(snake_ptr->get_head_x(), snake_ptr->get_head_y());

    red_apple->Update();
    
    for (int c = 0; c < red_apple->getCnt(); c++)
    {
        snake_ptr->increase_size(10);
        // std::cout << "Snake size increased! New size: " << snake_ptr->get_size() << std::endl;
    }

    yellow_apple->Update();
    if (yellow_apple->getCnt() == -1)
    {
        lost = 1;
    }

    if (!lost)
    {
        if (red_apple->vect_Apples.size() == 0)
        {
            win = 1;
        }
    }
    snake_ptr->updateBody();
    
    // std::cout << "Apples-> Red:" << red_apple->vect_Apples.size() << "\tYellow:" << yellow_apple->vect_Apples.size() << std::endl;
    // std::cout << "Snake Head: (" << snake_ptr->get_head_x() << ", " << snake_ptr->get_head_y() << ")" << std::endl;
    // std::cout << "Snake Body Size: " << snake_ptr->rq.size() << std::endl;
}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    snake_ptr->Render();
    red_apple->Render();
    yellow_apple->Render();
}
void Game::clean()
{
    if (!isNotGameOver())
    {
        std::cout << "here game over" << std::endl;
        gameOver_loadTexture(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

void Game::gameOver_loadTexture(SDL_Renderer *tex_renderer)
{
    int GO_h, GO_w;
    if (lost)
    {
        gameOver_texture = IMG_LoadTexture(tex_renderer, "assets/game_over.png");
        if (!gameOver_texture)
        {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
            return;
        }
    }
    else if (win)
    {
        gameOver_texture = IMG_LoadTexture(tex_renderer, "assets/win.png");
        if (!gameOver_texture)
        {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
            return;
        }
    }
    SDL_QueryTexture(gameOver_texture, NULL, NULL, &GO_w, &GO_h);
    float scale = std::min((float)window_width / GO_w, (float)window_height / GO_h);
    int scaledWidth = GO_w * scale;
    int scaledHeight = GO_h * scale;

    SDL_Rect imgRect = {
        (window_width - scaledWidth) / 2,
        (window_height - scaledHeight) / 2,
        scaledWidth,
        scaledHeight};

    SDL_RenderCopy(renderer, gameOver_texture, NULL, &imgRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    SDL_DestroyTexture(gameOver_texture);
}
