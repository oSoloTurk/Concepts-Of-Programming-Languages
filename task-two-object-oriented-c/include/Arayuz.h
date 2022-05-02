//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_ARAYUZ_H
#define PDP_TASK_TWO_ARAYUZ_H

#include <stdio.h>
#include <stdlib.h>
#include "Kisi.h"

struct Arayuz {
    void* (*cleanScreen)(struct Arayuz*);
    void* (*writeStatus)(struct Arayuz*, int luckyNumber, int round, double house, struct Kisi* topRich);
    void* (*writeFinish)(struct Arayuz*,int round, double house);
};

typedef struct Arayuz *Arayuz;

Arayuz new_Arayuz();

void* delete_Arayuz(Arayuz arayuz);

void* writeStatus(const Arayuz arayuz, int luckyNumber, int round, double house, Kisi topRich);
void* writeFinish(const Arayuz arayuz, int round, double house);
void* cleanScreen(const Arayuz arayuz);

#endif //PDP_TASK_TWO_ARAYUZ_H
