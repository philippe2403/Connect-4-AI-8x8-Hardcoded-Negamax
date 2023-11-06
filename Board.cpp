#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

Board::Board() {
        clean(); // Initialize the board
    }

//
void Board::clean() {
        for (int i = 0; i <= 64; i++) {
            input[i] = ' ';
        }
    }

int Board::GetValue(int column) {
        if (column > 8)
            return 0;
        int n = 0;
        for (int i = 0; i <= 8; i++) {
            if (input[column + 8 * i] == ' ') {
                n = column + 8 * i;
                break;
            }
        }
        if (n > 64)
            return 0;
        return n;
    }

int Board::winning(){
    int temp = 0;
    for (int i = 1; i <= 64; i++) {
        if (input[i] != ' ') {
            temp++;
            
            // Horizontal Winning Check
            if (i - int((i - 1) / 8) * 8 <= 5)
                if (input[i] == input[i + 1] && input[i] == input[i + 2] && input[i] == input[i + 3])
                    if (input[i] == 'X')
                        return 1;
                    else
                        return 2;

            // Vertical Winning Check
            if (i <= 40)
                if (input[i] == input[i + 8] && input[i] == input[i + 16] && input[i] == input[i + 24])
                    if (input[i] == 'X')
                        return 1;
                    else
                        return 2;

            // Diagonal Winning Check (Top-left to Bottom-right)
            if (i - int((i - 1) / 8) * 8 <= 5 && i <= 37)
                if (input[i] == input[i + 9] && input[i] == input[i + 18] && input[i] == input[i + 27])
                    if (input[i] == 'X')
                        return 1;
                    else
                        return 2;

            // Diagonal Winning Check (Top-right to Bottom-left)
            if (i - int((i - 1) / 8) * 8 >= 4 && i <= 40)
                if (input[i] == input[i + 7] && input[i] == input[i + 14] && input[i] == input[i + 21])
                    if (input[i] == 'X')
                        return 1;
                    else
                        return 2;
        }
    }

    // Full Board Check
    if (temp == 64)
        return 3;

    return 0;
}

void Board::DrawBoard(){
            cout << endl << " 1 2 3 4 5 6 7 8" << endl;
            
            for (int i = 7; i >= 0; i--) {
                cout << string(17, '-') << endl;
                for (int j = 0; j < 8; j++) {
                    cout << "|" << input[i * 8 + j + 1];
                }
                cout << "|";
                cout << endl;
            }
            cout << string(17, '-') << endl;
            cout << endl << " 1 2 3 4 5 6 7 8" << endl;
}

void Board::PlayPosition(char XO) {
        int sth;
        cout << endl << "Where would you like to play? (Enter -1 to stop)" << endl;

        while (true) {
            cin >> sth;

            if (sth == -1) {
                cout << "Thanks for playing!" << endl;
                exit(0);  
            }

            sth = GetValue(sth);

            if (sth != 0) {
                input[sth] = XO;
                int columnChosen = sth % 8 == 0 ? 8 : sth % 8;  // Calculate the actual column number
                cout << "\n\n\n\n\nPlayer has picked column " << columnChosen << endl;  
                return;
            } else {
                cout << "ERROR: Invalid position. Try again or enter -1 to stop." << endl;
            }
        }
}
