//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_OYUN_H
#define PDP_TASK_TWO_OYUN_H

#include "Kisi.h"
#include "Dosya.h"
#include "Arayuz.h"
#include<stdio.h>

struct Oyun{
    
   int round;
   int winnerNumber;
   double house;
   int playerSize;

   Kisi* players;

   Dosya winnerNumbers;

   int* (*getRound)(struct Oyun*);
   int* (*getWinnerNumber)(struct Oyun*);
   double* (*getHouse)(struct Oyun*);
   Dosya (*getWinnerNumbers)(struct Oyun*);
   Kisi* (*getPlayers)(struct Oyun*);
   int* (*getPlayerSize)(struct Oyun*);

   void* (*setPlayers)(struct Oyun*, Kisi*);

   void* (*nextRound)(struct Oyun*);
   void* (*playGame)(struct Oyun*, struct Arayuz*);
   void* (*printStatus)(struct Oyun*, struct Arayuz*);

   void* (*joinGame)(struct Oyun*, Kisi);
};

typedef struct Oyun *Oyun;


Oyun new_Oyun();


int* getWinnerNumber(const Oyun);
int* getRound(const Oyun);
double* getHouse(const Oyun);
Dosya getWinnerNumbers(const Oyun);
Kisi* getPlayers(const Oyun);
int* getPlayerSize(const Oyun);

void* setPlayers(const Oyun, Kisi*);

void* nextRound(const Oyun);
void* playGame(const Oyun, const Arayuz);
void* printStatus(const Oyun, const Arayuz);

void* joinGame(const Oyun, const Kisi);

#endif //PDP_TASK_TWO_OYUN_H
