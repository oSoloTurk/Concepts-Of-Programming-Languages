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
   void* (*incrRound)(struct Oyun*);
   int* (*getWinnerNumber)(struct Oyun*);
   double* (*getHouse)(struct Oyun*);
   Dosya (*getWinnerNumbers)(struct Oyun*);
   Kisi* (*getPlayers)(struct Oyun*);
   int* (*getPlayerSize)(struct Oyun*);

   void* (*setPlayers)(struct Oyun*, Kisi*);
   void* (*setHouse)(struct Oyun*, double);
   void* (*setPlayerSize)(struct Oyun*, int);

   void* (*nextRound)(struct Oyun*);
   void* (*playGame)(struct Oyun*, struct Arayuz*);
   void* (*printStatus)(struct Oyun*, struct Arayuz*);

   void* (*joinGame)(struct Oyun*, Kisi);
};

typedef struct Oyun *Oyun;


Oyun new_Oyun();
void* delete_Oyun(const Oyun oyun);


int* getWinnerNumber(const Oyun oyun);
int* getRound(const Oyun oyun);
void* incrRound(const Oyun oyun);
double* getHouse(const Oyun oyun);
void* setHouse(const Oyun oyun, const double value);
Dosya getWinnerNumbers(const Oyun oyun);
Kisi* getPlayers(const Oyun oyun);
int* getPlayerSize(const Oyun oyun);
void* setPlayerSize(const Oyun oyun, const int value);

void* setPlayers(const Oyun oyun, Kisi*);

void* nextRound(const Oyun oyun);
void* playGame(const Oyun oyun, const Arayuz arayuz);
void* printStatus(const Oyun oyun, const Arayuz arayuz);

void* joinGame(const Oyun oyun, const Kisi kisi);

#endif //PDP_TASK_TWO_OYUN_H
