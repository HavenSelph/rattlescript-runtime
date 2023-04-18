//
// Created by haven on 4/17/2023.
//

#ifndef DYNAMICLISTS_STRING_H
#define DYNAMICLISTS_STRING_H

#include "value.h"

typedef struct String {
    char *val;
    int size;
} String;

String *str_new(char *val);

#endif //DYNAMICLISTS_STRING_H
