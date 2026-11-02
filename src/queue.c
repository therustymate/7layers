#include "queue.h"

int queue_init(PathQueue* q, size_t initial_capacity) {
    q->items = calloc(initial_capacity, sizeof(*q->items));
    if (!q->items) return -1;
    q->count = 0;
    q->capacity = initial_capacity;
    return 0;
}

void queue_free(PathQueue* q) {
    free(q->items);
    q->items = NULL;
    q->count = q->capacity = 0;
}

int queue_push(PathQueue* q, const char* path) {
    size_t len = c_strlen(path);
    if (len >= MAX_PATH) return -1;

    if (q->count >= q->capacity) {
        size_t new_cap = q->capacity ? q->capacity * 2 : 64;
        char (*p)[MAX_PATH] = realloc(q->items, new_cap * sizeof(*p));
        if (!p) return -1;
        q->items    = p;
        q->capacity = new_cap;
    }

    c_memcpy(q->items[q->count], path, len + 1);
    q->count++;
    return 0;
}