#include "dynamic_array.h"
#include <stdlib.h>

int init_array(DynamicArray *arr, size_t initial_capacity) {
    arr->data = (int *)malloc(initial_capacity * sizeof(int));
    if (arr->data == NULL) {
        arr->capacity = 0;
        arr->size = 0;
        return -1; // Failure
    }
    arr->capacity = initial_capacity;
    arr->size = 0;
    return 0; // Success
}

void free_array(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
    arr->capacity = 0;
    arr->size = 0;
}

int append(DynamicArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        return -1; // Failure: array full
    }
    arr->data[arr->size] = value;
    arr->size++;
    return 0; // Success
}