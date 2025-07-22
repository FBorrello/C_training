#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

int init_array(DynamicArray *arr, size_t initial_capacity);
void free_array(DynamicArray *arr);
int append(DynamicArray *arr, int value);

#endif