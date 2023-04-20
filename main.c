#include <stdio.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"
#include "Types/vector.h"


int main() {
    Value *val1 = value_new_int(1);
    Value *val2 = value_new_int(2);
    Value *val3 = value_new_int(3);
    Value *val4 = value_new_int(4);

    Vector *vec = vector_new_v(4, ValueType_Integer, val1, val2, val3, val4);
    vector_print(vec); endln;
    val1 = vector_pop(vec);
    vector_free(vec);
    value_print(val1); endln;
    value_free(val1);
}
