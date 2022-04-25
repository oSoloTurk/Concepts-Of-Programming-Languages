#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


Queue new_Queue(){
    Queue queue = (Queue)malloc(sizeof(struct Queue));

    queue->head = NULL;

    queue->add = &add;
    queue->remove = &remove;
    queue->get = &get;
}

void* add(Queue queue, void* value) {
    Node newNode = (Node)malloc(sizeof(struct Node));
    *newNode->value = *value;
    if (queue->head == NULL) {
        newNode->next = NULL;
    }
    newNode->next = queue->head;
    queue->head = newNode;
}

void* remove(Queue queue, void* find) {
  Node queueNode = queue->head;
  Node cutTemp = NULL;
  int found = 0;
  while (queueNode != NULL) {
    if (*queueNode->value == *find) {
      found = 1;
      break;
    }
    cutTemp = queueNode;
    queueNode = queueNode->next;
  }
  if (found) {
    cutTemp->next = queueNode->next;
    free(queueNode);
  }
  queueNode = startTemp;
}
