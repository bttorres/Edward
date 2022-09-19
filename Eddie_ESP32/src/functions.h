#ifndef EDDIE_FUNCTIONS_H_
#define EDDIE_FUNCTIONS_H_

// Include needed libraries
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <esp_timer.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <driver/timer.h>
#include <driver/uart.h>

// Allow some variables to be used across multiple files/functions
extern int distance;
extern double neck_position;
extern double right_speed;
extern double left_speed;

// Initialize functions
void gpio_init();
void uart_init();
void ultrasonic_timer_init();
void ultrasonic_timer_function();
void neck_init();
void right_init();
void left_init();
void neck_servo();
void right_servo();
void left_servo();
void set_neck(char *input);
void set_right(char *input);
void set_left(char *input);

#endif // EDDIE_FUNCTIONS_H_
