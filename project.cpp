#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>
using namespace std;

bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100];
int nTail;

std::string fruit = "*";

enum eDirections
{
    STOP = 0,
    LEFT,
    RIGHT ,
    UP,
    DOWN,
};

eDirections dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width + 1;
    fruitY = rand() % height + 1;
    score = 0;
}
void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width + 1; j++)
        {
            if (j == 1 || j == width + 1)
                std::cout << "#";
            if (i == y && j == x)
            {
                std::cout << "O";
            }
            else if (j == fruitX && i == fruitY)
            {
                std::cout << fruit;
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width + 2; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'l':
            dir = LEFT;
            break;
        case 'r':
            dir = RIGHT;
            break;
        case 'u':
            dir = UP;
            break;
        case 'd':
            dir = DOWN;
            break;
        case '0':
            gameOver = true;
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if ((x > width || x < 0) || (y > height || y < 0))
    {
        std::cout << "\t\tGame Over" << std::endl;
        std::cout << "\t    You Hit the wall!";
        gameOver = true;
    }
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            std::cout << "\t\tGame Over" << std::endl;
            std::cout << "\t    You Hit the Tail!";
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        nTail++;
        fruitX = rand() % width + 1;
        fruitY = rand() % height + 1;
    }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(150);
    }
    std::cout << fruitX << " " << fruitY;
    return 0;
}
