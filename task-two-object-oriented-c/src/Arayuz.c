//
// Created by hakki on 4/15/2022.
//
#include <malloc.h>
#include "../include/Arayuz.h"

#define INTERFACE_HEIGHT 16
#define ESTIMATED_LINE_WIDTH 100

Arayuz new_Arayuz() {
    Arayuz arayuz = (Arayuz) malloc(sizeof(struct Arayuz));    

    arayuz->cleanScreen = &cleanScreen;
    arayuz->writeStatus = &writeStatus;

    return arayuz;
}

void *writeStatus(const Arayuz arayuz, int luckyNumber, int round, float house, const Kisi topRich) {
    printf("\n\n"); //top 2 empty line
    printf("\t\t\t\t##########################################\n");
    printf("\t\t\t\t##\t\t\t\tSANSLI SAYI: %d\t\t\t##\n", luckyNumber);
    printf("\t\t\t\t##########################################\n");
    printf("\t\t\t\t##########################################\n");
    printf("\t\t\t\t##\t\t\t\tTUR: %d\t\t\t\t\t##\n", round);
    printf("\t\t\t\t##\t\tMASA BAKIYE: %.4f\t\t\t\t##\n", house);
    printf("\t\t\t\t##\t\t\t\t\t\t\t\t\t\t##\n");
    printf("\t\t\t\t##--------------------------------------##\n");
    printf("\t\t\t\t##\t\t\t\tEN ZENGIN KISI\t\t\t##\n");
    printf("\t\t\t\t##\t\t\t\t%s\t\t\t\t##\n", topRich->getName(topRich));
    printf("\t\t\t\t##\t\tBAKIYESI: %f\t\t\t##\n", *topRich->getTotalMoney(topRich));
    printf("\t\t\t\t##########################################\n");
    printf("\n\n"); //bottom 2 empty line
  return 0;
}

void *cleanScreen(const Arayuz arayuz) {
  //This is good but like a lifehack, legacy way below the here
  system("cls");

  /*
  for(int eraseCursor = 0;eraseCursor < (INTERFACE_HEIGHT * ESTIMATED_LINE_WIDTH);eraseCursor++) {
    printf("\b");
  }
  for(int yCoord = 0;yCoord < INTERFACE_HEIGHT;yCoord++) {
    for(int xCoord = 0; xCoord < ESTIMATED_LINE_WIDTH;xCoord++) {
        printf(" ");
    }
    printf("\n");
  }
  */
}