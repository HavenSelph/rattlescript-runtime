#include "common.h"
#include "Context/scope.h"
#include "Types/dynamic_list.h"
#include "Types/hash_map.h"
#include "Types/linked_list.h"
#include "Types/string.h"
#include "Types/queue.h"
#include "Types/vector.h"

int main() {
    Value *hm = value_new_hash_map(hm_new());
    Value *str = value_new_string(5, "Hello");
    Value *str2 = value_new_string(5, "World");
    for (int i = 0; i < 10000000; ++i) {
        hm_push(hm->as_hash_map, value_new_int(i), (i%2==0) ? ref(str) : ref(str2));
    }
    printf("Done\n"); endln;
    getchar();
    value_unref(str);
    value_unref(str2);
    value_unref(hm);
    printf("Freed\n"); endln;
    getchar();
}
