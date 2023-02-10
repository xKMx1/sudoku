#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

bool checkingCol(int tab[][9][2], int c, int x)
{
    for (int i = 0; i < 9; i++)
    {
        if (tab[i][c][0] == x)
            return false;
        else
            return true;
    }
}

bool checkingRow(int tab[][9][2], int r, int x)
{
    for (int i = 0; i < 9; i++)
    {
        if (tab[r][i][0] == x)
            return false;
        else
            return true;
    }
}

int detectSquare(int tab[][9][2], int c, int r)
{
    if (c <= 2 && r <= 2)
    { // #1 square
        return 1;
    }
    if (c <= 2 && (r > 2 && r <= 5))
    { // #2 square
        return 2;
    }
    if (c <= 2 && (r > 5 && r <= 8))
    { // #3 square
        return 3;
    }
    if ((c > 2 && c <= 5) && r <= 2)
    { // #4 square
        return 4;
    }
    if ((c > 2 && c <= 5) && (r > 2 && r <= 5))
    { // #5 square
        return 5;
    }
    if ((c > 2 && c <= 5) && (r > 5 && r <= 8))
    { // #6 square
        return 6;
    }
    if ((c > 5 && c <= 8) && r <= 2)
    { // #7 square
        return 7;
    }
    if ((c > 5 && c <= 8) && (r > 2 && r <= 5))
    { // #8 square
        return 8;
    }
    if ((c > 5 && c <= 8) && (r > 5 && r <= 8))
    { // #9 square
        return 9;
    }
}

bool checkingSquare(int tab[][9][2], int c, int r, int x)
{
    int s = detectSquare(tab, c, r);

    int i, j;

    if (s == 1)
    {
        i = 0;
        j = 0;
    }
    if (s == 2)
    {
        i = 0;
        j = 3;
    }
    if (s == 3)
    {
        i = 0;
        j = 6;
    }
    if (s == 4)
    {
        i = 3;
        j = 0;
    }
    if (s == 5)
    {
        i = 3;
        j = 3;
    }
    if (s == 6)
    {
        i = 3;
        j = 6;
    }
    if (s == 7)
    {
        i = 6;
        j = 0;
    }
    if (s == 8)
    {
        i = 6;
        j = 3;
    }
    if (s == 9)
    {
        i = 6;
        j = 6;
    }

    for (i; i < 3; i++)
    {
        for (j; j < 3; j++)
        {
            if (tab[i][j][0] = x)
                return false;
            else
                return true;
        }
    }
}

void fillZero(int tab[][9][2])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            tab[i][j][0] = 0;
        }
    }
}

void genNumbers(int tab[][9][2])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (int n = 0; n < 10; n++)
            {
                int x = rand() % 9 + 1;
                if (checkingCol(tab, j, x))
                    if (checkingRow(tab, i, x))
                        if (checkingSquare(tab, j, i, x))
                            tab[i][j][0] = x;
            }
        }
    }
}

void printBoard(int tab[][9][2])
{
    for (int i = 0; i < 3; i++)
    {
        for (int n = 0; n < 3; n++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cout << setw(2) << tab[3 * i + n][3 * j + k][0] << ' ';
                }
                cout << " | ";
            }
            cout << endl;
        }
        cout << "----------------------------------|" << endl;
    }
}

int main()
{
    int sudokuBoard[9][9][2];

    fillZero(sudokuBoard);
    genNumbers(sudokuBoard);
    printBoard(sudokuBoard);

    return 0;
}
