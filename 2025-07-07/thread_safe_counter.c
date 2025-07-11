#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <stdint.h>

volatile uint32_t counter = 0;
SemaphoreHandle_t counter_semaphore;

void init_semaphore(void) {
    counter_semaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(counter_semaphore); // Initialize as available
}

void sensor_isr() {
    while (1) {
        if (xSemaphoreTake(counter_semaphore, portMAX_DELAY) == pdTRUE) {
            counter++;
            xSemaphoreGive(counter_semaphore);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 ms delay
    }
}

#include <stdint.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

volatile uint8_t semaphore = 0;
SemaphoreHandle_t semaphore_handler;

void init_semaphore(void) {
    semaphore_handler = xSemaphoreCreateBinary();
    xSemaphoreGive(semaphore_handler); // Initialize as available
}

void acquire_semaphore() {
    while (1) {
        if (xSemaphoreTake(semaphore_handler, portMAX_DELAY) == pdTRUE) {
            semaphore = 1;
            xSemaphoreGive(semaphore_handler);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 ms delay
    }
}

void release_semaphore() {
    while (1) {
        if (xSemaphoreTake(semaphore_handler, portMAX_DELAY) == pdTRUE) {
            semaphore = 0;
            xSemaphoreGive(semaphore_handler);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1000 ms delay
    }
}