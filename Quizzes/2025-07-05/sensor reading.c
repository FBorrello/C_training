#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BUFFER_SIZE 8
#define SENSOR_MEAN 25.0    // Mean temperature in °C
#define SENSOR_STDDEV 2.0   // Standard deviation for Gaussian noise
#define MAX_INTERRUPTS 5    // Number of simulated interrupts
#define MIN_DELAY_MS 100    // Minimum delay between interrupts (ms)
#define MAX_DELAY_MS 1000   // Maximum delay between interrupts (ms)

volatile int buffer[BUFFER_SIZE];
volatile int head = 0, tail = 0;
volatile int buffer_count = 0; // Track number of items in buffer

// Gaussian random number generator (Box-Muller transform)
double gaussian_random(double mean, double stddev) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;
    double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + stddev * z;
}

int enqueue(int val) {
    if (buffer_count >= BUFFER_SIZE) {
        printf("Buffer overflow: cannot enqueue %d\n", val);
        return -1; // Indicate failure
    }
    buffer[tail] = val;
    tail = (tail + 1) % BUFFER_SIZE;
    buffer_count++;
    return 0; // Indicate success
}

int dequeue() {
    if (buffer_count <= 0) {
        printf("Buffer underflow: cannot dequeue\n");
        return -1; // Indicate failure
    }
    int val = buffer[head];
    head = (head + 1) % BUFFER_SIZE;
    buffer_count--;
    return val;
}

void interrupt_sensor_reading() {
    // Generate realistic temperature reading with Gaussian noise
    double temp = gaussian_random(SENSOR_MEAN, SENSOR_STDDEV);
    // Ensure temperature is within realistic bounds (e.g., 15°C to 35°C)
    temp = fmax(15.0, fmin(35.0, temp));
    enqueue((int)(temp * 10)); // Store as integer (scaled by 10 for precision)
}

void simulate_delay(int min_ms, int max_ms) {
    int delay = min_ms + rand() % (max_ms - min_ms + 1);
    // Simulate delay by busy-waiting (for simplicity; real systems use timers)
    time_t start = time(NULL);
    while (time(NULL) - start < delay / 1000);
}

int main() {
    srand(time(NULL));
    
    // Simulate initial sensor readings
    enqueue((int)(22.5 * 10)); // 22.5°C
    enqueue((int)(23.8 * 10)); // 23.8°C
    
    // Simulate multiple interrupts with random delays
    for (int i = 0; i < MAX_INTERRUPTS; i++) {
        simulate_delay(MIN_DELAY_MS, MAX_DELAY_MS);
        interrupt_sensor_reading();
    }
    
    // Dequeue and print all available readings
    while (buffer_count > 0) {
        int val = dequeue();
        if (val != -1) {
            printf("Reading: %.1f°C\n", val / 10.0);
        }
    }
    
    return 0;
}