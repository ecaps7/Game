#include "head.h"

void setRandomValue(int map[][4], int value)
{
    int ranRow, ranCol;
    do {
        ranRow = rand() % 4;
        ranCol = rand() % 4;
    } while (map[ranRow][ranCol] != 0);
    map[ranRow][ranCol] = value;
}

void bas_dif(int map[][4], int ranRow, int ranCol)
{
    int difficulty = rand() % 2;
    int dice = rand() % 10;
    if (dice < difficulty)
    {
        map[ranRow][ranCol] = 4;
    }
    else
    {
        map[ranRow][ranCol] = 2;
    }
}

void init2048(int map[][4])
{
    srand(static_cast<unsigned int>(time(nullptr) + clock()));
    int ranCorner = rand() % 4;
    int corners[4][2] = { {0, 0}, {0, 3}, {3, 0}, {3, 3} };
    map[corners[ranCorner][0]][corners[ranCorner][1]] = 2; // 在一个角落放置2

    int ranRow, ranCol;
    do {
        ranRow = rand() % 4;
        ranCol = rand() % 4;
    } while (map[ranRow][ranCol] != 0);
    
    int probability = 3 + rand() % 2;

    switch (cho_dif)
    {
    case 1: // classic and easy
        if (rand() % 10 < probability)
        {
            map[ranRow][ranCol] = 4;
        }
        else
        {
            map[ranRow][ranCol] = 2;
        }
        break;
    case 2: // classic and difficult
        bas_dif(map, ranRow, ranCol);
        break;
    case 3: // interesting and easy
        bas_dif(map, ranRow, ranCol);
        setRandomValue(map, 1);
        break;
    case 4: // interesting and difficult
        bas_dif(map, ranRow, ranCol);
        int nums = 2 + rand() % 2;
        for (int i = 0; i < nums; i++)
        {
            setRandomValue(map, 1);
        }
        break;
    }
}