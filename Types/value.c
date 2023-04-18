//
// Created by haven on 4/7/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "value.h"
#include "linked_list.h"
#include "dynamic_list.h"
#include "hash_map.h"

// todo: fix string escape characters

static int allocated = 0;
static int freed = 0;


static Value *new_val(ValueType type) {
    allocated++;
    Value *val = calloc(1, sizeof(Value));
    val->type = type;
    val->ref_count = 1;
    return val;
}


Value *value_new_int(int num) {
    Value *val = new_val(ValueType_Integer);
    val->as_int = num;
    return val;
}

Value *value_new_float(float num) {
    Value *val = new_val(ValueType_Float);
    val->as_float = num;
    return val;
}

Value *value_new_bool(bool boo) {
    Value *val = new_val(ValueType_Bool);
    val->as_bool = boo;
    return val;
}

Value *value_new_string(char *text) {
    /*
     * Allocation and copying is handled by caller
     */
    Value *val = new_val(ValueType_String);
    val->as_text = calloc(strlen(text), sizeof(char));
    strcpy(val->as_text, text);
    return val;
}

Value *value_new_list(List *list) {
    Value *val = new_val(ValueType_List);
    val->as_list = list;
    return val;
}

Value *value_new_linked_list(LinkedList *ll) {
    Value *val = new_val(ValueType_LinkedList);
    val->as_linked_list = ll;
    return val;
}

Value *value_new_hash_map(HashMap *map) {
    Value *val = new_val(ValueType_HashMap);
    val->as_hash_map = map;
    return val;
}

bool value_equals(Value *left, Value *right) {
    if (left->type != right->type) return false;
    switch (left->type) {
        case ValueType_Integer:
            return left->as_int == right->as_int;
        case ValueType_Float:
            return left->as_float == right->as_float;
        case ValueType_Bool:
            return left->as_bool == right->as_bool;
        case ValueType_String:
            return strcmp(left->as_text, right->as_text) == 0;
        case ValueType_List:
            if (left->as_list->size != right->as_list->size) return false;
            for (int i = 0; i < left->as_list->size; ++i) {
                if (!value_equals(left->as_list->val[i], right->as_list->val[i])) return false;
            }
            return true;
        case ValueType_LinkedList: {
            if (left->as_linked_list->size != right->as_linked_list->size) return false;
            LLNode *left_node = left->as_linked_list->start;
            LLNode *right_node = right->as_linked_list->start;
            while (left_node != NULL) {
                if (!value_equals(left_node->val, right_node->val)) return false;
                left_node = left_node->next;
                right_node = right_node->next;
            }
            if (right_node != NULL) return false;
            return true;
        }
        case ValueType_HashMap:
            return false;
    }
}

int value_hash(Value *val) {
    switch (val->type) {
        case ValueType_Integer:
            return val->as_int * 31;
        case ValueType_Float:
            return (int) val->as_float * 67;
        case ValueType_Bool:
            return val->as_bool * 13;
        case ValueType_String: {
            int hash = 0;
            for (int i = 0; i < strlen(val->as_text); ++i) {
                hash = hash << 3;
                hash ^= val->as_text[i];
            }
            return hash;
        }
        case ValueType_List:
        case ValueType_LinkedList:
        case ValueType_HashMap:
            printf("Cannot hash a mutable object.");
            exit(1);

    }
}

void value_free(Value *val) {
    if (--val->ref_count > 0) return;
    switch (val->type) {
        case ValueType_String: {
            free(val->as_text);
            break;
        }
        case ValueType_List: {
            list_free(val->as_list);
            break;
        }
        case ValueType_LinkedList: {
            ll_free(val->as_linked_list);
            break;
        }
        case ValueType_HashMap: {
            hm_free(val->as_hash_map);
            break;
        }
        default: break;
    }
    free(val);
    freed++;
}

Value *value_ref(Value *val) {
    val->ref_count++;
    return val;
}

void value_print(Value *val) {
    switch (val->type) {
        case ValueType_Integer: printf("%d", val->as_int); break;
        case ValueType_Float: printf("%f", val->as_float); break;
        case ValueType_Bool: printf("%s", val->as_float ? "true" : "false"); break;
        case ValueType_String: printf("'%s'", val->as_text); break;
        case ValueType_List: list_print(val->as_list); break;
        case ValueType_LinkedList: ll_print(val->as_linked_list); break;
        case ValueType_HashMap: hm_print(val->as_hash_map); break;
    }
}

__attribute__((destructor))
void print_free() {
    printf("\nAllocated: %d, Freed: %d", allocated, freed);
}
