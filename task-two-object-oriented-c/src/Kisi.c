//
// Created by hakki on 4/15/2022.
//
#include "../include/Kisi.h"

Kisi new_Kisi(char* name, float totalMoney, float spendMoneyEachRound, int luckyNumber){
    Kisi kisi = (Kisi)malloc(sizeof(Kisi));
    kisi->name = name;
    kisi->totalMoney = totalMoney;
    kisi->spendMoneyEachRound = spendMoneyEachRound;
    kisi->luckyNumber = luckyNumber;

    kisi->getName = &getName;
    kisi->toString = &toString;
    kisi->getTotalMoney = &getTotalMoney;
    kisi->getSpendMoneyEachRound = &getSpendMoneyEachRound;
    kisi->getLuckyNumber = &getLuckyNumber;

    return kisi;
}

char* getName(const Kisi kisi){
    return kisi->name;
}

char* toString(const Kisi kisi){
    return kisi->getName(kisi);
}

float getTotalMoney(const Kisi kisi){
    return kisi->totalMoney;
}

float getSpendMoneyEachRound(const Kisi kisi){
    return kisi->spendMoneyEachRound;
}

int getLuckyNumber(const Kisi kisi){
    return kisi->luckyNumber;
}