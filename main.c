#include "common.h"
#include "Context/scope.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"
#include "Types/vector.h"

int main() {
    Value *val = value_new_int(5);
    value_print(val); endln;

    Value *list = value_new_list(list_new_v(4, value_new_int(1), value_new_int(2), value_new_int(3), ref(val)));
    value_print(list); endln;
    unref(list);
    value_print(val); endln;
    unref(val);
}
