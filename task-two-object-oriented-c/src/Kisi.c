//
// Created by hakki on 4/15/2022.
//
#include "../include/Kisi.h"
#include <stdio.h>

Kisi new_Kisi(char* name, double totalMoney, double spendMoneyEachRound, int luckyNumber){
    Kisi kisi = (Kisi)malloc(sizeof(struct Kisi));
    
    kisi->name = name;
    kisi->totalMoney = totalMoney;
    kisi->spendMoneyEachRound = spendMoneyEachRound;
    kisi->luckyNumber = luckyNumber;

    kisi->getName = &getName;
    kisi->getTotalMoney = &getTotalMoney;
    kisi->getSpendMoneyEachRound = &getSpendMoneyEachRound;
    kisi->getLuckyNumber = &getLuckyNumber;

    kisi->setTotalMoney = &setTotalMoney;

    return kisi;
}

void delete_Kisi(Kisi kisi) {
    free(kisi); // mark as free
    kisi = NULL; // block access until the override
}

char* getName(const Kisi kisi){
    return kisi->name;
}

double* getTotalMoney(const Kisi kisi){
    return &(kisi->totalMoney);
}

void* setTotalMoney(const Kisi kisi, const double value){
    kisi->totalMoney = value;
}

double* getSpendMoneyEachRound(const Kisi kisi){
    return &(kisi->spendMoneyEachRound);
}

int* getLuckyNumber(const Kisi kisi){
    return &(kisi->luckyNumber);
}