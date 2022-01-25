#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
//#include <malloc.h>
#include <string.h>
#include "list.h"
#include "board.h"
#include <getopt.h>

list_t openList_p;
list_t closedList_p;

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <algorithm> \n", argv[0]);
  fprintf(stderr, "-b: bfs \n");
  fprintf(stderr, "-d: dfs \n");
  fprintf(stderr, "-u: ucs \n");
  fprintf(stderr, "Choose an algorithm between DFS, BFS and UCS !\n");
  exit(EXIT_FAILURE);
}

void showSolution(Item *goal)
{
  int i = 0, j;

  printf("\nSolution:");

  while (goal)
  {
    printBoard(goal);
    goal = goal->parent;
    i++;
  }
  printf("\nLength of the solution = %d\n", i - 1);
  printf("Size of open list = %d\n", openList_p.numElements);
  printf("Size of closed list = %d\n", closedList_p.numElements);
  return;
}

void bfs(void)
{
  Item *cur_node, *child_p, *temp;
  int i;

  while (listCount(&openList_p))
  { /* While items are on the open list */
    /* Get the first item on the open list */
    cur_node = popFirst(&openList_p);
    //printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    addLast(&closedList_p, cur_node);
    /* Do we have a solution? */
    if (evaluateBoardK(cur_node) == 0.0)
    {
      showSolution(cur_node);
      return;
    }
    else
    {
      /* Enumerate adjacent states */
      for (int i = 0; i < MAX_BOARD; i++)
      {
        child_p = getChildBoardK(cur_node, i);

        if (child_p != NULL)
        { // it's a valid child!
          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL)
          {
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

void dfs(void)
{

  Item *cur_node, *child_p;
  while (listCount(&openList_p))
  {
    cur_node = popFirst(&openList_p);
    addFirst(&closedList_p, cur_node);
    if (evaluateBoardK(cur_node) == 0.0)
    {
      showSolution(cur_node);
      return;
    }
    else
    {
      for (int i = 0; i < MAX_BOARD; i++)
      {
        child_p = getChildBoardK(cur_node, i);
        if (child_p != NULL)
        { // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL)
          {
            /* Add child node to openList */
            addFirst(&openList_p, child_p);
          }
        }
      }
    }
  }
}

void ucs(void)
{

  Item *cur_node, *child_p, *tmp;
  while (listCount(&openList_p))
  {
    cur_node = popBest(&openList_p);
    addFirst(&closedList_p, cur_node);
    if (evaluateBoardK(cur_node) == 0.0)
    {
      showSolution(cur_node);
      return;
    }
    else
    {
      for (int i = 0; i < MAX_BOARD; i++)
      {
        child_p = getChildBoardK(cur_node, i);
        if (child_p != NULL)
        { // it's a valid child!

          /* Ignore this child if already visited */
          if (onList(&closedList_p, child_p->board) == NULL)
          {
            /* Add child node to openList */
            tmp = onList(&openList_p, child_p->board);
            if (tmp == NULL)
            {
              addFirst(&openList_p, child_p);
            }
            else
            {
              if (tmp->f > child_p->f)
              {
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

int main(int argc, char *argv[])
{ 
  if (argc !=2) {
    usage(argc, argv);
  }
  /* init lists */
  initList(&openList_p);
  initList(&closedList_p);

  printf("\nInitial:");
  Item *initial_state = initGameK();
  printBoard(initial_state);

  printf("\nSearching ...\n");

  addLast(&openList_p, initial_state);

   char* c= argv[1];
  if (strcmp(c,"-b")==0) goto bfs;
  if (strcmp(c,"-d")==0) goto dfs;
  if (strcmp(c,"-u")==0) goto ucs;
  if ((strcmp(c,"-b")!=0) || (strcmp(c,"-d")!=0) || (strcmp(c,"-u")!=0) ) usage(argc,argv);

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

  /* clean lists */

  cleanupList(&openList_p);
  cleanupList(&closedList_p);

  return 0;
}
