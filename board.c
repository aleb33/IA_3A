#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

#define MAX_VECTOR 4

typedef struct {
  int len;
  unsigned int valid[MAX_VECTOR];
} move_t;

const move_t moves[MAX_BOARD] = {
    /* 0 */ {2, {1, 3}},
    /* 1 */ {3, {0, 2, 4}},
    /* 2 */ {2, {1, 5}},
    /* 3 */ {3, {0, 4, 6}},
    /* 4 */ {4, {1, 3, 5, 7}},
    /* 5 */ {3, {2, 4, 8}},
    /* 6 */ {2, {3, 7}},
    /* 7 */ {3, {4, 6, 8}},
    /* 8 */ {2, {5, 7}}};

// Initialize a new Game for the nQueens problem: an empty board..
Item *initGame() {
  int i;
  Item *node;

  char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
  for (int i = 0; i < MAX_BOARD; i++) initial[i] = 0;

  node = nodeAlloc();
  initBoard(node, initial);

  node->depth = 0;
  node->size = MAX_BOARD;
  return node;
}

Item *initGameK() {
  int i;
  Item *node;

  char *initial = (char *)malloc(MAX_BOARD * sizeof(char));
  for (int i = 0; i < MAX_BOARD; i++) {
    initial[i] = 0;
  }

  node = nodeAlloc();
  initBoard(node, initial);
  node->depth = 0;
  node->board[0] = 1;
  node->size = MAX_BOARD;

  return node;
}

Item *initGameT(int niveau) {
  Item *node = nodeAlloc();
  node->depth = 0;
  char easy[MAX_BOARD] = {1, 2, 5, 3, 0, 4, 7, 8, 6};
  char medium[MAX_BOARD] = {7, 4, 8, 2, 5, 6, 3, 1, 0};
  char difficult[MAX_TAQUIN] = {8, 0, 7, 5, 6, 1, 3, 2, 4};

  switch (niveau) {
    case 0:
      initBoardT(node, easy);
      node->blank = 4;
      break;
    case 1:
      initBoardT(node, medium);
      node->blank = 8;
      break;
    case 2:
      initBoardT(node, difficult);
      node->blank = 1;
      break;
    default:
      break;
  }

  node->size = MAX_TAQUIN;
  return node;
}

// print a board
void printBoard(Item *node) {
  assert(node);
  printf("\n");
  for (int j = 0; j < WH_BOARD; j++)
    if (j == 0)
      printf(" ___");
    else
      printf("____");
  printf("\n");
  for (int i = 0; i < MAX_BOARD; i++) {
    if (i % WH_BOARD == 0) printf("|");
    if (node->board[i] == 0)
      printf("   |");
    else
      printf("%2d |", node->board[i]);
    if (((i + 1) % WH_BOARD) == 0) {
      printf("\n");
      for (int j = 0; j < WH_BOARD; j++)
        if (j == 0)
          printf(" ___");
        else
          printf("____");
      printf("\n");
    }
  }
  printf("\n");
}

void printBoardT(Item *node) {
  assert(node);
  printf("\n");
  for (int j = 0; j < WH_TAQUIN; j++)
    if (j == 0)
      printf(" ___");
    else
      printf("____");
  printf("\n");
  for (int i = 0; i < MAX_TAQUIN; i++) {
    if (i % WH_TAQUIN == 0) printf("|");
    if (node->board[i] == 0)
      printf("   |");
    else
      printf("%2d |", node->board[i]);
    if (((i + 1) % WH_TAQUIN) == 0) {
      printf("\n");
      for (int j = 0; j < WH_TAQUIN; j++)
        if (j == 0)
          printf(" ___");
        else
          printf("____");
      printf("\n");
    }
  }
  printf("\n");
}

// initialize node's state from a given board
void initBoard(Item *node, char *board) {
  assert(node);

  node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));

  for (int i = 0; i < MAX_BOARD; i++) {
    node->board[i] = board[i];
  }

  /* Copy board */
}

void initBoardK(Item *node) {
  assert(node);

  node->size = MAX_BOARD;
  node->board = calloc(MAX_BOARD, sizeof(char));

  for (int i = 0; i < MAX_BOARD; i++) {
    node->board[i] = 0;
  }

  /* Copy board */
}

void initBoardT(Item *node, char *tab) {
  assert(node);

  node->size = MAX_TAQUIN;
  node->board = calloc(MAX_TAQUIN, sizeof(char));

  for (int i = 0; i < MAX_TAQUIN; i++) {
    node->board[i] = tab[i];
  }

  /* Copy board */
}
// Return 0 if all queens are placed. Positive otherwise
// Ie: nb queens that still need to be placed.
double evaluateBoard(Item *node) {
  double nb = 0;

  for (int i = 0; i < MAX_BOARD; i++) {
    if (node->board[i] == 1) nb++;
  }

  return WH_BOARD - nb;
}

double evaluateBoardK(Item *node) {
  assert(node);
  if (node->board[MAX_BOARD - 1] == 1) {
    return 0;
  } else {
    return 1;
  }
}

double evaluateBoardT(Item *node) {
  double cpt = 0;
  char tab[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  for (int i = 0; i < MAX_TAQUIN; i++) {
    if (node->board[i] == tab[i]) {
      cpt++;
    }
  }

  return MAX_TAQUIN - cpt;
}

// Test if position pos is valid with respect to node's state
// nQueens -> not same row ; not same column ; not same diagonal
int isValidPosition(Item *node, int pos) {
  int ii = pos / WH_BOARD;
  int jj = pos % WH_BOARD;

  for (int i = 0; i < WH_BOARD; i++) {
    for (int j = 0; j < WH_BOARD; j++) {
      if (node->board[i * WH_BOARD + j] == 1) {
        if (i == ii || j == jj) {
          return 0;
        } else if (i + j == ii + jj || i - j == ii - jj) {
          return 0;
        }
      }
    }
  }
  return 1;
}

double distance_Euclidienne(int i1, int j1, int i2, int j2) {
  return sqrt((i2 - i1) * (i2 - i1) + (j2 - j1) * (j2 - j1));
}

int isValidPositionK(Item *node, int pos) {
  int ii = pos / WH_BOARD;
  int jj = pos % WH_BOARD;

  int i = 0;

  while (i < MAX_BOARD && node->board[i] != 1) {
    i++;
  }

  if (MAX_BOARD == i) {
    return 0;
  }

  int cav_i = i / WH_BOARD;
  int cav_j = i % WH_BOARD;

  return distance_Euclidienne(ii, jj, cav_i, cav_j) == sqrt(5);
}

int isValidPositionT(Item *node, int pos) {
  for (int i = 0; i < moves[node->blank].len; i++) {
    if (moves[node->blank].valid[i] == pos) {
      return 1;
    }
  }

  return 0;
}

// Return a new item where a new queen is added at position pos if possible.
// NULL if not valid
Item *getChildBoard(Item *node, int pos) {
  Item *child_p = NULL;

  if (isValidPosition(node, pos) == 1) {
    /* allocate and init child node */
    child_p = nodeAlloc();
    /* Make move */
    child_p->depth = node->depth + 1;
    child_p->f = child_p->depth;
    initBoard(child_p, node->board);
    child_p->board[pos] = 1;
    /* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}

Item *getChildBoardK(Item *node, int pos) {
  Item *child_p = NULL;

  if (isValidPositionK(node, pos) == 1) {
    /* allocate and init child node */
    child_p = nodeAlloc();
    /* Make move */
    child_p->depth = node->depth + 1;
    child_p->f = child_p->depth;
    initBoardK(child_p);
    child_p->board[pos] = 1;
    /* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}

Item *getChildBoardT(Item *node, int pos) {
  Item *child_p = NULL;

  if (isValidPositionT(node, pos) == 1) {
    /* allocate and init child node */
    child_p = nodeAlloc();
    /* Make move */
    child_p->depth = node->depth + 1;
    child_p->f = child_p->depth;
    child_p->g = child_p->f;
    initBoardT(child_p, node->board);
    char tmp;
    tmp = child_p->board[pos];
    child_p->board[pos] = 0;
    child_p->board[node->blank] = tmp;
    child_p->blank = pos;
    child_p->size = MAX_TAQUIN;
    /* link child to parent for backtrack */
    child_p->parent = node;
  }

  return child_p;
}