#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include <rom/ets_sys.h>

#define TRIG_PIN GPIO_NUM_13
#define ECHO_PIN GPIO_NUM_15
#define STAND_BY_LED_PIN GPIO_NUM_4
#define TANK_DEPTH 30.0 // Tank depth in cm (adjust based on your tank)
#define ECHO_TIMEOUT_US 50000 // Timeout for ECHO pin (50ms, adjust as needed)
static const char *TAG = "WATER_LEVEL_TASK";

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
        float duration = (end_time - start_time) / 1000.0; // Convert to ms
        float distance = (duration * 0.034) / 2; // Distance in cm
        if (distance < 2.0 || distance > 400.0 || duration == 0) {
            ESP_LOGE(TAG, "Invalid measurement: %.2f cm", distance);
        } else {
            float level_percent = ((TANK_DEPTH - distance) / TANK_DEPTH) * 100;
            ESP_LOGI(TAG, "Distance: %.2f cm, Water Level: %.1f%%", distance, level_percent);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
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
    xTaskCreate(water_level_task, "water_level_task", 4096, NULL, 5, NULL);
    xTaskCreate(stand_by_task, "stand_by_task", 2048, NULL, 1, NULL);
}