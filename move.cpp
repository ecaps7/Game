#include "head.h"
#include "move.h"

//ºÏ²¢
void mergeLeft()
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4 - 1; j++)
        {
            if (map[i][j] != 0)
            {
                for (int k = j + 1; k < 4; k++)
                {
                    if (map[i][j] == 1)
                    {
                        continue;
                    }
                    if (map[i][j] == map[i][k])
                    {
                        score += map[i][j];
                        map[i][j] *= 2;
                        map[i][k] = 0;
                        times++;
                    }
                    else if (map[i][k] != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}

// ÒÆ¶¯
void moveLeft()
{
    mergeLeft();
    for (int i = 0; i < 4; i++)
    {
        int count = 0;
        for (int j = 0; j < 4; j++)
        {
            map[i][count] = map[i][j];
            if (map[i][j] != 0)
            {
                if (j != count)
                {
                    map[i][j] = 0;
                    times++;
                }
                count++;
            }
        }
    }
    if (times != 0)
    {
        score--;
    }
}

void mergeRight()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (map[i][j] != 0)
            {
                for (int k = j - 1; k >=0; k--)
                {
                    if (map[i][j] == 1)
                    {
                        continue;
                    }
                    if (map[i][j] == map[i][k])
                    {
                        score += map[i][j];
                        map[i][j] *= 2;
                        map[i][k] = 0;
                        times++;
                    }
                    else if (map[i][k] != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}

void moveRight()
{
    mergeRight();
    for (int i = 0; i < 4; i++)
    {
        int count = 4 - 1;
        for (int j = 4 - 1; j >= 0; j--)
        {
            if (map[i][j] != 0)
            {
                map[i][count] = map[i][j];
                if (j != count)
                {
                    map[i][j] = 0;
                    times++;
                }
                count--;
            }
        }
    }
    if (times != 0)
    {
        score--;
    }
}

void mergeUp()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4 - 1; j++)
        {
            if (map[j][i] != 0)
            {
                for (int k = j + 1; k < 4; k++)
                {
                    if (map[j][i] == 1)
                    {
                        continue;
                    }
                    if (map[j][i] == map[k][i])
                    {
                        score += map[j][i];
                        map[j][i] *= 2;
                        map[k][i] = 0;
                        times++;
                    }
                    else if (map[k][i] != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}

void moveUp()
{
    mergeUp();
    for (int i = 0; i < 4; i++)
    {
        int count = 0;
        for (int j = 0; j < 4; j++)
        {
            if (map[j][i] != 0)
            {
                map[count][i] = map[j][i];
                if (j != count)
                {
                    map[j][i] = 0;
                    times++;
                }
                count++;
            }
        }
    }
    if (times != 0)
    {
        score--;
    }
}

void mergeDown()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (map[j][i] != 0)
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if (map[j][i] == 1)
                    {
                        continue;
                    }
                    if (map[j][i] == map[k][i])
                    {
                        score += map[j][i];
                        map[j][i] *= 2;
                        map[k][i] = 0;
                        times++;
                    }
                    else if (map[k][i] != 0)
                    {
                        break;
                    }
                }
            }
        }
    }
}

void moveDown()
{
    mergeDown();
    for (int i = 0; i < 4; i++)
    {
        int count = 4 - 1;
        for (int j = 3; j >= 0; j--)
        {
            if (map[j][i] != 0)
            {
                map[count][i] = map[j][i];
                if (j != count)
                {
                    map[j][i] = 0;
                    times++;
                }
                count--;
            }
        }
    }
    if (times != 0)
    {
        score--;
    }
}