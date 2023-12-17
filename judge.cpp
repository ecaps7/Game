#include "head.h"
#include "judge.h"

// �ж��ܷ��ƶ�
bool canMove()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (map[i][j] == 0)
            {
                return true;
            }
            else if (j < 4 - 1 && map[i][j] != 1 && map[i][j] == map[i][j + 1])
            {
                return true;
            }
            else if (i < 4 - 1 && map[i][j] != 1 && map[i][j] == map[i + 1][j])
            {
                return true;
            }
        }
    }
    return false;
}

// �ж��Ƿ����2048
bool isFinish_2048()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (map[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}
