#include "list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Item Functions */

Item *nodeAlloc() {
  Item *node;

  node = (Item *)malloc(sizeof(Item));
  assert(node);

  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;

  return node;
}

void freeItem(Item *node) {
  if (node && node->board) free(node->board);
  if (node) free(node);
}

void initList(list_t *list_p) {
  // if (list_p == NULL) list_p = malloc(sizeof(list_t));
  assert(list_p);

  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

int listCount(list_t *list) { return list->numElements; }

/* 1 même chaîne, 0 sinon */
int isSameChaine(Item *node, char *board) {
  for (int i = 0; i < node->size; i++) {
    if (node->board[i] != board[i]) {
      return 0;
    }
  }
  return 1;
}

// return an item with corresponding board , or null
Item *onList(list_t *list, char *board) {
  Item *p = list->first;

  while (p != NULL) {
    if (isSameChaine(p, board) == 1) {
      return p;
    }
    p = p->next;
  }
  return NULL;
}

// return and remove first item
Item *popFirst(list_t *list)  //
{
  assert(list->first != NULL);
  Item *item = list->first;
  delList(list, item);
  return item;
}

// return and remove last item
Item *popLast(list_t *list)  //
{
  assert(list->last != NULL);
  Item *item = list->last;
  delList(list, item);
  return item;
}

// remove a node from list
void delList(list_t *list, Item *node) {
  assert(list->first != NULL);
  if (list->first == list->last) {
    list->first = list->last = NULL;
    node->next = node->prev = NULL;
  } else if (list->last == node) {
    list->last = list->last->prev;
    node->prev = NULL;
    if (list->last != NULL) {
      list->last->next = NULL;
    }
  } else if (list->first == node) {
    list->first = list->first->next;
    node->next = NULL;
    list->first->prev = NULL;
  } else {
    Item *tmp = node->next;
    node->next->prev = node->prev;
    node->prev->next = tmp;
    node->next = node->prev = NULL;
  }
  list->numElements--;
}

// return and remove best item with minimal f value
Item *popBest(list_t *list)  // and remove the best board from the list.
{
  assert(list->first);
  Item *item = list->first;
  if (item != NULL) {
    Item *p = list->first->next;
    while (p != NULL) {
      if (item->f > p->f) {
        item = p;
      }
      p = p->next;
    }
  }
  delList(list, item);
  return item;
}

// add item in top
void addFirst(list_t *list, Item *node)  // add in head
{
  if (list->first == NULL) {
    node->next = NULL;
    node->prev = NULL;
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    node->prev = NULL;
    list->first->prev = node;
    list->first = node;
  }
  list->numElements++;
}

// add item in queue
void addLast(list_t *list, Item *node)  // add in tail
{
  if (list->last == NULL) {
    list->first = node;
    list->last = node;
    node->next = NULL;
    node->prev = NULL;
  } else {
    node->next = NULL;
    node->prev = list->last;
    list->last->next = node;
    list->last = node;
  }
  list->numElements++;
}


void cleanupList(list_t *list)
{
    Item *p = list->first;
    Item *tmp=p;

    while (p != NULL)
    {
        
        p = p->next;
        freeItem(tmp);
        tmp=p;
    }
    
    initList(list);
}

void printList(list_t list) {
  Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);
}

// TEST LIST

/*int main()
{
        Item *item;
        char str[3];

        list_t openList;

        initList(&openList);

        for (int i = 0; i < 10; i++)
        {
                item = nodeAlloc();
                item->f = i;
                sprintf(str, "%2d", i);
                item->board = strdup(str);
                addLast(&openList, item);
        }

        for (int i = 20; i < 25; i++)
        {
                item = nodeAlloc();
                item->f = i;
                sprintf(str, "%2d", i);
                item->board = strdup(str);
                addFirst(&openList, item);
        }
        printList(openList);
        printf("\n");

        Item *node = popBest(&openList);
        printf("best node = %.2f\n", node->f);
        printList(openList);
        printf("\n");

        strcpy(str, "23");
        node = onList(&openList, str);
        if (node)
                printf("found %s: %.2f!\n", str, node->f);
        printList(openList);
        printf("\n");

        node = popFirst(&openList);

        item = nodeAlloc();
        item->f = 50;
        sprintf(str, "50");
        item->board = strdup(str);
        addLast(&openList, item);

        node = popFirst(&openList);
        if (node)
                printf("first: %.2f\n", node->f);
        printList(openList);
        printf("\n");

        node = popLast(&openList);
        if (node)
                printf("last: %.2f\n", node->f);
        printList(openList);
        printf("\n");

        printf("clean\n");
        cleanupList(&openList);
        printList(openList);
        printf("\n");

        return 0;
}
*/