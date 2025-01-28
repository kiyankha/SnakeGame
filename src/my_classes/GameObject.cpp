#include "GameObject.h"

GameObject::~GameObject() {}

Snake::Snake(int x, int y, SDL_Renderer *s_rend) : GameObject(s_rend), xpos(x), ypos(y), dir(0), size(1), self_collision(false)
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
    std::for_each(rq.begin(), rq.end()-1, [&](auto &snake_segment)
                  {
        if(get_head_x() == snake_segment.x && get_head_y() == snake_segment.y)
        {
            self_collision = true;
            set_size(1);
        } });

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
    for (int i = 0; i < 50; i++)
    {
        int x = (rand() % (800 / 10)) * 10;
        int y = (rand() % (640 / 10)) * 10;
        if (x != 500 && y != 500)
        {
            vect_Apples.emplace_back(SDL_Rect{x, y, 10, 10});
        }
    }
}

void RedApple::Update()
{
    vect_Apples.erase(
        std::remove_if(vect_Apples.begin(), vect_Apples.end(),
                       [&](const SDL_Rect &apple)
                       {
                           if (get_snake_x() == apple.x && get_snake_y() == apple.y)
                           {
                               increaseCnt();
                               return true;
                           }
                           return false;
                       }),
        vect_Apples.end());
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
    for (int i = 0; i < 10; i++)
    {
        int attempts = 0;
        while (attempts < 10)
        {
            int x = (rand() % (800 / 10)) * 10;
            int y = (rand() % (640 / 10)) * 10;
            SDL_Rect new_apple = {x, y, 10, 10};
            if (x != 500 && y != 500)
            {
                bool overlap = false;
                for (const auto &existing_apple : vect_Apples)
                {
                    if (SDL_HasIntersection(&new_apple, &existing_apple))
                    {
                        overlap = true;
                        break;
                    }
                }

                if (!overlap)
                {
                    vect_Apples.emplace_back(new_apple);
                    break;
                }
                attempts++;
            }
        }
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
        } });
}

void YellowApple::Render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    std::for_each(vect_Apples.begin(), vect_Apples.end(), [&](auto &apple)
                  { SDL_RenderFillRect(renderer, &apple); });
    SDL_RenderPresent(renderer);
}
