//
// Created by haven on 4/17/2023.
//
#include "string.h"
#include <stdlib.h>
#include "string.h"

String *str_new(char *val) {
    String *str = calloc(1, sizeof(String));
    str->val = calloc(strlen(val), sizeof(char));
    strcpy(str->val, val);
    str->size = strlen(val);
    return str;
}

String *str_add(String *str1, String *str2) {
    String *str = calloc(1, sizeof(String));
    str->val = calloc(str1->size + str2->size, sizeof(char));
    for (int i = 0; i < str1->size; ++i) {
        str->val[i] = str1->val[i];
    }
    str->size = str1->size + str2->size;

    return str;
}
