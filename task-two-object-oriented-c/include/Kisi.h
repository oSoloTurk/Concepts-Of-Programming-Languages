//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_KISI_H
#define PDP_TASK_TWO_KISI_H

#include <string.h>
#include <malloc.h>

struct Kisi{
    char* name;
    double totalMoney;
    double spendMoneyEachRound;
    int luckyNumber;

    char* (*getName)(struct Kisi*);
    double* (*getTotalMoney)(struct Kisi*);
    void* (*setTotalMoney)(struct Kisi*, double);
    double* (*getSpendMoneyEachRound)(struct Kisi*);
    int* (*getLuckyNumber)(struct Kisi*);
};

typedef struct Kisi *Kisi;

Kisi new_Kisi(char* name, double totalMoney, double spendMoneyEachRound, int luckyNumber);
void delete_Kisi(Kisi kisi);

char* getName(const Kisi kisi);
double* getTotalMoney(const Kisi kisi);
void* setTotalMoney(const Kisi kisi, const double value);
double* getSpendMoneyEachRound(const Kisi kisi);
int* getLuckyNumber(const Kisi kisi);

#endif //PDP_TASK_TWO_KISI_H
