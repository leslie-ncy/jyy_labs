#include <stdlib.h>
#include <assert.h>

struct co* cos[5];
static int len = 0;
static int cur_idx = -1;

static void co_node_insert(struct co *coroutine) {
    cos[len] = coroutine;
    cur_idx = len;
    ++len;
}

static struct co* co_node_remove() {
    struct co* res = cos[cur_idx];
    for (int i = cur_idx + 1; i < len; ++i) {
        cos[i - 1] = cos[i];
    }
    --len;
    cos[len] = NULL;
    return res;
}