

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Board.h"
#include "AI.h"

using namespace std;

int main() {
    srand(time(0));
    Board board;
    AI ai;

    cout << "Who should go first? (1 for Player, 2 for AI): ";
    int choice;
    cin >> choice;
    while (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Please choose 1 for Player or 2 for AI: ";
        cin >> choice;
    }

    while (true) {
        if (choice == 2) {
            int aiMove = ai.AIManager(board);  // Store the AI's move
            board.input[aiMove] = 'O';
            cout << "\n\n\n\n\nAI has picked column " << (aiMove % 8 == 0 ? 8 : aiMove % 8) << endl;
            choice = 1; // After the AI has played, it's now the player's turn
        } else {
            board.PlayPosition('X');
            choice = 2; // After the player has played, it's now the AI's turn
        }

        board.DrawBoard();
        int winningtemp = board.winning();
        if (winningtemp != 0) {
            if (winningtemp == 1)
                cout << endl << "PLAYER WON !\n";
            else if (winningtemp == 2)
                cout << endl << "AI WON !\n";
            else if (winningtemp == 3)
                cout << "You Tie ! ";
            string dummy;
            getline(cin, dummy);  // To wait for user input before clearing the board
            getline(cin, dummy); 

            board.clean();

            // Reset choice after game ends
            cout << "NEW GAME: who should go first? (1 for Player, 2 for AI), or enter -1 to quit: ";
            cin >> choice;
            if (choice == -1) {
                cout << "Thanks for playing!" << endl;
                exit(0); 
            }
            while (cin.fail() || (choice != 1 && choice != 2)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid choice. Please choose 1 for Player or 2 for AI: ";
                cin >> choice;
            }
        }
    }

    return 0;
}

