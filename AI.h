#ifndef AI_H
#define AI_H

#include "Board.h"

class AI {
    private:
        int PlayOut = 0;  // Count of total play out
        int EVA = 0;      // Evaluation score which is the possibility of winning
    public:
        int AIManager(Board &);
        int Negamax(Board &, int);
};

#endif // AI_H
