#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cctype>
using namespace std;

string game = "---------";

vector<vector<char>> setOriginal();
void showGrid(vector<vector<char>>& grid);
int updatePlayerMove(vector<vector<char>>& grid, int r, int c);
char updateBotMove(vector<vector<char>>& grid);
char anyWinner(vector<vector<char>>& grid);


int main()
{
    int r, c, result;
    bool win = false;
    char winner;
    vector<vector<char>> originalGrid = setOriginal(); //It builds the grid
    cout << "\nOriginal, you play with 'X':\n";
    showGrid(originalGrid); //Prints the original sudoku

    while (!win) {
        cout << "\nYour move (0 1 = Row 0, Col 1):\n";
        cin >> r >> c;
        cout << endl;
        result = updatePlayerMove(originalGrid, r, c);
        if (result == 0) {
            cout << "--Error: Out of boundaries, you should write: (0, 1, 2).\n";
        }
        else if (result == 1) {
            cout << "--Error: That position isn't available.\n";
        }

        winner = anyWinner(originalGrid);

        if (winner == 'O' || winner == 'X') {
            break;
        }

        if (updateBotMove(originalGrid) == 'F') {
            break;
        }

        winner = anyWinner(originalGrid);
        if (winner == 'O' || winner == 'X') {
            break;
        }
    }

    switch (winner) {
    case 'X':
        cout << "\nCongratulations!! You won!!";
        break;
    case 'O':
        cout << "\nYou have been beaten by me :D";
        break;
    default:
        cout << "\nIt was a tie!";
        break;
    }

    return 0;
}

vector<vector<char>> setOriginal() {
    vector<vector<char>> grid;
    int i = 0;
    while (i++ < 3) {
        grid.push_back({ '-', '-', '-' });
    }
    return grid;
}

void showGrid(vector<vector<char>>& grid) {
    int i = 0, j = 0, n = 3;
    while (i < 3) {
        while (j < 3) {
            cout << grid[i][j++] << ' ';
        }
        j = 0;
        i++;
        cout << endl;
    }
    cout << endl;
}

int updatePlayerMove(vector<vector<char>>& grid, int r, int c) {
    if (r >= 3 || c >= 3) {
        return 0;
    }
    if (grid[r][c] != '-') {
        return 1;
    }
    grid[r][c] = 'X';
    game[r * 3 + c] = 'X';

    cout << "Your move:\n";
    showGrid(grid);
    return 2;
}

char anyWinner(vector<vector<char>>& grid) {
    if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])) { //Diagonal match
        return grid[1][1];
    }
    for (int i = 0; i < 3; i++) { //Row match | Column match
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]) {
            return grid[i][0];
        }
        if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i]) {
            return grid[0][i];
        }
    }
    return '-';
}

char updateBotMove(vector<vector<char>>& grid) {
    int count = 0, tileX = 0, tileO = 0, i = 0, value, valueR, valueC;
    vector<int> spaces;

    for (char c : game) {
        if (c == '-') {
            count++;
            spaces.push_back(i);
        }
        i++;
    }

    if (count == 0) return 'F';

    switch (count) {
    case 8:
        if (game[0] == 'X' || game[2] == 'X' || game[6] == 'X' || game[8] == 'X') { //Corner
            game[4] = 'O';
            grid[1][1] = 'O';
        }
        else if (game[4] == 'X') { //Center
            game[0] = 'O';
            grid[0][0] = 'O';
        }
        else { //Lateral
            game[4] = 'O';
            grid[1][1] = 'O';
        }
        break;
    case 6:
        if (game[4] == 'X') {
            if (game[1] == 'X') {
                game[7] = 'O';
                grid[2][1] = 'O';
            }
            else if (game[2] == 'X') {
                game[6] = 'O';
                grid[2][0] = 'O';
            }
            else if (game[3] == 'X') {
                game[5] = 'O';
                grid[1][2] = 'O';
            }
            else if (game[5] == 'X') {
                game[3] = 'O';
                grid[1][0] = 'O';
            }
            else if (game[6] == 'X') {
                game[2] = 'O';
                grid[0][2] = 'O';
            }
            else {
                game[1] = 'O';
                grid[0][1] = 'O';
            }
        }
        else {
            if (game[0] == 'X' && game[1] == 'X' || game[5] == 'X' && game[8] == 'X') {
                game[2] = 'O';
                grid[0][2] = 'O';
            }
            else if (game[0] == 'X' && game[2] == 'X') {
                game[1] = 'O';
                grid[0][1] = 'O';
            }
            else if (game[1] == 'X' && game[2] == 'X' || game[3] == 'X' && game[6] == 'X') {
                game[0] = 'O';
                grid[0][0] = 'O';
            }
            else if (game[0] == 'X' && game[3] == 'X' || game[7] == 'X' && game[8] == 'X') {
                game[6] = 'O';
                grid[2][0] = 'O';
            }
            else if (game[0] == 'X' && game[6] == 'X') {
                game[3] = 'O';
                grid[1][0] = 'O';
            }
            else if (game[2] == 'X' && game[5] == 'X' || game[6] == 'X' && game[7] == 'X') {
                game[8] = 'O';
                grid[2][2] = 'O';
            }
            else if (game[2] == 'X' && game[8] == 'X') {
                game[5] = 'O';
                grid[1][2] = 'O';
            }
            else {
                game[7] = 'O';
                grid[2][1] = 'O';
            }
        }
        break;
    default:
        for (int s : spaces) {
            switch (s) {
            case 0:
                if ((game[1] == 'O' && game[1] == game[2]) || (game[4] == 'O' && game[4] == game[8]) || (game[3] == 'O' && game[3] == game[6])) value = 3;
                else if ((game[1] == 'X' && game[1] == game[2]) || (game[4] == 'X' && game[4] == game[8]) || (game[3] == 'X' && game[3] == game[6])) value = 2;
                else value = 1;

                valueR = 0;
                valueC = 0;

                break;
            case 1:
                if ((game[0] == 'O' && game[0] == game[2]) || (game[4] == 'O' && game[4] == game[7])) value = 3;
                else if ((game[0] == 'X' && game[0] == game[2]) || (game[4] == 'X' && game[4] == game[7])) value = 2;
                else value = 1;

                valueR = 0;
                valueC = 1;

                break;
            case 2:
                if ((game[1] == 'O' && game[1] == game[0]) || (game[4] == 'O' && game[4] == game[6]) || (game[5] == 'O' && game[5] == game[8])) value = 3;
                else if ((game[1] == 'X' && game[1] == game[0]) || (game[4] == 'X' && game[4] == game[6]) || (game[5] == 'X' && game[5] == game[8])) value = 2;
                else value = 1;


                valueR = 0;
                valueC = 2;
                break;
            case 3:
                if ((game[0] == 'O' && game[0] == game[6]) || (game[4] == 'O' && game[4] == game[5])) value = 3;
                else if ((game[0] == 'X' && game[0] == game[6]) || (game[4] == 'X' && game[4] == game[5])) value = 2;
                else value = 1;

                valueR = 1;
                valueC = 0;

                break;
            case 5:
                if ((game[2] == 'O' && game[8] == game[2]) || (game[4] == 'O' && game[4] == game[3])) value = 3;
                else if ((game[2] == 'X' && game[8] == game[2]) || (game[4] == 'X' && game[4] == game[3])) value = 2;
                else value = 1;

                valueR = 1;
                valueC = 2;
                break;
            case 6:
                if ((game[0] == 'O' && game[0] == game[3]) || (game[4] == 'O' && game[4] == game[2]) || (game[8] == 'O' && game[7] == game[8])) value = 3;
                else if ((game[0] == 'X' && game[0] == game[3]) || (game[4] == 'X' && game[4] == game[2]) || (game[8] == 'X' && game[7] == game[8])) value = 2;
                else value = 1;

                valueR = 2;
                valueC = 0;
                break;
            case 7:
                if ((game[6] == 'O' && game[6] == game[8]) || (game[4] == 'O' && game[4] == game[1])) value = 3;
                else if ((game[6] == 'X' && game[6] == game[8]) || (game[4] == 'X' && game[4] == game[1])) value = 2;
                else value = 1;

                valueR = 2;
                valueC = 1;
                break;
            default:
                if ((game[2] == 'O' && game[5] == game[2]) || (game[4] == 'O' && game[4] == game[0]) || (game[6] == 'O' && game[7] == game[6])) value = 3;
                else if ((game[2] == 'X' && game[5] == game[2]) || (game[4] == 'X' && game[4] == game[0]) || (game[6] == 'X' && game[7] == game[6])) value = 2;
                else value = 1;

                valueR = 2;
                valueC = 2;
                break;
            }
            if (value == 3) break;
        }
        game[valueR * 3 + valueC] = 'O';
        grid[valueR][valueC] = 'O';
        break;
    }

    cout << "My move:\n";
    showGrid(grid);
    return '-';
}

/*
O  X

          [X][0] [X][1] [X][2]
    [0][X]  -      -      -
    [1][X]  -      -      -
    [2][X]  -      -      -



*/