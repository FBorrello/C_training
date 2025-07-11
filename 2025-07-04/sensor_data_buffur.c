#include <stdio.h>
#include <stdlib.h>

/*
Implement a circular buffer for IoT sensor data using pointer arithmetic.
The buffer stores up to 4 float values, overwriting the oldest when full.
*/

typedef struct CircularBuffer {
    float* data;
    int capacity;
    float* head;
    float* tail;
    int size;
} CircularBuffer;

CircularBuffer* create_buffer(int capacity) {
    CircularBuffer* cb = (CircularBuffer*)malloc(sizeof(CircularBuffer));
    cb->data = (float*)malloc(capacity * sizeof(float));
    cb->capacity = capacity;
    cb->head = cb->data;
    cb->tail = cb->data;
    cb->size = 0;
    return cb;
}

void push(CircularBuffer* cb, float value) {
    // Write the new value at head
    *cb->head = value;

    // Update size and tail based on whether the buffer is full
    if (cb->size < cb->capacity) {
        cb->size++;  // Not full, increase size
    } else {
        // Full, move tail to overwrite oldest data
        cb->tail++;
        if (cb->tail == cb->data + cb->capacity) {
            cb->tail = cb->data;  // Wrap tail around
        }
    }

    // Move head to the next position
    cb->head++;
    if (cb->head == cb->data + cb->capacity) {
        cb->head = cb->data;  // Wrap head around
    }
}

float pop(CircularBuffer* cb) {
    if (cb->size == 0) {
        return NAN;  // Buffer empty, return NAN
    }
    float value = *cb->tail;  // Read the value at tail
    cb->tail++;               // Move tail forward
    if (cb->tail == cb->data + cb->capacity) {
        cb->tail = cb->data;  // Wrap tail back to start if at end
    }
    cb->size--;               // Decrease size
    return value;
}

int main() {
    CircularBuffer* cb = create_buffer(4);
    push(cb, 1.0);
    push(cb, 2.0);
    push(cb, 3.0);
    push(cb, 4.0);
    printf("%.1f\n", pop(cb)); // Should print 1.0
    push(cb, 5.0);
    printf("%.1f\n", pop(cb)); // Should print 2.0
    free(cb->data);
    free(cb);
    return 0;
}