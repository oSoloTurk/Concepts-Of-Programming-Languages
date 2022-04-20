//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_KISI_H
#define PDP_TASK_TWO_KISI_H

#include <string.h>
#include <malloc.h>

struct Kisi{
    char* name;
    float totalMoney;
    float spendMoneyEachRound;
    float luckyNumber;

    char* (*getName)(struct Kisi*);
    char* (*toString)(struct Kisi*);
    float (*getTotalMoney)(struct Kisi*);
    float (*getSpendMoneyEachRound)(struct Kisi*);
    int (*getLuckyNumber)(struct Kisi*);
};

typedef struct Kisi *Kisi;

Kisi new_Kisi(char* name, float totalMoney, float spendMoneyEachRound, int luckyNumber);

char* getName(const Kisi kisi);
char* toString(const Kisi Number);
float getTotalMoney(const Kisi kisi);
float getSpendMoneyEachRound(const Kisi kisi);
int getLuckyNumber(const Kisi kisi);

#endif //PDP_TASK_TWO_KISI_H
