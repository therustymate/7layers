#pragma once

#include "7layers.h"

typedef struct {
    char (*items)[MAX_PATH];
    size_t count;
    size_t capacity;
} PathQueue;

int queue_init(PathQueue* q, size_t initial_capacity);
void queue_free(PathQueue* q);
int queue_push(PathQueue* q, const char* path);

// I SUPPOSE TO USE C++