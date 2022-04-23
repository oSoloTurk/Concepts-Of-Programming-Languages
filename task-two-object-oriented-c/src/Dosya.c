//
// Created by hakki on 4/15/2022.
//
#include <malloc.h>
#include "../include/Dosya.h"
#include <errno.h>
#include <string.h>

Dosya new_Dosya(char *path) {
    Dosya dosya = (Dosya) malloc(sizeof(Dosya));
    dosya->path = path;
    errno = 0;
    dosya->file = fopen(dosya->path, "r+");
    if (dosya->file == NULL) {
        printf("We do not acces to %s for read operation, errno: %d\n", dosya->path, errno);
        return NULL;
    }

    dosya->next = &next;
    dosya->getFile = &getFile;

    return dosya;
}

char *next(const Dosya dosya, char* format) {
    char* readedInput = (char*) malloc(sizeof(char)*ESTIMATED_LINE_LENGTH);
    fscanf(dosya->getFile(dosya), format, readedInput);
    printf(":%s\n", readedInput);    
    return realloc(readedInput, sizeof(char) * strlen(readedInput));
}

FILE *getFile(const Dosya dosya) {
    return dosya->file;
}

char *getPath(const Dosya dosya) {
    return dosya->path;
}