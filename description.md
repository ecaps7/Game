# 详细介绍

## 简介

这是一个2048游戏，有 4 种模式可以选择。 Classic 模式实现了现实生活中大多数2048游戏的功能，同时按难度分为 Easy 和 Difficult 两种；Interesting 模式加入了可移动的障碍物，按障碍物的个数也分为 Easy 和 Difficult 两种难度。同时，该游戏还有计分功能，每移动一次扣1分，将两数合并会增加对应数字的分数。

## 技术和工具

- 本游戏使用 C++ 语言在 Microsoft Visual Studio 2022 上开发完成
- 在创建图形化界面时，使用了 EasyX 图形库
- 多文件编程
  - `head.h`：专门存放程序中需要频繁使用到的头文件与全局变量
  - `initialize.h` 与 `initialize.cpp`：主要用于初始化 `map` 数组
  - `random.h` 与 `random.cpp`：主要用于生成随机数。在本游戏中，随机数用于确定 `map` 中最初两个数字的位置、数字为 2 或 4 的概率以及 Interesting 模式下可移动障碍物的个数和位置
  - `move.h` 与 `move.cpp`：游戏最核心的部分，实现数字的移动逻辑
  - `output.h` 与 `output.cpp`：专门用于实现图形化界面，包括：欢迎界面、游戏进行时的界面、分数的展示、游戏结束界面以及告别界面
  - `main.cpp`：主文件，构建整个游戏的框架

## 界面

### 欢迎界面

欢迎界面展现了游戏最基础的元素，包括游戏标题、得分（初始化为0），此外还有模式选择的窗口，用户点击 4 个模式按钮的任意一个即可进入对应的游戏界面。

### 游戏过程界面

这里借鉴了 [2048 Game](https://2048game.com/) 的界面。

### 结束界面

当出现2048 或无法继续移动时，游戏会弹出结束界面。此时用户可以选择再来一局或者结束。

- 如果用户选择了 `Yes`，程序会将地图重新初始化（*进入的仍然是用户一开始选择的模式*），然后用户就能再玩一次，游戏再次结束时相同的界面会重新出现。
- 如果用户选择了 `No`，程序会弹出告别文字 `See you next time.`，1 秒后窗口自动关闭。

## 基础功能实现

基础功能即实现一般2048游戏的规则：遇到相同的数就会合并翻倍，同时数字会移动到底，以及计分功能。在这里，我通过构建了一个 $4\times4$ 的二维数组 `int map[4][4];` 实现。

> [!NOTE]
> 大作业要求的计分规则与现实中大部分2048游戏略有不同，这主要体现在移动一次会扣一分。

### 初始化游戏

这里主要指对二维数组 `map` 进行初始化。首先需要在四角中的某一个位置出现一个 2，这使用 `rand() % 4`就可以；然后要在其他位置产生一个 2 或 4，位置的横纵坐标与产生2或4的概率都可以用随机数生成。当然一开始要获取生成随机数的种子 `srand(static_cast<unsigned int>(time(nullptr)));`。

### 相同数字合并

这一功能由单独的函数实现，主要思路是逆着移动的方向遍历数组，当遇到相同的两数相邻或是中间只隔了0，那么先被遍历的到的数翻倍，另一个赋为0。

```cpp
// 基础功能版本，不包含拓展功能的部分
// 以左移为例
void mergeLeft()
{
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4 - 1; j++)
        {
            if (map[i][j] != 0)
            {
                // 对于每一个数字，向后寻找(忽略0)有没有相同的
                for (int k = j + 1; k < 4; k++)
                {
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
```

### 移动数字

这一功能同样由单独的函数实现，并会包含上面的合并数字函数。在这里，需要考虑的问题主要是如何将数字移动到底。为此，可以在遍历到这一行时定义一个整型变量 `count` 计下遍历时非零元素的个数。在遍历时遇到非零的元素（如`map[i][j]`）时，将其赋给 `map[i][count]`，然后判断被赋值的位置与原来的位置是否一致，不一致就令原来的位置为0（*这相当于将两者的位置交换*），最后将 `count` 自增。

```cpp
// 以左移为例
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
```

> [!NOTE]
> 这里会出现这样的问题，就是当出现诸如 `2248` 的情况时，不应当直接产生 `16`，而是变成 `448*`。对于这个问题，我主要在 `merge` 函数中做了一些处理。我逆着移动方向遍历数字，如果遇到可以合并的就更改当前数字，另一个数字设为 `0`，同时结束循环。至于移动就交给 `move` 函数完成。这样就有效地规避了这类问题。

### 关于计分

由于大作业文件中要求计分时移动一次扣一分，因此，我需要更细致地考虑移动的过程。此外，在玩网上一些2048游戏时，我发现，当你选择的方向导致数字无法移动时，是不会出现新的数字的。因此，这应当算作一次无效的移动，不应扣分。这样，就需要考虑什么算作时有效的移动。这有 2 种情况。第一是有数字合并；第二是有数字被移动了，体现在代码执行上，就是可能是进入了 `map[i][j] == map[i][k]` 的分支，也可能是进入了 `j != count` 的分支。因此，只需要在这两个分支中加入 `count++;` 就能够区分出有效的移动了。

### 在某一位置新生成一个数

类似于 [初始化游戏](#初始化游戏) ，但同样需要注意，没有移动时不能出现新的数字。这时，只需要再次判断 `times` 是否为 `0` 即可，判断后应将其归零以便于下一次判断。

## 拓展功能实现

### 重新开始游戏

当出现 2048 或数字无法再移动时，会弹出窗口，提示用户选择是否要再来一次，如果选择再来一次，游戏会在**当前模式和难度**下重新初始化，`score` 会被清零。
在具体实现上，可以在外层有一个 `while` 的大循环，条件为 `true`，然后每移动一次判断本次游戏是否结束，如果游戏结束且用户选择再来一次，那么将重新执行初始化游戏的步骤，然后就可以开始移动数字。

```cpp
 while (true)
 {
     // 这里省略了对用户按键处理的代码    
     addRandomNum();
     drawMap();// 绘制新的 map，将原有的覆盖
     if (!canMove() || isFinish_2048())
     {
         ending();
         if (choice == 1)
         {
             // 重新初始化
             score = 0;
             for (int i = 0; i < 4; i++)
             {
                 for (int j = 0; j < 4; j++)
                 {
                     map[i][j] = 0;
                 }
             }
             score = 0;
             drawGame();// 游戏重新开始，但模式不变
             init2048(map);
             drawMap();
            while (_kbhit()) // 清除缓冲区多余的按键
            {
                _getch();
            }
             continue;
         }
         else
         {
             goodBye();
             this_thread::sleep_for(chrono::seconds(1));//1s后自动关闭
             closegraph();
             system("pause");
             return 0;
         }
     }
 }
```

> [!NOTE]
> 在测试时我发现，如果我在游戏结束后仍然按键，那么多按的键会被直接进入下一次循环导致下一次游戏的开始界面异常。因此，我做了一个小改动，加入了一个小循环将在键盘中缓冲的多余的键全部抛弃。
>
> ```cpp
> while(_kbhit())
> {
>     _getch();
> } 
> ```

### 同一模式下的难度分级

这里的难度分级主要依赖于随机产生 2 或 4 的概率。在 Easy 难度下，产生 4 的概率在 30% ~ 40%，但在 Difficult 难度下，产生 4 的概率为 0 ~ 10%。这只需要多定义几个随机数就能做到。

### 趣味模式

在趣味模式中，会出现可移动的障碍物。这些障碍物不能被合并，但能随着其他数字一起移动。同时，趣味模式也分 Easy 和 Difficult 两种难度，这里的难度区分主要是通过产生障碍物的多少。具体来说，Easy 难度只会产生 1 个障碍物，而 Difficult 难度会产生 2 到 3 个障碍物。为了实现这样的功能，我们需要修改用于初始化地图的源文件 `initialize.cpp`。目前有 4 种情况，它们的不同主要体现在产生 4 的概率不同以及产生障碍物的个数不同。只需要多定义几个随机数就能实现这几种情况，但代码就会稍稍有些冗长。

```cpp
// 加入趣味功能的 initialize.cpp

#include "head.h" // 包含需要的头文件以及相关变量、数组

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
```

我们还需要相应地修改合并逻辑，当遇到障碍物时，应当直接跳过。在具体实现中，我将障碍物的值赋为`1`，在合并数字时，遍历到它会直接跳过。而移动函数就不需要修改了，因为障碍物也是要移动的。

```cpp
// 以左移为例
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
                        continue;// 遇到1时直接跳过
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

// moveleft() 无需修改
```

## 图形化界面

前面提到，图形化界面使用了 EasyX 图形库，这个图形库相对简单，但我最终做出来的代码只能是差强人意。由于专门实现图形化界面的源文件 `output.cpp` 有 280 多行代码，因此我在这里只是大致说一下思路。我把图形化界面主要分为两个部分。第一是贴图片，第二是输出文字。贴图片需要设置颜色，确定大小位置即可。而输出文字类似，需要设置样式、确定内容以及位置。设置图片的颜色使用到函数 `setfillcolor()`；~~而为了适当地增加一点美感~~，我将所有图片都设置为圆角矩形 `solidroundrect()` 。输出文字则需要先设置字体样式 `settextstyle()`，然后设置字体颜色 `settextcolor()`，还需设置字体背景透明 `setbkmode(TRANSPARENT)`。最繁琐的还是确定位置，为了确定图片的位置不至于出现混乱以及将字体居中显示，我不得不逐一确定每一个界面中图片和字体的位置，这是导致代码冗长和可读性差的主要原因。另外，游戏开始和结束时有一个窗口会让玩家选择，这里我制作了几个按钮。所谓的按钮其实也是一个填充矩形，但鼠标在那片区域点击时程序会执行相应的语句从而产生不同的结果。下面是一个小例子，是关于绘制游戏背景的函数的，包括图形和文字的绘制。

```cpp
//设置游戏背景
void drawGame()
{
    setbkcolor(RGB(250, 248, 239));// 设置背景颜色
    cleardevice();// 清屏

    settextstyle(70, 0, "Arial", 0, 0, FW_SEMIBOLD, false, false, false);// 设置字体样式
    settextcolor(RGB(119, 110, 101));// 设置字体颜色
    setbkmode(TRANSPARENT);// 设置字体背景透明
    char str0[5]{};
    sprintf(str0, "%d", 2048);
    int tiheight = textheight(str0);
    outtextxy(50, 15, str0);
    drawScore();
}
```

## 总结

这次开发2048游戏的过程让我收获颇丰。我不仅掌握了C++多文件编程的要领，还将其成功地运用于项目实践中；与此同时，我也习得了基础的图形界面制作技术。事实上，这个项目对我来说，更是一场理想与现实之间的不断博弈与妥协。我原本计划是做一个一个掼蛋托管机器人，但随着项目的深入，我发现出牌环节的复杂性远超预期，最终不得不放弃。在做出这个决定时，我犹豫重重，毕竟除了出牌环节，其他部分我都已经完成。然而，经过深思熟虑，我意识到自己的能力还未达到完成这一任务的水平，于是转向了2048游戏。

转向2048后，我希望将图形界面做得出彩。最初，我打算学习使用Qt，但很快发现在有限的时间内掌握Qt并运用它完成项目几乎是不可能的任务。因此，我最终选择了更易上手的EasyX。尽管EasyX相对简单，但在实际制作图形界面时，我依然花了很大一番功夫。

这一次又一次的妥协，颇具戏剧性，却使我开始真正理性地评估自己的能力并接受自身的局限。勇往直前的精神固然重要，但不可盲目行事。适时地停下来，审视自己是否具备足够实力来推进当前任务的完成，同样至关重要。这不是畏难，而是学会勇敢面对自我，并从中获得更大的动力。
