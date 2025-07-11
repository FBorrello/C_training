#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_system.h"

#define STAND_BY_LED_PIN 4
#define RX_LED_PIN 33

typedef struct {
    int rx_bits;
    int delay;
} sim_data_t;

TaskHandle_t stand_by_task_handler = NULL;
SemaphoreHandle_t rx_semaphore = NULL;

void stand_by_task(void *pvParameters) {
    while (1) {
        printf("stand-by\n");
        gpio_set_level(STAND_BY_LED_PIN, 1); // Active-high
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(STAND_BY_LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void rx_task(void *pvParameters) {
    sim_data_t *data = (sim_data_t *)pvParameters;
    int rx_bits = data->rx_bits;
    int delay = data->delay * 1000;

    if (xSemaphoreTake(rx_semaphore, portMAX_DELAY) == pdTRUE) {
        if (stand_by_task_handler != NULL) {
            vTaskSuspend(stand_by_task_handler);
            gpio_set_level(STAND_BY_LED_PIN, 0);
        } else {
            printf("Error: stand_by_task_handler is NULL\n");
            xSemaphoreGive(rx_semaphore);
            vTaskDelete(NULL);
            return;
        }

        printf("Receiving %d bits delay: %d ms\n", rx_bits, delay);

        for (int i = 0; i < rx_bits; i++) {
            gpio_set_level(RX_LED_PIN, 0); // Active-high
            vTaskDelay(100 / portTICK_PERIOD_MS);
            gpio_set_level(RX_LED_PIN, 1);
            vTaskDelay(100 / portTICK_PERIOD_MS);
        }

        if (stand_by_task_handler != NULL) {
            vTaskResume(stand_by_task_handler);
        }

        gpio_set_level(RX_LED_PIN, 0);
        vTaskDelay(delay / portTICK_PERIOD_MS);

        xSemaphoreGive(rx_semaphore);
    }

    vTaskDelete(NULL);
}

void simulation_task(void *pvParameters) {
    sim_data_t sim_matrix[5] = {{20, 5}, {10, 2}, {40, 8}, {80, 15}, {5, 5}};
    int sim_matrix_size = sizeof(sim_matrix) / sizeof(sim_matrix[0]);

    printf("Sim matrix size: %d\n", sim_matrix_size);

    for (int i = 0; i < sim_matrix_size; i++) {
        TaskHandle_t telemetry_task_handler;
        if (xTaskCreate(rx_task, "rx_task", 2048, &sim_matrix[i], 2, &telemetry_task_handler) == pdPASS) {
            // Wait for rx_task to complete
            vTaskDelay((sim_matrix[i].rx_bits * 200 + sim_matrix[i].delay * 1000 + 1000) / portTICK_PERIOD_MS);
        } else {
            printf("Failed to create rx_task %d!\n", i);
        }
    }

    // Clean up
    if (stand_by_task_handler != NULL) {
        vTaskDelete(stand_by_task_handler);
        stand_by_task_handler = NULL;
    }
    if (rx_semaphore != NULL) {
        vSemaphoreDelete(rx_semaphore);
        rx_semaphore = NULL;
    }

    gpio_reset_pin(STAND_BY_LED_PIN);
    gpio_set_level(RX_LED_PIN, 0);

    printf("Simulation complete, system cleaned\n");
    vTaskDelete(NULL);
}

void app_main(void) {
    printf("Init LED GPIOs.\n");
    gpio_reset_pin(STAND_BY_LED_PIN);
    gpio_set_direction(STAND_BY_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(RX_LED_PIN);
    gpio_set_direction(RX_LED_PIN, GPIO_MODE_OUTPUT);

    printf("Create semaphore.\n");
    rx_semaphore = xSemaphoreCreateBinary();
    if (rx_semaphore == NULL) {
        printf("Failed to create semaphore!\n");
        return;
    }
    xSemaphoreGive(rx_semaphore);

    printf("Start simulation.\n");
    if (xTaskCreate(stand_by_task, "stand_by_task", 2048, NULL, 1, &stand_by_task_handler) != pdPASS) {
        printf("Failed to create stand_by_task!\n");
        vSemaphoreDelete(rx_semaphore);
        return;
    }
    if (xTaskCreate(simulation_task, "simulation_task", 2048, NULL, 1, NULL) != pdPASS) {
        printf("Failed to create simulation_task!\n");
        vSemaphoreDelete(rx_semaphore);
        vTaskDelete(stand_by_task_handler);
        return;
    }
}