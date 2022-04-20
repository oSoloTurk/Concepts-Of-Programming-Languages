//
// Created by hakki on 4/15/2022.
//
#include <malloc.h>
#include "../include/Dosya.h"

Dosya new_Dosya(char *path) {
    Dosya dosya = (Dosya) malloc(sizeof(Dosya));
    dosya->path = path;
    if ((dosya->file = fopen(dosya->path, "r")) == NULL) {
        printf("We do not acces to %s for write operation\n", dosya->path);
        return NULL;
    }

    dosya->next = &next;
    dosya->getFile = &getFile;

    return dosya;
}

char *next(const Dosya dosya, char* format) {
    char* readedInput = (char*) calloc(ESTIMATED_LINE_LENGTH, sizeof(char));
    char* readLine;
    fscanf(dosya->getFile(dosya), format, readLine);
    return readedInput;
}

FILE *getFile(const Dosya dosya) {
    return dosya->file;
}