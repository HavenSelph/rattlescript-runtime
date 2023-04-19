#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"


int main() {
    Value *lhs = value_new_string(1, "x");
    value_print(lhs);
    Value *rhs = value_new_string(1, "y");
    value_print(rhs);
    Value *val = value_add(lhs, rhs);

    value_print(val); endln;
    value_free(val);
}
