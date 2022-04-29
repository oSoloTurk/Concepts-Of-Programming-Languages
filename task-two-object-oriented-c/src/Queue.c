#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "../include/Queue.h"


Queue new_Queue(){
    Queue queue = (Queue)malloc(sizeof(struct Queue));

    queue->head = NULL;

    queue->addItem = &addItem;
    queue->removeItem = &removeItem;
    queue->get = &get;

    return queue;
}

void* addItem(Queue queue, Kisi value) {
    Node newNode = (Node)malloc(sizeof(struct Node));
    newNode->value = value;
    if (queue->head == NULL) {
        newNode->next = NULL;
    }
    newNode->next = queue->head;
    queue->head = newNode;
}

void* removeItem(Queue queue, Kisi find) {
  Node startTemp = queue->head;
  Node queueNode = queue->head;
  Node cutTemp = NULL;
  int found = 0;
  while (queueNode != NULL) {
    if (queueNode->value == find) {
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

Kisi get(Queue queue, int index){
  int counter = 0;
  Node temp = queue->head;
  while(counter < index && temp != NULL) temp = temp->next;
  return temp->value;
}