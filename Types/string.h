//
// Created by haven on 4/17/2023.
//

#ifndef DYNAMICLISTS_STRING_H
#define DYNAMICLISTS_STRING_H

typedef struct String {
    char *text;
    int length;
} String;

String *string_new(int length, char *text);

int string_compare(String *str1, String *str2);
void string_print(String *str);

void string_free(String *str);

#endif //DYNAMICLISTS_STRING_H
