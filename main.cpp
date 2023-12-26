#define _CRT_SECURE_NO_WARNINGS
#include "head.h"
#include "initialize.h"
#include "move.h"
#include "random.h"
#include "output.h"
#include "judge.h"
int map[4][4]{};
int score = 0;
int times = 0;
int choice = 0;
int cho_dif = 0;
Number number[13] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, ELEVEN, BACK};
int main()
{
    initgraph(475, 575, SHOWCONSOLE);
    drawGame();
    beginning();
    init2048(map);
    drawMap();
    while (true)
    {
        char sign = _getch();
        switch (sign) 
        {
        case 0xE0: case 0: case -32:
            sign = _getch();
        default:
            switch (sign) 
            {
            case 'H': case 'W': case 'w':
                moveUp();
                break;
            case 'P': case 'S': case 's':
                moveDown();
                break;
            case 'K': case 'A': case 'a':
                moveLeft();
                break;
            case 'M': case 'D': case 'd':
                moveRight();
                break;
            default:
                break;
            }
        }
        addRandomNum();
        drawMap();
        if (!canMove() || isFinish_2048())
        {
            ending();
            if (choice == 1)
            {
                score = 0;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        map[i][j] = 0;
                    }
                }
                score = 0;
                drawGame();
                init2048(map);
                drawMap();
                while (_kbhit()) // 检查缓冲区是否有按键事件
                {
                    _getch();
                }    
                continue;
            }
            else
            {
                goodBye();
                this_thread::sleep_for(chrono::seconds(1));
                closegraph();
                system("pause");
                return 0;
            }
        }
    }
    getchar();
    closegraph();
    system("pause");
    return 0;
}