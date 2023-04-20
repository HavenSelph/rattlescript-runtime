#include <stdio.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"
#include "Types/vector.h"


int main() {
    Vector *vec = vector_new(ValueType_Integer);
    vector_push(vec, value_new_int(1));
    vector_push(vec, value_new_int(2));
    vector_push(vec, value_new_int(3));

    vector_print(vec);

    vector_free(vec);
}
