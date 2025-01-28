#include "Game.h"
#include "GameObject.h"

SDL_Texture *playerTex;
SDL_Rect srcR, destR;
SDL_Renderer *Game::renderer = nullptr;
GameObject *snake, *apples;
Snake *snake_ptr;
Apple *apples_ptr;
RedApple *red_apple;
YellowApple *yellow_apple;

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
        std::cout << "1.Subsytems Initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, 800, 640, flags);
        if (window)
        {
            std::cout << "2.Window Created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "3.Renderer Created" << std::endl;
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
        begin = true;
        break;
    default:
        break;
    }
}
void Game::update()
{
    snake_ptr = dynamic_cast<Snake *>(snake);
    snake_ptr->Update();
    red_apple->Update();
    
    red_apple->set_snake_position(snake_ptr->get_head_x(), snake_ptr->get_head_y());
    yellow_apple->set_snake_position(snake_ptr->get_head_x(), snake_ptr->get_head_y());

    red_apple->Update();

    for (int c = 0; c < red_apple->getCnt(); c++)
    {
        snake_ptr->increase_size(10);
    }
    red_apple->setCnt(0);
    yellow_apple->Update();
    snake_ptr->updateBody();

    if (yellow_apple->getCnt() == -1 || (begin && snake_ptr->check_self_collision()))
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
    float scale = std::min((float)800 / GO_w, (float)640 / GO_h);
    int scaledWidth = GO_w * scale;
    int scaledHeight = GO_h * scale;

    SDL_Rect imgRect = {
        (800 - scaledWidth) / 2,
        (640 - scaledHeight) / 2,
        scaledWidth,
        scaledHeight};

    SDL_RenderCopy(renderer, gameOver_texture, NULL, &imgRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
    SDL_DestroyTexture(gameOver_texture);
}
