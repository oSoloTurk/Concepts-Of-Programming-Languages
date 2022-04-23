#include "../include/Dosya.h"

#include "../include/Kisi.h"

#include "../include/Oyun.h"

#include "../include/Arayuz.h"

#include <errno.h>

//
// Created by hakki on 4/15/2022.
//
int main(int argc, char ** argv) {
  Kisi * kisiler = (Kisi * ) calloc(1, sizeof(Kisi));
  Dosya kisilerDosya = new_Dosya("Kisiler.txt");

  char buffer[100];
  for (int line = 1; fgets(buffer, sizeof buffer, kisilerDosya -> getFile(kisilerDosya));) {
    char * name = malloc(sizeof(char) * 25);
    char * total = malloc(sizeof(char) * 25);
    char * spendMoneyEachRound = malloc(sizeof(char) * 25);
    char * luckyNumber = malloc(sizeof(char) * 25);
    printf(":%s", buffer);
    sscanf(buffer, "%[^#]s", name);
    sscanf(buffer, "%[^#]s", total);
    sscanf(buffer, "%[^#]s", spendMoneyEachRound);
    sscanf(buffer, "%[^#]s", luckyNumber);
    kisiler[line] = new_Kisi(name, atof(total), atof(spendMoneyEachRound), atoll(luckyNumber));
    line++;
    kisiler = realloc(kisiler, sizeof(Kisi) * line);
  }
  Oyun oyun = new_Oyun();
  for (int index = 0; index < (sizeof(kisiler) / sizeof(Kisi)); index++) {
    oyun -> joinGame(oyun, kisiler[index]);
  }
  Arayuz arayuz = new_Arayuz();
  oyun -> playGame(oyun, arayuz);

  return 0;
}