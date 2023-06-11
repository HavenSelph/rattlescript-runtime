//
// Created by haven on 4/7/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "common.h"
#include "Types/value.h"
#include "Types/string.h"
#include "Types/dynamic_list.h"
#include "Types/vector.h"
#include "Types/linked_list.h"
#include "Types/hash_map.h"
#include "Types/queue.h"


char *value_type_to_string(ValueType type) {
    switch (type) {
        case ValueType_Integer:
            return "Integer";
        case ValueType_Float:
            return "Float";
        case ValueType_Bool:
            return "Bool";
        case ValueType_String:
            return "String";
        case ValueType_List:
            return "List";
        case ValueType_Vector:
            return "Vector";
        case ValueType_LinkedList:
            return "LinkedList";
        case ValueType_Queue:
            return "Queue";
        case ValueType_HashMap:
            return "HashMap";
    }
}

static int refs;
static int unrefs;

static Value *new_val(ValueType type) {
    Value *val = allocate(1, sizeof(Value));
    val->type = type;
    val->ref_count = 1;
    refs++;
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

Value *value_new_string(int length, char *text) {
    Value *val = new_val(ValueType_String);
    val->as_string = string_new(length, text);
    return val;
}

Value *value_new_string_from(String *text) {
    Value *val = new_val(ValueType_String);
    val->as_string = text;
    return val;
}

Value *value_new_list(List *list) {
    Value *val = new_val(ValueType_List);
    val->as_list = list;
    return val;
}

Value *value_new_vector(Vector *vector) {
    Value *val = new_val(ValueType_Vector);
    val->as_vector = vector;
    return val;
}

Value *value_new_linked_list(LinkedList *ll) {
    Value *val = new_val(ValueType_LinkedList);
    val->as_linked_list = ll;
    return val;
}

Value *value_new_queue(Queue *queue) {
    Value *val = new_val(ValueType_Queue);
    val->as_queue = queue;
    return val;
}


Value *value_new_hash_map(HashMap *map) {
    Value *val = new_val(ValueType_HashMap);
    val->as_hash_map = map;
    return val;
}
/* ====================================================================================================
 * Return Value types
 * ==================================================================================================*/

#define unref2(left, right) do { \
    value_unref(left); \
    value_unref(right); \
} while (0)


// :Operations

Value *value_add(Value *left, Value *right) {
    Value *out = NULL;
    if (left->type == ValueType_Integer && right->type == ValueType_Integer) {
        out = value_new_int(left->as_int + right->as_int);

    } else if (left->type == ValueType_Float && right->type == ValueType_Integer) {
        out = value_new_float(left->as_float + right->as_int);

    } else if (left->type == ValueType_Integer && right->type == ValueType_Float) {
        out = value_new_float(left->as_int + right->as_float);

    } else if (left->type == ValueType_Float && right->type == ValueType_Float) {
        out = value_new_float(left->as_float + right->as_float);

    } else if (left->type == ValueType_String && right->type == ValueType_String) {
        String *str = string_new_empty(left->as_string->length + right->as_string->length);
        memcpy(str->text, left->as_string->text, left->as_string->length);
        memcpy(str->text + left->as_string->length, right->as_string->text, right->as_string->length);
        out = value_new_string_from(str);

    } else if (left->type == ValueType_LinkedList && right->type == ValueType_LinkedList) {
        LinkedList *ll = ll_new();
        LLNode *left_node = left->as_linked_list->start;
        LLNode *right_node = right->as_linked_list->start;
        while (left_node != NULL) {
            ll_push(ll, left_node->val);
            left_node = left_node->next;
        }
        while (right_node != NULL) {
            ll_push(ll, right_node->val);
            right_node = right_node->next;
        }
        out = value_new_linked_list(ll);
    } else {
        printf("\nCannot add types %s and %s", value_type_to_string(left->type), value_type_to_string(right->type));
        exit(1);
    }

    unref2(left, right);
    return out;
}

Value *value_subtract(Value *left, Value *right) {
    Value *out = NULL;
    if (left->type == ValueType_Integer && right->type == ValueType_Integer) {
        out = value_new_int(left->as_int - right->as_int);

    } else if (left->type == ValueType_Float && right->type == ValueType_Integer) {
        out = value_new_float(left->as_float - right->as_int);

    } else if (left->type == ValueType_Integer && right->type == ValueType_Float) {
        out = value_new_float(left->as_int - right->as_float);

    } else if (left->type == ValueType_Float && right->type == ValueType_Float) {
        out = value_new_float(left->as_float - right->as_float);

    } else {
        printf("\nCannot subtract types %s and %s", value_type_to_string(left->type), value_type_to_string(right->type));
        exit(1);
    }

    unref2(left, right);
    return out;
}

Value *value_power(Value *left, Value *right) {
    Value *out = NULL;

    if (left->type == ValueType_Integer && right->type == ValueType_Integer) {
        out = value_new_int(value_pow_int_c(left->as_int, right->as_int));

    } else if (left->type == ValueType_Float && right->type == ValueType_Integer) {
        out = value_new_float(powf(left->as_float, (float) right->as_int));

    } else if (left->type == ValueType_Integer && right->type == ValueType_Float) {
        out = value_new_float(powf((float) left->as_int, right->as_float));

    } else if (left->type == ValueType_Float && right->type == ValueType_Float) {
        out = value_new_float(powf(left->as_float, right->as_float));

    } else {
        printf("\nPower not possible on types %s and %s", value_type_to_string(left->type), value_type_to_string(right->type));
        exit(1);
    }

    unref2(left, right);
    return out;
}

Value *value_multiply(Value *left, Value *right) {
    Value *out = NULL;
    if (left->type == ValueType_Integer && right->type == ValueType_Integer) {
        out = value_new_int(left->as_int * right->as_int);

    } else if (left->type == ValueType_Float && right->type == ValueType_Integer) {
        out = value_new_float(left->as_float * right->as_int);

    } else if (left->type == ValueType_Integer && right->type == ValueType_Float) {
        out = value_new_float(left->as_int * right->as_float);

    } else if (left->type == ValueType_Float && right->type == ValueType_Float) {
        out = value_new_float(left->as_float * right->as_float);

    } else if (left->type == ValueType_String && right->type == ValueType_Integer) {
        String *str = string_new(left->as_string->length * right->as_int, left->as_string->text);
        for (int i = 1; i < right->as_int; i++) {
            memcpy(str->text + left->as_string->length * i, left->as_string->text, left->as_string->length);
        }
        out = value_new_string(str->length, str->text);

    } else {
        printf("\nCannot multiply types %s and %s", value_type_to_string(left->type), value_type_to_string(right->type));
        exit(1);
    }

    unref2(left, right);
    return out;
}


Value *value_divide(Value *left, Value *right) {
    Value *out = NULL;
    if (left->type == ValueType_Integer && right->type == ValueType_Integer) {
        out = value_new_int(left->as_int / right->as_int);

    } else if (left->type == ValueType_Float && right->type == ValueType_Integer) {
        out = value_new_float(left->as_float / right->as_int);

    } else if (left->type == ValueType_Integer && right->type == ValueType_Float) {
        out = value_new_float(left->as_int / right->as_float);

    } else if (left->type == ValueType_Float && right->type == ValueType_Float) {
        out = value_new_float(left->as_float / right->as_float);

    } else {
        printf("\nCannot divide types %s and %s", value_type_to_string(left->type), value_type_to_string(right->type));
        exit(1);
    }

    unref2(left, right);
    return out;
}

// :Logic

Value *value_hash(Value *val) {
    Value *out = value_new_int(value_hash_c(val));
    value_unref(val);
    return out;
}

Value *value_equals(Value *left, Value *right) {
    Value *out = value_new_bool(value_equals_c(left, right));
    unref2(left, right);
    return out;
}

Value *value_as_bool(Value *val) {
    Value *out = value_new_bool(value_as_bool_c(val));
    value_unref(val);
    return out;
}

Value *value_or(Value *left, Value *right) {
    Value *out = value_new_bool(value_as_bool_c(left) || value_as_bool_c(right));
    unref2(left, right);
    return out;
}

Value *value_and(Value *left, Value *right) {
    Value *out = value_new_bool(value_as_bool_c(left) && value_as_bool_c(right));
    unref2(left, right);
    return out;
}

Value *value_not(Value *val) {
    Value *out = value_new_bool(!value_as_bool_c(val));
    value_unref(val);
    return out;
}


/* ====================================================================================================
 * Return C types
 * ==================================================================================================*/
bool value_equals_c(Value *left, Value *right) {
    if (left->type != right->type) return false;
    switch (left->type) {
        case ValueType_Integer:
            return left->as_int == right->as_int;
        case ValueType_Float:
            return left->as_float == right->as_float;
        case ValueType_Bool:
            return left->as_bool == right->as_bool;
        case ValueType_String:
            return string_compare(left->as_string, right->as_string);
        case ValueType_List:
            if (left->as_list->size != right->as_list->size) return false;
            for (int i = 0; i < left->as_list->size; ++i) {
                if (!value_equals_c(left->as_list->val[i], right->as_list->val[i])) return false;
            }
            return true;
        case ValueType_Vector:
            if (left->as_vector->size != right->as_vector->size) return false;
            for (int i = 0; i < left->as_vector->size; ++i) {
                if (!value_equals_c(left->as_vector->values[i], right->as_vector->values[i])) return false;
            }
            return true;
        case ValueType_LinkedList: {
            if (left->as_linked_list->size != right->as_linked_list->size) return false;
            LLNode *left_node = left->as_linked_list->start;
            LLNode *right_node = right->as_linked_list->start;
            while (left_node != NULL) {
                if (!value_equals_c(left_node->val, right_node->val)) return false;
                left_node = left_node->next;
                right_node = right_node->next;
            }
            return true;
        }
        case ValueType_Queue:
            if (left->as_queue->size != right->as_queue->size) return false;
            QueueNode *left_node = left->as_queue->head;
            QueueNode *right_node = right->as_queue->head;
            while (left_node != NULL) {
                if (!value_equals_c(left_node->value, right_node->value)) return false;
                left_node = left_node->next;
                right_node = right_node->next;
            }
            return true;
        case ValueType_HashMap:
            printf("Cannot compare hash maps");
            exit(1);
    }
}

int value_hash_c(Value *val) {
    switch (val->type) {
        case ValueType_Integer:
            return val->as_int * 31;
        case ValueType_Float:
            return (int) val->as_float * 67;
        case ValueType_Bool:
            return val->as_bool * 13;
        case ValueType_String: {
            int hash = 0;
            for (int i = 0; i < val->as_string->length; ++i) {
                hash = hash << 3;
                hash ^= val->as_string->text[i];
            }
            return hash;
        }
        case ValueType_List:
        case ValueType_Vector:
        case ValueType_LinkedList:
        case ValueType_Queue:
        case ValueType_HashMap:
            printf("Cannot hash a complex mutable object: %s", value_type_to_string(val->type));
            exit(1);

    }
}

bool value_as_bool_c(Value *val) {
    switch (val->type) {
        case ValueType_Integer:
            return val->as_int != 0;
        case ValueType_Float:
            return val->as_float != 0;
        case ValueType_Bool:
            return val->as_bool;
        case ValueType_String:
            return val->as_string->length != 0;
        case ValueType_List:
            return val->as_list->size != 0;
        case ValueType_Vector:
            return val->as_vector->size != 0;
        case ValueType_LinkedList:
            return val->as_linked_list->size != 0;
        case ValueType_Queue:
            return val->as_queue->size != 0;
        case ValueType_HashMap:
            return val->as_hash_map->size != 0;
    }
}

bool value_or_c(Value *left, Value *right) {
    bool out = value_as_bool_c(left) || value_as_bool_c(right);
    return out;
}

bool value_and_c(Value *left, Value *right) {
    bool out = value_as_bool_c(left) && value_as_bool_c(right);
    return out;
}

bool value_not_c(Value *val) {
    bool out = !value_as_bool_c(val);
    return out;
}

int value_pow_int_c(int left, int right) {
    int result = 1;
    while (1) {
        if (right & 1) result *= left;
        right >>= 1;
        if (!right) break;
        left *= left;
    }
    return result;
}


void value_free(Value *val) {
    switch (val->type) {
        case ValueType_String: {
            string_free(val->as_string);
            break;
        }
        case ValueType_List: {
            list_free(val->as_list);
            break;
        }
        case ValueType_Vector: {
            vector_free(val->as_vector);
            break;
        }
        case ValueType_LinkedList: {
            ll_free(val->as_linked_list);
            break;
        }
        case ValueType_Queue: {
            queue_free(val->as_queue);
            break;
        }
        case ValueType_HashMap: {
            hm_free(val->as_hash_map);
            break;
        }
        default:
            break;
    }
    deallocate(val);
}

Value *value_ref(Value *val) {
    refs++;
    val->ref_count++;
    return val;
}

void value_unref(Value *val) {
    unrefs++;
    if (--val->ref_count > 0) return;
    value_free(val);
}

void value_print(Value *val) {
    switch (val->type) {
        case ValueType_Integer:
            printf("%d", val->as_int);
            break;
        case ValueType_Float:
            printf("%f", val->as_float);
            break;
        case ValueType_Bool:
            printf("%s", val->as_bool ? "true" : "false");
            break;
        case ValueType_String:
            string_print(val->as_string);
            break;
        case ValueType_List:
            list_print(val->as_list);
            break;
        case ValueType_Vector:
            vector_print(val->as_vector);
            break;
        case ValueType_LinkedList:
            ll_print(val->as_linked_list);
            break;
        case ValueType_Queue:
            queue_print(val->as_queue);
            break;
        case ValueType_HashMap:
            hm_print(val->as_hash_map);
            break;
    }
}

__attribute__((destructor))
static void print_refs_unrefs() {
    printf("\nValue Refs: %d, Unrefs: %d\n", refs, unrefs);
}
