//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_OYUN_H
#define PDP_TASK_TWO_OYUN_H

#include "Kisi.h"
#include "Dosya.h"

struct Oyun{
    
   int round;
   int winnerNumber;
   float house;

   Kisi* players;

   Dosya winnerNumbers;

   void* (*nextRound)(struct Oyun*);
   int* (*getWinnerNumber)(struct Oyun*);
   void* (*joinGame)(struct Oyun*, Kisi, float);
};

typedef struct Oyun *Oyun;


Oyun new_Oyun();

void* nextRound(const Oyun);
int* getWinnerNumber(const Oyun);
void* joinGame(const Oyun, const Kisi, const float);

#endif //PDP_TASK_TWO_OYUN_H
