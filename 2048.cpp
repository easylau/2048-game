// @File : 2048.cpp
// @Author : Easylau
// @Time : 2022/02/08 11:13:16
#include <iostream>
using namespace std;
#include <conio.h> //console input/ouput
#include <ctime>
#include<cstdlib>

int randNum();                        //产生2/4随机数
int randPosition();                   //产生随机位置
void printArr(int *mainArr, int len); //打印数组
void upPile(int *mainArr, int len);   //上移操作
void moveUp(int *mainArr, int len, int *score);
void downPile(int *mainArr, int len); //下移操作
void moveDown(int *mainArr, int len, int *score);
void leftPile(int *mainArr, int len); //左移操作
void moveLeft(int *mainArr, int len, int *score);
void rightPile(int *mainArr, int len); //右移操作
void moveRight(int *mainArr, int len, int *score);
void generateNum(int *mainArr, int len); //在随机位置上放置随机数
int checkResult(int *mainArr, int len);  //通过返回值判断游戏状态（赢、输、继续）

int randNum()
{
    srand((int)time(0));
    return (rand() % 2 + 1) * 2;
}

int randPosition()
{
    srand((int)time(0));
    return rand() % 16;
}

void printArr(int *mainArr, int len)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << mainArr[i * 4 + j] << "\t";
        }
        cout << endl;
        cout << endl;
    }
}

void upPile(int *mainArr, int len)
{
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int x = i - 1; x > 0; x--)
            {
                if (mainArr[x * 4 + j] == 0)
                {
                    mainArr[x * 4 + j] = mainArr[(x + 1) * 4 + j];
                    mainArr[(x + 1) * 4 + j] = 0;
                }
            }
        }
    }
}

void moveUp(int *mainArr, int len, int *score)
{
    upPile(mainArr, len);
    for (int i = 1; i < 4; i++) //从第2行开始
    {
        for (int j = 0; j < 4; j++)
        {
            if (mainArr[i * 4 + j] == mainArr[(i - 1) * 4 + j] || mainArr[(i - 1) * 4 + j] == 0)
            {
                mainArr[(i - 1) * 4 + j] += mainArr[i * 4 + j];
                mainArr[i * 4 + j] = 0;
                *score += mainArr[(i - 1) * 4 + j];
            }
        }
    }
}

void downPile(int *mainArr, int len)
{
    for (int i = 3; i > -1; i--)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int x = i + 1; x < 4; x++)
            {
                if (mainArr[x * 4 + j] == 0)
                {
                    mainArr[x * 4 + j] = mainArr[(x - 1) * 4 + j];
                    mainArr[(x - 1) * 4 + j] = 0;
                }
            }
        }
    }
}

void moveDown(int *mainArr, int len, int *score)
{
    downPile(mainArr, len);
    for (int i = 3; i > 0; i--) //从最后一行开始
    {
        for (int j = 0; j < 4; j++)
        {
            if (mainArr[i * 4 + j] == mainArr[(i - 1) * 4 + j] || mainArr[i * 4 + j] == 0)
            {
                mainArr[i * 4 + j] += mainArr[(i - 1) * 4 + j];
                mainArr[(i - 1) * 4 + j] = 0;
                *score += mainArr[i * 4 + j];
            }
        }
    }
}

void leftPile(int *mainArr, int len)
{
    for (int j = 1; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int x = j - 1; x > -1; x--)
            {
                if (mainArr[i * 4 + x] == 0)
                {
                    mainArr[i * 4 + x] = mainArr[i * 4 + x + 1];
                    mainArr[i * 4 + x + 1] = 0;
                }
            }
        }
    }
}

void moveLeft(int *mainArr, int len, int *score)
{
    leftPile(mainArr, len);
    for (int j = 1; j < 4; j++) //从第二列开始
    {
        for (int i = 0; i < 4; i++)
        {
            if (mainArr[i * 4 + j] == mainArr[i * 4 + j - 1] || mainArr[i * 4 + j - 1] == 0)
            {
                mainArr[i * 4 + j - 1] += mainArr[i * 4 + j];
                mainArr[i * 4 + j] = 0;
                *score += mainArr[i * 4 + j - 1];
            }
        }
    }
}

void rightPile(int *mainArr, int len)
{
    for (int j = 2; j > -1; j--)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int x = j + 1; x < 4; x++)
            {
                if (mainArr[i * 4 + x] == 0)
                {
                    mainArr[i * 4 + x] = mainArr[i * 4 + x - 1];
                    mainArr[i * 4 + x - 1] = 0;
                }
            }
        }
    }
}

void moveRight(int *mainArr, int len, int *score)
{
    rightPile(mainArr, len);
    for (int j = 3; j > 0; j--) //从最后一列开始
    {
        for (int i = 0; i < 4; i++)
        {
            if (mainArr[i * 4 + j] == mainArr[i * 4 + j - 1] || mainArr[i * 4 + j] == 0)
            {
                mainArr[i * 4 + j] += mainArr[i * 4 + j - 1];
                mainArr[i * 4 + j - 1] = 0;
                *score += mainArr[i * 4 + j];
            }
        }
    }
}

void generateNum(int *mainArr, int len)
{
    while (1)
    {
        int p = randPosition();
        if (mainArr[p] == 0)
        {
            mainArr[p] = randNum();
            break;
        }
    }
}

int checkResult(int *mainArr, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (mainArr[i] == 2048) //赢的条件
        {
            return 1; //赢了
        }
        else if (mainArr[i] == 0)
        {
            count = count;
        }
        else
        {
            count++;
        }
    }
    if (count == 16) //输的条件
    {
        return 0; //输了
    }
    else
    {
        return 2; //继续
    }
}

int main()
{
    int mainArr[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int len = sizeof(mainArr) / sizeof(mainArr[0]); //行数
    int score = 0;
    char choice = ' ';
    system("color 02");
    cout << "按w上，s下，a左，d右。" << endl;
    cout << endl;
    generateNum(mainArr, len);
    printArr(mainArr, len);
    cout << "您的上一步操作是：" << choice << endl;
    cout << "得分：" << score << endl;
    while (1)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 119: // W
                choice = 'W';
                moveUp(mainArr, len, &score);
                break;
            case 115: // S
                choice = 'S';
                moveDown(mainArr, len, &score);
                break;
            case 97: // A
                choice = 'A';
                moveLeft(mainArr, len, &score);
                break;
            case 100: // D
                choice = 'D';
                moveRight(mainArr, len, &score);
                break;
            default:
                choice = 'N';
            }
            if (choice != 'N')
            {
                generateNum(mainArr, len);
                switch (checkResult(mainArr, len))
                {
                case 0:
                    system("cls");
                    cout << "您输了！" << endl;
                    cout << "得分：" << score << endl;
                    break;

                case 1:
                    system("cls");
                    cout << "您赢了！" << endl;
                    cout << "得分：" << score << endl;
                    break;

                case 2:
                    system("cls");
                    cout << "按w上，s下，a左，d右。" << endl;
                    cout << endl;
                    printArr(mainArr, len);
                    cout << "您的上一步操作是：" << choice << endl;
                    cout << "得分：" << score << endl;
                    break;
                }
            }
            else
            {
                system("cls");
                cout << "按w上，s下，a左，d右。" << endl;
                cout << endl;
                printArr(mainArr, len);
                cout << "您的上一步操作不合法！" << endl;
                cout << "得分：" << score << endl;
            }
        }
    }
    return 0;
}
