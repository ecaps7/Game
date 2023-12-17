#include "head.h"
#include "random.h"

// 根据选择的难度生成位置和随机数
void addRandomNum() 
{
	if (times == 0)
	{
		return;
	}
	times = 0;
	int judge_0 = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 0)
			{
				judge_0 = 0;
				break;
			}
		}
	}
	if (judge_0 == 1)
	{
		return;
	}
	srand(static_cast<unsigned int>(time(nullptr) + clock()));
	int addRow;
	int addCol;
	do
	{
		addRow = rand() % 4;
		addCol = rand() % 4;
	} while (map[addRow][addCol] != 0);
	if (cho_dif == 1 || cho_dif == 3)
	{
		int ranDif = 3 + rand() % 2;
		int dice = rand() % 10;
		if (dice < ranDif)
		{
			map[addRow][addCol] = 4;
		}
		else
		{
			map[addRow][addCol] = 2;
		}
	}
	else if (cho_dif == 2 || cho_dif == 4)
	{
		int ranDif = rand() % 2;
		int dice = rand() % 10;
		if (dice < ranDif)
		{
			map[addRow][addCol] = 4;
		}
		else
		{
			map[addRow][addCol] = 2;
		}
	}

}