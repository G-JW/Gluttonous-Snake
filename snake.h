#pragma once
#include "Map2D.h"
using std::array;
using std::list;

class Snake
{
public:
	inline static const char SNAKE_HEAD = '@';
	inline static const char SNAKE_BODY = 'o';
	inline static const char SNAKE_TAIL = '&';
	inline static const char FOOD = '*';

private:
	inline static const array<array<int, 2>, 4> offset = {-1, 0, 1, 0, 0, -1, 0, 1};
	enum direction
	{
		up,
		down,
		left,
		right
	};
	enum state
	{
		dead,
		eating,
		common
	};

public:
	Snake(Map2D *map);
	int input(char command);

private:
	Map2D *map;					 //蛇所在地图
	int max_size;				 //蛇的最大长度
	int timer;					 //计时器
	int speed;					 //爬行速度
	int food_nutrition;			 //吃食物增加的蛇的长度
	direction orientation;		 //蛇的朝向
	state condition;			 //蛇的状态
	list<Map2D_unit> snake_list; //蛇的位置
	int move();
};