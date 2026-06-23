#include <iostream>
using namespace std;

char board[3][3];

// Initialize board
void initializeBoard()
{
    char position = '1';

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = position++;
        }
    }
}

// Display board
void displayBoard()
{
    cout << "\n";

    for (int i = 0; i < 3; i++)
    {
        cout << " ";

        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];

            if (j < 2)
                cout << " | ";
        }

        cout << endl;

        if (i < 2)
            cout << "---|---|---" << endl;
    }

    cout << "\n";
}

// Check winner
bool checkWinner(char player)
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
            return true;
    }

    // Columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == player &&
            board[1][j] == player &&
            board[2][j] == player)
            return true;
    }

    // Diagonals
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
        return true;

    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
        return true;

    return false;
}

// Check draw
bool checkDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
        }
    }

    return true;
}

// Make move
bool makeMove(int position, char player)
{
    if (position < 1 || position > 9)
        return false;

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O')
        return false;

    board[row][col] = player;
    return true;
}

int main()
{
    char replay;

    do
    {
        initializeBoard();
        char currentPlayer = 'X';
        int position;

        while (true)
        {
            displayBoard();

            cout << "Player " << currentPlayer
                 << ", enter position (1-9): ";
            cin >> position;

            if (!makeMove(position, currentPlayer))
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            if (checkWinner(currentPlayer))
            {
                displayBoard();
                cout << "Player " << currentPlayer
                     << " wins!\n";
                break;
            }

            if (checkDraw())
            {
                displayBoard();
                cout << "Game Draw!\n";
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        cout << "\nPlay Again? (Y/N): ";
        cin >> replay;

    } while (replay == 'Y' || replay == 'y');

    cout << "Thanks for playing!\n";
    return 0;
}
