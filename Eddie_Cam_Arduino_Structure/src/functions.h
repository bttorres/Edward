#ifndef EDDIE_CAM_ARDUINO_STRUCTURE_FUNCTIONS_H_
#define EDDIE_CAM_ARDUINO_STRUCTURE_FUNCTIONS_H_

// Library that allows developer to code with Arduino structure
#include <Arduino.h>
/* Libraries that allows developer to code ESP32-Cam's
    WiFi and camera capabilities */
#include <esp_http_server.h>
#include <esp_timer.h>
#include <esp_camera.h>
#include <img_converters.h>
#include <Arduino.h>
#include <esp_camera.h>
#include <esp32-hal-ledc.h>
#include <soc/soc.h>
#include <soc/rtc_cntl_reg.h>
#include <WiFi.h>

// Allow variable to be used across multiple files/functions
extern int sendVal[5];

// Initialize functions
esp_err_t index_handler(httpd_req_t *req);
esp_err_t status_handler(httpd_req_t *req);
esp_err_t cmd_handler(httpd_req_t *req);
esp_err_t stream_handler(httpd_req_t *req);
void startCameraServer();
void cam_pin_config();

#endif // EDDIE_CAM_ARDUINO_STRUCTURE_FUNCTIONS_H_
