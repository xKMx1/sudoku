#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void genNumbers(int tab[][9][2])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            tab[i][j][0] = rand() % 10 + 1;
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

    genNumbers(sudokuBoard);
    printBoard(sudokuBoard);

    return 0;
}
