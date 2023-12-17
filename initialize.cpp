#include "head.h"


void bas_dif(int ranRow, int ranCol)
{
    int ranDif = rand() % 2;
    int dice = rand() % 10;
    if (dice < ranDif)
    {
        map[ranRow][ranCol] = 4;
    }
    else
    {
        map[ranRow][ranCol] = 2;
    }
}

// ³õÊ¼»¯map[4][4]
void init2048(int map[][4]) 
{
    srand(static_cast<unsigned int>(time(nullptr) + clock()));
    int ranCorner = rand() % 4;
    switch (ranCorner) 
    {
    case 0:
        map[0][0] = 2;
        break;
    case 1:
        map[0][4 - 1] = 2;
        break;
    case 2:
        map[4 - 1][0] = 2;
        break;
    case 3:
        map[4 - 1][4 - 1] = 2;
        break;
    }    
    int ranRow;
    int ranCol;
    do 
    {
        ranRow = rand() % 4;
        ranCol = rand() % 4;
    } while (map[ranRow][ranCol] != 0);
    
    if (cho_dif == 1)
    {
        int ranDif = 3 + rand() % 2;
        int dice = rand() % 10;
        if (dice < ranDif)
        {
            map[ranRow][ranCol] = 4;
        }
        else
        {
            map[ranRow][ranCol] = 2;
        }
    }
    else if (cho_dif == 2)
    {
        bas_dif(ranRow, ranCol);
    }
    else if (cho_dif == 3)
    {
        bas_dif(ranRow, ranCol);
        do
        {
            ranRow = rand() % 4;
            ranCol = rand() % 4;
        } while (map[ranRow][ranCol] != 0);
        map[ranRow][ranCol] = 1;
    }
    else
    {
        bas_dif(ranRow, ranCol);
        int nums = 2 + rand() % 2;
        for (int i = 0; i < nums; i++)
        {
            do
            {
                ranRow = rand() % 4;
                ranCol = rand() % 4;
            } while (map[ranRow][ranCol] != 0);
            map[ranRow][ranCol] = 1;
        }
    }
}