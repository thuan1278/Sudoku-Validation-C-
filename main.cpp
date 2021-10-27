#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<cstdlib>
#include <sstream>

using namespace std;
stringstream row_invalid;
stringstream col_invalid;
bool valid(vector<vector<int> >& board)
{
    //Check of duplicates
    for (int i = 0; i < 9; i++)
        for (int j = 1; j < 9; j++) {
            int keyCol = board[i][j];
            int keyRow = board[j][i];
            int x = j - 1;

            //Check row
            while (x >= 0) {
                x -= 1;
                if (board[i][x + 1] == keyCol && board[i][x + 1] != 0) {
                    row_invalid << "row " << i << " has a duplicate of " << keyCol << "s";
                    return false;
                }
            }

            //Check column
            x = j - 1;
            while (x >= 0) {
                x -= 1;
                if (board[x + 1][i] == keyRow && board[x + 1][i] != 0) {
                    col_invalid << "col " << i << " has a duplicate of " << keyRow << "s";
                    return false;
                }
            }
        }

	return true;
}

bool solve(vector<vector<int> >& board)
{
    int sumRow = 0;
	int sumCol = 0;

		if (valid(board))
		{
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					sumRow += board[i][j];
					sumCol += board[j][i];
				}
				if (sumRow != 45 || sumCol != 45)
					return false;
				else {
					sumRow = 0;
					sumCol = 0;
				}

			}
		}
		else
         {
			return false;
		 }

	return true;
}

int main()
{
	fstream f;
	string inputFileName;

	//ask the user for file name
    getline(cin, inputFileName);
	f.open(inputFileName, ios::in | ios::out);
	string word;
	string name;
	vector<vector<int> > sudoku_board(9, vector<int>(9, 0));
	vector<vector<char> > sudoku_board_display(9, vector<char>(9, 0));

	if (!f)
	{
		cout << "File does not exist!" << endl;
		return 0;
	}
	else
	{
        while (!f.eof())
         {
            int board_row = 0;
            int row = 0, col = 0;

            while (getline(f, word) && board_row < 9)
            {
                if (word.length() != 9)
                {
                    name.assign(word);
                    continue;
                }
                for (int p = 0; p < 9; p++)
                {
                    sudoku_board_display[row][col] = word[p];
                    if (word[p] == ' ')
                        sudoku_board[row][col] = 0;
                    else {
                        int ch = word[p] - '0';
                        sudoku_board[row][col] = ch;
                    }
                    col++;

                    if (col == 9)
                    {
                        row++;
                        if (row == 9)
                            break;
                        col = 0;
                    }
                }
                board_row++;
            }

            if (valid(sudoku_board))
            {
                if (solve(sudoku_board))
                {
                    cout << name <<" solved" << endl;
                } else
                    cout << name << " valid" << endl;
            }
            else
            {
                if (col_invalid.str().empty())
                        cout << name << " invalid " << row_invalid.str() << endl;
                else
                        cout << name << " invalid " << col_invalid.str() << endl;
           }
        }
            f.close();
    }
}
