#define _CRT_SECURE_NO_WARNINGS

#include "head.h"
#include "output.h"
#include "judge.h"

// ���ӿ�� 100
// �������� 4 * 4
// ����֮��ļ�� 15

//���� SCORE
void drawScore()
{
    setfillcolor(RGB(187, 173, 160));
    solidroundrect(240, 20, 450, 80, 5, 5);

    settextstyle(30, 0, "Arial");
    settextcolor(RGB(236, 228, 218));
    setbkmode(TRANSPARENT);
    char str1[20] = "SCORE   ";
    int tlen = textwidth(str1);
    int thei = textheight(str1);
    outtextxy(255, 50 - thei / 2, str1);

    settextstyle(30, 0, "Arial");
    settextcolor(RGB(255, 255, 255));
    setbkmode(TRANSPARENT);
    char strScore[20]{};
    sprintf(strScore, "%d", score);
    outtextxy(255 + tlen, 50 - thei / 2, strScore);
}

// ��ť����
void drawButton(int x, int y, char* buttonText) 
{

    setfillcolor(RGB(180, 178, 178));
    solidroundrect(x, y, x + 120, y + 40, 5, 5);

    settextcolor(RGB(255, 255, 255));
    settextstyle(20, 0, "Arial");
    setbkmode(TRANSPARENT);

    int x0 = textwidth(buttonText);
    outtextxy(x + 60 - x0/2, y + 10, buttonText);
}

// ��ʼ���棨��������ʼ����
void beginning()
{
    drawScore();
    setfillcolor(RGB(230, 230, 230));
    solidroundrect(40, 150, 435, 415, 10, 10);

    // ��ӭ�� Welcome to 2048!
    settextstyle(45, 0, "Arial");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(148, 91, 88));
    char texts[20] = "Welcome to 2048!";
    int tw = textwidth(texts);
    int th = textheight(texts);
    int textsX = (475 - tw) / 2;
    outtextxy(textsX, 165, texts);

    // ���Ʋ�ͬģʽ���Ѷȵİ�ť
    settextstyle(30, 0, "Arial");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(87, 114, 137));
    char choices[15] = "Classic";
    char choices_1[15] = "Interesting";
    int cw = textwidth(choices);
    int cw_1 = textwidth(choices_1);
    int ch = textheight(choices);
    int ch_1 = textheight(choices_1);
    int chx = (40 + 435 + 80 - 2 * cw) / 4;
    int chx_1 = (40 + 435 * 3 - 2 * cw_1) / 4;
    outtextxy(chx, 165 + th + 25, choices);
    outtextxy(chx_1, 165 + th + 25, choices_1);

    int left_1 = (40 * 3 + 435 - 240) / 4;
    int left_2 = (435 * 3 + 40 - 240) / 4;
    int top_1 = 165 + th + 20 + ch + 25;
    int top_2 = top_1 + 40 + 20;
    char difficulty[10] = "Easy";
    char difficulty_1[10] = "Difficult";
    drawButton(left_1, top_1, difficulty);
    drawButton(left_2, top_1, difficulty);
    drawButton(left_1, top_2, difficulty_1);
    drawButton(left_2, top_2, difficulty_1);

    //����갴��λ�õ���Ӧ
    MOUSEMSG mouseMsg;
    while (true)
    {
        if (MouseHit())
        {
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONDOWN)
            {
                int mouseX = mouseMsg.x;
                int mouseY = mouseMsg.y;
                if (mouseX >= left_1 && mouseX <= left_1 + 120 && mouseY >= top_1 && mouseY <= top_1 + 40)
                {
                    cho_dif = 1;;
                    break;
                }
                else if (mouseX >= left_1 && mouseX <= left_1 + 120 && mouseY >= top_2 && mouseY <= top_2 + 40)
                {
                    cho_dif = 2;
                    break;
                }
                else if (mouseX >= left_2 && mouseX <= left_2 + 120 && mouseY >= top_1 && mouseY <= top_1 + 40)
                {
                    cho_dif = 3;
                    break;
                }
                else if (mouseX >= left_2 && mouseX <= left_2 + 120 && mouseY >= top_2 && mouseY <= top_2 + 40)
                {
                    cho_dif = 4;
                    break;
                }
            }
        }
    }
}

//������Ϸ����
void drawGame()
{
    setbkcolor(RGB(250, 248, 239));// ���ñ�����ɫ
    cleardevice();// ����

    settextstyle(70, 0, "Arial", 0, 0, FW_SEMIBOLD, false, false, false);
    settextcolor(RGB(119, 110, 101));
    setbkmode(TRANSPARENT);
    char str0[5]{};
    sprintf(str0, "%d", 2048);
    int tiheight = textheight(str0);
    outtextxy(50, 15, str0);
    drawScore();
}

//���� 4 * 4 �ĵ�ͼ
void drawMap()
{
    setfillcolor(RGB(187, 173, 160));
    solidroundrect(0, 100, 475, 575, 10, 10);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int x = 15 + 115 * j;
            int y = 115 + 115 * i;// �������Ͻǵ�λ������
            int index;
            if (map[i][j] == 0)
            {
                index = 0;
            }
            else if (map[i][j] == 1)
            {
                index = 12;
            }
            else
            {
                index = (int)log2((double)map[i][j]);
            }
            setfillcolor(number[index]);// ���������ɫ
            solidroundrect(x, y, x + 100, y + 100, 10, 10);// ���Բ�Ǿ���
            settextstyle(50, 0, "Arial");// ����������ʽ
            setbkmode(TRANSPARENT);// �������屳��͸��
            char str[10]{};
            if (map[i][j] != 0)
            {
                
                if (map[i][j] >= 8 || map[i][j] == 1)
                {
                    settextcolor(RGB(255, 255, 255));
                }
                else
                {
                    settextcolor(RGB(119, 110, 101));
                }
                if (map[i][j] == 1)
                {
                    strcpy(str, "#");
                }
                else
                {
                    sprintf(str, "%d", map[i][j]);// ת�����ַ���
                }                
                int tw = textwidth(str);
                int th = textheight(str);

                int textX = x + 50 - tw / 2;
                int textY = y + 50 - th / 2;
                outtextxy(textX, textY, str);
            }
        }
    }
    drawScore();
}


// ���ս�������
void goodBye()
{
    setfillcolor(RGB(230, 230, 230));
    solidroundrect(35, 200, 440, 400, 10, 10);
    settextstyle(50, 0, "Arial");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(119, 110, 101));
    char bye[40] = "See you next time.";
    int byw = textwidth(bye);
    int byh = textheight(bye);
    outtextxy((475 - byw) / 2, 300 - byh / 2, bye);
}

// ��Ϸ��������
void ending()
{
    setfillcolor(RGB(230, 230, 230));
    solidroundrect(50, 200, 425, 400, 10, 10);

    // ���������
    settextstyle(50, 0, "Arial");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(148, 91, 88));
    char text_1[20];
    if (isFinish_2048())
    {
        char str[20] = "Congratulations!";
        strcpy(text_1, str);
    }
    else
    {
        char str[20] = "Game over.";
        strcpy(text_1, str);
    }
    int tw = textwidth(text_1);
    int th = textheight(text_1);
    int textX = (475 - tw) / 2;
    outtextxy(textX, 220, text_1);

    settextstyle(30, 0, "Arial");
    setbkmode(TRANSPARENT);
    settextcolor(RGB(88, 137, 126));
    char text_2[100] = "Do you want to play it again?";
    int sw = textwidth(text_2);
    int sh = textheight(text_2);
    int senX = (475 - sw) / 2;
    outtextxy(senX, 230 + th, text_2);

    char text_3[10] = "Yes";
    char text_4[10] = "No";
    drawButton(80, 250 + th + sh, text_3);
    drawButton(275, 250 + th + sh, text_4);

    // ��������ʱ��ѡ��ť
    MOUSEMSG mouseMsg;
    while (true)
    {
        if (MouseHit())
        {
            mouseMsg = GetMouseMsg();
            if (mouseMsg.uMsg == WM_LBUTTONDOWN)
            {
                int mouseX = mouseMsg.x;
                int mouseY = mouseMsg.y;

                if (mouseX >= 80 && mouseX <= 200 && mouseY >= 250 + th + sh && mouseY <= 290 + th + sh)
                {
                    choice = 1;
                    //cout << "Yes." << endl;
                    break;
                }
                else if (mouseX >= 275 && mouseX <= 395 && mouseY >= 250 + th + sh && mouseY <= 290 + th + sh)
                {
                    choice = 0;
                    //cout << "No." << endl;
                    break;
                }
            }
        }
    }
}
