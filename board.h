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

double distance_Euclidienne(int i1, int j1, int i2, int j2);

int isValidPositionK(Item *node, int pos);

void printBoard(Item *board);

Item *getChildBoardK(Item *node, int pos);

/* Taquin */
#define WH_TAQUIN 3
#define MAX_TAQUIN WH_TAQUIN *WH_TAQUIN

Item *initGameT(int niveau);
void initBoardT(Item *node, char *tab);
void printBoardT(Item *node);
double evaluateBoardT(Item *node);
int isValidPositionT(Item *node, int pos);
Item *getChildBoardT(Item *node, int pos);

double getManhattanHeuristic(Item *node);