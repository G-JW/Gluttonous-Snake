#include "snake.h"
#include <iostream>
#include <random>
#include <ctime>
using std::cout;
using std::endl;

Snake::Snake(Map2D *map)
{
    this->map = map;
    max_size = 6;
    timer = 0;
    speed = 10;
    food_nutrition = 1;
    orientation = direction::right;
    snake_list.push_back(Map2D_unit{map->length / 2, map->width / 2, Snake::SNAKE_HEAD});
}

int Snake::input(char command)
{
    ++timer;
    if (timer % speed == 0)
    {
        if (map->random_generate(Snake::FOOD))
            return move();
        else
            return 0;
    }
    switch (command)
    {
    case 'w':
        if (orientation != direction::down)
            orientation = direction::up;
        break;
    case 's':
        if (orientation != direction::up)
            orientation = direction::down;
        break;
    case 'a':
        if (orientation != direction::right)
            orientation = direction::left;
        break;
    case 'd':
        if (orientation != direction::left)
            orientation = direction::right;
        break;
    case 'q':
        return 0;
    default:
        break;
    }
    return 2;
}

int Snake::move()
{
    //前进目标计算
    Map2D_unit next = this->snake_list.front();
    next.x += Snake::offset[this->orientation][0];
    next.y += Snake::offset[this->orientation][1];
    //预测未来状态
    switch (map->get_unit(next.x, next.y))
    {
    case Map2D::WALL:
    case Snake::SNAKE_HEAD:
    case Snake::SNAKE_BODY:
    case Snake::SNAKE_TAIL:
        condition = dead;
        break;
    case Snake::FOOD:
        condition = eating;
        break;
    case Map2D::SPACE:
    default:
        condition = common;
    }
    //状态处理
    switch (condition)
    {
    case dead:
        for (Map2D_unit i : this->snake_list)
        {
            map->add_buffer(i.x, i.y, Map2D::SPACE);
            map->add_buffer(i.x, i.y, Map2D::WALL);
        }
        return 0;
        break;
    case eating:
        max_size += food_nutrition;
        break;
    case common:
    default:
        break;
    }
    //整体前进处理
    map->add_buffer(snake_list.front().x, snake_list.front().y, Snake::SNAKE_BODY);
    map->add_buffer(snake_list.back().x, snake_list.back().y, Map2D::SPACE);
    snake_list.push_front(next);
    if (snake_list.size() > max_size)
        snake_list.pop_back();
    map->add_buffer(snake_list.back().x, snake_list.back().y, Snake::SNAKE_TAIL);
    map->add_buffer(snake_list.front().x, snake_list.front().y, Snake::SNAKE_HEAD);
    return 1;
}
