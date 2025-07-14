/**
 * @file blinking_led_button.c
 * @brief ESP32 CAM project implementing a button-triggered telemetry simulation with LEDs.
 * @author Fabrizio Borrello
 * @date July 14, 2025
 * @version 1.0
 * @ingroup telemetry_simulation
 *
 * This file contains the implementation of a FreeRTOS-based application for the ESP32 CAM,
 * simulating a telemetry system. It uses GPIO 4 for a stand-by LED, GPIO 33 for an RX LED,
 * and GPIO 13 for a button input. The system blinks LEDs based on button presses and cleans
 * up resources upon completion.
 */

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "freertos/semphr.h"
#include <driver/gpio.h>
#include <esp_log.h>

/** @defgroup telemetry_simulation Telemetry Simulation Group
 *  @brief Group for functions and data related to the telemetry simulation.
 *  @{
 */

/** @def STAND_BY_LED_PIN
 *  @brief GPIO number for the stand-by LED (active-high).
 *  @details Connected to GPIO 4 on the ESP32 CAM.
 */
#define STAND_BY_LED_PIN GPIO_NUM_4

/** @def RX_LED_PIN
 *  @brief GPIO number for the RX LED (active-low).
 *  @details Connected to GPIO 33 on the ESP32 CAM.
 */
#define RX_LED_PIN GPIO_NUM_33

/** @def BUTTON_PIN
 *  @brief GPIO number for the button input.
 *  @details Connected to GPIO 13 with a pull-down resistor.
 */
#define BUTTON_PIN GPIO_NUM_13

/** @def QUEUE_LENGTH
 *  @brief Maximum number of items in the telemetry queue.
 *  @details Set to 5 to handle multiple button press events.
 */
#define QUEUE_LENGTH 5

/** @def QUEUE_ITEM_SIZE
 *  @brief Size of each item in the telemetry queue.
 *  @details Equals the size of the sim_data_t structure.
 */
#define QUEUE_ITEM_SIZE sizeof(sim_data_t)

/** @var MAIN_TAG
 *  @brief Log tag for the main application.
 */
static const char *MAIN_TAG = "Main";

/** @var STAND_BY_TAG
 *  @brief Log tag for the stand-by task.
 */
static const char *STAND_BY_TAG = "stand-by task";

/** @var BUTTON_TAG
 *  @brief Log tag for the button task.
 */
static const char *BUTTON_TAG = "button task";

/** @var RX_TAG
 *  @brief Log tag for the RX task.
 */
static const char *RX_TAG = "rx task";

/** @var stand_by_task_handler
 *  @brief Handle for the stand-by task.
 *  @details Used to suspend/resume the task during RX operations.
 */
static TaskHandle_t stand_by_task_handler = NULL;

/** @var simulation_complete
 *  @brief Flag to indicate the simulation has completed.
 *  @details Set to true by button_task when all data is sent.
 */
static bool simulation_complete = false;

/** @var telemetry_queue
 *  @brief Handle for the FreeRTOS queue storing telemetry data.
 */
static QueueHandle_t telemetry_queue = NULL;

/** @var rx_semaphore
 *  @brief Binary semaphore for mutual exclusion between tasks.
 */
static SemaphoreHandle_t rx_semaphore = NULL;

/** @struct sim_data_t
 *  @brief Structure to hold telemetry simulation data.
 *  @var rx_bits Number of blink cycles for the RX LED.
 *  @var delay Delay in milliseconds after blinking.
 */
typedef struct {
    int rx_bits; /**< Number of blink cycles. */
    int delay;   /**< Delay in milliseconds. */
} sim_data_t;

/** @struct sim_t
 *  @brief Structure to pass simulation data to tasks.
 *  @var sim Pointer to an array of sim_data_t.
 *  @var size Number of elements in the sim array.
 */
typedef struct {
    sim_data_t* sim; /**< Pointer to simulation data array. */
    int size;        /**< Size of the simulation data array. */
} sim_t;

/** @var sim_matrix
 *  @brief Static array of simulation data.
 *  @details Contains predefined telemetry events for the simulation.
 */
static sim_data_t sim_matrix[5] = {{20, 5}, {10, 2}, {40, 8}, {80, 15}, {5, 5}};

/**
 * @brief Task to toggle the stand-by LED at 1 Hz.
 * @param pvParameters Unused task parameter.
 * @note The LED is active-high and blinks continuously until suspended.
 */
void stand_by_task(void *pvParameters) {
    gpio_reset_pin(STAND_BY_LED_PIN);
    gpio_set_direction(STAND_BY_LED_PIN, GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(STAND_BY_LED_PIN, 1); // Active-high
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(STAND_BY_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        ESP_LOGI(STAND_BY_TAG, "Stand-by LED toggle, stack: %u", uxTaskGetStackHighWaterMark(NULL));
    }
}

/**
 * @brief Task to handle button presses and send telemetry data to the queue.
 * @param pvParameters Pointer to a sim_t structure containing simulation data.
 * @note Waits for 5 button presses, sends data, and sets simulation_complete flag.
 */
void button_task(void *pvParameters) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    sim_t simulation = *((sim_t*)pvParameters);
    int sim_matrix_size = simulation.size;

    ESP_LOGW(BUTTON_TAG, "Prepare Simulation data.");
    for (int i = 0; i < sim_matrix_size; i++) {
        ESP_LOGI(BUTTON_TAG, "Check simulation data %d bits delay: %d ms", simulation.sim[i].rx_bits, simulation.sim[i].delay);
    }

    for (int i = 0; i < sim_matrix_size; i++) {
        while (1) {
            if (gpio_get_level(BUTTON_PIN) == 1 && xSemaphoreTake(rx_semaphore, portMAX_DELAY) == pdTRUE) {
                if (xQueueSend(telemetry_queue, &simulation.sim[i], 0) == pdTRUE) {
                    ESP_LOGI(BUTTON_TAG, "Button pressed, data sent to queue, stack: %u", uxTaskGetStackHighWaterMark(NULL));
                    ESP_LOGI(BUTTON_TAG, "Sending %d bits delay: %d ms", simulation.sim[i].rx_bits, simulation.sim[i].delay * 1000);
                } else {
                    ESP_LOGW(BUTTON_TAG, "Queue full, data not sent");
                }
                vTaskDelay(pdMS_TO_TICKS(500)); // Debounce
                xSemaphoreGive(rx_semaphore);
                break;
            }
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }

    simulation_complete = true;
    ESP_LOGW(BUTTON_TAG, "Simulation complete");
    vTaskDelete(NULL);
}

/**
 * @brief Task to process telemetry data and control the RX LED.
 * @param pvParameters Unused task parameter.
 * @note Suspends stand-by task, blinks RX LED at 5 Hz, resumes stand-by task, and cleans up.
 */
void rx_task(void *pvParameters) {
    sim_data_t data;
    while (!simulation_complete || uxQueueMessagesWaiting(telemetry_queue) > 0) {
        if (xQueueReceive(telemetry_queue, &data, portMAX_DELAY) == pdTRUE) {
            if (xSemaphoreTake(rx_semaphore, portMAX_DELAY) == pdTRUE) {
                if (stand_by_task_handler != NULL) {
                    vTaskSuspend(stand_by_task_handler);
                    gpio_set_level(STAND_BY_LED_PIN, 0);
                } else {
                    ESP_LOGE(RX_TAG, "stand_by_task_handler is NULL");
                    xSemaphoreGive(rx_semaphore);
                    continue;
                }

                ESP_LOGI(RX_TAG, "RX task started, stack: %u", uxTaskGetStackHighWaterMark(NULL));
                ESP_LOGI(RX_TAG, "Receiving %d bits delay: %d ms", data.rx_bits, data.delay * 1000);

                for (int i = 0; i < data.rx_bits; i++) {
                    gpio_set_level(RX_LED_PIN, 0); // Active-low ON
                    vTaskDelay(pdMS_TO_TICKS(100)); // 5 Hz ON
                    gpio_set_level(RX_LED_PIN, 1); // OFF
                    vTaskDelay(pdMS_TO_TICKS(100)); // 5 Hz OFF
                }

                gpio_set_level(RX_LED_PIN, 0);
                vTaskDelay(pdMS_TO_TICKS(data.delay * 1000)); // Delay in ms
                gpio_set_level(RX_LED_PIN, 1);

                if (stand_by_task_handler != NULL) {
                    vTaskResume(stand_by_task_handler);
                }

                xSemaphoreGive(rx_semaphore);
            }
        }
    }

    // Clean up when queue is processed
    if (stand_by_task_handler != NULL) {
        vTaskDelete(stand_by_task_handler);
        stand_by_task_handler = NULL;
    }
    if (rx_semaphore != NULL) {
        vSemaphoreDelete(rx_semaphore);
        rx_semaphore = NULL;
    }
    if (telemetry_queue != NULL) {
        vQueueDelete(telemetry_queue);
        telemetry_queue = NULL;
    }

    gpio_set_level(RX_LED_PIN, 0);
    gpio_set_level(STAND_BY_LED_PIN, 0);

    ESP_LOGW(RX_TAG, "RX task cleanup complete, system shut down\n");
    vTaskDelete(NULL);
}

/**
 * @brief Entry point for the ESP32 application.
 * @details Initializes LEDs, creates semaphore and queue, sets up tasks, and starts the simulation.
 */
void app_main(void) {
    // Initialize LEDs
    gpio_reset_pin(STAND_BY_LED_PIN);
    gpio_set_direction(STAND_BY_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_reset_pin(RX_LED_PIN);
    gpio_set_direction(RX_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(RX_LED_PIN, 1); // Active-low, OFF

    ESP_LOGI(MAIN_TAG, "Create semaphore.");
    rx_semaphore = xSemaphoreCreateBinary();
    if (rx_semaphore == NULL) {
        ESP_LOGI(MAIN_TAG, "Failed to create semaphore!\n");
        return;
    }
    xSemaphoreGive(rx_semaphore);

    // Create queue
    telemetry_queue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    if (telemetry_queue == NULL) {
        ESP_LOGE(MAIN_TAG, "Failed to create queue");
        return;
    }

    int sim_matrix_size = sizeof(sim_matrix) / sizeof(sim_matrix[0]);
    sim_t simulation = {sim_matrix, sim_matrix_size};

    ESP_LOGW(MAIN_TAG, "Prepare Simulation data.");
    for (int i = 0; i < sim_matrix_size; i++) {
        ESP_LOGI(MAIN_TAG, "Preparing simulation data %d bits delay: %d ms", simulation.sim[i].rx_bits, simulation.sim[i].delay);
    }

    // Create tasks
    if (xTaskCreate(stand_by_task, "stand_by_task", 2048, NULL, 1, &stand_by_task_handler) != pdPASS ||
        xTaskCreate(button_task, "button_task", 2048, &simulation, 2, NULL) != pdPASS ||
        xTaskCreate(rx_task, "rx_task", 2048, NULL, 3, NULL) != pdPASS) {
        ESP_LOGE(MAIN_TAG, "Failed to create tasks");
        return;
    }

    ESP_LOGI(MAIN_TAG, "Blinking LED and button setup running on ESP32 CAM");
}

/** @} */ // End of telemetry_simulation group