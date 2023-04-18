#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"


int main() {
    // Value *val = value_new_list(list_new(10));
    // Value *val2 = value_new_list(list_new(10));
    // for (int i = 0; i < 10; i++) {
    //     list_push(val->as_list, value_new_int(i));
    //     list_push(val2->as_list, value_new_int(i));
    // }
    // list_push(val->as_list, value_ref(val2));
    // value_free(val2);
    // value_print(val);
    // value_free(val);

    Value *val = value_new_int(10);
    Value *val2 = value_new_int(10);
    Value *val3 = value_equals(ref(val), ref(val2));
    if (value_as_bool_c(value_subtract(val,val2))) {
        printf("True");
    } else {
        printf("False");
    }
    value_print(val3);
    value_free(val3);
}
