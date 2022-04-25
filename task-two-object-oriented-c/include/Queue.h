//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_QUEUE_H
#define PDP_TASK_TWO_QUEUE_H

struct Node {
   void* value;

   struct Node* next;
}

typedef struct Node* Node;

struct Queue{

   Node head;

   void* (*add)(struct Queue*, void*);
   void* (*remove)(struct Queue*, void*);
   void* (*get)(struct Queue, int);
};

typedef struct Queue *Queue;


Queue new_Queue();

void* add(const Oyun, void*);
void* playGame(const Oyun, void*);
void* get(const Oyun, int);

#endif //PDP_TASK_TWO_QUEUE_H
