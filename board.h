#include "list.h"

#define RANDINIT() srand(time(NULL))
#define RANDOM() ((float)rand() / (float)RAND_MAX)
#define RANDMAX(x) (int)((float)(x)*rand() / (RAND_MAX + 1.0))

#define WH_BOARD 8                    // 5
#define MAX_BOARD WH_BOARD *WH_BOARD  // 25

Item *initGame();

Item *initGameK();

void initBoard(Item *node, char *board);

void initBoardK(Item *node);

Item *getChildBoard(Item *node, int pos);

double evaluateBoard(Item *node);

double evaluateBoardK(Item *node);