#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    char input[65];
    Board();
    void clean();
    int GetValue(int);
    int winning();
    void DrawBoard();
    void PlayPosition(char);
};

#endif // BOARD_H
