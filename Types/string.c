//
// Created by haven on 4/17/2023.
//
#include <memory.h>
#include <stdio.h>

#include "common.h"
#include "Types/string.h"

String *string_new(int length, char *text) {
    String *str = allocate(1, sizeof(String));
    str->text = allocate(length, sizeof(char));
    str->length = length;
    for (int i = 0; i < length; ++i) {
        str->text[i] = text[i];
    }
    return str;
}

int string_compare(String *str1, String *str2) {
    if (str1->length != str2->length) return 0;
    return memcmp(str1->text, str2->text, str1->length)==0;
}

void string_print(String *str) {
    printf("'");
    for (int i = 0; i < str->length; ++i) {
        printf("%c", str->text[i]);
    }
    printf("'");
}

void string_free(String *str) {
    if (!str) return;
    deallocate(str->text);
    deallocate(str);
}
