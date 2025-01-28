#include "GameObject.h"
#include "TextureManager.h"

// GameObject::GameObject(const char *textureSheet, int x, int y)
// {
//     textureSheet = "assets/chadwel.png";
//     objTexture = TextureManager::LoadTexture(textureSheet);

//     xpos = x;
//     ypos = y;
// }

GameObject::~GameObject() {}

// void GameObject::Update()
// {
//     if(dir == 1)
//     {
//         ypos--;
//     }
//     else if (dir == 2)
//     {
//         ypos++;
//     }
//     else if(dir == 3)
//     {
//         xpos--;
//     }
//     else if(dir == 4)
//     {
//         xpos++;
//     }
//     // SetDir(0);
//     srcRect.h = 32;
//     srcRect.w = 32;
//     srcRect.x = 0;
//     srcRect.y = 0;

//     destRect.x = xpos;
//     destRect.y = ypos;
//     destRect.w = srcRect.w * 2;
//     destRect.h = srcRect.h * 2;
// }

// void GameObject::Render()
// {
//     SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
// }

Snake::Snake(int x, int y, SDL_Renderer *s_rend) : GameObject(s_rend), xpos(x), ypos(y), dir(0), size(1)
{
    head = {x, y, 10, 10};
    rq.push_front(head);
}

void Snake::Update()
{
    switch (dir)
    {
    case UP:
        head.y -= 10;
        break;
    case DOWN:
        head.y += 10;
        break;
    case LEFT:
        head.x -= 10;
        break;
    case RIGHT:
        head.x += 10;
        break;
    default:
        break;
    }
}

void Snake::updateBody()
{
    // std::for_each(rq.begin(), rq.end(), [&](auto &snake_segment)
    //               {
    //     if(get_head_x() == snake_segment.x && get_head_y() == snake_segment.y)
    //     {
    //         set_size(1);
    //     } });
    for(auto& snake_segment: rq)
    {
        if(get_head_x() == snake_segment.x && get_head_y() == snake_segment.y)
        {
            set_size(1);
            break;
        }
    }

    rq.push_front(head);
    while (rq.size() > get_size())
    {
        rq.pop_back();
    }
}
void Snake::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    std::for_each(rq.begin(), rq.end(), [&](auto &snake_segment)
                  { SDL_RenderFillRect(renderer, &snake_segment); });
}

RedApple::RedApple(SDL_Renderer *a_rend) : Apple(a_rend)
{
    for (int i = 0; i < 10; i++)
    {
        vect_Apples.emplace_back(SDL_Rect{rand() % 100 * 10, rand() % 100 * 10, 10, 10});
    }
}

void RedApple::Update()
{
    std::for_each(vect_Apples.begin(), vect_Apples.end(), [&](auto &r_apple)
                  {
        if(get_snake_x() == r_apple.x && get_snake_y() == r_apple.y)
        {
            increaseCnt(1);
            r_apple.x = -10;
            r_apple.y = -10;
            // std::cout << "Apple eaten! Increasing size." << std::endl;
        } });
}

void RedApple::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    std::for_each(vect_Apples.begin(), vect_Apples.end(), [&](auto &apple)
                  { SDL_RenderFillRect(renderer, &apple); });
    SDL_RenderPresent(renderer);
}

YellowApple::YellowApple(SDL_Renderer *a_rend) : Apple(a_rend)
{
    for (int i = 0; i < 5; i++)
    {
        vect_Apples.emplace_back(SDL_Rect{rand() % 10 * 10, rand() % 10 * 10, 10, 10});
    }
}

void YellowApple::Update()
{
    std::for_each(vect_Apples.begin(), vect_Apples.end(), [&](auto &y_apple)
                  {
        if(get_snake_x() == y_apple.x && get_snake_y() == y_apple.y)
        {
            setCnt(-1);
            y_apple.x = -10;
            y_apple.y = -10;
            // std::cout << "Ouch Eaten a yellow apple" << std::endl;
        } });
}

void YellowApple::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    std::for_each(vect_Apples.begin(), vect_Apples.end(), [&](auto &apple)
                  { SDL_RenderFillRect(renderer, &apple); });
    SDL_RenderPresent(renderer);
}