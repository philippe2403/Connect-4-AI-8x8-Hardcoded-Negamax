#include "AI.h"
#include "Board.h"

using namespace std;

    /**
     * Main AI move manager. Decides the best move for the AI and returns it.
     * @param board - The game board to evaluate and decide the move on.
     * @return - The best column number for the AI to play its move.
     */
    int AI::AIManager(Board &board) {
        float chance[2] = {9999999, 0}; // Array to hold the best chance and corresponding column

        for (int column = 1; column <= 8; column++) {
            PlayOut = 0;
            EVA = 0;
            int PlayNumber = board.GetValue(column);  // Get the available position in the column

            if (PlayNumber != 0) {
                board.input[PlayNumber] = 'O';

                // If AI wins with this move, return this move
                if (board.winning() == 2) {
                    board.input[PlayNumber] = ' ';
                    return PlayNumber;
                }

                float temp = -100 * Negamax(board, 1);
                if (PlayOut != 0) {
                    temp -= (100.0 * EVA) / PlayOut; // Adjusting the score based on evaluations
                }

                // Update the best chance and corresponding column if current chance is better
                if (chance[0] > temp) {
                    chance[0] = temp;
                    chance[1] = PlayNumber;
                }

                board.input[PlayNumber] = ' ';
            }
        }
        return chance[1];
    }


    // Negamax algorithm: think of the best move for the AI and the worst scenario that it might face
    /**
     * Recursive NegaMax algorithm. Evaluates board positions to decide the best move.
     * @param board - The current state of the game board.
     * @param Depth - The current depth level of the recursive search.
     * @return - The evaluation score of the board after considering all possible moves. 
     */
    int AI::Negamax(Board &board, int Depth) {
        char XO;
        int PlayNumber[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};  // Positions to play in each column
        int chance = 0;

        // Determine whether to place 'X' or 'O' based on current depth
        if (Depth % 2 != 0)
            XO = 'X';
        else
            XO = 'O';

        // Get the available position in each column
        for (int column = 1; column <= 8; column++)
            PlayNumber[column] = board.GetValue(column);

        for (int column = 1; column <= 8; column++) {
            if (PlayNumber[column] != 0) {
                board.input[PlayNumber[column]] = XO;

                // If there's a winner after this move, update PlayOut and EVA accordingly
                if (board.winning() != 0) {
                    PlayOut++;
                    if (XO == 'O')
                        EVA++;
                    else
                        EVA--;

                    board.input[PlayNumber[column]] = ' ';
                    return -1;
                }
                board.input[PlayNumber[column]] = ' ';
            }
        }

        // Recurse to a maximum depth of 6
        if (Depth <= 6) {
            for (int column = 1; column <= 8; column++) {
                int temp = 0; // Temporary variable to store the current chance
                if (PlayNumber[column] != 0) {
                    board.input[PlayNumber[column]] = XO;

                    if (board.winning() != 0) { 
                        PlayOut++;
                        if (XO == 'O')
                            EVA++;
                        else
                            EVA--;

                        board.input[PlayNumber[column]] = ' ';
                        return -1;
                    }
                    temp = Negamax(board, Depth + 1); // Recurse to the next depth
                    if (column == 1)
                        chance = temp;
                    if (chance < temp)
                        chance = temp;
                    board.input[PlayNumber[column]] = ' ';
                }
            }
        }
        return -chance;  // Return the negative value of chance to alternate maximizing/minimizing
    }


