#ifndef HEAD_H
#define HEAD_H

#include <graphics.h>		// 引用图形库头文件
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;
extern int map[4][4];
extern int score;
extern int times;
extern int choice;
extern int cho_dif;


extern enum Number
{
    ZERO = RGB(205, 193, 180),
    ONE = RGB(238, 228, 218),
    TWO = RGB(237, 224, 200),
    THREE = RGB(242, 176, 121),
    FOUR = RGB(245, 148, 99),
    FIVE = RGB(246, 124, 95),
    SIX = RGB(246, 94, 59),
    SEVEN = RGB(237, 207, 114),
    EIGHT = RGB(237, 204, 97),
    NINE = RGB(255, 0, 128),
    TEN = RGB(145, 0, 72),
    ELEVEN = RGB(242, 17, 158),
    BACK = RGB(87, 114, 137)
};
extern Number number[13];
#endif
