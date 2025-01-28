#ifndef GameObject_h_
#define GameObject_h_

#include "Game.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


class GameObject
{
public:
    GameObject(SDL_Renderer *rend) : renderer(rend) {}
    ~GameObject();
    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    SDL_Renderer *renderer;
};

class Snake : public GameObject
{
public:
    Snake(int x, int y, SDL_Renderer *s_rend);
    ~Snake() = default;
    virtual void Update() override;
    virtual void Render() override;
    void set_dir(int next_dir) { dir = next_dir; }
    int get_head_x() { return head.x; }
    int get_head_y() { return head.y; }
    int get_head_w() { return head.w; }
    int get_head_h() { return head.h; }
    void set_size(int val) { size = val; }
    void increase_size(int val) { size += val; }
    int get_size() { return size; }
    void updateBody();
    bool check_self_collision() { return self_collision;}
    SDL_Rect head;
    std::deque<SDL_Rect> rq;

private:
    int dir, size;
    int xpos, ypos;
    bool self_collision;
};

class Apple : public GameObject
{
public:
    Apple(SDL_Renderer *a_rend) : GameObject(a_rend), cnt(0) {}
    ~Apple() = default;
    virtual void Update() override = 0;
    virtual void Render() override = 0;
    void set_snake_position(int x, int y)
    {
        snake_x = x;
        snake_y = y;
    }
    int get_snake_x() {return snake_x;}
    int get_snake_y() {return snake_y;}
    void setCnt(int n) { cnt = n;}
    void increaseCnt() { cnt ++;}
    int getCnt() { return cnt; }
    std::vector<SDL_Rect> vect_Apples;

private:
    int snake_x, snake_y, cnt;
};

class RedApple : public Apple
{
public:
    RedApple(SDL_Renderer *a_rend);
    ~RedApple() = default;
    virtual void Update() override;
    virtual void Render() override;
};

class YellowApple : public Apple
{
public:
    YellowApple(SDL_Renderer *a_rend);
    ~YellowApple() = default;
    virtual void Update() override;
    virtual void Render() override;
};

#endif