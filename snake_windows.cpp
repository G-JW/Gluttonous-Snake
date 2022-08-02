#include "snake.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
//#include <string>
using std::cout;
using std::endl;
using std::string;

LPCWSTR stringToLPCWSTR(string orig);
void consoleInit();
void consoleCursorSet(int x, int y);
void consolePut(Map2D_unit unit);
void consolePrint(list<Map2D_unit> list);

int main()
{
    consoleInit();
    Map2D arena(30, 20);
    arena.fill();
    arena.fill_margin();
    consolePrint(arena.get_buffer());
    arena.clear_buffer();
    Snake kc(&arena);
    char buffer;
    int temp;
    while (1)
    {
        Sleep(20);
        if (_kbhit())
        {
            buffer = getch();
        }
        temp = kc.input(buffer);
        switch (temp)
        {
        case 1:
            consolePrint(arena.get_buffer());
            // system("cls");
            // arena.print();
            break;
        case 0:
            consoleCursorSet(arena.width, 0);
            cout << "Game Over!" << endl;
            system("pause");
            return 0;
            break;
        case 2:
            break;
        }
        arena.clear_buffer();
    }
}

LPCWSTR stringToLPCWSTR(string orig)
{
    size_t origsize = orig.length() + 1;
    const size_t newsize = 100;
    size_t convertedChars = 0;
    wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t) * (orig.length() - 1));
    mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

    return wcstring;
}

void consoleInit()
{
    //更改控制台标题
    SetConsoleTitleW(stringToLPCWSTR("Snake"));
    //更改控制台长宽
    char cmd[64];
    int col = 1000;
    int line = 1000;
    sprintf(cmd, "mode con cols=%d lines=%d", col, line);
    system(cmd);
    //更改控制台位置
    int x = 100;
    int y = 100;
    MoveWindow(GetConsoleWindow(), x, y, col, line, 1);
    //关闭光标闪烁
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void consoleCursorSet(int x, int y)
{
    COORD temp;
    temp.X = y;
    temp.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
}

void consolePut(Map2D_unit unit)
{
    consoleCursorSet(unit.x, unit.y);
    cout << unit.item;
}

void consolePrint(list<Map2D_unit> list)
{
    for (Map2D_unit i : list)
        consolePut(i);
}