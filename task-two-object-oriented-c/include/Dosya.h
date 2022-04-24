//
// Created by hakki on 4/15/2022.
//

#ifndef PDP_TASK_TWO_DOSYA_H
#define PDP_TASK_TWO_DOSYA_H
#define ESTIMATED_LINE_LENGTH 100

#include <stdio.h>
#include <stdlib.h>

struct Dosya {
    char* path;
    FILE* file;

    FILE* (*getFile)(struct Dosya*);
    char* (*getPath)(struct Dosya*);
};

typedef struct Dosya *Dosya;

Dosya new_Dosya(char* path);

FILE* getFile(const Dosya dosya);
char* getPath(const Dosya dosya);

#endif //PDP_TASK_TWO_DOSYA_H
