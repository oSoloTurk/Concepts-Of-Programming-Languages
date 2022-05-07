//
// Created by hakki on 4/15/2022.
//
#include <malloc.h>
#include "../include/Dosya.h"
#include <errno.h>
#include <string.h>

Dosya new_Dosya(char *path) {
    Dosya dosya = (Dosya) malloc(sizeof(struct Dosya));
    dosya->path = path;
    errno = 0;
    dosya->file = fopen(dosya->path, "r+");
    if (dosya->file == NULL) {
        printf("We do not acces to %s for read operation, errno: %d\n", dosya->path, errno);
        return NULL;
    }

    dosya->getFile = &getFile;
    dosya->reload = &reload;
    dosya->getPath = &getPath;

    return dosya;
}

void* delete_Dosya(Dosya dosya){
    fclose(dosya->getFile(dosya));
    free(dosya);
    dosya = NULL;
}

FILE *getFile(const Dosya dosya) {
    return dosya->file;
}

void* reload(const Dosya dosya) {
    fclose(dosya->getFile(dosya));
    dosya->file = fopen(dosya->path, "r+");
    if (dosya->file == NULL) {
        printf("We do not acces to %s for read operation, errno: %d\n", dosya->path, errno);
        return NULL;
    }
}

char *getPath(const Dosya dosya) {
    return dosya->path;
}