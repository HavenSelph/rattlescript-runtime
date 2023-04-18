#include <stdio.h>
#include <stdlib.h>

#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"


int main() {
    Value *val = value_new_list(list_new(10));
    Value *val2 = value_new_list(list_new(10));
    for (int i = 0; i < 10; i++) {
        list_push(val->as_list, value_new_int(i));
        list_push(val2->as_list, value_new_int(i));
    }
    list_push(val->as_list, value_ref(val2));
    value_free(val2);
    value_print(val);
    value_free(val);
}
