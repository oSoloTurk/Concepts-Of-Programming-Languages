//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_QUEUE_H
#define PDP_TASK_TWO_QUEUE_H

#include "Kisi.h"

struct Node {
   Kisi value;

   struct Node* next;
};

typedef struct Node* Node;

struct Queue{

   Node head;

   void* (*addItem)(struct Queue*, Kisi);
   void* (*removeItem)(struct Queue*, Kisi);
   Kisi (*get)(struct Queue*, int);
};

typedef struct Queue *Queue;


Queue new_Queue();

void* addItem(const Queue, Kisi);
void* removeItem(const Queue, Kisi);
Kisi get(const Queue, int);

#endif //PDP_TASK_TWO_QUEUE_H
