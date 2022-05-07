#include "../include/Dosya.h"
#include "../include/Kisi.h"
#include "../include/Oyun.h"
#include "../include/Arayuz.h"
#include <errno.h>

//
// Created by hakki on 4/15/2022.
//
int main(int argc, char ** argv) {
  Dosya kisilerDosya = new_Dosya("Kisiler.txt");

  char buffer[100];
  char total[20];
  char spendMoneyEachRound[20];
  char luckyNumber[20];
  char trash = '\0';
  Oyun oyun = new_Oyun();
  //William Murphy#77243.19#0.99#7
  for (int line = 0, size = 1; fgets(buffer, sizeof buffer, kisilerDosya -> getFile(kisilerDosya));line++, size++) {
    char* name = malloc(20 * sizeof(char));
    char* surname = malloc(20 * sizeof(char));
    sscanf(buffer, "%s %[^#]%c%[^#]%c%[^#]%c%s", name, surname, &trash, total, &trash, spendMoneyEachRound, &trash, luckyNumber);
    strcat(name, " ");
    strcat(name, surname);
    Kisi kisi = new_Kisi(name, atof(total), atof(spendMoneyEachRound), atol(luckyNumber));
    oyun -> joinGame(oyun, kisi);
  }
  Arayuz arayuz = new_Arayuz();
  oyun -> playGame(oyun, arayuz);
  delete_Oyun(oyun);
  delete_Dosya(kisilerDosya);
  delete_Arayuz(arayuz);
  return 0;
}