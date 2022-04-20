#include "../include/Dosya.h"
#include "../include/Kisi.h"

//
// Created by hakki on 4/15/2022.
//
int main(int argc,char **argv) {
    Kisi *kisiler = (Kisi*) calloc(1, sizeof(Kisi));
    Dosya kisilerDosya = new_Dosya("Kisiler.txt");
    int line = 0;

    while (1) { 
        char *readLine = kisilerDosya->next(kisilerDosya, "%[^\n]s\n");
        if (readLine == NULL) {
            break;
        }
        char *name = malloc(sizeof(char) * 100);
        char *total = malloc(sizeof(char) * 100);
        char *spendMoneyEachRound = malloc(sizeof(char) * 100);
        char *luckyNumber = malloc(sizeof(char) * 100);
        sscanf(readLine, "%[^#]s", name);
        readLine += strlen(name) + 1;
        sscanf(readLine, "%[^#]s", total);
        readLine += strlen(total) + 1;
        sscanf(readLine, "%[^#]s", spendMoneyEachRound);
        readLine += strlen(spendMoneyEachRound) + 1;
        sscanf(readLine, "%[^#]s", luckyNumber);
        kisiler[line] = new_Kisi(name, atof(total), atof(spendMoneyEachRound), atoll(luckyNumber));
        line++;
        kisiler = realloc(kisiler, sizeof(Kisi) * line);
    }
    printf("Size: %d", sizeof(kisiler));
    for (int index = 0; index < sizeof(kisiler) / sizeof(Kisi); index++) {
        printf("Person: %s\n", kisiler[index]->toString);
    }
    return 0;
}