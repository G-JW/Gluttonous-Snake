#include "Map2D.h"
#include <iostream>
#include <random>
#include <ctime>
using std::cout;
using std::endl;

Map2D::Map2D(int length, int width)
{
    if (length > MAX_SIZE || length < MIN_SIZE)
        length = 20;
    if (width > MAX_SIZE || width < MIN_SIZE)
        width = 20;
    this->length = length;
    this->width = width;
    units[0].fill(' ');
    units.fill(units[0]);
    space_num = length * width;
}

Map2D::~Map2D()
{
}

void Map2D::fill(char item)
{
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < length; ++j)
            add_buffer(i, j, item);
}

void Map2D::fill_margin(char item, int thickness)
{
    for (int i = 0; i < thickness; ++i)
        for (int j = 0; j < length; ++j)
        {
            add_buffer(i, j, item);
            add_buffer(width - i - 1, j, item);
        }
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < thickness; ++j)
        {
            add_buffer(i, j, item);
            add_buffer(i, length - j - 1, item);
        }
}

bool Map2D::random_generate(char item)
{
    if (space_num < 20)
        return 0;
    Map2D_unit unit;
    srand(time(nullptr));
    while (1)
    {
        unit.x = rand() % (width - 2) + 1;
        unit.y = rand() % (length - 2) + 1;
        if (units[unit.x][unit.y] == Map2D::SPACE)
        {
            unit.item = item;
            add_buffer(unit.x, unit.y, unit.item);
            return 1;
        }
        else
            continue;
    }
}

bool Map2D::add_buffer(int x, int y, char item)
{
    if (x < 0 || x >= width || y < 0 || y >= length)
    {
        cout << "数值越界" << endl;
        return 0;
    }
    else
    {
        units_buffer.push_back({x, y, item});
        return 1;
    }
}

void Map2D::clear_buffer()
{
    for (Map2D_unit i : units_buffer)
    {
        if (units[i.x][i.y] == SPACE && i.item != SPACE)
            --space_num;
        else if (units[i.x][i.y] != SPACE && i.item == SPACE)
            ++space_num;
        units[i.x][i.y] = i.item;
    }
    units_buffer.clear();
}

list<Map2D_unit> &Map2D::get_buffer()
{
    return units_buffer;
}

void Map2D::print()
{
    for (int i = 0; i < Map2D::width; ++i)
    {
        for (int j = 0; j < Map2D::length; ++j)
            cout << units[i][j];
        cout << endl;
    }
}

char Map2D::get_unit(int x, int y)
{
    return units[x][y];
}