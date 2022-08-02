#pragma once
#include <array>
#include <list>
using std::array;
using std::list;

struct Map2D_unit
{
    int x;
    int y;
    char item;

    Map2D_unit(int x = 0, int y = 0, char item = ' ') : x(x), y(y), item(item){};
};

class Map2D
{
private:
    static const int MAX_SIZE = 100;
    static const int MIN_SIZE = 10;

public:
    static const char WALL = '#';
    static const char SPACE = ' ';

private:
    int space_num;
    list<Map2D_unit> units_buffer;
    array<array<char, Map2D::MAX_SIZE>, Map2D::MAX_SIZE> units;

public:
    int length;
    int width;

    Map2D(int length = 20, int width = 20);
    ~Map2D();
    void fill(char item = SPACE);
    void fill_margin(char item = WALL, int thickness = 1);
    bool random_generate(char item);
    bool add_buffer(int x, int y, char item);
    void clear_buffer();
    list<Map2D_unit> &get_buffer();
    char get_unit(int x,int y);
    void print();
};