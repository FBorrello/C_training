#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include <rom/ets_sys.h>
#include <freertos/queue.h>

#define TRIG_PIN GPIO_NUM_16
#define ECHO_PIN GPIO_NUM_15
#define STAND_BY_LED_PIN GPIO_NUM_4
#define RX_LED_PIN 33
#define TANK_DEPTH 80.0 // Tank depth in cm (adjust based on your tank)
#define ECHO_TIMEOUT_US 50000 // Timeout for ECHO pin (50ms, adjust as needed)
static const char *TAG = "WATER_LEVEL_TASK";
QueueHandle_t telemetry_queue;
TaskHandle_t stand_by_task_handle;

void water_level_task(void *pvParameters) {
    gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
    while (1) {
        // Trigger pulse
        gpio_set_level(TRIG_PIN, 0);
        ets_delay_us(2);
        gpio_set_level(TRIG_PIN, 1);
        ets_delay_us(10);
        gpio_set_level(TRIG_PIN, 0);

        // Measure echo pulse duration with timeout
        uint64_t start_time = esp_timer_get_time();
        while (gpio_get_level(ECHO_PIN) == 0) {
            if (esp_timer_get_time() - start_time > ECHO_TIMEOUT_US) {
                ESP_LOGE(TAG, "Timeout waiting for ECHO high");
                break;
            }
            taskYIELD();
        }
        start_time = esp_timer_get_time();
        while (gpio_get_level(ECHO_PIN) == 1) {
            if (esp_timer_get_time() - start_time > ECHO_TIMEOUT_US) {
                ESP_LOGE(TAG, "Timeout waiting for ECHO low");
                break;
            }
            taskYIELD();
        }
        uint64_t end_time = esp_timer_get_time();

        // Calculate distance and water level
        float duration = (end_time - start_time); // Convert to us
        float distance = (duration /2) * 0.0343; // Distance in cm
        if (distance < 2.0 || distance > 400.0 || duration == 0) {
            ESP_LOGE(TAG, "Invalid measurement: %.2f cm", distance);
        } else {
            float level_percent = ((TANK_DEPTH - distance) / TANK_DEPTH) * 100;
            ESP_LOGI(TAG, "Distance: %.2f cm, Water Level: %.1f%%", distance, level_percent);
            xQueueSend(telemetry_queue, &level_percent, portMAX_DELAY);
            ESP_LOGI(TAG, "Sent: %.1f%%", level_percent);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void telemetry_task(void *pvParameters) {
    float level_percent;
    while (1) {
        if (xQueueReceive(telemetry_queue, &level_percent, portMAX_DELAY)) {
            vTaskSuspend(stand_by_task_handle);
            gpio_set_level(STAND_BY_LED_PIN, 0);
            gpio_set_level(RX_LED_PIN, 1);
            ESP_LOGI(TAG, "Telemetry: %.1f%%", level_percent);
            vTaskDelay(pdMS_TO_TICKS(200));
            gpio_set_level(RX_LED_PIN, 0);
            vTaskResume(stand_by_task_handle);
        }
    }
}

void stand_by_task(void *pvParameters) {
    gpio_set_direction(STAND_BY_LED_PIN, GPIO_MODE_OUTPUT);
    while (1) {
        gpio_set_level(STAND_BY_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(STAND_BY_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_main() {
    gpio_set_direction(RX_LED_PIN, GPIO_MODE_OUTPUT);
    telemetry_queue = xQueueCreate(5, sizeof(float));
    xTaskCreate(water_level_task, "water_level_task", 2048, NULL, 2, NULL);
    xTaskCreate(telemetry_task, "telemetry_task", 2048, NULL, 3, NULL);
    xTaskCreate(stand_by_task, "stand_by_task", 1024, NULL, 1, &stand_by_task_handle);
}