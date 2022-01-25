#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "board.h"
#include "list.h"

list_t openList_p;
list_t closedList_p;
// Une fonction de type "heuristic" est une fonction h() qui renvoie
// une distance (double) pour un noeud donné.
// de fin de la grille.On peut comme ça utiliser n'importe quelle heuristique pour astar
typedef double (*heuristic)(Item*);

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <algorithm> \n", argv[0]);
   fprintf(stderr, "-b: bfs \n");
   fprintf(stderr, "-d: dfs \n");
   fprintf(stderr, "-u: ucs \n");
   fprintf(stderr, "-a: astar \n");
  fprintf(stderr, "Choose an algorithm between DFS, BFS, UCS and Astar!\n");
  exit(EXIT_FAILURE);
}


double distanceManhattan(int target, int pos) {
  int i = pos / WH_TAQUIN;
  int j = pos % WH_TAQUIN;

  int ii = target / WH_TAQUIN;
  int jj = target % WH_TAQUIN;

  return abs(ii - i) + abs(jj - j);
}

double getSimpleHeuristic(Item *node) { return 0.0; }

double getManhattanHeuristic(Item *node) {
  char target[MAX_TAQUIN] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  double sum = 0;
  for (int i = 0; i < MAX_TAQUIN; i++) {
    if (node->board[i] != 0) {
      sum = sum + distanceManhattan((node->board[i] - 1), i);
    }
  }
  return sum;
}

void showSolution(Item *goal) {
  int i = 0, j;

  printf("\nSolution:");

  while (goal) {
    printBoardT(goal);
    goal = goal->parent;
    i++;
  }
  printf("\nLength of the solution = %d\n", i - 1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}

void bfs(void) {
  Item *cur_node, *child_p, *temp;
  int i;

  while (listCount(&openList_p)) { /* While items are on the open list */
    /* Get the first item on the open list */
    cur_node = popFirst(&openList_p);
    // printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    addLast(&closedList_p, cur_node);
    /* Do we have a solution? */
    if (evaluateBoardT(cur_node) == 0.0) {
      showSolution(cur_node);
      return;
    } else {
      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_TAQUIN; i++) {
        child_p = getChildBoardT(cur_node, i);

        if (child_p != NULL) {  // it's a valid child!
          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL) {
            /* Add child node to openList */
            addLast(&openList_p, child_p);
            //   printBoard(child_p);
          }
        }
      }
    }
  }

  return;
}

void dfs(void) {
  Item *cur_node, *child_p;
  while (listCount(&openList_p)) {
    cur_node = popFirst(&openList_p);
    addFirst(&closedList_p, cur_node);
    if (evaluateBoardT(cur_node) == 0.0) {
      showSolution(cur_node);
      return;
    } else {
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoardT(cur_node, i);
        if (child_p != NULL) {  // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL) {
            /* Add child node to openList */
            addFirst(&openList_p, child_p);
          }
        }
      }
    }
  }
}

void ucs(void) {
  Item *cur_node, *child_p, *tmp;
  while (listCount(&openList_p)) {
    cur_node = popBest(&openList_p);
    addFirst(&closedList_p, cur_node);
    if (evaluateBoardT(cur_node) == 0.0) {
      showSolution(cur_node);
      return;
    } else {
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoardT(cur_node, i);
        if (child_p != NULL) {  // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL) {
            /* Add child node to openList */
            tmp = onList(&openList_p, child_p->board);
            if (tmp == NULL) {
              addFirst(&openList_p, child_p);
            } else {
              if (tmp->f > child_p->f) {
                delList(&openList_p, tmp);
                addFirst(&openList_p, child_p);
              }
            }
          }
        }
      }
    }
  }
}


void astar(heuristic h) {
  Item *cur_node, *child_p, *tmp;
  while (listCount(&openList_p)) {
    cur_node = popBest(&openList_p);
    addFirst(&closedList_p, cur_node);
    if (evaluateBoardT(cur_node) == 0.0) {
      showSolution(cur_node);
      return;
    } else {
      for (int i = 0; i < MAX_BOARD; i++) {
        child_p = getChildBoardT(cur_node, i);
        if (child_p != NULL) {  // it's a valid child!
          child_p->f = child_p->g + h(child_p);

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL) {
            /* Add child node to openList */
            tmp = onList(&openList_p, child_p->board);
            if (tmp == NULL) {
              addFirst(&openList_p, child_p);
            } else {
              tmp->f = tmp->g + h(tmp);
              if (tmp->f > child_p->f) {
                delList(&openList_p, tmp);
                addFirst(&openList_p, child_p);
              }
            }
          }
        }
      }
    }
  }
}

int main(int argc,char*argv[]) {
  if (argc !=2) {
    usage(argc, argv);
  }
  printf(
      "Bienvenue dans le jeu du taquin !\n Choissisez le niveau :\n0 : EASY\n1 "
      ": MEDIUM\n2 : DIFFICULT\n");
  int niveau = 5;
  while (niveau > 3 || niveau < 0) {
    scanf("%d", &niveau);

    printf("Vous avez choisis le niveau %d : ", niveau);
    switch (niveau) {
      case 0:
        printf("Easy\n");
        break;
      case 1:
        printf("Medium\n");
        break;
      case 2:
        printf("Difficult\n");
        break;
      default:
        printf("\nChoisir un niveau entre 0 et 2\n");
        break;
    }
  }
  printf("\nInitial:");
  Item *initial_state = initGameT(niveau);
  printBoardT(initial_state);
  addLast(&openList_p, initial_state);
  char* c= argv[1];
  if (strcmp(c,"-b")==0) goto bfs;
  if (strcmp(c,"-d")==0) goto dfs;
  if (strcmp(c,"-u")==0) goto ucs;
  if (strcmp(c,"-a")==0) goto astar;
  if ((strcmp(c,"-b")!=0) || (strcmp(c,"-d")!=0) || (strcmp(c,"-u")!=0) ||  (strcmp(c,"-a")!=0)) usage(argc,argv);

  bfs:
    printf("BFS :\n");
    bfs();
    cleanupList(&openList_p);
    cleanupList(&closedList_p);
    return 0;

  dfs:
    printf("DFS :\n");
    dfs();
    cleanupList(&openList_p);
    cleanupList(&closedList_p);
    return 0;

  ucs:
    printf("UCS :\n");
    ucs();
    cleanupList(&openList_p);
    cleanupList(&closedList_p);
    return 0;

  astar:
    printf("Astar :\n");
    printf(
      "Choissisez l'heuristique:\n0 : Heurisitrique Simple\n1 "
      ": Heuristique Manhattan\n");
    int h = 3;
    while (h > 2 || h < 0) {
      scanf("%d", &h);
      printf("Vous avez choisis l'heuristique %d : ", h);
      switch (h) {
        case 0:
          astar(getSimpleHeuristic);
          break;
        case 1:
          astar(getManhattanHeuristic);
          break;
        default:
          printf("\nChoisir une heuristique entre 0 et 1 \n");
          break;
      }
    }
    cleanupList(&openList_p);
    cleanupList(&closedList_p);
    return 0;


  printf("\nSearching ...\n");

  
  printf("Finished!\n");

  /* clean lists */

  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}
