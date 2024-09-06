idf_component_register(SRCS "wifi.c" "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES freertos esp_common driver esp_timer esp_wifi nvs_flash)
