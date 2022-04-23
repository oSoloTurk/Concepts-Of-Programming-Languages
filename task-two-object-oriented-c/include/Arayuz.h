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
    void* (*writeStatus)(struct Arayuz*, int luckyNumber, int round, float house, struct Kisi* topRich);
};

typedef struct Arayuz *Arayuz;

Arayuz new_Arayuz();

void* writeStatus(const Arayuz arayuz, int luckyNumber, int round, float house, Kisi topRich);
void* cleanScreen(const Arayuz arayuz);

#endif //PDP_TASK_TWO_ARAYUZ_H
